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


#include "BelajarKerja.h"
#include "MenuBelajar.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* BelajarKerja::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = BelajarKerja::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}

const std::string kata_kerja[] =
{
        "Makan",
        "Minum",
        "Tidur",
        "Pergi",
        "Datang",
        "Belajar",
        "Duduk",
        "Lihat",
        "Mendengar",
        "Menulis"
};

const std::string ngoko[] =
{
        "Mangan",
        "Ngombe",
        "Turu",
        "Lungo",
        "Teka",
        "Sinau",
        "Lungguh",
        "Delok",
        "Krungu",
        "Nulis"
};

const std::string krama[] =
{
        "Dahar",
        "Ngunjuk",
        "Sare",
        "Tindak",
        "Rawuh",
        "Sinau",
        "Lenggah",
        "Mriksani",
        "Midhanget",
        "Nyerat"
};

const std::string klmtjw[] =
{
        "Aku Mangan Sega",
        "Dheweke Ngombe \nBanyu",
        "Bocah Iku Turu Ing \nKamar",
        "Aku Arep Lungo Menyang\n Pasar",
        "Guru Teka Ing Kelas",
        "Aku Lagi Sinau Bahasa\n Jawa",
        "Kowe Lungguh Ing Kursi",
        "Aku Delok Pemandangan\n Ing Gunung",
        "Aku Krungu Swara \nMusik",
        "Dheweke Nulis Surat\n Kanggo Ibune"
};

const std::string klmtidn[] =
{
        "(Saya Makan Nasi)",
        "(Dia Minum Air)",
        "(Anak Itu Tidur Di Kamar)",
        "(Saya Akan Pergi Ke Pasar)",
        "(Guru Datang Di Kelas)",
        "(Saya Sedang Belajar \nBahasa Jawa)",
        "(Kamu Duduk Di Kursi)",
        "(Saya Melihat Pemandangan\n Di Gunung)",
        "(Saya Mendengar Suara\n Musik)",
        "(Dia Menulis Surat Untuk\n Ibunya)"
};

const std::string audio1[] =
{
        "audio/makan",
        "audio/minum",
        "audio/tidur",
        "audio/pergi",
        "audio/datang",
        "audio/belajar",
        "audio/duduk",
        "audio/lihat",
        "audio/mendengar",
        "audio/menulis"
};

const std::string audio2[] =
{
        "audio/mangan",
        "audio/ngombe",
        "audio/turu",
        "audio/lungo",
        "audio/teko",
        "audio/sinau",
        "audio/lungguh",
        "audio/delok",
        "audio/krungu",
        "audio/nulis"
};

const std::string audio3[] =
{
        "audio/dahar",
        "audio/ngunjuk",
        "audio/sare",
        "audio/tindak",
        "audio/rawuh",
        "audio/sinau",
        "audio/lenggah",
        "audio/mriksani",
        "audio/midhanget",
        "audio/nyerat"
};

const std::string audio4[] =
{
        "audio/aku mangan sego",
        "audio/deweke ngombe banyu",
        "audio/bocah iku turu ing kamar",
        "audio/aku arep lungo menyang pasar",
        "audio/guru teko ing kelas",
        "audio/aku lagi sinau bahasa jawa",
        "audio/koe lunggung ing kursi",
        "audio/aku delok pemandangan ing gununf",
        "audio/aku krungu suara musik",
        "audio/deweke nulis surat kanggo ibune"
};

const std::string audio5[] =
{
        "audio/sya mkan nasi",
        "audio/dia minum air",
        "audio/anak itu tidur dikamar",
        "audio/saya akan pergi kepasar",
        "audio/guru datang dikelas",
        "audio/saya sedang belajar bahasa jawa",
        "audio/kamu duduk dikursi",
        "audio/saya melihat pemandangan digunung",
        "audio/saya mendengar suara musik",
        "audio/dia menulis surat buat ibunya"
};

bool BelajarKerja::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::create("menubermain/belajar kata kerja/bg tanpa panel.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);

    panel = Sprite::create("menubermain/belajar kata kerja/panel.png");
    panel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(panel);
    panel->setScale(0);
    auto scaleUp = ScaleTo::create(1, 0.8f);
    auto elastic = EaseBackOut::create(scaleUp);
    panel->runAction(elastic);

    currentIndex = 0;

    label1 = Label::createWithTTF(kata_kerja[1], "fonts/JandaManateeSolid.ttf", 100);
    label1->setPosition(Vec2(panel->getContentSize().width - 1160, panel->getContentSize().height - 275));
    label1->setColor(Color3B::ORANGE);
    label1->setScale(0);
    panel->addChild(label1);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 touchPos = touch->getLocation();
        // Convert local label position to world space coordinates since touch is in world space
        Vec2 labelPos = label1->getParent()->convertToWorldSpace(label1->getPosition());
        Size labelSize = label1->getContentSize();
        // Create rect considering label's scale and position
        Rect labelRect = Rect(
            labelPos.x - (labelSize.width * label1->getScale() / 2),
            labelPos.y - (labelSize.height * label1->getScale() / 2),
            labelSize.width * label1->getScale(),
            labelSize.height * label1->getScale()
        );

        if (labelRect.containsPoint(touchPos)) {
            // Stop any existing actions
            CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
            label1->stopAllActions();
            label2->stopAllActions();
            label3->stopAllActions();
            kalimatjw->stopAllActions();
            kalimatind->stopAllActions();

            // Play animation and sound
            label1->runAction(Sequence::create(
                ScaleTo::create(0.5, 1.2),
                CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 1)),
                ScaleTo::create(0.5, 1.0),
                nullptr
            ));
            
            DelayTime* delay1 = DelayTime::create(1);
            label2->runAction(Sequence::create(
                delay1,
                ScaleTo::create(0.5, 1.2),
                CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 2)),
                ScaleTo::create(0.5, 1.0),
                nullptr
            ));
            
            DelayTime* delay2 = DelayTime::create(2.1);
            label3->runAction(Sequence::create(
                delay2,
                ScaleTo::create(0.5, 1.2),
                CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 3)),
                ScaleTo::create(0.5, 1.0),
                nullptr
            ));
            
            DelayTime* delay3 = DelayTime::create(3.5);
            kalimatjw->runAction(Sequence::create(
                delay3,
                ScaleTo::create(0.5, 1.2),
                CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 4)),
                ScaleTo::create(0.5, 1.0),
                nullptr
            ));
            
            DelayTime* delay4 = DelayTime::create(6.3);
            kalimatind->runAction(Sequence::create(
                delay4,
                ScaleTo::create(0.5, 1.2),
                CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 5)),
                ScaleTo::create(0.5, 1.0),
                nullptr
            ));
            return true;
        }
        return false;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, label1);

    
    label2 = Label::createWithTTF(ngoko[1], "fonts/JandaManateeSolid.ttf", 56);
    label2->setPosition(Vec2(panel->getContentSize().width - 1100, panel->getContentSize().height - 535));
    label2->setColor(Color3B::GREEN);
    label2->setScale(0);
    panel->addChild(label2);
    
    label3 = Label::createWithTTF(krama[1], "fonts/JandaManateeSolid.ttf", 56);
    label3->setPosition(Vec2(panel->getContentSize().width - 1100, panel->getContentSize().height - 695));
    label3->setScale(0);
    label3->setColor(Color3B::BLUE);
    panel->addChild(label3);
    
    kalimatjw = Label::createWithTTF(klmtjw[1], "fonts/JandaManateeSolid.ttf", 56);
    kalimatjw->setPosition(Vec2(panel->getContentSize().width - 400, panel->getContentSize().height - 440));
    kalimatjw->setColor(Color3B::BLUE);
    kalimatjw->setHorizontalAlignment(TextHAlignment::CENTER);
    kalimatjw->setScale(0);
    kalimatjw->setVerticalAlignment(TextVAlignment::CENTER);
    panel->addChild(kalimatjw);
    
    kalimatind = Label::createWithTTF(klmtidn[1], "fonts/JandaManateeSolid.ttf", 56);
    kalimatind->setPosition(Vec2(panel->getContentSize().width - 400, panel->getContentSize().height - 650));
    kalimatind->setColor(Color3B::RED);
    kalimatind->setHorizontalAlignment(TextHAlignment::CENTER);
    kalimatind->setVerticalAlignment(TextVAlignment::CENTER);
    kalimatind->setScale(0);
    panel->addChild(kalimatind);
        
    previous = Button::create("menubermain/belajar kata kerja/previous.png");
    previous->setAnchorPoint(Point(0, 0));
    previous->setScale(0);
    previous->setPosition(Vec2(origin.x + 180, visibleSize.height / 2 + origin.y - 100));
    previous->runAction(EaseBackOut::create(ScaleTo::create(1, 0.7)));
    this->addChild(previous);
    previous->addClickEventListener([this](Ref* sender) {
        label1->stopAllActions();
        label2->stopAllActions();
        label3->stopAllActions();
        kalimatjw->stopAllActions();
        kalimatind->stopAllActions();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        updateLabels(false);
        });

    next = Button::create("menubermain/belajar kata kerja/previous.png");
    next->setAnchorPoint(Point(1, 0));
    next->setScale(0);
    next->setRotation(180.0f);
    next->setPosition(Vec2(origin.x + 1340, visibleSize.height / 2 + origin.y - 10));
    next->runAction(EaseBackOut::create(ScaleTo::create(1, 0.7)));
    this->addChild(next);
    next->addClickEventListener([this](Ref* sender) {
        label1->stopAllActions();
        label2->stopAllActions();
        label3->stopAllActions();
        kalimatjw->stopAllActions();
        kalimatind->stopAllActions();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        updateLabels(true);
        });

    b_kembali = Button::create("menubermain/button_back.png");
    b_kembali->setAnchorPoint(Point(0, 1));
    b_kembali->setScale(0);
    b_kembali->setPosition(Vec2(origin.x + 20, visibleSize.height + origin.y - 20));
    DelayTime* delay = DelayTime::create(0.3);
    b_kembali->runAction(Sequence::create(delay, EaseBackOut::create(ScaleTo::create(0.5, 0.7)), nullptr));
    this->addChild(b_kembali);
    b_kembali->setZoomScale(0.1);
    b_kembali->addClickEventListener([=](Ref* Sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        auto scene = MenuBelajar::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });

    DelayTime* delayawal = DelayTime::create(3.1);
    this->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(BelajarKerja::playInitialBacksound, this)),
        delayawal,
        CallFunc::create(CC_CALLBACK_0(BelajarKerja::updateLabels, this, true)), nullptr));
    return true;
}

void BelajarKerja::updateLabels(bool isNext)
{
    // Update the index, wrapping around if necessary
    if (isNext)
    {
        currentIndex = (currentIndex + 1) % 10;
    }
    else
    {
        currentIndex = (currentIndex - 1 + 10) % 10;
    }

    // Update the labels with new content
    DelayTime* prtext12 = DelayTime::create(1);
        label1->setString(kata_kerja[currentIndex]);
        label1->setScale(0);
        label1->runAction(Sequence::create(
            ScaleTo::create(0.5, 1.2),
            CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 1)),
            ScaleTo::create(0.5, 1),
            nullptr
        ));

        label2->setString(ngoko[currentIndex]);
        label2->setScale(0);
        label2->runAction(Sequence::create(
            prtext12,
            ScaleTo::create(0.5, 1.2),
            CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 2)),
            ScaleTo::create(0.5, 1),
            nullptr
        ));

        DelayTime* prtext23 = DelayTime::create(2.1);
        label3->setString(krama[currentIndex]);
        label3->setScale(0);
        label3->runAction(Sequence::create(
            prtext23 ,
            ScaleTo::create(0.5, 1.2),
            CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 3)),
            ScaleTo::create(0.5, 1),
            nullptr
        ));

        DelayTime* prtext34 = DelayTime::create(3.5);
        kalimatjw->setString(klmtjw[currentIndex]);
        kalimatjw->setScale(0);
        kalimatjw->runAction(Sequence::create(
            prtext34,
            ScaleTo::create(0.5, 1.2),
            CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 4)),
            ScaleTo::create(0.5, 1),
            nullptr
        ));

        DelayTime* prtext45 = DelayTime::create(6.3);
        kalimatind->setString(klmtidn[currentIndex]);
        kalimatind->setScale(0);
        kalimatind->runAction(Sequence::create(
            prtext45,
            ScaleTo::create(0.5, 1.2),
            CallFunc::create(CC_CALLBACK_0(BelajarKerja::backsound, this, 5)),
            ScaleTo::create(0.5, 1),
            nullptr
        ));
       
        
}

void BelajarKerja::backsound(int x)
{
    if (x == 1) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audio1[currentIndex].c_str())->getCString());
    }
    else if (x == 2) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audio2[currentIndex].c_str())->getCString());
    }
    else if (x == 3) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audio3[currentIndex].c_str())->getCString());
    }
    else if (x == 4) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audio4[currentIndex].c_str())->getCString());
    }
    else if (x == 5) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audio5[currentIndex].c_str())->getCString());
    }
}

void BelajarKerja::playInitialBacksound()
{
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/belajarkatakerja.mp3");
    
}
