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

#ifndef __bermain_cocok_H__
#define __bermain_cocok_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace tinyxml2;


class bermain_cocok : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(bermain_cocok);
private:
    //Sprite
    Sprite* background;
    Button* b_back;
    Sprite* bagus;
    Sprite* pintar;
    Sprite* berhsil;
    Sprite* salah;
    Sprite* pandai;
    Sprite* p_gambar[3];
    Sprite* p_kata[3];

    int drag;
    void jika_benar(int x);
    Sprite* object[3];
    Sprite* panel_waktu;
    Sprite* panel_bintang;
    Label* nama_object[3];
    Point point_began;
    Point point_moved;
    Point point_ended;
    int fungsi = 0;
    Rect b_1;
    Rect b_2;
    Rect b_3;
    Label* l_waktu;
    Label* l_poin;
    int poin = 0;
    Rect a_1;
    Rect a_2;
    Rect a_3;
    int waktu = 60;
    void fungsi_waktu();
    int random[3];
    void v_random();
    void game_selesai();
    void memanggil();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    bool fiks = true;
    bool fiks1 = true;
    bool fiks2 = true;


    Sprite* bg1;
    Sprite* result;
    Sprite* bintang_1;
    Sprite* bintang_2;
    Sprite* bintang_3;
    void v_bintang(int x);
    void getar();
    int untuk_aksi = 0;
};


#endif // __HELLOWORLD_SCENE_H__
