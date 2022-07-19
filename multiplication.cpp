//
// Created by andy on 2022/7/18.
//

#include "multiplication.h"
#include "addition.h"

//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif

Coordinate multiplicationRhymeDisplayLeftTop={750,150},multiplicationRhymeDisplayRightBottom{1250,183};

//显示表达式计算的结果
void drawExpressionOfMultiplication()
{
    setFontSizeTo32();
    double facNumber = atof(original_c_first_operand);
    double mulNumber = atof(original_c_second_operand);
    stringGenerator<<facNumber<<"*"<<mulNumber<<"="<<facNumber*mulNumber;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawExpression(strInfo);
    stringGenerator.str("");
    setFontSizeTo16();
}

//绘制一个数的盘式
void drawNumOnAbacusOfMultiplication(Num *sa)
{
    cleardevice(); //清空屏幕内容
    drawExpressionOfMultiplication(); // 绘制列式计算的结果
    drawAbacus(sa,AbacusParams()); //绘制算盘
//    drawMnemonicRhymeOfMultiplication(); //绘制
}

/**
 * 模拟大九九口诀表返回乘积
 * @param fac
 * @param mul
 * @param placeOfFirstDigit 积的第一个数字所在的挡位
 * @param product
 */
void lookUpMultiplicationTable(int _product, int placeOfFirstDigit, Num* product){
    if(_product<10){
        setNumToAbacusMulVersion(_product, product, placeOfFirstDigit+1); //0不用放置，直接放置第二位
    }else{
        setNumToAbacusMulVersion(_product / 10, product, placeOfFirstDigit); //放置第一位
        setNumToAbacusMulVersion(_product % 10, product, placeOfFirstDigit+1); //放置第二位
    }
}

/**
 *
 * @param result
 * @param len1 被乘数位数
 * @param len2 乘数位数（位数少的那一个）
 */
void simulateMultiplication(Num* result, int len1, int len2){
    //定位
    int productDigitNum = oneToNumber(&a_first_operand[PLACES_NUM - len1]) *
                          oneToNumber(&a_second_operand[PLACES_NUM - len2]) < 10 ? len1 + len2 - 1 : len1 + len2; //积的位数
    productDigitNum+=2; //加上两位小数的位置
    Num* fac = a_first_operand;
    Num* mul = a_second_operand;
    Num* currentFac = &fac[PLACES_NUM-len1];
    Num* currentMul = &mul[PLACES_NUM-len2];
    int outerAccumulationPointer=PLACES_NUM-productDigitNum; //1*n位乘积累加的错位指针
    int innerAccumulationPointer; // 1位乘法累加的错位指针
    Num product[PLACES_NUM]; //1位乘法之积
    int _product;
    //乘法
    for (int i = 0; i < len2; ++i,outerAccumulationPointer++) {  // 1*n位乘法的积错位相加
        currentMul = &mul[PLACES_NUM-len2+i],
        innerAccumulationPointer = outerAccumulationPointer;
        for (int j = 0; j < len1; ++j,innerAccumulationPointer++) {  // 1位乘法的积错位相加 5*7821
            currentFac = &fac[PLACES_NUM-len1+j];
            //得1位乘法之积
            _product = oneToNumber(currentFac)*oneToNumber(currentMul);
            lookUpMultiplicationTable(_product, innerAccumulationPointer, product);

            //显示累加之积
            /*stringGenerator<<"错位累加";
            if(_product<10){
                stringGenerator<<"0"<<_product;
            }
            else{
                stringGenerator<<_product;
            }
            strcpy(strInfo,stringGenerator.str().c_str());
            drawMultiplicationRhymeProduct(strInfo);
            stringGenerator.clear();
            stringGenerator.str("");*/


            //将积累加到结果中
            for (int k = PLACES_NUM-productDigitNum; k < PLACES_NUM; k++){
                if(oneToNumber(&product[k]) != 0){
                    simulateAddition(result, product, k);
                }
            }

            clearAbacus(product);
            //show result
            drawNumOnAbacusOfMultiplication(result);
            double r = allToNumber(result);
            cout<<r<<endl;
        }
    }
}

void drawMultiplicationRhymeProduct(const char *str) {
    setFontSizeTo32();
    RECT r1 = {multiplicationRhymeDisplayLeftTop.x, multiplicationRhymeDisplayLeftTop.y,
               multiplicationRhymeDisplayRightBottom.x, multiplicationRhymeDisplayRightBottom.y};
    drawtext(str, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    setFontSizeTo16();
}

//# pragma warning (disable:4819)