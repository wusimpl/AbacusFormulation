//
// Created by andy on 2022/5/6.
//
#include "addition.h"
#include "subtraction.h"
#include "radication.h"
#include "multiplication.h"
#include "division.h"

//#define DEBUG
#ifdef DEBUG
#define _getch() ;
#endif

#define GraphSizeOfWidth 1400
#define GraphSizeOfHeight 750

void menu();
void initDrawingEnv();
void addition();
void subtraction();
void radication();
void multiplication();
void division();

void menu(){
    printf("*******珠算可视化演示与学习系统********\n");
    printf("1.加法\n");
    printf("2.减法\n");
    printf("3.乘法（空盘前乘法）\n");
    printf("4.除法（商除法）\n");
    printf("5.开方（折半商除开平方）\n");
    printf("***************************\n");
}

int main()
{
    stringGenerator.precision(2);
    stringGenerator.setf(ios::fixed);
    menu();
    int arithmetic = 0;
    printf("请选择：");
    scanf("%d",&arithmetic);
    switch (arithmetic) {
        case 1:
            addition();
            break;
        case 2:
            subtraction();
            break;
        case 3:
            multiplication();
            break;
        case 4:
            division();
            break;
        case 5:
            radication();
            break;
        default:
            exit(0);
    }
}

void division() {
    int errorHappened;
    size_t integerLen1,integerLen2; //被除数、除数整数部分的位数
    do{
        errorHappened = 0;
        printf("请输入被除数和除数(被除数整数部分不超过13位，小数部分不超过2位，除数需为整数，且除数小于被除数)：");
        scanf("%s %s", char_1operand, char_2operand);

        strcpy(ochar_1operand, char_1operand);
        strcpy(ochar_2operand, char_2operand);

        size_t dotLocationOfFirstOperand = getDotLocation(ochar_1operand); //得到小数点的位置（用于后面的定位）
        size_t dotLocationOfSecondOperand = getDotLocation(ochar_2operand); //得到小数点的位置（用于后面的定位）
        integerLen1 = dotLocationOfFirstOperand == 0 ? strlen(ochar_1operand) : dotLocationOfFirstOperand; //整数部分的位数
        integerLen2 = dotLocationOfSecondOperand == 0 ? strlen(ochar_2operand) : dotLocationOfSecondOperand; //整数部分的位数

        if(!assertCharNumber(ochar_1operand, 13, 1)
           || !assertCharNumber(ochar_2operand, 13, 0)
           || !assertNonNegative(ochar_1operand) || !assertNonNegative(ochar_2operand)
           || !assertInteger(ochar_2operand) || !assertNonZero(ochar_2operand)
           || !assertEBigger(ochar_1operand, ochar_2operand)
           ){
            printf("输入数据不符合规范，请重新输入\n");
            errorHappened = 1;
        }
    } while(errorHappened);

    numberToAbacusV2(num_1operand, strtod(ochar_1operand, nullptr));
    numberToAbacusV2(num_2operand, strtod(ochar_2operand, nullptr));

    initDrawingEnv();
    drawNumOnAbacusOfDivision(num_1operand); //初始化算盘（绘制算盘、列式）

    _getch();
    simulateDivision(integerLen1, integerLen2);

    drawRules("计算结束");
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void multiplication() {
    int errorHappened;
    size_t integerLen1,integerLen2; //被乘数、乘数整数部分的位数
    do{
        errorHappened = 0;
        printf("请输入两个数（整数部分不超过6位，小数部分不超过1位)：");
        scanf("%s %s", char_1operand, char_2operand);

        strcpy(ochar_1operand, char_1operand);
        strcpy(ochar_2operand, char_2operand);
        size_t dotLocationOfFirstOperand = getDotLocation(ochar_1operand); //得到小数点的位置（用于后面的定位）
        size_t dotLocationOfSecondOperand = getDotLocation(ochar_2operand); //得到小数点的位置（用于后面的定位）
        integerLen1 = dotLocationOfFirstOperand == 0 ? strlen(ochar_1operand) : dotLocationOfFirstOperand; //整数部分的位数
        integerLen2 = dotLocationOfSecondOperand == 0 ? strlen(ochar_2operand) : dotLocationOfSecondOperand; //整数部分的位数

        if(!assertCharNumber(ochar_1operand, 6, 1) || !assertCharNumber(ochar_2operand, 6, 1)
           || !assertNonNegative(ochar_1operand) || !assertNonNegative(ochar_2operand)){
            printf("输入数据不符合规范，请重新输入\n");
            errorHappened = 1;
        }

    } while(errorHappened);

    numberToAbacusV2(num_1operand, strtod(ochar_1operand, nullptr));
    numberToAbacusV2(num_2operand, strtod(ochar_2operand, nullptr));

    initDrawingEnv();
    Num result[PLACES_NUM];
    drawNumOnAbacusOfMultiplication(result); //初始化算盘（绘制算盘、列式）
    //乘法
    _getch();
    simulateMultiplication(result, integerLen1, integerLen2);

    drawRules("计算结束");
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void subtraction() {
    int errorHappened;
    int len1,len2;
    int maxLen;
    do{
        errorHappened = 0;
        printf("请输入两个长度不超过14位的数(被减数和减数,被减数大于减数，允许两位小数)：");
        scanf("%s %s", char_1operand, char_2operand);
        strcpy(ochar_1operand, char_1operand);
        strcpy(ochar_2operand, char_2operand);
        len1 = strlen(char_1operand);
        len2 = strlen(char_2operand);
        maxLen = len1 > len2 ? len1 : len2;
        if(!assertCharNumber(ochar_1operand, 13, 2) || !assertCharNumber(ochar_2operand, 13, 2)
           || !assertNonNegative(ochar_1operand) || !assertNonNegative(ochar_2operand)
           || !assertEBigger(ochar_1operand, ochar_2operand)){
            printf("输入数据不符合规范，请重新输入\n");
            errorHappened = 1;
        }
    } while(errorHappened);

//    numberToAbacus(num_1operand, char_1operand, len1);
//    numberToAbacus(num_2operand, char_2operand, len2);
    numberToAbacusV2(num_1operand, strtod(ochar_1operand, nullptr));
    numberToAbacusV2(num_2operand, strtod(ochar_2operand, nullptr));
    initgraph(GraphSizeOfWidth, GraphSizeOfHeight); //初始化绘图环境

    initDrawingEnv();
    drawNumOnAbacusOfSubtraction(num_1operand); //初始化算盘（绘制算盘、列式、口诀表）

    _getch();
    for (int i = 0; i < maxLen; i++){ //从左到右按位依次减法
        if(oneToNumber(&num_1operand[PLACES_NUM - i - 1]) != 0 ||
           oneToNumber(&num_2operand[PLACES_NUM - i - 1]) != 0){ //本位的加数和被加数不都为零
            simulateSubtraction(num_1operand, num_2operand, PLACES_NUM - i - 1);
        }
    }
    drawRules("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void addition() {
    int errorHappened = 0;
    int len1,len2;
    int maxLen;
    do{
        errorHappened = 0;
        printf("请输入两个长度不超过14位的数(被加数和加数，允许两位小数)：");
        scanf("%s %s", char_1operand, char_2operand);
        strcpy(ochar_1operand, char_1operand);
        strcpy(ochar_2operand, char_2operand);
        len1 = strlen(char_1operand);
        len2 = strlen(char_2operand);
        maxLen = len1 > len2 ? len1 : len2;
        if(!assertCharNumber(ochar_1operand, 12, 2) || !assertCharNumber(ochar_2operand, 12, 2)
           || !assertNonNegative(ochar_1operand) || !assertNonNegative(ochar_2operand)){
            printf("输入数据不符合规范，请重新输入\n");
            errorHappened = 1;
        }
    } while(errorHappened);

    numberToAbacusV2(num_1operand, strtod(ochar_1operand, nullptr));
    numberToAbacusV2(num_2operand, strtod(ochar_2operand, nullptr));

    initDrawingEnv();
    drawNumOnAbacusOfAddition(num_1operand); //初始化算盘（绘制算盘、列式、口诀表）

    _getch();
    for (int i = 0; i < maxLen; i++){ //从右到左按位依次加法
        if(oneToNumber(&num_2operand[PLACES_NUM - i - 1]) != 0){ //被加数的当前计算挡位不为零
            simulateAddition(num_1operand, num_2operand, PLACES_NUM - i - 1);
        }
    }

    drawRules("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void radication(){
    int errorHappened; //true if error happened
    int lenWithoutDot; //去掉小数点后的长度
    int num_1operandLen; //整数部分位数
    size_t dotLocation; //小数点的位置
    do{
        errorHappened = false;
        printf("请输入被开方数(被开方数不超过15位，允许最多两位小数)：");
        scanf("%s", char_1operand); //读取
        strcpy(ochar_1operand, char_1operand);
        dotLocation = getDotLocation(char_1operand); //得到小数点的位置（用于定位）
        num_1operandLen = dotLocation==0?strlen(char_1operand):dotLocation;
        lenWithoutDot = strlen(char_1operand); //原始长度（不算上小数点）
        if(convertToDecimal(char_1operand)){ //若为整数，末尾添加00；若为小数，*100
            //如果是小数
            lenWithoutDot -= 1;
        }
        if(!assertCharNumber(ochar_1operand, 13, 2) //检查数据是否符合规范
           || atof(ochar_1operand) < 1){ //整数部分不为0
            printf("输入数据不符合规范，请重新输入\n");
            errorHappened = true;
        }
    } while(errorHappened);

    char_2operand[14] = '0'; //存储开方结果
    numberToAbacusV2(num_2operand, strtod(ochar_2operand, nullptr));
    numberToAbacusV2(num_1operand, strtod(ochar_1operand, nullptr));

    initDrawingEnv();
    drawNumOnAbacusOfRadication(num_1operand, num_2operand); //初始化算盘
    simulateRadication(dotLocation,lenWithoutDot,num_1operandLen); //simulation

    drawRules("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

//初始化绘图环境
void initDrawingEnv() {
    initgraph(GraphSizeOfWidth, GraphSizeOfHeight); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
//    setcolor(BLACK); //设置前景颜色 never use it, it's awful!
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式
    setlinecolor(BLACK);
    settextcolor(BLACK);
}