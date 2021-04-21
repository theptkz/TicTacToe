#include "GameAIScene.h"

USING_NS_CC;

Scene *GameAIScene::createScene()
{
    return  GameAIScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameAISceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameAIScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    //TODO: Initialitation Data
    initial();

    //TODO: Touch Listener
    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = CC_CALLBACK_2(GameAIScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameAIScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameAIScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameAIScene::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // android back press event
    auto touchListener2 = EventListenerKeyboard::create();
    touchListener2->onKeyReleased = CC_CALLBACK_2(GameAIScene::keyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener2, this);

    ai = new AI();
    endscene = new EndScene( this);
    return true;
}

bool GameAIScene::onTouchBegan(Touch *touch, Event *event)
{
    LuaLog("Sentuh");

    // if (player%2 != 0)
    // {
    //     int aimove = ai->PlacePiece(post, move);
    //     int aimoveX = aimove/3;
    //     int aimoveY = aimove%3;
    //     if (sisa[1] > 0 && post[aimoveX][aimoveY] == 99 && !stop)
    //     {
    //         post[aimoveX][aimoveY] = 1;
    //         Vec2 areaX = Vec2(origin.x + visibleSize.width / 2 - 100 + aimoveX * 100 - 50,
    //                             origin.y + visibleSize.height / 2 - 100 + aimoveY * 100 - 50);
    //         auto sprite = Sprite::create();
    //         sprite = Sprite::create("res/X.png");
    //         sprite->setPosition(areaX.x + 50, areaX.y + 50);
    //         this->addChild(sprite);
    //         sisa[1]--;
    //         move++;
    //         player++;
    //         Xturn->setOpacity(0);
    //         Oturn->setOpacity(255);
    //         checkGameOver(aimoveX, aimoveY, 1);
    //     }
    // }
    //else{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Vec2 areaX = Vec2(origin.x + visibleSize.width / 2 - 100 + i * 100 - 50,
                            origin.y + visibleSize.height / 2 - 100 + j * 100 - 50);
            Vec2 areaX2 = Vec2(origin.x + visibleSize.width / 2 - 100 + i * 100 + 50,
                            origin.y + visibleSize.height / 2 - 100 + j * 100 - 50);
            Vec2 areaX3 = Vec2(origin.x + visibleSize.width / 2 - 100 + i * 100 - 50,
                            origin.y + visibleSize.height / 2 - 100 + j * 100 + 50);
            Vec2 areaX4 = Vec2(origin.x + visibleSize.width / 2 - 100 + i * 100 + 50,
                            origin.y + visibleSize.height / 2 - 100 + j * 100 + 50);
            
            if (touch->getLocation().x < areaX4.x && touch->getLocation().x > areaX.x &&
                touch->getLocation().y < areaX4.y && touch->getLocation().y > areaX.y)
            {
                if (sisa[0] > 0 && post[i][j] == 99 && !stop)
                {
                    post[i][j] = 0;
                    auto sprite = Sprite::create();
                    sprite = Sprite::create("res/O.png");
                    sprite->setPosition(areaX.x + 50, areaX.y + 50);
                    this->addChild(sprite);
                    sisa[0]--;
                    move++;
                    if (Oturn->getOpacity() > 0)
                    {
                        Xturn->setOpacity(255);
                        Oturn->setOpacity(0);
                    }
                    else
                    {
                        Xturn->setOpacity(0);
                        Oturn->setOpacity(255);
                    }
                    checkGameOver(i, j, 0);
                }
            }
        }
    }
    delayAiMove();
    //}
    return true;
}

void GameAIScene::aiMove(float dt)
{
    int aimove = ai->PlacePiece(post, move);
    int aimoveX = aimove/3;
    int aimoveY = aimove%3;
    if (sisa[1] > 0 && post[aimoveX][aimoveY] == 99 && !stop)
    {
        post[aimoveX][aimoveY] = 1;
        Vec2 areaX = Vec2(origin.x + visibleSize.width / 2 - 100 + aimoveX * 100 - 50,
                            origin.y + visibleSize.height / 2 - 100 + aimoveY * 100 - 50);
        auto sprite = Sprite::create();
        sprite = Sprite::create("res/X.png");
        sprite->setPosition(areaX.x + 50, areaX.y + 50);
        this->addChild(sprite);
        sisa[1]--;
        move++;
        Xturn->setOpacity(0);
        Oturn->setOpacity(255);
        checkGameOver(aimoveX, aimoveY, 1);
    }
}

void GameAIScene::delayAiMove()
{
    float delay = 0.2f;
    this->scheduleOnce(static_cast<cocos2d::SEL_SCHEDULE>(&GameAIScene::aiMove), delay);
}

void GameAIScene::onTouchEnded(Touch *touch, Event *event)
{
    cocos2d::log("touch ended");
}

void GameAIScene::onTouchMoved(Touch *touch, Event *event)
{
    cocos2d::log("touch moved");
}

void GameAIScene::onTouchCancelled(Touch *touch, Event *event)
{
    cocos2d::log("touch cancelled");
}

void GameAIScene::initial()
{
    //TODO: Make a Solid Color Background
    auto bg = LayerColor::create(Color4B(0, 188, 212, 255));
    this->addChild(bg);

    //TODO: Draw a Line
    auto draw = DrawNode::create();
    draw->drawLine(
        Vec2(origin.x + visibleSize.width / 2 - 150, origin.y + visibleSize.height / 2 - 50),
        Vec2(origin.x + visibleSize.width / 2 + 150, origin.y + visibleSize.height / 2 - 50),
        Color4F::WHITE);

    addChild(draw);
    draw->drawLine(
        Vec2(origin.x + visibleSize.width / 2 - 150, origin.y + visibleSize.height / 2 + 50),
        Vec2(origin.x + visibleSize.width / 2 + 150, origin.y + visibleSize.height / 2 + 50),
        Color4F::WHITE);

    addChild(draw);
    draw->drawLine(
        Vec2(origin.x + visibleSize.width / 2 - 50, origin.y + visibleSize.height / 2 - 150),
        Vec2(origin.x + visibleSize.width / 2 - 50, origin.y + visibleSize.height / 2 + 150),
        Color4F::WHITE);

    addChild(draw);
    draw->drawLine(
        Vec2(origin.x + visibleSize.width / 2 + 50, origin.y + visibleSize.height / 2 - 150),
        Vec2(origin.x + visibleSize.width / 2 + 50, origin.y + visibleSize.height / 2 + 150),
        Color4F::WHITE);

    addChild(draw);

    //Sign O | X
    Oturn = Sprite::create("res/O.png");
    Xturn = Sprite::create("res/X.png");
    Oturn->setScale(0.5);
    Xturn->setScale(0.5);
    Oturn->setPosition(
        Vec2(origin.x + visibleSize.width * 3 / 4 + 100, origin.y + visibleSize.height / 2));
    Xturn->setPosition(
        Vec2(origin.x + visibleSize.width * 1 / 4 - 100, origin.y + visibleSize.height / 2));
    this->addChild(Oturn);
    this->addChild(Xturn);

    //Because O first
    Xturn->setOpacity(0);

    stop = false;
    sisa[0] = 5;
    sisa[1] = 4;
    move = 0;
    player = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            post[i][j] = 99;
        }
    }
}

void GameAIScene::checkGameOver(int x, int y, int player)
{
    bool gameOver = true;
    float delay = 2.0f;
    auto delayAction = DelayTime::create(delay);
    auto funcCallback = CallFunc::create([player, gameOver, this]() {
        reset(player, gameOver);
    });

    for (int i = 0; i < 3; i++)
    {
        if (post[i][y] != player)
        {
            gameOver = false;
            break;
        }
    }

    if (gameOver)
    {
        Xturn->setOpacity(0);
        Oturn->setOpacity(0);
        stop = true;
        this->runAction(Sequence::create(delayAction, funcCallback, NULL));
        return;
    }

    gameOver = true;
    for (int i = 0; i < 3; i++)
    {
        if (post[x][i] != player)
        {
            gameOver = false;
            break;
        }
    }

    if (gameOver)
    {
        Xturn->setOpacity(0);
        Oturn->setOpacity(0);
        stop = true;
        this->runAction(Sequence::create(delayAction, funcCallback, NULL));
        return;
    }

    if (x == y)
    {
        gameOver = true;
        for (int i = 0; i < 3; i++)
        {
            if (post[i][i] != player)
            {
                gameOver = false;
                break;
            }
        }
    }

    if (gameOver)
    {
        Xturn->setOpacity(0);
        Oturn->setOpacity(0);
        stop = true;
        this->runAction(Sequence::create(delayAction, funcCallback, NULL));
        return;
    }

    if (x == y - 2 || y == x - 2 || (x == 1 && y == 1))
    {
        LuaLog("masukkkk");
        gameOver = true;
        for (int i = 0; i < 3; i++)
        {
            if (post[i][2 - i] != player)
            {
                gameOver = false;
                break;
            }
        }
    }

    if (move == 9 || gameOver)
    {
        stop = true;
        Xturn->setOpacity(0);
        Oturn->setOpacity(0);
        auto funcCallback = CallFunc::create([player, gameOver, this]() {
            reset(player, gameOver);
        });
        this->runAction(Sequence::create(delayAction, funcCallback, NULL));
    }
    return;
}

void GameAIScene::reset(int player, bool check)
{
    //TODO: Make a new Layer
    auto bg = LayerColor::create(Color4B(0, 188, 212, 255));
    this->addChild(bg);

    auto label = Label::create();
    if (!check)
    {
        label = Label::createWithTTF("DRAW!", "fonts/Roboto.ttf", 50);
    }
    else
    {
        if (player == 0)
        {
            label = Label::createWithTTF("O WIN!", "fonts/Roboto.ttf", 50);
        }
        else
        {
            label = Label::createWithTTF("X WIN!", "fonts/Roboto.ttf", 50);
        }
    }
    label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    endscene->ShowGameOver(this);
    this->addChild(label);

}

void GameAIScene::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    Director::getInstance()->end();
}
