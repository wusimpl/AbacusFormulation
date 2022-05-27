//
// Created by andy on 2022/5/26.
//

#include "radication.h"
#include <cmath>
#include <string>
#include <stdio.h>


#define CSTR_TO_NUM(cstr) (atoi(cstr))
#define NUM_TO_CSTR(num,str) (sprintf(str,"%.2lf",num))

void drawNumOnAbacusOfRadication(Num *sa, Num* result) {
    cleardevice(); //清空屏幕内容
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

void simulateRadication(char* c_original_first_operand,size_t dotLocation,int originalLen, int convertedLen){
    int integralDigitsCount = 0; //开方结果的整数的位数
    //根据小数点的位置确定integralDigitsCount
    if(dotLocation == 0){//整数
        integralDigitsCount = ceil(originalLen/2.0); //上取整
    }else{//小数
        integralDigitsCount = ceil(dotLocation/2.0);
    }
    int currentRootLocation = integralDigitsCount; //以小数点为原点0，向左依次+1，向右依次-1
    double currentRoot = 0; // root value
    double currentRootWithDigits = 0; // root * 10^(its digit)
    char head[3]; // 要估算的位，例如344.2，估首根，head为3
    double sumUpOfRoots = 0; // 已经求得的根之和
    double denominator = 0; // 法数：2(root1 + root2 + root3 ...)
    double remainder = allToNumberForm(a_first_operand);//余数
    double subtrahend = 0; //减数：(法数+当前根)*当前根

    //估首根
    getHead(c_original_first_operand,originalLen,dotLocation,head);
    currentRoot = int(sqrt(CSTR_TO_NUM(head)));
    currentRootWithDigits = currentRoot * pow(10,currentRootLocation-1);
    sumUpOfRoots += currentRootWithDigits;
    denominator = 2*sumUpOfRoots;
    //减首根平方
    remainder -= pow(currentRootWithDigits,2);
    currentRootLocation--;
    //估其他根
    char remainderStrForm[15];
    for (int i = currentRootLocation; i > -2; --i) {
        //估根
        NUM_TO_CSTR(remainder, remainderStrForm);
        dotLocation = getDotLocation(remainderStrForm);
//        getHead(remainderStrForm, strlen(remainderStrForm),dotLocation,head);
        currentRoot = i>0?int(remainder/denominator/ pow(10,i-1)):int((remainder/denominator)*pow(10,-(i-1))); //估
        currentRootWithDigits = currentRoot * pow(10,i-1);
        sumUpOfRoots += currentRootWithDigits;
        subtrahend = (denominator + currentRootWithDigits) * currentRootWithDigits;
        remainder -= subtrahend;
        denominator = 2*sumUpOfRoots; //更新法数

        if((remainder-0.0) < 0.000001){ //开方开尽，退出
            break;
        }
    }
}

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

void getHead(const char* strNum, int length, size_t dotLocation, char *head) {
    int headLength = 0;
    size_t integralDigitsNum = 0; //被开方数的整数部分的位数

    integralDigitsNum = dotLocation == 0 ? length : dotLocation;

    headLength = integralDigitsNum%2==0 ? 2 : 1; //判断head是一位还是两位

    int i = 0;
    for (i = 0; i < headLength; ++i) {
        head[i] = strNum[i];
    }
    head[i] = '\0';
}
