//
// Created by andy on 2022/5/6.
//
#include "addition.h"
#include "subtraction.h"
#include "radication.h"

void addition();
void subtraction();
void radication();

void menu(){
    printf("*******算盘的演算过程********\n");
    printf("1.加法\n");
    printf("2.减法\n");
    printf("3.开方\n");
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
    int errorHappened = 0;
    int len1,len2;
    int maxLen;
   do{
        printf("请输入两个长度不超过14位的数(被加数和加数，允许两位小数)：");
        scanf("%s %s", c_first_operand, c_second_operand);
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

    toAbacusForm(first_operand, c_first_operand, len1);
    toAbacusForm(second_operand, c_second_operand, len2);
    initgraph(1100, 700); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BROWN); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    drawNumOnAbacusOfAddition(first_operand); //初始化算盘（绘制算盘、列式、口诀表）

    getchar();
    for (int i = 0; i < maxLen; i++){ //从右到左按位依次加法
        getchar();
        if(toNumberForm(&first_operand[i]) != 0 || toNumberForm(&second_operand[i]) != 0){ //本位的加数和被加数不都为零
            simulateAddition(first_operand, second_operand, i);
        }
    }

    drawStr("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

void radication(){
    int errorHappened = 0;
    int originalLen = 0;
    int convertedLen=0;
    size_t dotLocation = 0; //小数点在第dotLocation位数字的后面
    char c_original_first_operand[PLACES_NUM+1]; //未去掉小数点的cstr
    do{
        printf("请输入被开方数(允许两位小数)：");
        scanf("%s", c_first_operand); //读取
        strcpy(c_original_first_operand, c_first_operand);
        dotLocation = getDotLocation(c_first_operand); //得到小数点的位置（用于后面的定位）
//        cout<<"dotLocation:"<<dotLocation<<endl;
        originalLen = strlen(c_first_operand)-1; //原始长度（不算上小数点）
        convertToDecimal(c_first_operand);//若为整数，末尾添加00；若为小数，*100
        convertedLen = strlen(c_first_operand);
//        cout << "convertedLen:" << convertedLen << endl;
        toAbacusForm(first_operand, c_first_operand, convertedLen); //转为算盘形式

        if (convertedLen > 14){
            printf("您输入的数过大，请重新输入\n");
            errorHappened = 1;
        }
    } while(errorHappened);

    initgraph(1100, 700); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BROWN); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    c_second_operand[14] = '0'; //存储开方结果
    convertToDecimal(c_second_operand);
    toAbacusForm(second_operand,c_second_operand,1);

    drawNumOnAbacusOfRadication(first_operand,second_operand); //初始化算盘（绘制算盘、列式、口诀表）

    // simulation
    simulateRadication(c_original_first_operand,dotLocation,originalLen,convertedLen);

    drawStr("计算结束"); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

