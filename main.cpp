﻿//
// Created by andy on 2022/5/6.
//
#include "addition.h"
#include "subtraction.h"
#include "radication.h"

#define GraphSizeOfWidth 1200
#define GraphSizeOfHeight 1200

#define DEBUG 1
#ifdef DEBUG
#define _getch()
#define getchar()
#endif

void addition();
void subtraction();
void radication();

void menu(){
    printf("*******算盘的演算过程********\n");
    printf("1.加法\n");
    printf("2.减法\n");
    printf("3.乘法\n");
    printf("4.除法\n");
    printf("5.开方\n");
    printf("***************************\n");
}

int main()
{
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
            radication();
            break;
        case 4:
            radication();
            break;
        case 5:
            radication();
            break;
        default:
            exit(0);
    }
}

void subtraction() {
    int errorHappened = 0;
    int len1,len2;
    int maxLen;
    do{
        printf("请输入两个长度不超过14位的数(被减数和减数,被减数大于减数，允许两位小数)：");
        scanf("%s %s", c_first_operand, c_second_operand);
        strcpy(original_c_first_operand,c_first_operand);
        strcpy(original_c_second_operand,c_second_operand);
        convertToDecimal(c_first_operand);//判断是否为小数
        convertToDecimal(c_second_operand);
        len1 = strlen(c_first_operand);
        len2 = strlen(c_second_operand);
        maxLen = len1 > len2 ? len1 : len2;
        if (maxLen > 14){
            printf("您输入的数过大，请重新输入\n");
            errorHappened = 1;
        }
    } while(errorHappened);

    toAbacusForm(a_first_operand, c_first_operand, len1);
    toAbacusForm(a_second_operand, c_second_operand, len2);
    initgraph(GraphSizeOfWidth, GraphSizeOfHeight); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BLACK); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    drawNumOnAbacusOfSubtraction(a_first_operand); //初始化算盘（绘制算盘、列式、口诀表）

    getchar();
    for (int i = 0; i < maxLen; i++){ //从左到右按位依次减法
        getchar();
        if(toNumberForm(&a_first_operand[i]) != 0 || toNumberForm(&a_second_operand[i]) != 0){ //本位的加数和被加数不都为零
            simulateSubtraction(a_first_operand, a_second_operand, i);
        }
    }

    drawStrOfSize32("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void addition() {
    int errorHappened = 0;
    int len1,len2;
    int maxLen;
   do{
        printf("请输入两个长度不超过14位的数(被加数和加数，允许两位小数)：");
        scanf("%s %s", c_first_operand, c_second_operand);
        strcpy(original_c_first_operand,c_first_operand);
        strcpy(original_c_second_operand,c_second_operand);
        convertToDecimal(c_first_operand);//判断是否为小数
        convertToDecimal(c_second_operand);
        len1 = strlen(c_first_operand);
        len2 = strlen(c_second_operand);
        maxLen = len1 > len2 ? len1 : len2;
        if (maxLen > 14){
            printf("您输入的数过大，请重新输入\n");
            errorHappened = 1;
        }
    } while(errorHappened);

    toAbacusForm(a_first_operand, c_first_operand, len1);
    toAbacusForm(a_second_operand, c_second_operand, len2);
    initgraph(GraphSizeOfWidth, GraphSizeOfHeight); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BLACK); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    drawNumOnAbacusOfAddition(a_first_operand); //初始化算盘（绘制算盘、列式、口诀表）

    getchar();
    for (int i = 0; i < maxLen; i++){ //从右到左按位依次加法
        getchar();
        if(toNumberForm(&a_first_operand[i]) != 0 || toNumberForm(&a_second_operand[i]) != 0){ //本位的加数和被加数不都为零
            simulateAddition(a_first_operand, a_second_operand, i);
        }
    }

    drawStrOfSize32("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void radication(){
    int errorHappened; //true如果用户输入的数字位数>14
    int originalLen; //用户输入的数字的原始长度
    int lenWithoutDot; //去掉小数点后的长度
    int convertedLen; //*100之后的长度
    size_t dotLocation; //小数点在第dotLocation位数字的后面
//    char original_c_first_operand[PLACES_NUM+1]; //未去掉小数点的cstr
    do{
        printf("请输入被开方数(允许两位小数)：");
        scanf("%s", c_first_operand); //读取
        strcpy(original_c_first_operand, c_first_operand);
        dotLocation = getDotLocation(c_first_operand); //得到小数点的位置（用于后面的定位）
        lenWithoutDot = originalLen = strlen(c_first_operand); //原始长度（不算上小数点）
        if(convertToDecimal(c_first_operand)){ //若为整数，末尾添加00；若为小数，*100
            //如果是小数
            lenWithoutDot -= 1;
        }
        convertedLen = strlen(c_first_operand);
        toAbacusForm(a_first_operand, c_first_operand, convertedLen); //转为算盘形式

        if (convertedLen > 14){
            printf("您输入的数过大，请重新输入\n");
            errorHappened = true;
        }else{
            errorHappened = false;
        }
    } while(errorHappened);

    initgraph(GraphSizeOfWidth, GraphSizeOfHeight); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BLACK); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    c_second_operand[14] = '0'; //存储开方结果
    convertToDecimal(c_second_operand);
    toAbacusForm(a_second_operand, c_second_operand, 1);

    drawNumOnAbacusOfRadication(a_first_operand, a_second_operand); //初始化算盘

    // simulation
    simulateRadication(original_c_first_operand,dotLocation,lenWithoutDot,convertedLen);

    drawStrOfSize32("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

