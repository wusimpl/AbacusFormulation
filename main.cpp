//
// Created by andy on 2022/5/6.
//
#include "addition.h"
#include "subtraction.h"

void addition();

void subtraction();

void menu(){
    printf("*******算盘的演算过程********\n");
    printf("1.加法\n");
    printf("2.减法\n");
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
        default:
            exit(0);
    }
}

void subtraction() {
    int errorFlag = 0;
    int len1,len2;
    int maxLen;
    do{
        printf("请输入两个长度不超过14位的数(被减数和减数,被减数大于减数，允许两位小数)：");
        scanf("%s %s", c_first_operand, c_second_operand);
        isDecimal(c_first_operand);//判断是否为小数
        isDecimal(c_second_operand);
        len1 = strlen(c_first_operand);
        len2 = strlen(c_second_operand);
        maxLen = len1 > len2 ? len1 : len2;
        if (maxLen > 14){
            printf("您输入的数过大，请重新输入\n");
            errorFlag = 1;
        }
    } while(errorFlag);

    toAbacusForm(first_operand, c_first_operand, len1);
    toAbacusForm(second_operand, c_second_operand, len2);
    initgraph(1100, 700); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BROWN); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    drawNumOnAbacusOfSubtraction(first_operand); //初始化算盘（绘制算盘、列式、口诀表）

    getchar();
    for (int i = 0; i < maxLen; i++){ //从左到右按位依次减法
        getchar();
        if(toNumberForm(&first_operand[i]) != 0 || toNumberForm(&second_operand[i]) != 0){ //本位的加数和被加数不都为零
            simulateSubtraction(first_operand, second_operand, i);
        }
    }

    drawStr("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void addition() {
    int errorFlag = 0;
    int len1,len2;
    int maxLen;
   do{
        printf("请输入两个长度不超过14位的数(被加数和加数，允许两位小数)：");
        scanf("%s %s", c_first_operand, c_second_operand);
        isDecimal(c_first_operand);//判断是否为小数
        isDecimal(c_second_operand);
        len1 = strlen(c_first_operand);
        len2 = strlen(c_second_operand);
        maxLen = len1 > len2 ? len1 : len2;
        if (maxLen > 14){
            printf("您输入的数过大，请重新输入\n");
            errorFlag = 1;
        }
    } while(errorFlag);

    toAbacusForm(first_operand, c_first_operand, len1);
    toAbacusForm(second_operand, c_second_operand, len2);
    initgraph(1100, 700); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BROWN); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    drawNumOnAbacusOfAddition(first_operand); //初始化算盘（绘制算盘、列式、口诀表）

    getchar();
    for (int i = 0; i < maxLen; i++){ //从左到右按位依次加法
        getchar();
        if(toNumberForm(&first_operand[i]) != 0 || toNumberForm(&second_operand[i]) != 0){ //本位的加数和被加数不都为零
            simulateAddition(first_operand, second_operand, i);
        }
    }

    drawStr("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}


