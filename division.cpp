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
    stringGenerator<<diNumber<<"/"<<divNumber<<"="<<diNumber/divNumber;
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
    Num* div = a_second_operand; //被除数的算盘形式
    double divNum = allToNumber(a_second_operand); //被除数
    int headIndexOfDi = PLACES_NUM - integerLen1 - 2;
    int headIndexOfDiv = PLACES_NUM - integerLen2 - 2;
    int headIndexOfQuo = PLACES_NUM - integerLen1 - 2 - 2;
    int currentQuo; //当前所试出来的商（不带位的形态）
    double currentRealQuo; //当前所试出来的商（带位的形态，用于调商）
    int currentQuoLocation; //当前商所在(档位-1)
    size_t quoNum; //商总共有几位（整数部分）
    int CurrentDigitOfQuo=1; //当前商是第几个商
    int currentDi; //当前所比较的被除数
    int firstTwoDi; //被除数前两位
    int currentDiv; //当前所比较的除数
    int nextDiv; //除数下一档所代表的数
    int quoLocation = 1; //商的位置：1代表够除，隔位商；0代表不够除，挨位商

    //1.定位
    int sameNumDivOfDi = toNumber(di, headIndexOfDi, PLACES_NUM - integerLen1 - 2 + integerLen2) / pow(10, integerLen1 - integerLen2); //与除数取相同位数
    int integerPartOfDiv = toNumber(div, headIndexOfDiv, 12);
    quoNum = sameNumDivOfDi < integerPartOfDiv ? integerLen1 - integerLen2 : integerLen1 - integerLen2 + 1;
//    quoNum+=2; //加上两位小数的位置

    currentDiv = oneToNumber(&div[headIndexOfDiv]); //除首
    nextDiv = oneToNumber(&div[headIndexOfDiv+1]); //次首
    do{
        currentDi =oneToNumber(&di[headIndexOfDi]); //被首
        firstTwoDi = subNumber(di, headIndexOfDi, headIndexOfDi + 1); //被2

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
        currentQuoLocation = headIndexOfDi - 1 - quoLocation;
        setNumToAbacusMulVersion(currentQuo, di, currentQuoLocation);
        drawNumOnAbacusOfDivision(di);

        Num product[PLACES_NUM];
        double _product;
        Num* currentMul;

//        currentMul = &div[headIndexOfDiv]; //预估乘积
//        _product = currentQuo * oneToNumber(currentMul);
//        lookUpMultiplicationTableDivisionVersion(_product, headIndexOfDi, product);
        currentRealQuo = currentQuo*pow(10,(int)quoNum-CurrentDigitOfQuo);

        //4.退商：估商过大，须退商 （原为心算，用比较代替）
        while (currentRealQuo*divNum > toNumber(di, headIndexOfDi, PLACES_NUM - 1)) { //余数不够减当前商数*除数
            currentQuo--;
            currentRealQuo = currentQuo*pow(10,(int)quoNum-CurrentDigitOfQuo);
            setNumToAbacusMulVersion(currentQuo, di, headIndexOfDi - 1 - quoLocation);
            drawNumOnAbacusOfDivision(di);
        }

        //5.减积：1位乘法的积错位相减
//        int ptr = headIndexOfDi; //错位相减指针
        double mulDigit; //遍历乘数的每一位（带位的形态）
        char tmp[PLACES_NUM+1];
        for (int i = headIndexOfDiv; i < PLACES_NUM; ++i) {  //
            mulDigit = toNumber(div,i,i);
            if((mulDigit-0.00001) < 0){ // mulDigit = 0
                continue;
            }
            _product = currentRealQuo * mulDigit;
            sprintf(tmp,"%.2f",_product);
            convertToDecimal(tmp);
            numberToAbacus(product,tmp, strlen(tmp));

            for (int j = headIndexOfDi; j < PLACES_NUM; j++) {  // 只会在两档上进行减运算（不算上借位的情况，即使有借位的情况，减法中的递归调用也会解决此问题）
                if (oneToNumber(&product[j]) != 0) {
                    simulateSubtractionPureVersion(di, product, j);
                }
            }
            clearAbacus(product);
//            ptr++;
        }
        //6.补商：余数 > 除数*商所在位数（个位即为1，十位即为10，十分位即为0.1）
        while(toNumber(di, headIndexOfDi, PLACES_NUM-1) > divNum*(pow(10,(int)quoNum-CurrentDigitOfQuo))){
            currentQuo++;
            setNumToAbacusMulVersion(currentQuo, di, headIndexOfDi - 1 - quoLocation);
            drawNumOnAbacusOfDivision(di);

            //（从当前商数的位置起）隔位减一个除数
            for (int i = headIndexOfDiv; i < headIndexOfDiv + 2; i++){
                if(oneToNumber(&div[i]) != 0){
                    simulateSubtractionPureVersion(di, div, i);
                }
            }
        }

        while(oneToNumber(&di[++headIndexOfDi])==0);
        CurrentDigitOfQuo++;
    }while(allToNumber(di)!=0);

}
