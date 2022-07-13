#define _CRT_SECURE_NO_WARNINGS

#include "addition.h"


//绘制加法口诀表
void drawAdditionMnemonicRhyme()
{
    for (int i = 0; i < 12; ++i)
        line(50, 400 + 25 * i, 600, 400 + 25 * i);
    line(50, 400, 50, 675);
    line(100, 400, 100, 675);
    line(200, 400 + 25, 200, 675);
    line(300, 400, 300, 675);
    line(450, 400 + 25, 450, 675);
    line(600, 400, 600, 675);

    char a[][8] = { "加数", "一", "二", "三", "四" ,"五", "六", "七", "八", "九" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 50, 425 + 25 * i, 100, 450 + 25 * i };
        drawtext(a[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    RECT r = { 100, 400, 300, 425 };
    drawtext("不进位的加", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r1 = { 300, 400, 600, 425 };
    drawtext("进位的加", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    char b[11][12] = { "直加", "一上一", "二上二", "三上三", "四上四" ,"五上五", "六上六", "七上七", "八上八", "九上九" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 100, 425 + 25 * i, 200, 450 + 25 * i };
        drawtext(b[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char c[11][20] = { "满五加", "一下五去四", "二下五去三", "三下五去二", "四下五去一" };
    for (int i = 0; i < 5; ++i)
    {
        RECT r = { 200, 425 + 25 * i, 300, 450 + 25 * i };
        drawtext(c[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char d[11][20] = { "进十加", "一去九进一", "二去八进一", "三去七进一", "四去六进一" ,"五去五进一", "六去四进一", "七去三进一", "八去二进一", "九去一进一" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 300, 425 + 25 * i, 450, 450 + 25 * i };
        drawtext(d[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char e[11][32] = { "破五进十加", " ", " ", " ", " " ," ", "六上一去五进一", "七上二去五进一", "八上三去五进一", "九上四去五进一" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 450, 425 + 25 * i, 600, 450 + 25 * i };
        drawtext(e[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

//显示表达式计算的结果
void displayDraftCalculationOfAddition()
{
    setFontSizeTo32();
    double augNumber = atof(original_c_first_operand);
    double addNumber = atof(original_c_second_operand);
    stringGenerator<<augNumber<<"+"<<addNumber<<"="<<augNumber+addNumber;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawStrOfDisplayCalculationResult(strInfo);
    stringGenerator.str("");
    setFontSizeTo16();
}


//绘制一个数的盘式
void drawNumOnAbacusOfAddition(Num *sa)
{
    cleardevice(); //清空屏幕内容
    displayDraftCalculationOfAddition(); // 绘制列式计算的结果
    drawAbacus(sa,AbacusParams()); //绘制算盘
    drawAdditionMnemonicRhyme(); //绘制加法口诀表
}

//可视化模拟一位加法
void simulateAddition(Num* au, Num* ad, int n){
    Num* aug = &au[n];
    Num* add = &ad[n];
    Num* tmp = aug; //当前被加数的指针
    int augNumber = toNumberForm(aug); //被加数
    int addNumber = toNumberForm(add); //加数

    if (addNumber + augNumber <= 9){ //直接加或者凑五加
        if(augNumber<5&&addNumber<5&&addNumber+augNumber>=5){//凑五加：被加数下框离梁珠<加数 && 加数<5
            //凑五加：下五去凑五数
            tmp->upper += 1; //下五
            drawNumOnAbacusOfAddition(au);
            drawStrOfSize32("下五");
            _getch();
            tmp->lower -= 5 - addNumber;
            drawNumOnAbacusOfAddition(au);
            stringGenerator<<"去"<<INDEX_TO_CHINESE_NUM[5 - addNumber];
            strcpy(strInfo,stringGenerator.str().c_str());
            drawStrOfSize32(strInfo);
            stringGenerator.str("");
            _getch();
        }else{ //直接加
            tmp->upper += addNumber / 5;
            tmp->lower += addNumber % 5;
            drawNumOnAbacusOfAddition(au);
            stringGenerator<<"上"<<INDEX_TO_CHINESE_NUM[addNumber];
            strcpy(strInfo,stringGenerator.str().c_str());
            drawStrOfSize32(strInfo);
            stringGenerator.str("");
            _getch();
        }
    }else{ //进十加或者破五进十加
        int complement = 10-addNumber;//加数的补数
        /*先计算本位*/
        if(tmp->lower < complement && addNumber + augNumber != 10){//破五进十加：本档需用破五减
            //去五，上（5-补数）
            tmp->upper -= 1;
            drawNumOnAbacusOfAddition(au);
            drawStrOfSize32("去五");
            _getch();

            tmp->lower += 5 - complement;
            drawNumOnAbacusOfAddition(au);
            stringGenerator<<"上"<<INDEX_TO_CHINESE_NUM[5-complement];
        }else{ //进十加
            tmp->upper -= int(complement / 5);
            tmp->lower -= complement % 5;
            drawNumOnAbacusOfAddition(au);
            stringGenerator<<"去"<<INDEX_TO_CHINESE_NUM[complement];
        }
        strcpy(strInfo,stringGenerator.str().c_str());
        drawStrOfSize32(strInfo);
        stringGenerator.str("");
        _getch();

        /*再计算进位
         * 进一可能引起前面许多位都有进位，所以本质上是连续加法，使用递归调用解决此问题。
         * 这里当做另外一次加法来做，被加数：当前算盘的数，加数：1。
         * */
        CARRYNUM carryNumber(n+1);

        drawNumOnAbacusOfAddition(au);
        drawStrOfSize32("进一");
        _getch();
        simulateAddition(au, carryNumber.carry, n + 1);
    }
}

