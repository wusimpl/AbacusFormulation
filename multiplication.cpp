//
// Created by andy on 2022/7/18.
//

#include "multiplication.h"
//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif

//显示表达式计算的结果
void drawExpressionOfMultiplication()
{
    setFontSizeTo32();
    double facNumber = atof(original_c_first_operand);
    double mulNumber = atof(original_c_second_operand);
    stringGenerator<<facNumber<<"+"<<mulNumber<<"="<<facNumber*mulNumber;
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
//    drawMnemonicRhymeOfMultiplication(); //绘制加法口诀表
}

/**
 * 模拟大九九口诀表返回乘积
 * @param fac
 * @param mul
 * @param placeOfFirstDigit 积的第一个数字所在的挡位
 * @param product
 */
void lookUpMultiplicationTable(int fac, int mul, int placeOfFirstDigit, Num* product){
    int _product = fac * mul;
    char charProduct[9];
    _itoa_s(_product,charProduct,10);

    if(_product<10){
        setNumToAbacus(_product, product, placeOfFirstDigit);
    }else{
        setNumToAbacus(_product, product, placeOfFirstDigit);
    }
}

//可视化模拟一位加法
void simulateMultiplication(Num* fa, Num* mu, int n){
    Num* fac = &fa[n];
    Num* mul = &mu[n];
    Num* tmp = fac; //当前被加数的指针
    int facNumber = toNumberForm(fac); //被加数
    int mulNumber = toNumberForm(mul); //加数

    if (mulNumber + facNumber <= 9){ //直接加或者凑五加
        if(facNumber<5&&mulNumber<5&&mulNumber+facNumber>=5){//凑五加：被加数下框离梁珠<加数 && 加数<5
            //凑五加：下五去凑五数
            tmp->upper += 1; //下五
            drawNumOnAbacusOfMultiplication(fa);
            drawRules("下五");
            _getch();
            tmp->lower -= 5 - mulNumber;
            drawNumOnAbacusOfMultiplication(fa);
            stringGenerator<<"去"<<INDEX_TO_CHINESE_NUM[5 - mulNumber];
            strcpy(strInfo,stringGenerator.str().c_str());
            drawRules(strInfo);
            stringGenerator.str("");
            _getch();
        }else{ //直接加
            tmp->upper += mulNumber / 5;
            tmp->lower += mulNumber % 5;
            drawNumOnAbacusOfMultiplication(fa);
            stringGenerator<<"上"<<INDEX_TO_CHINESE_NUM[mulNumber];
            strcpy(strInfo,stringGenerator.str().c_str());
            drawRules(strInfo);
            stringGenerator.str("");
            _getch();
        }
    }else{ //进十加或者破五进十加
        int complement = 10-mulNumber;//加数的补数
        /*先计算本位*/
        if(mulNumber>5&&tmp->upper==1){//破五进十加
            //去五，上（5-补数）
            tmp->upper -= 1;
            drawNumOnAbacusOfMultiplication(fa);
            drawRules("去五");
            _getch();

            tmp->lower += 5 - complement;
            drawNumOnAbacusOfMultiplication(fa);
            stringGenerator<<"上"<<INDEX_TO_CHINESE_NUM[5-complement];
        }else{ //进十加
            tmp->upper -= int(complement / 5);
            tmp->lower -= complement % 5;
            drawNumOnAbacusOfMultiplication(fa);
            stringGenerator<<"去"<<INDEX_TO_CHINESE_NUM[complement];
        }
        strcpy(strInfo,stringGenerator.str().c_str());
        drawRules(strInfo);
        stringGenerator.str("");
        _getch();

        /*再计算进位
         * 进一可能引起前面许多位都有进位，所以本质上是连续加法，使用递归调用解决此问题。
         * 这里当做另外一次加法来做，被加数：当前算盘的数，加数：1。
         * */
        CARRYNUM carryNumber(n+1);

        drawNumOnAbacusOfMultiplication(fa);
        drawRules("进一");
        _getch();
        simulateMultiplication(fa, carryNumber.carry, n + 1);
    }
}