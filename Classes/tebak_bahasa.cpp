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


#include "tebak_bahasa.h"
#include "HomePlay.h"
#include "ActionShake.h"
#include "MenuBermain.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d::network;
using namespace ui;


Scene* tebak_bahasa::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = tebak_bahasa::create();
    // add layer as a child to scene
    scene->addChild(layer);

    return  scene;
}
const std::string b_jawa[] =
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
const std::string b_indo[] =
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

const std::string rekaman_indo[] =
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

const std::string rekaman_jawa[] =
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



void tebak_bahasa::fungsi_waktu()
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
            this->stopAllActions();
            game_selesai();
        }
    }
}
bool tebak_bahasa::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();   

    bg = Sprite::create("bermain/tebak_bahasa/bg.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(bg);

    panel_soal = Sprite::create("bermain/tebak_bahasa/panel soal.png");
    panel_soal->setScale(0.7);
    panel_soal->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
    this->addChild(panel_soal);

    l_pertanyaan = Label::createWithTTF("Apa bahasa jawa dari ", "fonts/Freude.otf", 70);
    l_pertanyaan->setPosition(Vec2(panel_soal->getContentSize().width / 2, panel_soal->getContentSize().height / 2));
    l_pertanyaan->setTextColor(Color4B::BLACK);
    panel_soal->addChild(l_pertanyaan);

    panel_bintang = Sprite::create("stage/Pannel_bintang.png");
    panel_bintang->setAnchorPoint(Point(0.5, 1));
    panel_bintang->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height + origin.y - 20));
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


    for (int i = 0; i < 3; i++)
    {
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

        i_jawaban = RandomHelper::random_int(0, 2);
            
        b_jawaban[i] = Button::create("bermain/tebak_bahasa/button jawaban baru.png");
        b_jawaban[i]->setAnchorPoint(Point(0.5, 0.5));
        b_jawaban[i]->setZoomScale(-0.1);
        b_jawaban[i]->setScale(0);
        b_jawaban[i]->runAction(EaseBackOut::create(ScaleTo::create(0.5, 0.8)));
        this->addChild(b_jawaban[i]);

        s_salah[i] = Sprite::create("bermain/tebak_bahasa/icon salah x.png");
        s_salah[i]->setAnchorPoint(Point(0.5, 0.5));
        s_salah[i]->setScale(0);
        s_salah[i]->setPosition(Vec2(b_jawaban[i]->getContentSize().width / 2, b_jawaban[i]->getContentSize().height /2 + 100));
        b_jawaban[i]->addChild(s_salah[i]);

        s_benar[i] = Sprite::create("bermain/tebak_bahasa/icon benar.png");
        s_benar[i]->setAnchorPoint(Point(0.5, 0.5));
        s_benar[i]->setScale(0);
        s_benar[i]->setPosition(Vec2(b_jawaban[i]->getContentSize().width / 2, b_jawaban[i]->getContentSize().height / 2 + 100));
        b_jawaban[i]->addChild(s_benar[i]);

        l_jawaban[i] = Label::createWithTTF("60", "fonts/Freude.otf", 60);
        l_jawaban[i]->setString(__String::create(b_jawa[random[i]].c_str())->getCString());
        l_jawaban[i]->setPosition(Vec2(b_jawaban[i]->getContentSize() / 2));
        l_jawaban[i]->setTextColor(Color4B::BLACK);
        b_jawaban[i]->addChild(l_jawaban[i]);

        b_jawaban[i]->addClickEventListener([=](Ref* Sender) {
            if (i == i_jawaban) {
                l_jawaban[i]->setTextColor(Color4B::GREEN);
                b_jawaban[0]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[1]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[2]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                panel_soal->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::perulangan, this)), nullptr));
                s_benar[i_jawaban]->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
                poin = poin + 10;
                l_poin->setString(__String::createWithFormat("%i", poin)->getCString());
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", rekaman_jawa[random[i_jawaban]].c_str())->getCString());
            }
            else {
                l_jawaban[i]->setTextColor(Color4B::RED);
                l_jawaban[i_jawaban]->setTextColor(Color4B::GREEN);
                b_jawaban[0]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[1]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[2]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                panel_soal->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::perulangan, this)), nullptr));
                s_salah[i]->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
            }
            
            });
    }
    l_soal = Label::createWithTTF("60", "fonts/Freude.otf", 70);
    l_soal->setString(__String::create(b_indo[random[i_jawaban]].c_str())->getCString());
    l_soal->setPosition(Vec2(l_pertanyaan->getContentSize().width / 2 + 440, l_pertanyaan->getContentSize().height / 2));
    l_soal->setTextColor(Color4B::BLACK);
    l_pertanyaan->addChild(l_soal);

    b_jawaban[0]->setPosition(Vec2(visibleSize.width / 2 + origin.x - 400, visibleSize.height / 2 + origin.y - 250));
    b_jawaban[1]->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));
    b_jawaban[2]->setPosition(Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y - 250));
    
    this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::fungsi_waktu, this)), nullptr)));
    
    b_back = Button::create("stage/b_back.png");
    b_back->setAnchorPoint(Point(0, 1));
    b_back->setScale(0.7);
    b_back->setPosition(Vec2(origin.x + 20, visibleSize.height + origin.y - 20));
    this->addChild(b_back);
    b_back->setZoomScale(-0.1);
    b_back->addClickEventListener([=](Ref* Sender) {
        auto scene = MenuBermain::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B::WHITE));
        });
    

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/apa bahasa jawa dari.mp3");
    this->runAction(Sequence::create(DelayTime::create(2.3), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::untuk_audio, this)), nullptr));

    return true;
   
}
void tebak_bahasa::v_random()
{
    for (int i = 0; i < 3; i++)
    {
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
void tebak_bahasa::perulangan()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/apa bahasa jawa dari.mp3");
    this->runAction(Sequence::create(DelayTime::create(2.3), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::untuk_audio, this)), nullptr));

    panel_soal = Sprite::create("bermain/tebak_bahasa/panel soal.png");
    panel_soal->setScale(0.7);
    panel_soal->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
    this->addChild(panel_soal);

    l_pertanyaan = Label::createWithTTF("Apa bahasa jawa dari ", "fonts/Freude.otf", 70);
    l_pertanyaan->setPosition(Vec2(panel_soal->getContentSize().width / 2, panel_soal->getContentSize().height / 2));
    l_pertanyaan->setTextColor(Color4B::BLACK);
    panel_soal->addChild(l_pertanyaan);

    for (int i = 0; i < 3; i++)
    {
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

        i_jawaban = RandomHelper::random_int(0, 2);

        b_jawaban[i] = Button::create("bermain/tebak_bahasa/button jawaban baru.png");
        b_jawaban[i]->setAnchorPoint(Point(0.5, 0.5));
        b_jawaban[i]->setZoomScale(-0.1);
        b_jawaban[i]->setScale(0);
        b_jawaban[i]->runAction(EaseBackOut::create(ScaleTo::create(0.5, 0.8)));
        this->addChild(b_jawaban[i]);

        s_salah[i] = Sprite::create("bermain/tebak_bahasa/icon salah x.png");
        s_salah[i]->setAnchorPoint(Point(0.5, 0.5));
        s_salah[i]->setScale(0);
        s_salah[i]->setPosition(Vec2(b_jawaban[i]->getContentSize().width / 2, b_jawaban[i]->getContentSize().height / 2 + 100));
        b_jawaban[i]->addChild(s_salah[i]);

        s_benar[i] = Sprite::create("bermain/tebak_bahasa/icon benar.png");
        s_benar[i]->setAnchorPoint(Point(0.5, 0.5));
        s_benar[i]->setScale(0);
        s_benar[i]->setPosition(Vec2(b_jawaban[i]->getContentSize().width / 2, b_jawaban[i]->getContentSize().height / 2 + 100));
        b_jawaban[i]->addChild(s_benar[i]);

        l_jawaban[i] = Label::createWithTTF("60", "fonts/Freude.otf", 60);
        l_jawaban[i]->setString(__String::create(b_jawa[random[i]].c_str())->getCString());
        l_jawaban[i]->setPosition(Vec2(b_jawaban[i]->getContentSize() / 2));
        l_jawaban[i]->setTextColor(Color4B::BLACK);
        b_jawaban[i]->addChild(l_jawaban[i]);

        b_jawaban[i]->addClickEventListener([=](Ref* Sender) {
            if (i == i_jawaban) {
                l_jawaban[i]->setTextColor(Color4B::GREEN);
                b_jawaban[0]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[1]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[2]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                panel_soal->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::perulangan, this)), nullptr));
                s_benar[i_jawaban]->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
                poin = poin + 10;
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", rekaman_jawa[random[i_jawaban]].c_str())->getCString());
                l_poin->setString(__String::createWithFormat("%i", poin)->getCString());
            }
            else {
                l_jawaban[i]->setTextColor(Color4B::RED);
                l_jawaban[i_jawaban]->setTextColor(Color4B::GREEN);
                b_jawaban[0]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[1]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                b_jawaban[2]->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                panel_soal->runAction(Sequence::create(DelayTime::create(1), (EaseBackIn::create(ScaleTo::create(0.5, 0))), nullptr));
                this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::perulangan, this)), nullptr));
                s_salah[i]->runAction(EaseBackOut::create(ScaleTo::create(0.5, 1)));
                if (poin > 0) {
                    poin = poin - 10;
                    l_poin->setString(__String::createWithFormat("%i", poin)->getCString());
                }

            }

            });
    }
    l_soal = Label::createWithTTF("60", "fonts/Freude.otf", 70);
    l_soal->setString(__String::create(b_indo[random[i_jawaban]].c_str())->getCString());
    l_soal->setPosition(Vec2(l_pertanyaan->getContentSize().width / 2 + 440, l_pertanyaan->getContentSize().height / 2));
    l_soal->setTextColor(Color4B::BLACK);
    l_pertanyaan->addChild(l_soal);

    b_jawaban[0]->setPosition(Vec2(visibleSize.width / 2 + origin.x - 400, visibleSize.height / 2 + origin.y - 250));
    b_jawaban[1]->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));
    b_jawaban[2]->setPosition(Vec2(visibleSize.width / 2 + origin.x + 400, visibleSize.height / 2 + origin.y - 250));

}
//void HomePlay::menuCloseCallback(Ref* pSender)
//{
//    auto gr_scene = coba::createScene();
//    Director::getInstance()->replaceScene(TransitionFade::create(0.5, gr_scene, Color3B::WHITE));
//};

void tebak_bahasa::game_selesai()
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
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::v_bintang, this, 0)), nullptr));

    }
    else if (poin > 41 && poin <= 80)
    {
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::v_bintang, this, 0)), nullptr));
        this->runAction(Sequence::create(DelayTime::create(2.8), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::v_bintang, this, 1)), nullptr));

    }
    else if (poin > 81)
    {
        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::v_bintang, this, 0)), nullptr));
        this->runAction(Sequence::create(DelayTime::create(2.8), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::v_bintang, this, 1)), nullptr));
        this->runAction(Sequence::create(DelayTime::create(4.8), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::v_bintang, this, 2)), nullptr));
    }

    auto b_restart = Button::create("stage/restart.png");
    b_restart->setAnchorPoint(Point(0.5, 0.5));
    b_restart->setPosition(Vec2(result->getContentSize().width / 2 + 130, result->getContentSize().height / 2 - 300));
    b_restart->setZoomScale(-0.1);
    result->addChild(b_restart);
    b_restart->addClickEventListener([=](Ref* Sedner) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/touch.mp3");
        auto gr_scene = tebak_bahasa::createScene();
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

void tebak_bahasa::v_bintang(int x) {

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

        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::getar, this)), nullptr));


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

        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::getar, this)), nullptr));


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

        this->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(tebak_bahasa::getar, this)), nullptr));


    }
}

void tebak_bahasa::getar() {

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
void tebak_bahasa::untuk_audio()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(__String::createWithFormat("%s.mp3", rekaman_indo[random[i_jawaban]].c_str())->getCString());
    
}