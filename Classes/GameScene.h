#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "UI.h"
#include "AI.h"

class GameScene : public cocos2d::Scene
{
public:
    int post[3][3], sisa[2], player, move;
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
    cocos2d::Sprite *Oturn, *Xturn;
    static cocos2d::Scene* createScene();
    bool stop;
    virtual bool init();
    void initial();

    bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

    void checkGameOver(int x, int y, int player);

    void reset(int player, bool check);
    void removeAll(float dt);

    void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    AI *ai;
    UI *ui;
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
};

#endif // __GAME_SCENE_H__
