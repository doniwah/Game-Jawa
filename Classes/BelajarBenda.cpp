/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "BelajarBenda.h"
#include "MenuBelajar.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* BelajarBenda::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = BelajarBenda::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}

const std::string nama_object[] =
{
        "menubermain/namabenda/centong",
        "menubermain/namabenda/bola",
        "menubermain/namabenda/golok",
        "menubermain/namabenda/meja",
        "menubermain/namabenda/pensil",
        "menubermain/namabenda/pisau",
        "menubermain/namabenda/settip",
        "menubermain/namabenda/kursi",
        "menubermain/namabenda/topi",
        "menubermain/namabenda/buku"
};

const std::string nama_benda[] =
{
        "Centong",
        "Bola",
        "Parang",
        "Meja",
        "Pensil",
        "Pisau",
        "Penghapus",
        "Kursi",
        "Topi",
        "Buku"
};

const std::string nama_bendajw[] =
{
        "Irus",
        "Bal",
        "Wedung",
        "Gelondong",
        "Potelot",
        "Lading",
        "Setip",
        "Dingklik",
        "Songkok",
        "Buku"
};

const std::string benda[] =
{
        "menubermain/benda besar tengah/centong.png",
        "menubermain/benda besar tengah/Bola.png",
        "menubermain/benda besar tengah/Golok.png",
        "menubermain/benda besar tengah/Meja.png",
        "menubermain/benda besar tengah/Pensil.png",
        "menubermain/benda besar tengah/Pisau.png",
        "menubermain/benda besar tengah/Penghapus.png",
        "menubermain/benda besar tengah/Kursi.png",
        "menubermain/benda besar tengah/topi.png",
        "menubermain/benda besar tengah/Buku.png"
};

const std::string audioind[] =
{
        "audio/centong",
        "audio/bola",
        "audio/parang",
        "audio/meja",
        "audio/pensil",
        "audio/pisau",
        "audio/penghapus",
        "audio/kursi",
        "audio/topi",
        "audio/buku"
};

const std::string audiojw[] =
{
        "audio/irus",
        "audio/ball",
        "audio/wedung",
        "audio/glondong",
        "audio/potelot",
        "audio/lading",
        "audio/setip",
        "audio/dingklik",
        "audio/songkok",
        "audio/buku"
};


bool BelajarBenda::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::create("menubermain/namabenda/bg_non_panel.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);

    //backsound masuk
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/belajar nama benda.mp3");

    panel = Sprite::create("menubermain/namabenda/panel bawah.png");
    panel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 650));
    panel->runAction(EaseBackOut::create(MoveTo::create(1, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 340))));
    this->addChild(panel);

    //menampilkan panel utama
    panelutama = Sprite::create("menubermain/namabenda/panel transparan tengah.png");
    panelutama->setScale(0);
    panelutama->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
    panelutama->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
    this->addChild(panelutama);

    back = Button::create("menubermain/button_back.png");
    back->setAnchorPoint(Point(0, 1));
    back->setScale(0);
    back->setPosition(Vec2(origin.x + 20, visibleSize.height + origin.y - 20));
    back->runAction(EaseBackOut::create(ScaleTo::create(0.5, 0.7)));
    this->addChild(back);
    back->addClickEventListener([=](Ref* sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        auto scene = MenuBelajar::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });

    scroll = ScrollView::create();
    scroll->setDirection(ScrollView::Direction::HORIZONTAL);
    scroll->setContentSize(Size(panel->getContentSize().width, 230));
    scroll->setInnerContainerSize(Size(3520, 50));
    scroll->setAnchorPoint(Point(0.5, 0.5));
    scroll->setPosition(Vec2(visibleSize.width / 2 + origin.x + 155, visibleSize.height / 2 + origin.y - 260));
    scroll->setBounceEnabled(true);
    scroll->setClippingEnabled(true);
    scroll->setSwallowTouches(false);
    scroll->setScrollBarOpacity(0);

    currentLabel = nullptr;
    currentLabel2 = nullptr;
    currentSprite = nullptr;
    int get_y_posisi_button;

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    cocos2d::EventListenerTouchOneByOne* _touchListener = listener;

    listener->onTouchBegan = [this, visibleSize, origin](Touch* touch, Event* event) {
        if (currentLabel == nullptr) return false;

        Vec2 touchPos = touch->getLocation();
        Vec2 localPos = panelutama->convertToNodeSpace(touchPos);
        Rect labelRect = currentLabel->getBoundingBox();

        if (labelRect.containsPoint(localPos)) {
            DelayTime* delay = DelayTime::create(1.3);

            currentLabel->stopAllActions();
            currentLabel->runAction(Sequence::create(
                ScaleTo::create(0.5, 2),
                CallFunc::create(CC_CALLBACK_0(BelajarBenda::fungsi_audio, this, 0)),
                ScaleTo::create(0.5, 1.5),
                nullptr
            ));

            if (currentSprite) {
                currentSprite->runAction(Sequence::create(
                    delay,
                    RotateTo::create(0.5, 20),
                    RotateTo::create(0.5, 0),
                    nullptr
                ));
            }

            if (currentLabel2) {
                currentLabel2->runAction(Sequence::create(
                    delay,
                    CallFunc::create(CC_CALLBACK_0(BelajarBenda::fungsi_audio, this, 1)),
                    ScaleTo::create(0.5, 1.7),
                    ScaleTo::create(0.5, 1.5),
                    nullptr
                ));
            }

            return true;
        }
        return false;
        };

    this->addChild(scroll);

    // Add the listener to the scene level
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    for (int i = 0; i < 10; i++)
    {
        pict[i] = Button::create(__String::createWithFormat("%s.png", nama_object[i].c_str())->getCString());
        pict[i]->setAnchorPoint(Point(0.5, 0.5));
        pict[i]->setScale(0);
        pict[i]->setPosition(Vec2(+165 + ((visibleSize.width / 2 + origin.x - 485) * i),
            (visibleSize.height / 2 + origin.y - 378) - (i % 5)));
        pict[i]->runAction(CallFunc::create(CC_CALLBACK_0(BelajarBenda::animasi, this)));
        scroll->addChild(pict[i]);

        if (currentLabel != nullptr) {
            currentLabel->removeFromParentAndCleanup(true);
            currentLabel = nullptr; // Set ke nullptr setelah dihapus
        }
        
        if (currentLabel2 != nullptr) {
            currentLabel2->removeFromParentAndCleanup(true);
            currentLabel2 = nullptr; // Set ke nullptr setelah dihapus
        }
        
        if (currentSprite != nullptr) {
            currentSprite->removeFromParentAndCleanup(true);
            currentSprite = nullptr; // Set ke nullptr setelah dihapus
        }

        //gambar utama
        DelayTime* delayawalgam = DelayTime::create(3.4);
        DelayTime* delayawal = DelayTime::create(0.5);
        currentSprite = Sprite::create(benda[0]);
        currentSprite->setPosition(visibleSize.width / 2 + origin.x - 600, visibleSize.height / 2 + origin.y - 300);
        currentSprite->setScale(0);
        currentSprite->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 0.8)), nullptr));
        currentSprite->runAction(Sequence::create(
            delayawalgam,
            RotateTo::create(0.5, 20),
            RotateTo::create(0.5, 0),
            nullptr
        ));
        panelutama->addChild(currentSprite);

        // Tampilkan label baru
        DelayTime* delayawallab = DelayTime::create(2.3);
        currentLabel = Label::createWithTTF(nama_benda[0], "fonts/JandaManateeSolid.ttf", 40);
        currentLabel->setPosition(Vec2(panelutama->getContentSize().width - 190, panelutama->getContentSize().height - 150));
        currentLabel->setColor(getRandomColor());
        currentLabel->setScale(0);
        currentLabel->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 1.5)), nullptr));
        currentLabel->runAction(Sequence::create(
            delayawallab,
            CallFunc::create(CC_CALLBACK_0(BelajarBenda::backsoundlabelmasuk, this)),
            ScaleTo::create(0.5, 2),
            ScaleTo::create(0.5, 1.5),
            nullptr
        ));
        panelutama->addChild(currentLabel);

        DelayTime* delayawallab2 = DelayTime::create(3.4);
        currentLabel2 = Label::createWithTTF(nama_bendajw[0], "fonts/JandaManateeSolid.ttf", 50);
        currentLabel2->setPosition(Vec2(panelutama->getContentSize().width - 190, panelutama->getContentSize().height - 250));
        currentLabel2->setColor(getRandomColor2());
        currentLabel2->setScale(0);
        currentLabel2->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 1.3)), nullptr));
        currentLabel2->runAction(Sequence::create(
            delayawallab2,
            CallFunc::create(CC_CALLBACK_0(BelajarBenda::backsoundlabel2masuk, this)),
            ScaleTo::create(0.5, 1.7),
            ScaleTo::create(0.5, 1.5),
            nullptr
        ));
        panelutama->addChild(currentLabel2);
        
        pict[i]->addClickEventListener([=](Ref* Sender) {
            if (currentLabel != nullptr) {
                currentLabel->removeFromParentAndCleanup(true);
                currentLabel = nullptr; // Set ke nullptr setelah dihapus
            }
            
            if (currentLabel2 != nullptr) {
                currentLabel2->removeFromParentAndCleanup(true);
                currentLabel2 = nullptr; // Set ke nullptr setelah dihapus
            }

            if (currentSprite != nullptr) {
                currentSprite->removeFromParentAndCleanup(true);
                currentSprite = nullptr; // Set ke nullptr setelah dihapus
            }

            currentSprite = Sprite::create(benda[i]);
            currentSprite->setPosition(visibleSize.width / 2 + origin.x - 600, visibleSize.height / 2 + origin.y - 300);
            currentSprite->setScale(0);
            currentSprite->runAction(EaseBackOut::create(ScaleTo::create(1, 0.8)));
            panelutama->addChild(currentSprite);

            // Tampilkan label baru
            currentLabel = Label::createWithTTF(nama_benda[i], "fonts/JandaManateeSolid.ttf", 40);
            currentLabel->setPosition(Vec2(panelutama->getContentSize().width - 190, panelutama->getContentSize().height - 150));
            currentLabel->setColor(getRandomColor());
            currentLabel->runAction(EaseBackOut::create(ScaleTo::create(1, 1.5)));
            panelutama->addChild(currentLabel);

            currentLabel2 = Label::createWithTTF(nama_bendajw[i], "fonts/JandaManateeSolid.ttf", 50);
            currentLabel2->setPosition(Vec2(panelutama->getContentSize().width - 190, panelutama->getContentSize().height - 250));
            currentLabel2->setColor(getRandomColor2());
            currentLabel2->setScale(0);
            currentLabel2->runAction(EaseBackOut::create(ScaleTo::create(1, 1.3)));
            panelutama->addChild(currentLabel2);

            DelayTime* delaygambar = DelayTime::create(1.8);
            DelayTime* dela = DelayTime::create(0.5);
            currentLabel2->runAction(Sequence::create(
                delaygambar,
                CallFunc::create(CC_CALLBACK_0(BelajarBenda::fungsi_audio, this, 1)),
                ScaleTo::create(0.5, 1.7),
                ScaleTo::create(0.5, 1.5),
                nullptr
            ));

            currentLabel->runAction(Sequence::create(
                dela,
                CallFunc::create(CC_CALLBACK_0(BelajarBenda::fungsi_audio, this, 0)),
                ScaleTo::create(0.5, 2),
                ScaleTo::create(0.5, 1.5),
                nullptr
            ));
            currentSprite->runAction(Sequence::create(
                delaygambar,
                RotateTo::create(0.5, 20),
                RotateTo::create(0.5, 0),
                nullptr
            ));

            audioin = i;
            });

        if (i % 10 == 0 && i != 0)
        {
            //hitung_enter++;
            pict[i]->setPosition(Vec2(pict[i - 10]->getPositionX(),
                pict[i - 10]->getPositionY() - pict[i - 10]->getContentSize().height - 50));
            get_y_posisi_button = pict[i - 10]->getPositionY() - pict[i - 10]->getContentSize().height - 50;
        };
        if (i >= 10)
        {
            pict[i]->setPosition(Vec2(pict[i - 10]->getPositionX(),
                get_y_posisi_button));
        };
    }
    this->addChild(scroll);

    return true;
}
void BelajarBenda::animasi()
{
    DelayTime* delay1 = DelayTime::create(1);
    DelayTime* delay2 = DelayTime::create(1.3);
    DelayTime* delay3 = DelayTime::create(1.6);
    DelayTime* delay4 = DelayTime::create(1.9);
    DelayTime* delay5 = DelayTime::create(2.2);
    DelayTime* delay6 = DelayTime::create(2.5);
    DelayTime* delay7 = DelayTime::create(2.8);
    DelayTime* delay8 = DelayTime::create(3.1);
    DelayTime* delay9 = DelayTime::create(3.4);
    DelayTime* delay10 = DelayTime::create(3.7);
    pict[0]->runAction(Sequence::create(delay1, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[1]->runAction(Sequence::create(delay2, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[2]->runAction(Sequence::create(delay3, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[3]->runAction(Sequence::create(delay4, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[4]->runAction(Sequence::create(delay5, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[5]->runAction(Sequence::create(delay6, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[6]->runAction(Sequence::create(delay7, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[7]->runAction(Sequence::create(delay8, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[8]->runAction(Sequence::create(delay9, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
    pict[9]->runAction(Sequence::create(delay10, EaseBackOut::create(ScaleTo::create(0.3, 1)), nullptr));
}

Color3B BelajarBenda::getRandomColor() {
    // Array of bright, kid-friendly colors
    const Color3B colors[] = {
        Color3B(255, 0, 0),    // Red
        Color3B(0, 150, 255),  // Blue
        Color3B(0, 255, 0),    // Green
        Color3B(255, 165, 0)  // Orange
    };
    return colors[rand() % 4];  // Randomly select a color
}

Color3B BelajarBenda::getRandomColor2() {
    // Array of bright, kid-friendly colors
    const Color3B colors[] = {
        Color3B(238, 130, 238),// Violet
        Color3B(255, 255, 0),   // Kuning
        Color3B(139, 69, 19),  // Coklat Tua
        Color3B(169, 169, 169)   // abuabu
    };
    return colors[rand() % 4];  // Randomly select a color
}

void BelajarBenda::backsoundlabelmasuk() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/centong.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/centong.mp3");
}

void BelajarBenda::backsoundlabel2masuk() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/irus.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/irus.mp3");
}

void BelajarBenda::fungsi_audio(int x) {
    if (x == 0)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audioind[audioin].c_str())->getCString());

    }
    else if (x == 1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audiojw[audioin].c_str())->getCString());
    }
}