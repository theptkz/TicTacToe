#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene *SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Sprite *sprite = Sprite::create(SPLASH_SCENE_BACKGROUND_FILEPATH);
    sprite->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x, Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y));
    this->addChild(sprite);

    scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&SplashScene::SwitchToMainMenu), SPLASH_SCENE_SHOW_TIME);

    return true;
}

void SplashScene::SwitchToMainMenu(float dt)
{
    Scene *scene = MainMenuScene::createScene();
    TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

    Director::getInstance()->replaceScene(transition);
}