//
// Created by andy on 2022/7/23.
//

#include "division.h"
//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif
#include "subtraction.h"

void drawExpressionOfDivision(){
    setFontSizeTo32();
    double diNumber = atof(original_c_first_operand);
    double divNumber = atof(original_c_second_operand);
    stringGenerator<<diNumber<<"/"<<divNumber<<"=";
    stringGenerator.precision(3);
    stringGenerator<<diNumber/divNumber;
    stringGenerator.precision(2);
    strcpy(strInfo,stringGenerator.str().c_str());
    drawExpression(strInfo);
    stringGenerator.str("");
    setFontSizeTo16();
}

void drawNumOnAbacusOfDivision(Num* sa){
    cleardevice(); //清空屏幕内容
//    AbacusParams  param;
//    clearAbacus(param);
    drawExpressionOfDivision(); // 绘制列式计算的结果
    drawAbacus(sa,AbacusParams()); //绘制算盘
}

void simulateDivision(size_t integerLen1, size_t integerLen2){
    Num* di = a_first_operand;
    Num* div = a_second_operand; //被除数的算盘形式
    double divNum = allToNumber(a_second_operand); //被除数
    int headIndexOfDi = PLACES_NUM - integerLen1 - 2;
    int headIndexOfDiv = PLACES_NUM - integerLen2 - 2;
    int headIndexOfQuo = -1;
    int currentQuo; //当前所试出来的商（不带位的形态）
    double currentRealQuo; //当前所试出来的商（带位的形态，用于调商）
    int currentQuoLocation; //当前商所在(档位-1)
    size_t quoNum; //商总共有几位（整数部分）
    int currentDigitOfQuo; //当前商是第几个商
    int currentDi; //当前所比较的被除数
    int firstTwoDi; //被除数前两位
    int currentDiv; //当前所比较的除数
    int nextDiv; //除数下一档所代表的数
//    int quoLocation = 1; //商的位置：1代表够除，隔位商；0代表不够除，挨位商 #已移到循环内
    stringstream ss;

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

        int quoLocation = 1;
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
        ss<<"估得商为"<<currentQuo;
        strcpy(strInfo,ss.str().c_str());
        drawRules(strInfo);
        ss.str("");
        _getch();
        //3.置商
        currentQuoLocation = headIndexOfDi - 1 - quoLocation;
        if(headIndexOfQuo==-1){ //记录商的开始位置
            headIndexOfQuo = currentQuoLocation;
        }
        currentDigitOfQuo = currentQuoLocation-headIndexOfQuo+1; //当前是第几个商数

        setNumToAbacusMulVersion(currentQuo, di, currentQuoLocation);
        drawNumOnAbacusOfDivision(di);
        _getch();

        Num product[PLACES_NUM];
        double _product;
        currentRealQuo = currentQuo*pow(10, (int)quoNum - currentDigitOfQuo);

        //4.退商：估商过大，须退商 （原为心算，用比较代替）
        while (currentRealQuo*divNum > toNumber(di, headIndexOfDi, PLACES_NUM - 1)) { //余数不够减当前商数*除数
            ss<<"退商：估商过大，退1";
            strcpy(strInfo,ss.str().c_str());
            drawRules(strInfo);
            ss.str("");
            _getch();

            currentQuo--;
            currentRealQuo = currentQuo*pow(10, (int)quoNum - currentDigitOfQuo);
            setNumToAbacusMulVersion(currentQuo, di, headIndexOfDi - 1 - quoLocation);
            drawNumOnAbacusOfDivision(di);
            _getch();
        }

        //5.减积：1位乘法的积错位相减
        double mulDigit; //遍历乘数的每一位（带位的形态）
        char tmp[PLACES_NUM+1];
        for (int i = headIndexOfDiv; i < PLACES_NUM; ++i) {
            if((currentRealQuo-0.00001)<0){ //估商都为0了还减个啥积啊，跳过完事了
                break;
            }
            mulDigit = toNumber(div,i,i);
            if((mulDigit-0.00001) < 0){ // mulDigit = 0
                continue;
            }
            _product = currentRealQuo * mulDigit;
            sprintf(tmp,"%.2f",_product);
            convertToDecimal(tmp);
            numberToAbacus(product,tmp, strlen(tmp));

            ss<<"减积：减"<<_product;
            strcpy(strInfo,ss.str().c_str());
            drawRules(strInfo);
            ss.str("");
            _getch();

            for (int j = headIndexOfDi; j < PLACES_NUM; j++) {  // 只会在两档上进行减运算（不算上借位的情况，即使有借位的情况，减法中的递归调用也会解决此问题）
                if (oneToNumber(&product[j]) != 0) {
                    simulateSubtractionPureVersion(di, product, j);
                }
            }
            clearAbacus(product);
        }
        //6.补商：余数 > 除数*商所在位数（个位即为1，十位即为10，十分位即为0.1）
        while(toNumber(di, headIndexOfDi, PLACES_NUM-1) > divNum*(pow(10, (int)quoNum - currentDigitOfQuo))){
            ss<<"补商：估商过小，加1";
            strcpy(strInfo,ss.str().c_str());
            drawRules(strInfo);
            ss.str("");
            _getch();

            currentQuo++;
            setNumToAbacusMulVersion(currentQuo, di, headIndexOfDi - 1 - quoLocation);
            drawNumOnAbacusOfDivision(di);
            _getch();
            ss<<"补商：减一个除数";
            strcpy(strInfo,ss.str().c_str());
            drawRules(strInfo);
            ss.str("");
            //（从当前商数的位置起）隔位减一个(除数*商所在位数)
            double mei = divNum*(pow(10, (int)quoNum - currentDigitOfQuo));
            Num tmpDiv[PLACES_NUM];
            sprintf(tmp,"%.2f",mei);
            convertToDecimal(tmp);
            numberToAbacus(tmpDiv,tmp, strlen(tmp));
            for (int i = headIndexOfDi; i < PLACES_NUM; i++){
                if(oneToNumber(&tmpDiv[i]) != 0){
                    simulateSubtractionPureVersion(di, tmpDiv, i);
                }
            }
        }
        while(oneToNumber(&di[headIndexOfDi])==0){ //跳过被除数为0的位
            ++headIndexOfDi;
        }
    }while((toNumber(di, headIndexOfDi, PLACES_NUM-1)-0.00001)>0 && (currentDigitOfQuo-(int)quoNum)<2); //当余数不为0或未达到预设精度时，继续运算
}
