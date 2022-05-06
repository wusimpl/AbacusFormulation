//
// Created by andy on 2022/5/6.
//

#include "base.h"

Num ab_augend[PLACES_NUM], ab_addend[PLACES_NUM]; //数的算盘形式
char augend[PLACES_NUM], addend[PLACES_NUM]; //数的形式
const char* INDEX_TO_CHINESE_NUM[] = {"零","一","二","三","四","五","六","七","八","九","十"}; // 中文数字字符常量
string processHintPlaceHolder; //演算过程提示占位符

//绘制算珠（椭圆形状）
void drawOneBead(float x, float y)
{
    fillellipse(x - 20, y - 12.5, x + 20, y + 12.5); //left:椭圆外切矩形的左上角 x 坐标
}

void drawStr(const char* str){
    RECT r1 = { 900, 250, 1000, 275 };
    drawtext(str, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//绘制算盘
void drawAbacus(Num *sa) {
    int k;
    line(50, 100, 850, 100); //上框
    line(50, 200, 850, 200); //中框（梁）
    line(50, 375, 850, 375); //下框
    fillellipse(725 - 5, 200 - 5, 725 + 5, 200 + 5); //小数点

    for (int i = 0; i < 17; ++i) //左框+右框+档
    {
        line(50 + i * 50, 100, 50 + i * 50, 375);
    }

    for (int i = 0, j = 14; i < PLACES_NUM; ++i, --j) //绘制梁上算珠
    {
        for (k = 0; k < sa[j].high; ++k) //未入珠
            drawOneBead(100 + 50 * i, 187.5 - 25 * k);
        for (k = 0; k < 1 - sa[j].high; ++k) //入珠
            drawOneBead(100 + 50 * i, 112.5 + 25 * k);
    }

    for (int i = 0, j = 14; i < PLACES_NUM; ++i, --j) //绘制梁下算珠
    {
        for (int k = 0; k < sa[j].low; ++k) //入珠
            drawOneBead(100 + 50 * i, 212.5 + 25 * k);
        for (int k = 0; k < 4 - sa[j].low; ++k) //未入珠
            drawOneBead(100 + 50 * i, 362.5 - 25 * k);
    }
}

//判断是否为小数,如果为小数，则去掉小数点
void isDecimal(char *x)
{
    if((string(x)).find('.') == string::npos){ //整数
        strcat(x,"00");
    }else{ //小数
        itoa(atof(x)*100,x,10);
    }
}

//阿拉伯数字转换为算盘式数字
void toAbacusForm(Num *s, char *t, int len)
{
    for (int i = len - 1, k = 0; i >= 0; i--, k++)
    {
        int x = t[i] - '0';
        s[k].high = x / 5;
        s[k].low = x % 5;
    }
}

//算盘某档转为阿拉伯数字
int toNumberForm(Num *s){
    return s->high*5 + s->low;
}
