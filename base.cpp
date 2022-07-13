//
// Created by andy on 2022/5/6.
//

#include "base.h"

Num a_first_operand[PLACES_NUM], a_second_operand[PLACES_NUM]; //数的算盘形式
char c_first_operand[PLACES_NUM+1], c_second_operand[PLACES_NUM+1]; //数的字符形式
char original_c_first_operand[PLACES_NUM+1], original_c_second_operand[PLACES_NUM+1];//接收到的输入数字
const char* INDEX_TO_CHINESE_NUM[] = {"零","一","二","三","四","五","六","七","八","九","十"}; // 中文数字字符常量
//string processHintPlaceHolder; //演算过程提示占位符
char strInfo[100];
stringstream stringGenerator;

//绘制算珠（椭圆形状）
void drawOneBead(float x, float y)
{
    fillellipse(x - 20, y - 12.5, x + 20, y + 12.5); //left:椭圆外切矩形的左上角 x 坐标
}

void drawStr(const char* str){
    RECT r1 = { 900, 250, 1100, 275 };
    drawtext(str, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//拨珠规则显示
void drawStrOfSize32(const char* str){
    setFontSizeTo32();
    RECT r1 = { 900, 250, 1100, 280 };
    drawtext(str, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    setFontSizeTo16();
}

//表达式计算显示
void drawStrOfDisplayCalculationResult(const char* str){
    setFontSizeTo32();
    RECT r1 = { 900, 100, 1100, 125 };
    drawtext(str, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    setFontSizeTo16();
}

void setFontSizeTo16(){
    setFontSize(16);
}

void setFontSizeTo32(){
    setFontSize(32);
}

void setFontSize(int size){
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight =size;
    f.lfWeight = FW_NORMAL;
    settextstyle(&f);
}
//绘制算盘
void drawAbacus(Num *num, AbacusParams param) {
    Coordinate topLeft = param.topLeft;
    int width = param.width, heightToBeam = param.heightToBeam, heightToBottom = param.heightToBottom;
    int stickSpan = param.stickSpan;
    float beadHalfHeight = param.beadHalfHeight,beadHalfWidth = param.beadHalfWidth;
    int dotLocation = param.dotLocation;

    line(topLeft.x, topLeft.y, topLeft.x+width, topLeft.y); //上框
    line(topLeft.x, topLeft.y+heightToBeam, topLeft.x+width, topLeft.y+heightToBeam); //中框（梁）
    line(topLeft.x, topLeft.y+heightToBottom, topLeft.x+width, topLeft.y+heightToBottom); //下框
    fillellipse(topLeft.x+stickSpan/2+dotLocation*50 - 5, topLeft.y+heightToBeam - 5, topLeft.x+stickSpan/2+dotLocation*50 + 5, topLeft.y+heightToBeam + 5); //小数点

    for (int i = 0; i < 17; ++i) //左框+右框+档
    {
        line(topLeft.x + i * stickSpan, topLeft.y, topLeft.x + i * stickSpan, topLeft.y+heightToBottom);
    }

    for (int i = 0, j = 14; i < PLACES_NUM; ++i, --j) //绘制梁上算珠
    {
        for (int k = 0; k < num[j].upper; ++k) //入珠
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+heightToBeam-beadHalfHeight - 2*beadHalfWidth * k);
        for (int k = 0; k < 1 - num[j].upper; ++k) //未入珠
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+beadHalfHeight + 2*beadHalfWidth * k);
    }

    for (int i = 0, j = 14; i < PLACES_NUM; ++i, --j) //绘制梁下算珠
    {
        for (int k = 0; k < num[j].lower; ++k) //入珠
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+heightToBeam+beadHalfHeight + 2*beadHalfWidth * k);
        for (int k = 0; k < 4 - num[j].lower; ++k) //未入珠
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+heightToBottom-beadHalfHeight - 2*beadHalfWidth * k);
    }
}

//248->24800, 23.12 -> 2312, 0.3 -> 3-
bool convertToDecimal(char *x)
{
    bool isDecimal = true;
    if((string(x)).find('.') == string::npos) { //整数
        isDecimal = false;
    }
    itoa(atof(x)*100,x,10);
    return isDecimal;
}

void clearAbacus(Num* abacus){
    for (int i = 0; i < PLACES_NUM; ++i) {
        abacus[i].upper = 0;
        abacus[i].lower = 0;
    }
}

//阿拉伯数字转换为算盘式数字
void toAbacusForm(Num *abacus_number, const char* arabic_number, int len) //len：没有小数点
{
    for (int i = len - 1, k = 0; i >= 0; i--, k++)
    {
        int x = arabic_number[i] - '0';
        abacus_number[k].upper = x / 5;
        abacus_number[k].lower = x % 5;
    }
}

//算盘某档转为阿拉伯数字
int toNumberForm(Num *abacus_number){
    return abacus_number->upper * 5 + abacus_number->lower;
}

//将数字设置到算盘的某个挡位
void setNumToAbacus(int num, Num* abacus,int stickNum){
    abacus[stickNum-1].upper = num / 5;
    abacus[stickNum-1].lower = num % 5;
}

double allToNumberForm(Num* abacus_number){
    double result = 0;
    int digit;
    for (int i = 0; i < 15; ++i) {
        digit = toNumberForm(&abacus_number[i]);
        if(digit != 0){
            result += digit * pow(10,i-2);
        }
    }
    return result;
}
