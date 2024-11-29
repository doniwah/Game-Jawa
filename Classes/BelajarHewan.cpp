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


#include "BelajarHewan.h"
#include "MenuBelajar.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* BelajarHewan::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = BelajarHewan::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}

const std::string nama_object[] =
{
        "menubermain/namahewan/bandeng",
        "menubermain/namahewan/bebek",
        "menubermain/namahewan/babi",
        "menubermain/namahewan/cacing",
        "menubermain/namahewan/kodok",
        "menubermain/namahewan/ayam",
        "menubermain/namahewan/sapi",
        "menubermain/namahewan/kambing",
        "menubermain/namahewan/kelelawar",
        "menubermain/namahewan/kadal"
};

const std::string hewan[] =
{
        "menubermain/UNTUK PANEL TENGAH/IKAN.png",
        "menubermain/UNTUK PANEL TENGAH/BEBEK.png",
        "menubermain/UNTUK PANEL TENGAH/BABI.png",
        "menubermain/UNTUK PANEL TENGAH/CACING.png",
        "menubermain/UNTUK PANEL TENGAH/KATAK.png",
        "menubermain/UNTUK PANEL TENGAH/AYAM.png",
        "menubermain/UNTUK PANEL TENGAH/SAPI.png",
        "menubermain/UNTUK PANEL TENGAH/KAMBING.png",
        "menubermain/UNTUK PANEL TENGAH/KELELAWAR.png",
        "menubermain/UNTUK PANEL TENGAH/KADAL.png"
};

const std::string nama_hewan[] =
{
        "Iwak Bandeng",
        "Bebek",
        "Celeng",
        "Udhet",
        "Kodok",
        "Pitik",
        "Lembu",
        "Wedhus",
        "Chodot",
        "Kadal"
};

const std::string nama_hewanjw[] =
{
        "Ikan Bandeng",
        "Bebek",
        "Babi",
        "Cacing",
        "Katak",
        "Ayam",
        "Sapi",
        "Kambing",
        "Kelelawar",
        "Kadal"
};

const std::string hewancilik[] =
{
        "Nener",
        "Meri",
        "Gembluk",
        "Lur",
        "Cebong",
        "Piyik",
        "Pedhet",
        "Cempe",
        "Kampet",
        "Tobil"
};

const std::string audio[] =
{
        "audio/iwak bandeng",
        "audio/bebek",
        "audio/celeng",
        "audio/udhet",
        "audio/kodok",
        "audio/pitik",
        "audio/lembu",
        "audio/whedus",
        "audio/chodot",
        "audio/kadal"
};

const std::string audioind[] =
{
        "audio/ikan bandeng",
        "audio/bebek",
        "audio/babi",
        "audio/cacing",
        "audio/katak",
        "audio/ayam",
        "audio/sapi",
        "audio/kambing",
        "audio/kelelawar",
        "audio/kadal"
};

const std::string audiohewancilik[] =
{
        "audio/nener",
        "audio/meri",
        "audio/gembluk",
        "audio/lur",
        "audio/cebong",
        "audio/piyik",
        "audio/pedhet",
        "audio/cempe",
        "audio/kampet",
        "audio/tobil"
};

bool BelajarHewan::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //menampilkan background
    bg = Sprite::create("menubermain/UNTUK PANEL TENGAH/BG-NON-PANEL.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);

    //backsound masuk
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/belajar nama hewan.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/belajar nama hewan.mp3");

    //menampilkan panel bawah
    panel = Sprite::create("menubermain/namahewan/bg_panelbawah.png");
    panel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 650));
    panel->runAction(EaseBackOut::create(MoveTo::create(1, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 340))));
    this->addChild(panel);
    
    //menampilkan panel utama
    panelutama = Sprite::create("menubermain/UNTUK PANEL TENGAH/panel putih.png");
    panelutama->setScale(0);
    panelutama->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
    panelutama->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
    this->addChild(panelutama);

    back = Button::create("menubermain/button_back.png");
    back->setAnchorPoint(Point(0 , 1));
    back->setScale(0);
    back->setPosition(Vec2(origin.x + 20, visibleSize.height + origin.y - 20));
    back->runAction(EaseBackOut::create(ScaleTo::create(0.5, 0.7)));
    this->addChild(back);
    back->addClickEventListener([=](Ref* sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
        auto scene = MenuBelajar::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));

        });

    //membuat scroll
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

    //delay tampilan awal
    DelayTime* delayawal = DelayTime::create(0.5);

    //memanggil gambar 
    currentSprite = nullptr;
    DelayTime* delayawalgam = DelayTime::create(2.8);
    currentSprite = Sprite::create(hewan[0]);
    currentSprite->setPosition(visibleSize.width / 2 + origin.x - 590, visibleSize.height / 2 + origin.y - 270);
    currentSprite->setScale(0);
    currentSprite->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 0.7)), nullptr));
    currentSprite->runAction(Sequence::create(
        delayawalgam,
        RotateTo::create(0.5, 20),
        RotateTo::create(0.5, 0),
        nullptr
    ));
    panelutama->addChild(currentSprite);

    // Tampilkan label 
    currentLabel = nullptr;
    DelayTime* delayawallab = DelayTime::create(1.5);
    int get_y_posisi_button;
    currentLabel = Label::createWithTTF(nama_hewan[0], "fonts/JandaManateeSolid.ttf", 36);
    currentLabel->setPosition(Vec2(panelutama->getContentSize().width -250, panelutama->getContentSize().height - 140));
    currentLabel->setColor(Color3B(255, 197, 197));
    currentLabel->setScale(0);
    currentLabel->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 1.5)), nullptr));
    currentLabel->runAction(Sequence::create(
        delayawallab,
        CallFunc::create(CC_CALLBACK_0(BelajarHewan::backsoundlabelmasuk, this)),
        ScaleTo::create(0.5, 2),
        ScaleTo::create(0.5, 1.5),
        nullptr
    ));
    panelutama->addChild(currentLabel);
    
    // Tampilkan label 2
    currentLabel2 = nullptr;
    DelayTime* delayawallab2 = DelayTime::create(2.8);
    currentLabel2 = Label::createWithTTF(nama_hewanjw[0], "fonts/JandaManateeSolid.ttf", 24);
    currentLabel2->setPosition(Vec2(panelutama->getContentSize().width - 850, panelutama->getContentSize().height - 350));
    currentLabel2->setColor(Color3B::WHITE);
    currentLabel2->setScale(0);
    currentLabel2->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 1.5)), nullptr));
    currentLabel2->runAction(Sequence::create(
        delayawallab2,
        CallFunc::create(CC_CALLBACK_0(BelajarHewan::backsoundlabel2masuk, this)),
        ScaleTo::create(0.5, 1.8),
        ScaleTo::create(0.5, 1.5),
        nullptr
    ));
    panelutama->addChild(currentLabel2);
    
    // Tampilkan label anak hewan
    anakhewan = nullptr;
    anakhewan = Label::createWithTTF(hewancilik[0], "fonts/JandaManateeSolid.ttf", 36);
    anakhewan->setPosition(Vec2(panelutama->getContentSize().width - 300, panelutama->getContentSize().height - 350));
    anakhewan->setColor(Color3B(234, 157, 138));
    anakhewan->setScale(0);
    anakhewan->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 1.2)), nullptr));
    panelutama->addChild(anakhewan);

    suara = Button::create("menubermain/button suara.png");
    suara->setScale(0);
    suara->setPosition(Vec2(visibleSize.width / 2 + origin.x + 160, visibleSize.height / 2 + origin.y - 445));
    suara->runAction(Sequence::create(delayawal, EaseBackOut::create(ScaleTo::create(1, 0.4)), nullptr));
    suara->addClickEventListener([=](Ref* Sender) {
        suara->runAction(CallFunc::create(CC_CALLBACK_0(BelajarHewan::fungsi_audio, this, 2)));
        });
    panelutama->addChild(suara);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        Vec2 touchPos = touch->getLocation();
        // Convert label's position to world space
        Vec2 labelWorldPos = panelutama->convertToWorldSpace(currentLabel->getPosition());
        Size labelSize = currentLabel->getContentSize();
        // Create rect in world coordinates
        Rect labelRect = Rect(
            labelWorldPos.x - (labelSize.width * currentLabel->getScale() / 2),
            labelWorldPos.y - (labelSize.height * currentLabel->getScale() / 2),
            labelSize.width * currentLabel->getScale(),
            labelSize.height * currentLabel->getScale()
        );

        DelayTime* delay = DelayTime::create(1.3);

        if (labelRect.containsPoint(touchPos)) {
            currentLabel->stopAllActions();
            currentLabel->runAction(Sequence::create(
                ScaleTo::create(0.5, 1.8),
                CallFunc::create(CC_CALLBACK_0(BelajarHewan::backsoundlabelmasuk, this)),
                ScaleTo::create(0.5, 1.5),
                nullptr
            ));
            currentSprite->runAction(Sequence::create(
                delay,
                RotateTo::create(0.5, 20),
                RotateTo::create(0.5, 0),
                nullptr
            ));

            currentLabel2->runAction(Sequence::create(
                delay,
                ScaleTo::create(0.5, 1.8),
                CallFunc::create(CC_CALLBACK_0(BelajarHewan::backsoundlabel2masuk, this)),
                ScaleTo::create(0.5, 1.5),
                nullptr
            ));
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, currentLabel);

    for (int i = 0; i < 10; i++)
    {
        //menampilkan gambar dalam scroll
        pict[i] = Button::create(__String::createWithFormat("%s.png", nama_object[i].c_str())->getCString());
        pict[i]->setAnchorPoint(Point(0.5, 0.5));
        pict[i]->setScale(0);
        pict[i]->setPosition(Vec2(+165 + ((visibleSize.width / 2 + origin.x - 485) * i),
            (visibleSize.height / 2 + origin.y - 378) - (i % 5)));
        pict[i]->runAction(CallFunc::create(CC_CALLBACK_0(BelajarHewan::animasi, this)));
        scroll->addChild(pict[i]);

    

        //reaksi ketika gambar pada panel ditekan
        pict[i]->addClickEventListener([=](Ref* Sender) {
            //mengahpus label 
            if (currentLabel != nullptr) {
                currentLabel->removeFromParentAndCleanup(true);
                currentLabel = nullptr; 
            }

            //menghapus gambar
            if (currentSprite != nullptr) {
                currentSprite->removeFromParentAndCleanup(true);
                currentSprite = nullptr;
            }

            //menghapus label 2
            if (currentLabel2 != nullptr) {
                currentLabel2->removeFromParentAndCleanup(true);
                currentLabel2 = nullptr;
            }
            
            //menghapus label anak hewan
            if (anakhewan != nullptr) {
                anakhewan->removeFromParentAndCleanup(true);
                anakhewan = nullptr;
            }

            suara->setScale(0);
            suara->runAction(EaseBackOut::create(ScaleTo::create(1, 0.4)));

            // Tampilkan label baru
            currentLabel = Label::createWithTTF(nama_hewan[i], "fonts/JandaManateeSolid.ttf", 36);
            currentLabel->setPosition(Vec2(panelutama->getContentSize().width - 250, panelutama->getContentSize().height - 140));
            currentLabel->setColor(Color3B(255, 197, 197));
            currentLabel->runAction(EaseBackOut::create(ScaleTo::create(1, 1.5)));
            panelutama->addChild(currentLabel);

            currentLabel2 = Label::createWithTTF(nama_hewanjw[i], "fonts/JandaManateeSolid.ttf", 24);
            currentLabel2->setPosition(Vec2(panelutama->getContentSize().width - 850, panelutama->getContentSize().height - 350));
            currentLabel2->setColor(Color3B::WHITE);
            currentLabel2->runAction(EaseBackOut::create(ScaleTo::create(1, 1.5)));
            panelutama->addChild(currentLabel2);

            anakhewan = Label::createWithTTF(hewancilik[i], "fonts/JandaManateeSolid.ttf", 36);
            anakhewan->setPosition(Vec2(panelutama->getContentSize().width - 300, panelutama->getContentSize().height - 350));
            anakhewan->setColor(Color3B(234, 156, 138));
            anakhewan->setScale(0);
            anakhewan->runAction(EaseBackOut::create(ScaleTo::create(1, 1.2)));
            panelutama->addChild(anakhewan);


                auto listener = EventListenerTouchOneByOne::create();
                listener->setSwallowTouches(true);
                listener->onTouchBegan = [=](Touch* touch, Event* event) {
                    Vec2 touchPos = touch->getLocation();
                    // Convert label's position to world space
                    Vec2 labelWorldPos = panelutama->convertToWorldSpace(currentLabel->getPosition());
                    Size labelSize = currentLabel->getContentSize();
                    // Create rect in world coordinates
                    Rect labelRect = Rect(
                        labelWorldPos.x - (labelSize.width * currentLabel->getScale() / 2),
                        labelWorldPos.y - (labelSize.height * currentLabel->getScale() / 2),
                        labelSize.width * currentLabel->getScale(),
                        labelSize.height * currentLabel->getScale()
                    );

                    DelayTime* delaygambar = DelayTime::create(1.3);

                    if (labelRect.containsPoint(touchPos)) {
                        currentLabel->stopAllActions();
                        currentLabel->runAction(Sequence::create(
                            CallFunc::create(CC_CALLBACK_0(BelajarHewan::fungsi_audio, this, 0)),
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
                        currentLabel2->runAction(Sequence::create(
                            delaygambar,
                            CallFunc::create(CC_CALLBACK_0(BelajarHewan::fungsi_audio, this, 1)),
                            ScaleTo::create(0.5, 1.8),
                            ScaleTo::create(0.5, 1.5),
                            nullptr
                        ));
                        return true;
                    }
                    return false;
                    };
                _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, currentLabel);

            DelayTime* delaygambar = DelayTime::create(1.8);
            DelayTime* dela = DelayTime::create(0.5);
            currentLabel2->runAction(Sequence::create(
                delaygambar,
                CallFunc::create(CC_CALLBACK_0(BelajarHewan::fungsi_audio, this, 1)),
                ScaleTo::create(0.5, 1.8),
                ScaleTo::create(0.5, 1.5),
                nullptr
            ));

            currentLabel->runAction(Sequence::create(
                dela,
                CallFunc::create(CC_CALLBACK_0(BelajarHewan::fungsi_audio, this, 0)),
                ScaleTo::create(0.5, 2),
                ScaleTo::create(0.5, 1.5),
                nullptr
            ));
            

           
            //tampilkan gambar baru
            currentSprite = Sprite::create(hewan[i]);
            currentSprite->setPosition(visibleSize.width / 2 + origin.x - 590, visibleSize.height / 2 + origin.y - 270);
            currentSprite->setScale(0.7);
            panelutama->addChild(currentSprite);

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
void BelajarHewan::animasi()
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

    //backsound label pertama
void BelajarHewan::backsoundlabelmasuk() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/iwak bandeng.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/iwak bandeng.mp3");
}

void BelajarHewan::backsoundlabel2masuk() {
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/ikan bandeng.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/ikan bandeng.mp3");
}
void BelajarHewan::fungsi_audio(int x) {
    if (x == 0)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audio[audioin].c_str())->getCString());

    }
    else if (x == 1)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audioind[audioin].c_str())->getCString());
    }
    else if (x == 2)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", audiohewancilik[audioin].c_str())->getCString());
    }
}