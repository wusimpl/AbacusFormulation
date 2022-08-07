//
// Created by andy on 2022/5/26.
//

#include "radication.h"
#include <cmath>
#include <string>
#include <cstdio>
#include <iomanip>

//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif

#define CSTR_TO_NUM(cstr) (atoi(cstr))
#define NUM_TO_CSTR(num,str) (sprintf(str,"%.2lf",num))

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

void simulateRadication(char* original_c_first_operand,size_t dotLocation,int lenWithoutDot, int convertedLen){
    int integralDigitsCount = 0; //开方结果的整数的位数
    //根据小数点的位置确定integralDigitsCount
    integralDigitsCount = dotLocation == 0?lenWithoutDot:dotLocation;
    integralDigitsCount = integralDigitsCount%2==0?integralDigitsCount/2:integralDigitsCount/2+1;

    int currentRootLocation = integralDigitsCount; //以小数点为原点0，向左依次+1，向右依次-1
    double currentRoot = 0; // root value
    int currentResultStick = integralDigitsCount+2; // 显示结果的算盘的当前挡位（从右至左），因为有两位小数点，所以+2
    double currentRootWithDigits = 0; // root * 10^(its digit)
    char head[3]; // 要估算的位，例如344.2，估首根，head为3
    double sumUpOfRoots = 0; // 已经求得的根之和
    double denominator; // 法数：2(root1 + root2 + root3 ...)
    double remainder = allToNumber(a_first_operand);//余数
    double subtrahend; //减数：(法数+当前根)*当前根
    //估首根
    _getch();
    getHead(original_c_first_operand,lenWithoutDot,dotLocation,head);
    currentRoot = int(sqrt(CSTR_TO_NUM(head)));
    currentRootWithDigits = currentRoot * pow(10,currentRootLocation-1);
    sumUpOfRoots += currentRootWithDigits;
    denominator = 2*sumUpOfRoots;
    setNumToAbacusRadicationVersion(currentRoot, a_second_operand, currentResultStick);//可视化
    drawNumOnAbacusOfRadication(a_first_operand, a_second_operand);
    currentResultStick--;
    stringGenerator<<"估得首根为"<<currentRoot;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawRules(strInfo);
    stringGenerator.str("");
    _getch();
    //减首根平方
    remainder -= pow(currentRootWithDigits,2);
    currentRootLocation--;

    NUM_TO_CSTR(remainder,c_first_operand);//可视化
    convertToDecimal(c_first_operand);
    clearAbacus(a_first_operand);
//    numberToAbacus(a_first_operand, c_first_operand, strlen(c_first_operand));
    numberToAbacusV2(a_first_operand, strtod(original_c_first_operand,nullptr));
    drawNumOnAbacusOfRadication(a_first_operand, a_second_operand);
    stringGenerator<<"减首根平方"<<pow(currentRootWithDigits,2);
    strcpy(strInfo,stringGenerator.str().c_str());
    drawRules(strInfo);
    stringGenerator.str("");
    _getch();
    //估其他根
    char remainderStrForm[15];
    for (int i = currentRootLocation; i > -2; i--,currentResultStick--) {
        //估根
        NUM_TO_CSTR(remainder, remainderStrForm);
//        dotLocation = getDotLocation(remainderStrForm);
//        getHead(remainderStrForm, strlen(remainderStrForm),dotLocation,head);
        currentRoot = i>0?int(remainder/denominator/ pow(10,i-1)):int((remainder/denominator)*pow(10,-(i-1))); //估
        currentRootWithDigits = currentRoot * pow(10,i-1);
//        currentRootWithDigits = ((int)(currentRootWithDigits*100))/100.0; //0.1000004 -> 10 -> 0.100000 懂？
        while(remainder - (denominator+currentRootWithDigits)*currentRootWithDigits < 0){ //估根估大了，调整
            currentRoot--;
            currentRootWithDigits = currentRoot * pow(10,i-1);
//            currentRootWithDigits = ((int)(currentRootWithDigits*100))/100.0; //0.1000004 -> 10 -> 0.100000 懂？
        }


        setNumToAbacusRadicationVersion(currentRoot, a_second_operand, currentResultStick);//可视化
        drawNumOnAbacusOfRadication(a_first_operand, a_second_operand);
        stringGenerator<<"估得下一根为"<<currentRoot;
        strcpy(strInfo,stringGenerator.str().c_str());
        drawRules(strInfo);
        stringGenerator.str("");
        _getch();

        sumUpOfRoots += currentRootWithDigits;
        subtrahend = (denominator + currentRootWithDigits) * currentRootWithDigits;
        stringGenerator<<"减"<<subtrahend;
        remainder -= subtrahend;
        denominator = 2*sumUpOfRoots; //更新法数

        NUM_TO_CSTR(remainder,c_first_operand);//可视化
        convertToDecimal(c_first_operand);
        clearAbacus(a_first_operand);
        numberToAbacus(a_first_operand, c_first_operand, strlen(c_first_operand));
        numberToAbacusV2(a_first_operand, strtod(original_c_first_operand, nullptr));
        drawNumOnAbacusOfRadication(a_first_operand, a_second_operand);
        strcpy(strInfo,stringGenerator.str().c_str());
        drawRules(strInfo);
        stringGenerator.str("");
        _getch();

        if((remainder-0.0) < 0.000001){ //开方开尽，退出
            break;
        }
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
    double number = atof(original_c_first_operand);
    sg << "sqrt("<<number<<")"<<"="<<sqrt(number)<<"（保留两位小数）";
    strcpy(strInfo,sg.str().c_str());
    drawExpression(strInfo);
}
