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

#include "bermain_cocok.h"
#include "SimpleAudioEngine.h"
#include "ActionShake.h"
#include "MenuBermain.h"
#include "HomePlay.h"
#include "cocos/platform/CCDevice.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;

Scene* bermain_cocok::createScene()
{
    auto scene = Scene::create();

    auto layer = bermain_cocok::create();

    scene->addChild(layer);

    return scene;


}const std::string name_hewan[] =
{
        "hewan/ayam",
        "hewan/sapi",
        "hewan/bayu",
        "hewan/babi",
        "hewan/bebek",
        "hewan/cacing",
        "hewan/KELELAWAR",
        "hewan/katak",
        "hewan/ikan",
        "hewan/kadal"
};
const std::string nama[] =
{
        "Pitik",
        "Lembu",
        "Wedhus",
        "Celeng",
        "Bebek",
        "Udhet",
        "Codhot",
        "Kodhok",
        "Iwak Bandeng",
        "Kadal"
};

const std::string sound_effect[] =
{
        "sound/pitik",
        "sound/lembu",
        "sound/whedus",
        "sound/celeng",
        "sound/bebek",
        "sound/udhet",
        "sound/chodot",
        "sound/kodok",
        "sound/iwak bandeng",
        "sound/kadal"
};

void bermain_cocok::v_random()
{
    for (int i = 0; i < 3; ++i) {

        random[i] = RandomHelper::random_int(0, 9);

        if (random[0] == random[1])
        {
            random[1] = RandomHelper::random_int(0, 9);
            log("ada nilai yang sama");
            v_random();
        };
        if (random[1] == random[2])
        {
            random[2] = RandomHelper::random_int(0, 9);
            log("nilai kedua ada yang sama");
            v_random();
        };
        if (random[0] == random[2])
        {
            random[2] = RandomHelper::random_int(0, 9);
            log("ada nilai ketiga yang sama");
            v_random();
        }
    }
}
bool bermain_cocok::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    point_began = touch->getLocation();

        b_1 = p_kata[0]->getBoundingBox();
        b_2 = p_kata[1]->getBoundingBox();
        b_3 = p_kata[2]->getBoundingBox();

        if (b_1.containsPoint(point_began))
        {
            drag = 0;
            log("1 buah di touch began");
        }
        else if (b_2.containsPoint(point_began))
        {
            drag = 1;
            log("2 buah di touch began");
        }
        else if (b_3.containsPoint(point_began))
        {
            drag = 2;
            log("3 buah di touch began");
        }

    return true;
}

void bermain_cocok::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    point_moved = touch->getLocation();
    if (drag == 0 && fiks == true) {
        p_kata[0]->setPosition(point_moved);
    }
    else if (drag == 1 && fiks1 == true) {
        p_kata[1]->setPosition(point_moved);
    }
    else if (drag == 2 && fiks2 == true) {
        p_kata[2]->setPosition(point_moved);
    };
}


void bermain_cocok::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    a_1 = p_gambar[0]->getBoundingBox();
    a_2 = p_gambar[1]->getBoundingBox();
    a_3 = p_gambar[2]->getBoundingBox();


    b_1 = p_kata[0]->getBoundingBox();
    b_2 = p_kata[1]->getBoundingBox();
    b_3 = p_kata[2]->getBoundingBox();
        if (drag == 0 && fiks == true) {
            if (b_1.intersectsRect(a_3))
            {
                fiks = false;
                fungsi++;
                p_kata[0]->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 50)));
            }
            else
            {
                p_kata[0]->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2 + origin.x - 350, visibleSize.height / 2 + origin.y + 200)));
            };
        }
        else if (drag == 1 && fiks1 == true)
        {
            if (b_2.intersectsRect(a_1))
            {
                fiks1 = false;
                fungsi++;
                p_kata[1]->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2 + origin.x - 350, visibleSize.height / 2 + origin.y + 50)));
            }
            else
            {
                p_kata[1]->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 200)));
            };
        }
        else if(drag == 2 && fiks2 == true){
            if (b_3.intersectsRect(a_2))
            {
                fiks2 = false;
                fungsi++;
                p_kata[2]->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50)));
            }
            else
            {
                p_kata[0]->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 200)));
            };
        }

        if (fungsi == 3)
        {
            fiks = true;
            fiks1 = true;
            fiks2 = true;
            fungsi = 0;
            p_kata[0]->runAction(EaseBackIn::create(ScaleTo::create(1, 0)));
            p_kata[1]->runAction(EaseBackIn::create(ScaleTo::create(1, 0)));
            p_kata[2]->runAction(EaseBackIn::create(ScaleTo::create(1, 0)));
            p_gambar[0]->runAction(EaseBackIn::create(ScaleTo::create(1, 0)));
            p_gambar[1]->runAction(EaseBackIn::create(ScaleTo::create(1, 0)));
            p_gambar[2]->runAction(EaseBackIn::create(ScaleTo::create(1, 0)));
            poin = poin + 10;
            l_poin->setString(__String::createWithFormat("%i", poin)->getCString());
            jika_benar(untuk_aksi);
            this->runAction(Sequence::create(DelayTime::create(1.5),
            CallFunc::create(CC_CALLBACK_0(bermain_cocok::memanggil, this)), nullptr));
        }

}
void bermain_cocok::fungsi_waktu()
{
    for (int i = 0; i < 1; i++)
    {
        if (waktu == 0)
        {
            break;
        }
        waktu--;
        l_waktu->setString(__String::createWithFormat("%i", waktu)->getCString());

        if (waktu == 0)
        {
            /*fungsi_menang();*/
            game_selesai();
        }
    }
}
bool bermain_cocok::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background = Sprite::create("bermain/cocok/bg.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    panel_bintang = Sprite::create("stage/Pannel_bintang.png");
    panel_bintang->setAnchorPoint(Point(0.5, 1));
    panel_bintang->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200,  visibleSize.height + origin.y - 20));
    this->addChild(panel_bintang);

    panel_waktu = Sprite::create("stage/Pannel_waktu.png");
    panel_waktu->setAnchorPoint(Point(0.5, 1));
    panel_waktu->setPosition(Vec2(visibleSize.width / 2 + origin.x - 200, visibleSize.height + origin.y - 20));
    this->addChild(panel_waktu);

    l_waktu = Label::createWithTTF("60", "fonts/Freude.otf", 30);
    l_waktu->setString(__String::createWithFormat("%i", waktu)->getCString());
    l_waktu->setPosition(Vec2(panel_bintang->getContentSize().width / 2 + 40, panel_bintang->getContentSize().height / 2));
    l_waktu->setTextColor(Color4B::BLACK);
    panel_bintang->addChild(l_waktu);

    l_poin = Label::createWithTTF("60", "fonts/Freude.otf", 30);
    l_poin->setString(__String::createWithFormat("%i", poin)->getCString());
    l_poin->setPosition(Vec2(panel_waktu->getContentSize().width / 2 + 40, panel_waktu->getContentSize().height / 2));
    l_poin->setTextColor(Color4B::BLACK);
    panel_waktu->addChild(l_poin);


    b_back = Button::create("stage/b_back.png");
    b_back->setAnchorPoint(Point(0, 1));
    b_back->setScale(0.6);
    b_back->setPosition(Vec2(origin.x - 400, visibleSize.height + origin.y + 400));
    b_back->runAction(MoveTo::create(2, Vec2(origin.x + 15, visibleSize.height + origin.y - 15)));
    b_back->setZoomScale(-0.1);
    this->addChild(b_back);
    b_back->addClickEventListener([=](Ref* Sender) {
        auto scene = MenuBermain::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(bermain_cocok::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(bermain_cocok::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(bermain_cocok::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    memanggil();

    this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1),
        CallFunc::create(CC_CALLBACK_0(bermain_cocok::fungsi_waktu, this)), nullptr)));

    return true;
}
void bermain_cocok::memanggil()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < 3; ++i) {

        random[i] = RandomHelper::random_int(0, 9);

        if (random[0] == random[1])
        {
            random[1] = RandomHelper::random_int(0, 9);
            log("ada nilai yang sama");
            v_random();
        };
        if (random[1] == random[2])
        {
            random[2] = RandomHelper::random_int(0, 9);
            log("nilai kedua ada yang sama");
            v_random();
        };
        if (random[0] == random[2])
        {
            random[2] = RandomHelper::random_int(0, 9);
            log("ada nilai ketiga yang sama");
            v_random();
        }
    }

    for (int i = 0; i < 3; i++)
    {

        //Menampilkan

        p_gambar[i] = Sprite::create("bermain/cocok/panel_gambar.png");
        p_gambar[i]->setAnchorPoint(Point(0.5, 0.5));
        p_gambar[i]->setScale(0);
        p_gambar[i]->runAction(EaseBackOut::create(ScaleTo::create(1, 0.6)));

        //Menampilkan
        this->addChild(p_gambar[i]);

        object[i] = Sprite::create(__String::createWithFormat("%s.png", name_hewan[random[i]].c_str())->getCString());
        object[i]->setAnchorPoint(Point(0.5, 0.5));
        object[i]->setScale(0.7);
        object[i]->runAction(EaseBackOut::create(ScaleTo::create(1, 0.7)));
        object[i]->setPosition(Vec2(p_gambar[i]->getContentSize() / 2));
        p_gambar[i]->addChild(object[i]);

        p_kata[i] = Sprite::create("bermain/cocok/panel_nama.png");
        p_kata[i]->setAnchorPoint(Point(0.5, 0.5));
        p_kata[i]->setScale(0);
        p_kata[i]->runAction(EaseBackOut::create(ScaleTo::create(1, 0.6)));
        this->addChild(p_kata[i], 22);
        nama_object[i] = Label::createWithTTF("A", "fonts/Freude.otf", 65);
        //nama_object[i]->setString(__String::create(nama[random[i]].c_str())->getCString());
        nama_object[i]->setPosition(Vec2(p_kata[i]->getContentSize() / 2));
        nama_object[i]->setTextColor(Color4B::BLACK);
        p_kata[i]->addChild(nama_object[i]);
    }
    nama_object[1]->setString(__String::create(nama[random[0]].c_str())->getCString());
    nama_object[2]->setString(__String::create(nama[random[1]].c_str())->getCString());
    nama_object[0]->setString(__String::create(nama[random[2]].c_str())->getCString());

    //Menentukan posisi
    p_gambar[0]->setPosition(Vec2(visibleSize.width / 2 + origin.x - 350, visibleSize.height / 2 + origin.y - 150));
    p_gambar[1]->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 150));
    p_gambar[2]->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y - 150));

    p_kata[0]->setPosition(Vec2(visibleSize.width / 2 + origin.x - 350, visibleSize.height / 2 + origin.y + 200));
    p_kata[1]->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 200));
    p_kata[2]->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 200));

};
void bermain_cocok::game_selesai()
{

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bg1 = Sprite::create("bermain/cocok/bg.png");
    bg1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg1, 99);

    result = Sprite::create("stage/score.png");
    result->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    result->setScale(0.8);
    this->addChild(result, 99);

    auto nilai = Label::createWithTTF("", "fonts/Freude.otf", 60);
    nilai->setString(__String::createWithFormat("%i", poin)->getCString());
    nilai->setPosition(Vec2(result->getContentSize().width / 2 + 100, result->getContentSize().height / 2 - 160));
    nilai->setTextColor(Color4B::BLACK);
    result->addChild(nilai);

    bintang_1 = Sprite::create("stage/bintang.png");
    bintang_1->setPosition(Vec2(result->getContentSize().width / 2 - 130, result->getContentSize().height / 2 + 40));
    bintang_1->setScale(0);
    result->addChild(bintang_1);

    bintang_2 = Sprite::create("stage/bintang.png");
    bintang_2->setPosition(Vec2(result->getContentSize().width / 2 - 5, result->getContentSize().height / 2 + 95));
    bintang_2->setRotation(15);
    bintang_2->setScale(0);
    result->addChild(bintang_2);

    bintang_3 = Sprite::create("stage/bintang.png");
    bintang_3->setPosition(Vec2(result->getContentSize().width / 2 + 125, result->getContentSize().height / 2 + 40));
    bintang_3->setRotation(30);
    bintang_3->setScale(0);
    result->addChild(bintang_3);
    
    if (poin == 0) {

    }
    else if (poin > 1 && poin <= 40)
    {
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(bermain_cocok::v_bintang, this, 0)), nullptr));

    }
    else if (poin > 41 && poin <= 80)
    {
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(bermain_cocok::v_bintang, this, 0)), nullptr));
        this->runAction(Sequence::create(DelayTime::create(2.8), CallFunc::create(CC_CALLBACK_0(bermain_cocok::v_bintang, this, 1)), nullptr));

    }
    else if (poin > 81)
    {
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(bermain_cocok::v_bintang, this, 0)), nullptr));
        this->runAction(Sequence::create(DelayTime::create(2.8), CallFunc::create(CC_CALLBACK_0(bermain_cocok::v_bintang, this, 1)), nullptr));
        this->runAction(Sequence::create(DelayTime::create(4.8), CallFunc::create(CC_CALLBACK_0(bermain_cocok::v_bintang, this, 2)), nullptr));
    }




    auto b_restart = Button::create("stage/restart.png");
    b_restart->setAnchorPoint(Point(0.5, 0.5));
    b_restart->setPosition(Vec2(result->getContentSize().width / 2 + 130, result->getContentSize().height / 2 - 300));
    b_restart->setZoomScale(-0.1);
    result->addChild(b_restart);
    b_restart->addClickEventListener([=](Ref* Sedner) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
        auto gr_scene = bermain_cocok::createScene();
        Director::getInstance()->replaceScene(TransitionProgressHorizontal::create(0.5, gr_scene));
        });

    auto b_home = Button::create("stage/home.png");
    b_home->setAnchorPoint(Point(0.5, 0.5));
    b_home->setPosition(Vec2(result->getContentSize().width / 2 - 130, result->getContentSize().height / 2 - 300));
    b_home->setZoomScale(-0.1);
    result->addChild(b_home);
    b_home->addClickEventListener([=](Ref* Sedner) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
        auto gr_scene = HomePlay::createScene();
        Director::getInstance()->replaceScene(TransitionFlipY::create(0.5, gr_scene));
        });
}

void bermain_cocok::v_bintang(int x) {

    if (x == 0) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        bintang_1->setScale(0);
        bintang_1->runAction(EaseElasticOut::create(ScaleTo::create(0.7, 1)));

        cocos2d::ParticleSystemQuad* m_emitter;
        m_emitter = ParticleSystemQuad::create("stage/bintang_particle.plist");
        m_emitter->setVisible(true);
        this->addChild(m_emitter, 50);
        m_emitter->setScale(0.5);
        m_emitter->setPosition(ccp(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y + 30));
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ceting.mp3");

        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(bermain_cocok::getar, this)), nullptr));


    }

    if (x == 1) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        bintang_2->setScale(0);
        bintang_2->runAction(EaseElasticOut::create(ScaleTo::create(0.7, 1)));
        cocos2d::ParticleSystemQuad* m_emitter;
        m_emitter = ParticleSystemQuad::create("stage/bintang_particle.plist");
        m_emitter->setVisible(true);
        this->addChild(m_emitter, 50);
        m_emitter->setScale(0.5);
        m_emitter->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 60));
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ceting.mp3");

        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(bermain_cocok::getar, this)), nullptr));


    }

    if (x == 2) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        bintang_3->setScale(0);
        bintang_3->runAction(EaseElasticOut::create(ScaleTo::create(0.7, 1)));

        cocos2d::ParticleSystemQuad* m_emitter;
        m_emitter = ParticleSystemQuad::create("stage/bintang_particle.plist");
        m_emitter->setVisible(true);
        this->addChild(m_emitter, 50);
        m_emitter->setScale(0.5);
        m_emitter->setPosition(ccp(visibleSize.width / 2 + origin.x + 100, visibleSize.height / 2 + origin.y + 30));
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ceting.mp3");

        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(bermain_cocok::getar, this)), nullptr));


    }
}

void bermain_cocok::getar() {

    float interval = 1 / 60;
    float duration = 0.5f;
    float speed = 5.0f;
    float magnitude = 3.f;
    cocos2d::Device::vibrate(0.50f);
    this->runAction(ActionShake::create(duration, speed, magnitude));

    result->runAction(Sequence::create(MoveBy::create(0.1, Vec2(10, 0)), MoveBy::create(0.1, Vec2(0, -10)),
        MoveBy::create(0.1, Vec2(0, 10)), MoveBy::create(0.1, Vec2(-10, 0)), nullptr));
    bg1->runAction(Sequence::create(MoveBy::create(0.1, Vec2(10, 0)), MoveBy::create(0.1, Vec2(0, -10)),
        MoveBy::create(0.1, Vec2(0, 10)), MoveBy::create(0.1, Vec2(-10, 0)), nullptr));
}
void bermain_cocok::jika_benar(int x)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (x == 0)
    {
        
            bagus = Sprite::create("ekspresi/bagus.png");
            bagus->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            bagus->setScale(0);
            bagus->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.8, 0.35)),
                EaseBackIn::create(ScaleTo::create(0.8, 0)), nullptr));
            this->addChild(bagus, 100);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/intrumen/bagus.mp3");
            untuk_aksi++;
         
    }
    else if (x == 1)
    {
        
            pintar = Sprite::create("ekspresi/pintar.png");
            pintar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            pintar->setScale(0);
            pintar->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.8, 0.35)),
                EaseBackIn::create(ScaleTo::create(0.8, 0)), nullptr));
            this->addChild(pintar, 100);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/intrumen/pintar.mp3");
            untuk_aksi++;

    }
    else if (x == 2)
    {
 
            pandai = Sprite::create("ekspresi/Pandai.png");
            pandai->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            pandai->setScale(0);
            pandai->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.8, 0.35)),
                EaseBackIn::create(ScaleTo::create(0.8, 0)), nullptr));
            this->addChild(pandai, 100);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/intrumen/pndai.mp3");
            untuk_aksi++;

    }
    else if (x == 3)
    {
            
            berhsil = Sprite::create("ekspresi/berhasil.png");
            berhsil->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            berhsil->setScale(0);
            berhsil->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.8, 0.35)),
                EaseBackIn::create(ScaleTo::create(0.8, 0)), nullptr));
            this->addChild(berhsil, 100);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/intrumen/berhasil.mp3");
            untuk_aksi = 0;


    }
    else  if (x == 4)
    {
            salah = Sprite::create("ekspresi/yahh.png");
            salah->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            salah->setScale(0);
            salah->runAction(Sequence::create(EaseBackOut::create(ScaleTo::create(0.8, 0.35)),
                EaseBackIn::create(ScaleTo::create(0.8, 0)), nullptr));
            this->addChild(salah, 100);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/intrumen/yaaah.mp3");    
    };
}