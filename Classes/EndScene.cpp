//
//  EndScene.cpp
//  TicTacToePractise
//
//  Created by Sonar Systems on 22/03/2016.
//
//

#include "EndScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "GameAIScene.h"
#include "GameAIScene.h"
#include "MainMenuScene.h"

EndScene::EndScene( cocos2d::Scene *layer )
{
}

void EndScene::ShowGameOver( cocos2d::Scene *layer )
{
    Size screenSize = Director::getInstance( )->getVisibleSize( );

    Sprite *background = Sprite::create( GAME_OVER_BACKGROUND );
    background->setOpacity( 0 );
    layer->addChild( background );
    background->runAction( Sequence::create( DelayTime::create( 1 ), FadeIn::create( GAME_OVER_BACKGROUND_FADE_IN_TIME ), NULL ) );
    
    MenuItemImage *overlayWindowItem = MenuItemImage::create( GAME_OVER_WINDOW, GAME_OVER_WINDOW, GAME_OVER_WINDOW, NULL );
    Button *retryItem = Button::create( MAIN_MENU_PLAY_BUTTON, MAIN_MENU_PLAY_BUTTON_PRESSED);
    retryItem->setScaleX(0.3);
    retryItem->setScaleY(0.2);
    retryItem->setPosition( Vec2( overlayWindowItem->getContentSize( ).width / 10-100, retryItem->getPositionY( )-100 ) );
    retryItem->addTouchEventListener(CC_CALLBACK_2(EndScene::touchEvent, this));
    retryItem->setTag(TAG_REPLAY_BUTTON);
    
    Button *retryAIItem = Button::create( MAIN_MENU_PLAY_AI_BUTTON, MAIN_MENU_PLAY_AI_BUTTON_PRESSED);    
    retryAIItem->setScaleX(0.3);
    retryAIItem->setScaleY(0.2);
    retryAIItem->setPosition( Vec2( overlayWindowItem->getContentSize( ).width / 10+50, retryAIItem->getPositionY( )-100 ) );
    retryAIItem->addTouchEventListener(CC_CALLBACK_2(EndScene::touchEvent, this));
    retryAIItem->setTag(TAG_REPLAY_AI_BUTTON);

    Menu *menu = Menu::create( overlayWindowItem, retryItem,retryAIItem, NULL );
    layer->addChild( menu );
    

}

void EndScene::touchEvent(Ref *sender, Widget::TouchEventType type)
{
    Node *node = (Node *)sender;

    switch (type)
    {
    case Widget::TouchEventType::BEGAN:
        // code to handle when the button is first clicked
        break;

    case Widget::TouchEventType::MOVED:
        // code to handle when the user is moving their finger/cursor whilst clicking the button
        break;

    case Widget::TouchEventType::ENDED:
        // code to handle when the button click has ended (e.g. finger is lifted off the screen)
        if (TAG_REPLAY_BUTTON == node->getTag())
        {
            Scene *scene = GameScene::createScene();
            TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

            Director::getInstance()->replaceScene(transition);
        }
        // else if (TAG_ACHIEVEMENTS_BUTTON == node->getTag())
        // {
        //     SonarCocosHelper::GameCenter::showAchievements();
        //     SonarCocosHelper::GooglePlayServices::showAchievements();
        // }
        if (TAG_REPLAY_AI_BUTTON == node->getTag())
        {
            Scene *scene = GameAIScene::createScene();
            TransitionFade *transition = TransitionFade::create(SCENE_TRANSITION_TIME, scene);

            Director::getInstance()->replaceScene(transition);
        }
        // else if (TAG_ACHIEVEMENTS_BUTTON == node->getTag())
        // {
        //     SonarCocosHelper::GameCenter::showAchievements();
        //     SonarCocosHelper::GooglePlayServices::showAchievements();
        // }
        break;

    case Widget::TouchEventType::CANCELED:
        // code to handle when the button click has been cancelled,  this is usually handled the same way as ENDED in most applications (e.g. another application takes control of the device)
        break;

    default:
        break;
    }
}
