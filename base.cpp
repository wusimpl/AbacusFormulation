//
// Created by andy on 2022/5/6.
//

#include "base.h"

Num num_1operand[PLACES_NUM], num_2operand[PLACES_NUM]; //数的算盘形式
char char_1operand[PLACES_NUM + 1], char_2operand[PLACES_NUM + 1]; //数的字符形式
char ochar_1operand[PLACES_NUM + 1], ochar_2operand[PLACES_NUM + 1];//接收到的输入数字
const char* INDEX_TO_CHINESE_NUM[] = {"零","一","二","三","四","五","六","七","八","九","十"}; // 中文数字字符常量
//string processHintPlaceHolder; //演算过程提示占位符
Coordinate expressionDisplayLeftTop={50, 20},expressionDisplayRightBottom={850, 53};
Coordinate rulesDisplayLeftTop={885,190},rulesDisplayRightBottom{1350,223};
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
void drawRules(const char* str){
    setFontSizeTo32();
    RECT r1 = {rulesDisplayLeftTop.x, rulesDisplayLeftTop.y, rulesDisplayRightBottom.x, rulesDisplayRightBottom.y};
    clearrectangle(rulesDisplayLeftTop.x, rulesDisplayLeftTop.y, rulesDisplayRightBottom.x, rulesDisplayRightBottom.y);
    drawtext(str, &r1, DT_WORDBREAK | DT_VCENTER |  DT_LEFT);
    setFontSizeTo16();
}

//表达式计算显示
void drawExpression(const char* str){
    setFontSizeTo32();
    RECT r1 = {expressionDisplayLeftTop.x, expressionDisplayLeftTop.y, expressionDisplayRightBottom.x, expressionDisplayRightBottom.y};
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

    for (int i = 0, j = 0; i < PLACES_NUM; ++i, ++j) //绘制梁上算珠
    {
        for (int k = 0; k < num[j].upper; ++k) //入珠
        {
            setfillcolor(BLACK);
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+heightToBeam-beadHalfHeight - 2*beadHalfWidth * k);
        }
        for (int k = 0; k < 1 - num[j].upper; ++k) //未入珠
        {
            setfillcolor(WHITE);
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+beadHalfHeight + 2*beadHalfWidth * k);
        }
    }

    for (int i = 0, j = 0; i < PLACES_NUM; ++i, ++j) //绘制梁下算珠
    {
        for (int k = 0; k < num[j].lower; ++k) //入珠
        {
            setfillcolor(BLACK);
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+heightToBeam+beadHalfHeight + 2*beadHalfWidth * k);
        }
        for (int k = 0; k < 4 - num[j].lower; ++k) //未入珠
        {
            setfillcolor(WHITE);
            drawOneBead(topLeft.x+stickSpan + stickSpan * i, topLeft.y+heightToBottom-beadHalfHeight - 2*beadHalfWidth * k);
        }
    }
}



//248->24800, 23.12 -> 2312, 0.3 -> 3-
bool convertToDecimal(char *x)
{
    bool isDecimal = true;
    if((string(x)).find('.') == string::npos) { //整数
        isDecimal = false;
    }
    long long value = ceil(strtod(x,nullptr)*100);
    sprintf(x,"%lld",value);
    return isDecimal;
}

void clearAbacus(Num* abacus){
    for (int i = 0; i < PLACES_NUM; ++i) {
        abacus[i].upper = 0;
        abacus[i].lower = 0;
    }
}

//阿拉伯数字转换为算盘式数字
void numberToAbacus(Num *abacus_number, const char* arabic_number, int convertedLen) //convertedLen=strlen(a*100)
{
    for (int i = convertedLen - 1,j=0; i >= 0; i--,j++)
    {
        int digit = arabic_number[i] - '0';
        if(digit!=0){
            abacus_number[PLACES_NUM-1-j].upper = digit / 5;
            abacus_number[PLACES_NUM-1-j].lower = digit % 5;
        }
    }
}

//阿拉伯数字转换为算盘式数字
void numberToAbacusV2(Num *abacus_number,double number)
{
    for (int i = 0; i < 15; ++i) {
        abacus_number[i].upper = (long long)((long long)(100*number/ pow(10,15-i-1))%10/5);
        abacus_number[i].lower = (long long)(100*number/ pow(10,15-i-1))%10%5;
    }
}

//算盘某档转为阿拉伯数字
int oneToNumber(Num *abacus_number){
    return abacus_number->upper * 5 + abacus_number->lower;
}

//将数字设置到算盘的某个挡位
void setNumToAbacusRadicationStickVersion(int num, Num* abacus, int stickNum){
    abacus[stickNum-1].upper = num / 5;
    abacus[stickNum-1].lower = num % 5;
}

void setNumToAbacusIndexVersion(int num, Num* abacus, int indexNum){
    setNumToAbacusRadicationStickVersion(num,abacus,indexNum+1);
}

void setNumToAbacus(int num, Num* abacus,int placeNum){
    abacus[placeNum-1].upper = num / 5;
    abacus[placeNum-1].lower = num % 5;
}

double allToNumber(Num* abacus_number){
    return toNumber(abacus_number,0,14);
//    double result = 0;
//    int digit;
//    for (int i = PLACES_NUM-1; i >= 0; --i) {
//        digit = oneToNumber(&abacus_number[i]);
//        if(digit != 0){
//            result += digit * pow(10,PLACES_NUM-(i+1)-2);
//        }
//    }
//    return result;
}

//int oneToNumber(int upper, int lower) {
//    return upper * 5 + lower;
//}

size_t getDotLocation(const char cStr[]){
    for (int i = 0; i < 15; ++i) {
        if(cStr[i]=='.'){
            return i;
        }else if(cStr[i] == '\0'){
            return 0;
        }
    }
    return 0;
}

void clearAbacus(AbacusParams param) {
    clearrectangle(param.topLeft.x,param.topLeft.y,param.topLeft.x+param.width, param.topLeft.y+param.heightToBottom);
}

double toNumber(Num *abacus_number, int indexA, int indexB) {
    double result = 0;
    int digit;
    for (int i = indexB; i >= indexA; --i) {
        digit = oneToNumber(&abacus_number[i]);
        if(digit != 0){
            result += digit * pow(10,PLACES_NUM-3-i);
        }
    }
    return result;
}

double subNumber(Num *abacus_number, int indexA, int indexB) {
    double result = 0;
    int digit;
    for (int i = indexB; i >= indexA; --i) {
        digit = oneToNumber(&abacus_number[i]);
        if(digit != 0){
            result += digit * pow(10,indexB-i);
        }
    }
    return result;
}

/**
 * 判断字符串型数字是否符合规范
 * @param number
 * @param limitedIntegerCount 整数部分最多多少位
 * @param limitedDecimalCount  小数部分最多多少位
 * @return
 */
bool assertCharNumber(char *number,int limitedIntegerCount, int limitedDecimalCount) {
    int integerCount;
    int decimalCount=0;
    size_t dotPos = (string(number)).find('.');

    if(dotPos == string::npos) {
      integerCount = strlen(number);
    }else{
        integerCount = dotPos;
        decimalCount = strlen(number) - dotPos-1;
    }

    if(integerCount<=limitedIntegerCount && decimalCount<=limitedDecimalCount){
        return true;
    }else{
        return false;
    }

}

bool assertNonNegative(char *number) {
    if(atof(number)>=0){
        return true;
    }
    return false;
}

bool assertEBigger(char *number1, char *number2) {
    if(atof(number1)>=atof(number2)){
        return true;
    }
    return false;
}

bool assertNonZero(char *number) {
    if(fabs(atof(number)) > 1e-6){
        return true;
    }
    return false;
}

bool assertInteger(char *number) {
    return (string(number)).find('.') == string::npos;
}

void copy(Num *A, Num *B) {
    for (int i = 0; i < PLACES_NUM; ++i) {
        B[i] = A[i];
    }
}
