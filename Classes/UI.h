//
//  UI.hpp
//  TicTacToePractise
//
//  Created by Sonar Systems on 22/03/2016.
//
//

#pragma once

#include "cocos2d.h"

USING_NS_CC;

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
using namespace ui;
class UI
{
public:
    UI( cocos2d::Scene *layer );
    void ShowGameOver( cocos2d::Scene *layer );
    
private:
    void Retry( cocos2d::Ref *pSender );
    void touchEvent( Ref *sender, Widget::TouchEventType type);

};