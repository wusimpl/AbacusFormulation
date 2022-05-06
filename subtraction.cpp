//
// Created by andy on 2022/5/6.
//
#include "subtraction.h"

void decpro()  ///减法口诀表
{
    for(int i=0;i<12;++i)
        line(50,400+25*i,600,400+25*i);
    line(50,400,50,675);
    line(100,400,100,675);
    line(200,400+25,200,675);
    line(300,400,300,675);
    line(450,400+25,450,675);
    line(600,400,600,675);

    char a[11][8] = {"减数", "一", "二", "三", "四" ,"五", "六", "七", "八", "九"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {50, 425+25*i, 100, 450+25*i};
        drawtext(a[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    RECT r = {100, 400, 300, 425};
    drawtext("不退位的减", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r1 = {300, 400, 600, 425};
    drawtext("退位的减", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    char b[11][12] = {"直减", "一下一", "二下二", "三下三", "四下四" ,"五下五", "六下六", "七下七", "八下八", "九下九"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {100, 425+25*i, 200, 450+25*i};
        drawtext(b[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char c[11][20] = {"满五减", "一上四去五", "二上三去五", "三上二去五", "四上一去五" };
    for(int i = 0;i<5;++i)
    {
        RECT r = {200, 425+25*i, 300, 450+25*i};
        drawtext(c[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char d[11][20] = {"退位减", "一退一还九", "二退一还八", "三退一还七", "四退一还六" ,"五退一还五", "六退一还四", "七退一还三", "八退一还二", "九退一还一"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {300, 425+25*i, 450, 450+25*i};
        drawtext(d[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char e[11][24] = {"退十补五的减", " ", " ", " ", " " ," ", "六退一还五去一", "七退二还五去一", "八退三还五去一", "九退四还五去一"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {450, 425+25*i, 600, 450+25*i};
        drawtext(e[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}
