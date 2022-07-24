//
// Created by andy on 2022/7/23.
//

#include "division.h"
#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif
#include "subtraction.h"
#include "multiplication.h"

void drawExpressionOfDivision(){
    setFontSizeTo32();
    double diNumber = atof(original_c_first_operand);
    double divNumber = atof(original_c_second_operand);
    stringGenerator<<diNumber<<"/"<<divNumber<<"="<<diNumber*divNumber;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawExpression(strInfo);
    stringGenerator.str("");
    setFontSizeTo16();
}

void drawNumOnAbacusOfDivision(Num* sa){
    cleardevice(); //清空屏幕内容
    drawExpressionOfDivision(); // 绘制列式计算的结果
    drawAbacus(sa,AbacusParams()); //绘制算盘
}

void simulateDivision(size_t integerLen1, size_t integerLen2){
    Num* di = a_first_operand;
    Num* div = a_second_operand;
    int headIndexOfDi = PLACES_NUM - integerLen1 - 2;
    int headIndexOfDiv = PLACES_NUM - integerLen2 - 2;
    int headIndexOfQuo = PLACES_NUM - integerLen1 - 2 - 2;
    int currentQuo; //当前所试出来的商
    int currentDi; //当前所比较的被除数
    int firstTwoDi; //被除数前两位
    int currentDiv; //当前所比较的除数
    int nextDiv; //除数下一档所代表的数
    int quoLocation = 1; //商的位置：1代表够除，隔位商；0代表不够除，挨位商

    //1.定位
    int sameNumDivOfDi = toNumber(di, headIndexOfDi, PLACES_NUM - integerLen1 - 2 + integerLen2) / pow(10, integerLen1 - integerLen2); //与除数取相同位数
    int integerPartOfDiv = toNumber(div, headIndexOfDiv, 12);
    size_t quoNum = sameNumDivOfDi < integerPartOfDiv ? integerLen1 - integerLen2 : integerLen1 - integerLen2 + 1;
    quoNum+=2; //加上两位小数的位置

    currentDi =oneToNumber(&di[headIndexOfDi]); //被首
    firstTwoDi = toNumber(di, headIndexOfDi, headIndexOfDi + 1)/ pow(10, integerLen1 - integerLen2); //被2
    currentDiv = oneToNumber(&div[headIndexOfDiv]); //除首
    nextDiv = oneToNumber(&div[headIndexOfDiv+1]); //次首
    if(integerLen2==1){
        //2.估商（1位除）
        if (currentDi < currentDiv){
            currentQuo = firstTwoDi/currentDiv;
            quoLocation = 0;
        }else{
            currentQuo = currentDi/currentDiv;
        }
    }else{
        //2.估商（多位除）
        if (currentDi < currentDiv){ //被首<除首
            quoLocation = 0;
            if(nextDiv<=4){
                currentQuo = firstTwoDi/currentDiv;
            }else{
                currentQuo = firstTwoDi/(currentDiv+1);
            }
        }else{
            if(nextDiv<=4){
                currentQuo = currentDi/currentDiv;
            }else{
                currentQuo = currentDi/(currentDiv+1);
            }
        }
    }
    //3.置商
    setNumToAbacusMulVersion(currentQuo, di, headIndexOfDi - 1 - quoLocation);

    Num product[PLACES_NUM];
    int _product;
    Num* currentMul;
    for (int i = headIndexOfDiv; i < PLACES_NUM; ++i) {  // 1位乘法的积错位相减 5*7821
        currentMul = &di[i];
        //得1位乘法之积
        _product = currentQuo*oneToNumber(currentMul);
        lookUpMultiplicationTableDivisionVersion(_product, headIndexOfDiv, product);
        //被除数叠减乘积
        while(allToNumber(product) > toNumber(di,headIndexOfDi,PLACES_NUM-1)){//4.退商：估商过大，须退商 （原为心算，用比较代替）
            currentQuo--;
        }
        //5.减积
        for (int j = headIndexOfDiv; j < headIndexOfDiv+2; j++){  // 只会在两档上进行减运算（不算上借位的情况，即使有借位的情况，减法中的递归调用也会解决此问题）
            if(oneToNumber(&product[j]) != 0){
                simulateSubtractionPureVersion(di, product, j);
            }
        }
        //6.补商
        while(toNumber(di, headIndexOfDi, headIndexOfDi + 1)/ pow(10, integerLen1 - integerLen2) > toNumber(div, headIndexOfDiv, 12)){
            currentQuo++;
            //被除数减一个除数
            for (int j = headIndexOfDiv; j < headIndexOfDiv+2; j++){
                if(oneToNumber(&div[j]) != 0){
                    simulateSubtractionPureVersion(di, div, j);
                }
            }
        }
    }

}
