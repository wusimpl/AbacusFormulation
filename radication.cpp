//
// Created by andy on 2022/5/26.
//

#include "radication.h"
#include <cmath>
#include <string>
#include <cstdio>
#include <iomanip>
#include "subtraction.h"
#include "multiplication.h"
#include "division.h"

//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif

#define CSTR_TO_NUM(cstr) (atoi(cstr))
#define NUMBER_TO_CSTR(num,str) (sprintf(str,"%.2lf",num))

void drawNumOnAbacusOfRadication(Num *sa, Num* result) {
    cleardevice(); //清空屏幕内容
    drawExpressionOfRadication(); // 绘制列式计算的结果
    drawAbacus(sa,AbacusParams()); //绘制第一个算盘，用于展示余数的变化
    AbacusParams param = {{50,400},
                          800,
                          100,
                          275,
                          50,
                          12.5,
                          12.5,
                          13};
    drawAbacus(result, param); //绘制第二个算盘，用于展示开方结果的变化
}

void simulateRadication(size_t dotLocation, int lenWithoutDot,int radLen){
    Num* rad = num_1operand;
    Num* root = num_2operand;
    int rootLen = 0; //开方结果的整数的位数
    int location; //以小数点为原点0，向左依次+1，向右依次-1
    double cr = 0; // root value
    double rcr = 0; // root * 10^(its digit)
    int rootPtr; // 显示结果的算盘的当前挡位（从右至左），因为有两位小数点，所以+2
    int radPtr;
    char sec[3]; // 要估算的位，例如344.2，估首根，head为3
    double sum = 0; // 已经求得的根之和
    double den; // 法数：2(root1 + root2 + root3 ...)
    double remainder = allToNumber(rad);//余数
    double subtrahend; //减数：(法数+当前根)*当前根
    Num tmp1[PLACES_NUM], tmp2[PLACES_NUM];
    //定位

    radLen = dotLocation == 0 ? lenWithoutDot : dotLocation;
    rootLen = radLen % 2 == 0 ? radLen / 2 : radLen / 2 + 1;
    location = rootLen;
    rootPtr = 13 - rootLen; //index rather than location
    radPtr = 13 - radLen;
    //估首根
    _getch();
    getHead(ochar_1operand, lenWithoutDot, dotLocation, sec); //sec
    cr = int(sqrt(CSTR_TO_NUM(sec)));
    rcr = cr * pow(10, 12-rootPtr);
    sum += rcr; //累加前根之和
    den = 2 * sum;
    setNumToAbacusIndexVersion(cr, root, rootPtr);
    drawNumOnAbacusOfRadication(rad, root);//可视化
    rootPtr++;
    stringGenerator << "估得首根为" << cr;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawRules(strInfo);
    stringGenerator.str("");
    _getch();
    //减首根平方
    stringGenerator<<"减首根平方"<<pow(rcr, 2);
    strcpy(strInfo,stringGenerator.str().c_str());
    drawRules(strInfo);
    stringGenerator.str("");
    _getch();
    location--;
    numberToAbacusV2(tmp1,pow(rcr, 2));
    remainder -= pow(rcr, 2);
    for (int i = 0; i < 15; i++){ //从左到右按位依次减法
        if(oneToNumber(&rad[PLACES_NUM - i - 1]) != 0 ||
           oneToNumber(&tmp1[PLACES_NUM - i - 1]) != 0){
            simulateSubtractionPureVersion(rad, tmp1, PLACES_NUM - i - 1);
        }
    }
    clearAbacus(tmp1);
    //余数减半
    stringGenerator<<"余数减半为"<<allToNumber(rad)/2;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawRules(strInfo);
    stringGenerator.str("");
    _getch();
    while(oneToNumber(&rad[radPtr])==0){ //移动指针
        radPtr+=1;
        if(radLen!=0){
            radLen -= 1;
        }
    }
    Num fac[PLACES_NUM],mul[PLACES_NUM];
    copy(rad,fac);
    numberToAbacusV2(mul,0.5);
    clearAbacus(rad);
    simulateMultiplicationPureVersion(fac,mul,rad,radLen,0);
    //估其他根
    while(allToNumber(rad)>= sum && ((allToNumber(rad)-0.0) > 1e-6 || rootPtr < 15)) {
        //前根之和试除余数估下一根
        numberToAbacusV2(tmp1,sum);
        double tmp=sum;
        int sumLen = 1;
        while ((tmp=tmp/10) > 1){
            sumLen++;
        }
        copy(rad,tmp2);
        while(oneToNumber(&rad[radPtr])==0){ //移动指针
            radPtr+=1;
            if(radLen!=0){
                radLen -= 1;
            }
        }
        cr = int(simulateDivisionImprovedVersion(tmp2,tmp1,radLen,sumLen)%10);
        rcr = cr * pow(10, 12-rootPtr);

        stringGenerator << "估得下一根为" << cr;
        strcpy(strInfo,stringGenerator.str().c_str());
        drawRules(strInfo);
        stringGenerator.str("");
        _getch();
        setNumToAbacusRadicationStickVersion(cr, root, rootPtr+1);
        drawNumOnAbacusOfRadication(rad, root);//可视化
        //余数减法数
        den = sum * rcr;
        stringGenerator<<"余数减法数：减"<<den<<"，余"<<allToNumber(rad)-den;
        strcpy(strInfo,stringGenerator.str().c_str());
        drawRules(strInfo);
        stringGenerator.str("");
        _getch();
        numberToAbacusV2(tmp1,den);
        for (int j = 0; j < PLACES_NUM; j++){ //从左到右按位依次减法
            if(oneToNumber(&rad[PLACES_NUM - j - 1]) != 0 ||
               oneToNumber(&tmp1[PLACES_NUM - j - 1]) != 0){
                simulateSubtractionPureVersion(rad, tmp1, PLACES_NUM - j - 1);
            }
        }
        clearAbacus(tmp1);
        //减根平方半
        stringGenerator<<"余数减当前根平方的一半：减"<<rcr*rcr/2<<"，余"<<allToNumber(rad)-(rcr*rcr/2);
        numberToAbacusV2(tmp1,rcr*rcr/2);
        strcpy(strInfo,stringGenerator.str().c_str());
        drawRules(strInfo);
        stringGenerator.str("");
        _getch();
        for (int j = 0; j < PLACES_NUM; j++){ //从左到右按位依次减法
            if(oneToNumber(&rad[PLACES_NUM - j - 1]) != 0 ||
               oneToNumber(&tmp1[PLACES_NUM - j - 1]) != 0){
                simulateSubtractionPureVersion(rad, tmp1, PLACES_NUM - j - 1);
            }
        }
        clearAbacus(tmp1);
        sum+=rcr;
        rootPtr++;
        _getch();
    }
}

//size_t getDotLocation(const char cStr[]){
//    for (int i = 0; i < 15; ++i) {
//        if(cStr[i]=='.'){
//            return i;
//        }else if(cStr[i] == '\0'){
//            return 0;
//        }
//    }
//    return 0;
//}

void getHead(const char* strNum, int length, size_t dotLocation, char *head) {
    int headLength;
    int digitsNum; //被开方数的整数部分或小数部分的位数
    int start = 0; //从何位开始取数

    if(strNum[0]=='0'){ //纯小数
        digitsNum = length - dotLocation;
        start = dotLocation+1;
    }else{ //others
        digitsNum = dotLocation == 0 ? length : dotLocation;
    }
    headLength = digitsNum % 2 == 0 ? 2 : 1; //判断head是一位还是两位

    //开始截取数
    int i;
    for (i=0; i < headLength; ++i,++start) {
        head[i] = strNum[start];
    }
    head[i] = '\0';
}


void drawExpressionOfRadication() {
    stringstream sg;
    sg.precision(2);
    sg.setf(ios::fixed);
    double number = atof(ochar_1operand);
    sg << "sqrt("<<number<<")"<<"="<<sqrt(number)<<"（保留两位小数）";
    strcpy(strInfo,sg.str().c_str());
    drawExpression(strInfo);
}
