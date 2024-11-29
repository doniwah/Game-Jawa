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

#ifndef __BelajarHewan_H__
#define __BelajarHewan_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "cocos/platform/CCDevice.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace tinyxml2;

class BelajarHewan : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BelajarHewan);
private:
    Sprite* bg;

    Sprite* panel;
    Button* pict[10];
    Sprite* panelutama;
    Label* currentLabel;
    Label* currentLabel2;
    Label* anakhewan;
    Sprite* currentSprite;
    ScrollView* scroll;
    Button* suara;
    Button* back;

    void animasi();
    void backsoundlabel2masuk();
    void backsoundlabelmasuk();
    int audioin = 0;
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void fungsi_audio(int x);

};

#endif // __HELLOWORLD_SCENE_H__
