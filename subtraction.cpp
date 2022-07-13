//
// Created by andy on 2022/5/6.
//
#include "subtraction.h"
#include "addition.h"

void displayCalculationResultOfSubtraction(){//显示被减数、减数、结果
    setFontSizeTo32();
    double miNumber = atof(original_c_first_operand);
    double meiNumber = atof(original_c_second_operand);
    stringGenerator << miNumber << "-" << meiNumber << "=" << miNumber - meiNumber;
    strcpy(strInfo,stringGenerator.str().c_str());
    drawStrOfDisplayCalculationResult(strInfo);
    stringGenerator.str("");
    setFontSizeTo16();
}

void drawSubtractionMnemonicRhyme()  ///减法口诀表
{
    for(int i=0;i<12;++i)
        line(50,400+25*i,600,400+25*i);
    line(50,400,50,675);
    line(100,400,100,675);
    line(200,400+25,200,675);
    line(300,400,300,675);
    line(450,400+25,450,675);
    line(600,400,600,675);

    char a[11][8] = {"减数", "一", "二", "三", "四" ,"五", "六", "七", "八", "九"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {50, 425+25*i, 100, 450+25*i};
        drawtext(a[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    RECT r = {100, 400, 300, 425};
    drawtext("不退位的减", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r1 = {300, 400, 600, 425};
    drawtext("退位的减", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    char b[11][12] = {"直减", "一下一", "二下二", "三下三", "四下四" ,"五下五", "六下六", "七下七", "八下八", "九下九"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {100, 425+25*i, 200, 450+25*i};
        drawtext(b[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char c[11][20] = {"满五减", "一上四去五", "二上三去五", "三上二去五", "四上一去五" };
    for(int i = 0;i<5;++i)
    {
        RECT r = {200, 425+25*i, 300, 450+25*i};
        drawtext(c[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char d[11][20] = {"退位减", "一退一还九", "二退一还八", "三退一还七", "四退一还六" ,"五退一还五", "六退一还四", "七退一还三", "八退一还二", "九退一还一"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {300, 425+25*i, 450, 450+25*i};
        drawtext(d[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char e[11][24] = {"退十补五的减", " ", " ", " ", " " ," ", "六退一还五去一", "七退二还五去一", "八退三还五去一", "九退四还五去一"};
    for(int i = 0;i<10;++i)
    {
        RECT r = {450, 425+25*i, 600, 450+25*i};
        drawtext(e[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

void drawNumOnAbacusOfSubtraction(Num *sa)
{
    cleardevice(); //清空屏幕内容
    displayCalculationResultOfSubtraction(); // 绘制列式计算的结果
    drawAbacus(sa,AbacusParams()); //绘制算盘
    drawSubtractionMnemonicRhyme(); //绘制减法口诀表
}

//可视化模拟一位减法
void simulateSubtraction(Num* minuend, Num* meiosis, int n){
    Num* mi = &minuend[n];
    Num* mei = &meiosis[n];
    Num* tmp = mi; //当前被减数的指针
    int miNumber = toNumberForm(mi); //被减数
    int meiNumber = toNumberForm(mei); //减数

    if (miNumber >= meiNumber){ //不退位减
        if(miNumber>=5 && meiNumber<5 && meiNumber > (miNumber-5)){//破五减
            tmp->upper -= 1; //去五
            drawNumOnAbacusOfSubtraction(minuend);
            drawStrOfSize32("去五");
            _getch();
            tmp->lower += 5 - meiNumber; //上（5-减数）
            drawNumOnAbacusOfSubtraction(minuend);
            stringGenerator<<"上"<<INDEX_TO_CHINESE_NUM[5 - meiNumber];
            strcpy(strInfo,stringGenerator.str().c_str());
            drawStrOfSize32(strInfo);
            stringGenerator.str("");
            _getch();
        }else{ //直接减
            tmp->upper -= mei->upper;
            tmp->lower -= mei->lower;
            drawNumOnAbacusOfSubtraction(minuend);
            stringGenerator<<"去"<<INDEX_TO_CHINESE_NUM[meiNumber];
            strcpy(strInfo,stringGenerator.str().c_str());
            drawStrOfSize32(strInfo);
            stringGenerator.str("");
            _getch();
        }
    }else{ //退位减
        int complement = 10 - meiNumber;//减数的补数
        /*先计算本位*/
        if(meiNumber>5&&tmp->upper==0){//退十还五减
            tmp->upper += 1; //还五
            drawNumOnAbacusOfSubtraction(minuend);
            drawStrOfSize32("还五");
            _getch();
            tmp->lower -= meiNumber - 5;
            drawNumOnAbacusOfSubtraction(minuend);
            stringGenerator<<"去"<<INDEX_TO_CHINESE_NUM[meiNumber-5];
        }else{ //退十减
            tmp->upper += int(complement / 5);
            tmp->lower += complement % 5;
            drawNumOnAbacusOfSubtraction(minuend);
            stringGenerator<<"还"<<INDEX_TO_CHINESE_NUM[complement];
        }
        strcpy(strInfo,stringGenerator.str().c_str());
        drawStrOfSize32(strInfo);
        stringGenerator.str("");
        _getch();

        /*再计算借位
         * 退一可能引起前面许多位都有借位，所以本质上是连续减法，使用递归调用解决此问题。
         * 这里当做另外一次减法来做，被减数：当前算盘的数，减数：1。
         * */
        CARRYNUM carryNumber(n+1);

        drawNumOnAbacusOfSubtraction(minuend);
        drawStrOfSize32("退一");
        _getch();
        simulateSubtraction(minuend, carryNumber.carry, n + 1);
    }
}
