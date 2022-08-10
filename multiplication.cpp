//
// Created by andy on 2022/7/18.
//

#include "multiplication.h"
#include "addition.h"


//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif

Coordinate multiplicationRhymeDisplayLeftTop={885,150},multiplicationRhymeDisplayRightBottom{1350,183};

//显示表达式计算的结果
void drawExpressionOfMultiplication()
{
    setFontSizeTo32();
    double facNumber = atof(ochar_1operand);
    double mulNumber = atof(ochar_2operand);
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

void drawNumOnAbacusOfMultiplicationPureVersion(Num *sa)
{
    AbacusParams  param;
    clearAbacus(param);
    drawAbacus(sa,AbacusParams()); //绘制算盘
}

/**
 * 模拟大九九口诀表返回乘积
 * @param fac
 * @param mul
 * @param indexOfFirstDigit 积的第一个数字所在的挡位
 * @param product
 */
void lookUpMultiplicationTable(int _product, int indexOfFirstDigit, Num* product){
    if(_product<10){
        setNumToAbacusIndexVersion(_product, product, indexOfFirstDigit + 1); //0不用放置，直接放置第二位
    }else{
        setNumToAbacusIndexVersion(_product / 10, product, indexOfFirstDigit); //放置第一位
        setNumToAbacusIndexVersion(_product % 10, product, indexOfFirstDigit + 1); //放置第二位
    }
}

void lookUpMultiplicationTableDivisionVersion(int _product, int indexOfFirstDigit, Num* product){
    if(_product<10){
        setNumToAbacusIndexVersion(_product, product, indexOfFirstDigit); //0不用放置，直接放置第二位
    }else{
        setNumToAbacusIndexVersion(_product / 10, product, indexOfFirstDigit); //放置第一位
        setNumToAbacusIndexVersion(_product % 10, product, indexOfFirstDigit + 1); //放置第二位
    }
}

/**
 *
 * @param result
 * @param integerLen1 被乘数位数
 * @param integerLen2 乘数位数（位数少的那一个）
 */
void simulateMultiplication(Num* result, int integerLen1, int integerLen2){
    //定位
//    int productDigitNum = oneToNumber(&num_1operand[PLACES_NUM - integerLen1]) *
//                          oneToNumber(&num_2operand[PLACES_NUM - integerLen2]) < 10 ? integerLen1 + integerLen2 - 1 : integerLen1 + integerLen2; //积的位数
    int productDigitNum = integerLen1 + integerLen2; //积的位数
    productDigitNum+=2; //加上两位小数的位置
    Num* fac = num_1operand;
    Num* mul = num_2operand;
    Num* currentFac; //被乘数当前位
    Num* currentMul; //乘数当前位
    int outerAccumulationPointer=PLACES_NUM-productDigitNum; //1*n位乘积累加的错位指针
    int innerAccumulationPointer; // 1位乘法累加的错位指针
    Num product[PLACES_NUM]; //1位乘法之积
    int _product;
    stringstream ss; //yet another string builder
    char oneToNExpressionStrInfo[20];
    //乘法
    for (int i = 0; i < integerLen2 + 2; ++i,outerAccumulationPointer++) {  // 1*n位乘法的积错位相加
        currentMul = &mul[PLACES_NUM - (integerLen2 + 2) + i];
        if(oneToNumber(currentMul)==0){ //乘数当前位为零
            if(i==integerLen2){ //当前位为十分位，没必要继续算法了，out
                break;
            }else{ //当前位在整数位，跳过当前循环加速计算
                continue;
            }
        }
        innerAccumulationPointer = outerAccumulationPointer;

        ss << ochar_1operand << "*" << oneToNumber(currentMul);
        strcpy(oneToNExpressionStrInfo,ss.str().c_str());
        ss.clear();
        ss.str("");

        for (int j = 0; j < integerLen1 + 2; ++j,innerAccumulationPointer++) {  // 1位乘法的积错位相加 5*7821
            currentFac = &fac[PLACES_NUM - (integerLen1 + 2) + j];
            //得1位乘法之积
            _product = oneToNumber(currentFac)*oneToNumber(currentMul);
            if(_product==0){  //被乘数当前位为0，不用算了
                continue;
            }
            lookUpMultiplicationTable(_product, innerAccumulationPointer, product);
            //显示累加之积
            stringGenerator<<"错位累加"<<oneToNumber(currentFac)<<"*"<<oneToNumber(currentMul)<<"=";
            if(_product<10){
                stringGenerator<<"0"<<_product;
            }
            else{
                stringGenerator<<_product;
            }
            strcpy(strInfo,stringGenerator.str().c_str());
            drawMultiplicationRhymeProduct(oneToNExpressionStrInfo,strInfo);
            stringGenerator.clear();
            stringGenerator.str("");


            //将积累加到结果中
            _getch();
            for (int k = PLACES_NUM-productDigitNum; k < PLACES_NUM; k++){
                if(oneToNumber(&product[k]) != 0){
                    simulateAdditionPureVersion(result, product, k);
                }
            }

            clearAbacus(product);
            //show result
            drawNumOnAbacusOfMultiplication(result);
        }
    }
}

//显示1*n位乘法运算提示
void draw1toNExpression(const char* str){
    setFontSizeTo32();
    RECT r1 = {multiplicationRhymeDisplayLeftTop.x, multiplicationRhymeDisplayLeftTop.y,
               multiplicationRhymeDisplayRightBottom.x, multiplicationRhymeDisplayRightBottom.y};
    drawtext(str, &r1, DT_WORDBREAK | DT_VCENTER |  DT_LEFT);
    setFontSizeTo16();
}

//显示1位乘法运算提示
void drawMultiplicationRhymeProduct(const char* oneToNExpressionStrInfo,const char *str) {
    draw1toNExpression(oneToNExpressionStrInfo);
    drawRules(str);
}

void simulateMultiplicationPureVersion(Num *fac, Num* mul,Num *result, int integerLen1, int integerLen2) {
    int productDigitNum = integerLen1 + integerLen2; //积的位数
    productDigitNum+=2; //加上两位小数的位置
    Num* currentFac; //被乘数当前位
    Num* currentMul; //乘数当前位
    int outerAccumulationPointer=PLACES_NUM-productDigitNum; //1*n位乘积累加的错位指针
    int innerAccumulationPointer; // 1位乘法累加的错位指针
    Num product[PLACES_NUM]; //1位乘法之积
    int _product;
    stringstream ss; //yet another string builder
    //乘法
    for (int i = 0; i < integerLen2 + 2; ++i,outerAccumulationPointer++) {  // 1*n位乘法的积错位相加
        currentMul = &mul[PLACES_NUM - (integerLen2 + 2) + i];
        if(oneToNumber(currentMul)==0){ //乘数当前位为零
            if(i==integerLen2){ //当前位为十分位，没必要继续算法了，out
                break;
            }else{ //当前位在整数位，跳过当前循环加速计算
                continue;
            }
        }
        innerAccumulationPointer = outerAccumulationPointer;

        for (int j = 0; j < integerLen1 + 2; ++j,innerAccumulationPointer++) {  // 1位乘法的积错位相加 5*7821
            currentFac = &fac[PLACES_NUM - (integerLen1 + 2) + j];
            //得1位乘法之积
            _product = oneToNumber(currentFac)*oneToNumber(currentMul);
            if(_product==0){  //被乘数当前位为0，不用算了
                continue;
            }
            lookUpMultiplicationTable(_product, innerAccumulationPointer, product);
            //将积累加到结果中
            _getch();
            for (int k = PLACES_NUM-productDigitNum; k < PLACES_NUM; k++){
                if(oneToNumber(&product[k]) != 0){
                    simulateAdditionPureVersion(result, product, k);
                }
            }
            clearAbacus(product);
            drawNumOnAbacusOfMultiplicationPureVersion(result);
        }
    }
}

//# pragma warning (disable:4819)