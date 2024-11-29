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


#include "HomePlay.h"
#include "MenuBelajar.h"
#include "bermain_cocok.h"
#include "MenuBermain.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* HomePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = HomePlay::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}

const std::string nama_object[] =
{
        "Satu",
        "Dua",
        "Tiga",
        "Empat",
        "Lima",
        "Enam",
        "Tujuh",
        "Delapan",
        "Sembilan",
        "Sepuluh",
};
//void HomePlay::ganti_hewan()
//{
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    log("sayur ke %i", object_ke);
//
//    if (object_ke < 0)
//    {
//        object_ke = 9;
//    }
//
//    if (object_ke >= 10)
//    {
//        object_ke = 0;
//    };
//
//
//    object->setTexture(__String::createWithFormat("%s.png", nama_object[object_ke].c_str())->getCString());

  /*  if (tombol_auto_aktif == true)
    {
        object_ke++;
    }*/
//}
// on "init" you need to initialize your instance

    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();   

    bg = Sprite::create("homeplay/bg_homeplay.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);
    


    judul = Sprite::create("homeplay/teks.png");
    judul->setScale(0.45);
    judul->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 750));
    this->addChild(judul);
    judul->runAction(RepeatForever::create(Sequence::create(MoveTo::create(3, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100)),
        MoveTo::create(3, Vec2(visibleSize.width / 2 + origin.x - 35, visibleSize.height / 2 + origin.y + 50)),
        MoveTo::create(3, Vec2(visibleSize.width / 2 + origin.x + 35, visibleSize.height / 2 + origin.y + 50)), nullptr)));

    //animasi memunculkan object
    /*object = Sprite::create("homeplay/button_play.png");
    object->setScale(0);
    object->runAction(EaseBackOut::create(ScaleTo::create(1, 0.9)));
    object->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(object);*/

    //button
    /*b_next = Button::create("homeplay/back.jpg");
    b_next->setAnchorPoint(Point(0.5, 0.5));
    b_next->setPosition(Vec2(visibleSize.width / 2 + origin.x + 600, visibleSize.height / 2 + origin.y - 30));
    this->addChild(b_next);
    b_next->setZoomScale(0.1);
    b_next->addClickEventListener([=](Ref* Sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
        object_ke++;
        ganti_hewan();
        });*/
        
    b_belajar = Button::create("homeplay/button_belajar.png");
    b_belajar->setAnchorPoint(Point(0.5, 0.5));
    b_belajar->setScale(0);
    b_belajar->setPosition(Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height / 2 + origin.y - 200));
    b_belajar->runAction(EaseBackOut::create(ScaleTo::create(1.5, 0.7)));
    this->addChild(b_belajar);
    b_belajar->setZoomScale(0.1);
    b_belajar->addClickEventListener([=](Ref* Sender) {
        auto scene = MenuBelajar::createScene();
        //b_belajar->runAction(EaseBackOut::create(ScaleTo::create(1, 0)));
        //b_bermain->runAction(EaseBackOut::create(ScaleTo::create(1, 0)));
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
    });
    
    b_bermain = Button::create("homeplay/button_bermain.png");
    b_bermain->setAnchorPoint(Point(0.5, 0.5));
    b_bermain->setScale(0);
    b_bermain->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y - 200));
    b_bermain->runAction(EaseBackOut::create(ScaleTo::create(1.5, 0.7)));
    this->addChild(b_bermain);
    b_bermain->setZoomScale(0.1);
    b_bermain->addClickEventListener([=](Ref* Sender) {
        auto scene = MenuBermain::createScene();
        //b_belajar->runAction(EaseBackOut::create(ScaleTo::create(1, 0)));
        //b_bermain->runAction(EaseBackOut::create(ScaleTo::create(1, 0)));
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });
    
    btn_cancel = Button::create("homeplay/button_x.png");
    btn_cancel->setAnchorPoint(Point(1, 1));
    btn_cancel->setScale(0);
    btn_cancel->setPosition(Vec2(visibleSize.width + origin.x - 20, visibleSize.height + origin.y - 20));
    btn_cancel->runAction(EaseBackOut::create(ScaleTo::create(1.5, 0.8)));
    this->addChild(btn_cancel);
    btn_cancel->setZoomScale(0.1);
    btn_cancel->addClickEventListener([=](Ref* Sender) {
        Director::sharedDirector()->end();
        });
    

    /*
    b_left = Button::create("stage/b_next.png");
    b_left->setRotation(180);
    b_left->setAnchorPoint(Point(0.5, 0.5));
    b_left->setPosition(Vec2(visibleSize.width / 2 + origin.x - 600, visibleSize.height / 2 + origin.y - 30));
    this->addChild(b_left);
    b_left->setZoomScale(-0.1);
    b_left->addClickEventListener([=](Ref* Sender) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
        object_ke--;
        ganti_hewan();
        });*/

    //b_auto = Button::create("belajar/huruf_indonesia/b_auto_off.png");
    //b_auto->setAnchorPoint(Point(1, 1));
    //b_auto->setPosition(Vec2(visibleSize.width + origin.x - 20, visibleSize.height + origin.y - 35));
    //this->addChild(b_auto);
    //b_auto->setZoomScale(-0.1);
    //b_auto->addClickEventListener([=](Ref* Sender) {
        //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
        //if (tombol_auto_aktif == false) {
            //tombol_auto_aktif = true;
            //b_auto->loadTextureNormal("belajar/huruf_indonesia/b_auto_on.png");
            //this->runAction(RepeatForever::create(Sequence::create(
                //CallFunc::create(CC_CALLBACK_0(mengenal_buah_indonesia::ganti_hewan, this)), DelayTime::create(1.5), nullptr)));
       // }
        //else if (tombol_auto_aktif == true)
    //{
        //tombol_auto_aktif = false;
        //b_auto->loadTextureNormal("belajar/huruf_indonesia/b_auto_off.png");
        //this->stopAllActions();
    //}
    //});



       /* b_back = Button::create("stage/menu_pilihan/b_back.png");
        b_back->setAnchorPoint(Point(0, 1));
        b_back->setPosition(Vec2(origin.x + 20, visibleSize.height + origin.y - 20));
        this->addChild(b_back);
        b_back->setZoomScale(-0.1);
        b_back->addClickEventListener([=](Ref* Sender) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
            auto gr_scene = coba::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, gr_scene, Color3B::WHITE));
            });

        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/angka/inggris/one.mp3");*/

        return true;
    //}
}
//void HomePlay::menuCloseCallback(Ref* pSender)
//{
//    auto gr_scene = coba::createScene();
//    Director::getInstance()->replaceScene(TransitionFade::create(0.5, gr_scene, Color3B::WHITE));
//};

