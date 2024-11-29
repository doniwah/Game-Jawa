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


#include "MenuBelajar.h"
#include "HomePlay.h"
#include "BelajarHewan.h"
#include "BelajarBenda.h"
#include "BelajarHanacaraka.h"
#include "BelajarKerja.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* MenuBelajar::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = MenuBelajar::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}

bool MenuBelajar::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg = Sprite::create("menubermain/bg menu belajar baru.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);
    
    panel = Sprite::create("menubermain/Panel putih menu belajar (1).png");
    panel->setScale(0.8);
    panel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ));
    this->addChild(panel);

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/menu belajar(pilih salah satu menu belajar).mp3");

    b_namabenda = Button::create("menubermain/nama_benda.png");
    b_namabenda->setAnchorPoint(Point(0.5, 0.5));
    b_namabenda->setScale(0);
    b_namabenda->setPosition(Vec2(visibleSize.width / 2 + origin.x - 560, visibleSize.height / 2 + origin.y - 180));
    DelayTime* delay1 = DelayTime::create(0.8);
    b_namabenda->runAction(Sequence::create(delay1, EaseBackOut::create(ScaleTo::create(0.3, 1.2)), nullptr));
    panel->addChild(b_namabenda);
    b_namabenda->setZoomScale(0.1);
    b_namabenda->addClickEventListener([=](Ref* Sender) {
        auto scene = BelajarBenda::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });

    b_aksarajawa = Button::create("menubermain/aksara_jawa.png");
    b_aksarajawa->setAnchorPoint(Point(0.5, 0.5));
    b_aksarajawa->setScale(0);
    b_aksarajawa->setPosition(Vec2(visibleSize.width / 2 + origin.x - 140, visibleSize.height / 2 + origin.y - 180));
    DelayTime* delay2 = DelayTime::create(1.1);
    b_aksarajawa->runAction(Sequence::create(delay2, EaseBackOut::create(ScaleTo::create(0.3, 1.2)), nullptr));
    panel->addChild(b_aksarajawa);
    b_aksarajawa->setZoomScale(0.1);
    b_aksarajawa->addClickEventListener([=](Ref* Sender) {
        auto scene = BelajarHanacaraka::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });

    b_katakerja = Button::create("menubermain/kata_kerja.png");
    b_katakerja->setAnchorPoint(Point(0.5, 0.5));
    b_katakerja->setScale(0);
    b_katakerja->setPosition(Vec2(visibleSize.width / 2 + origin.x + 280 , visibleSize.height / 2 + origin.y - 180));
    DelayTime* delay3 = DelayTime::create(1.4);
    b_katakerja->runAction(Sequence::create(delay3, EaseBackOut::create(ScaleTo::create(0.3, 1.2)), nullptr));
    panel->addChild(b_katakerja);
    b_katakerja->setZoomScale(0.1);
    b_katakerja->addClickEventListener([=](Ref* Sender) {
        auto scene = BelajarKerja::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });
    
    b_namahewan = Button::create("menubermain/nama_hewan.png");
    b_namahewan->setAnchorPoint(Point(0.5, 0.5));
    b_namahewan->setScale(0);
    b_namahewan->setPosition(Vec2(visibleSize.width / 2 + origin.x + 700, visibleSize.height / 2 + origin.y - 180));
    DelayTime* delay4 = DelayTime::create(1.7);
    b_namahewan->runAction(Sequence::create(delay4, EaseBackOut::create(ScaleTo::create(0.3, 1.2)), nullptr));
    panel->addChild(b_namahewan);
    b_namahewan->setZoomScale(0.1);
    b_namahewan->addClickEventListener([=](Ref* Sender) {
        auto scene = BelajarHewan::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
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
        auto scene = HomePlay::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
    });
    return true;
}
