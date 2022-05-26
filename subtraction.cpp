//
// Created by andy on 2022/5/6.
//
#include "subtraction.h"

void displayDraftCalculationOfSubtraction(){//显示被减数、减数、结果
    RECT r1 = {900, 100, 1000, 125};
    char ta[17];
    sprintf(ta, "%.2f", atoi(c_first_operand) * 1.0 / 100);
    drawtext(ta, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    char tmp[17];
    sprintf(tmp, "-%17.2f", atoi(c_second_operand) * 1.0 / 100);
    RECT r2 = {900, 125, 1000, 150};
    drawtext(tmp, &r2, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    line(900, 150, 1000, 150);
    RECT r3 = {900, 150, 1000, 175};
    int ans = atoi(c_first_operand) - atoi(c_second_operand);
    char tans[17];
    sprintf(tans, "%.2f", ans * 1.0 / 100);
    drawtext(tans, &r3, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

    //显示个位位置
    RECT r4 = {692, 25, 707, 50};
    char m[6] = "个";
    drawtext(m, &r4, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    RECT r5 = {692, 50, 707, 75};
    char n[10] = "位";
    drawtext(n, &r5, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
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
    displayDraftCalculationOfSubtraction(); // 绘制列式计算的结果
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

    if (meiNumber + miNumber <= 9){ //直接减或者凑五减
        if(4-(mi->low) < meiNumber && meiNumber < 5){//凑五减：被减数下框离梁珠<减数 && 减数<5
            //凑五减：下五去凑五数
            tmp->high += 1; //下五
            drawNumOnAbacusOfSubtraction(minuend);
            drawStr("下五");
            getchar();
            tmp->low -= 5 - meiNumber; //去凑五数
            drawNumOnAbacusOfSubtraction(minuend);
            processHintPlaceHolder = (stringstream()<<"去"<<INDEX_TO_CHINESE_NUM[5 - meiNumber]).str();
            drawStr(processHintPlaceHolder.c_str());
            getchar();
        }else{ //直接减
            //直接减：减数>=5则梁上下五，梁下上减数-5；减数<5则梁下上减数
            if(meiNumber >= 5){
                tmp->high += 1;
                drawNumOnAbacusOfSubtraction(minuend);
                drawStr("下五");
                getchar();
                tmp->low += meiNumber - 5;
                processHintPlaceHolder = (stringstream()<<"上"<<INDEX_TO_CHINESE_NUM[meiNumber - 5]).str();
            }else{
                tmp->low += meiNumber;
                processHintPlaceHolder = (stringstream()<<"上"<<INDEX_TO_CHINESE_NUM[meiNumber]).str();

            }
            drawNumOnAbacusOfSubtraction(minuend);
            drawStr(processHintPlaceHolder.c_str());
            getchar();
        }
    }else{ //进十减或者破五进十减
        int complement = 10 - meiNumber;//减数的补数
        /*先计算本位*/
        if(tmp->low < complement && meiNumber + miNumber != 10){//破五进十减：被减数下框入珠数小于补数
            //去五，上（5-补数）
            tmp->high -= 1;
            drawNumOnAbacusOfSubtraction(minuend);
            drawStr("去五");
            getchar();

            tmp->low += 5-complement;
            processHintPlaceHolder = (stringstream()<<"上"<<INDEX_TO_CHINESE_NUM[5-complement]).str();
        }else{ //进十减
            //去补
            tmp->high -= int(complement/5);
//            drawNumOnAbacusOfAddition(minuend);
//            getchar();
            tmp->low -= complement%5;
            processHintPlaceHolder = (stringstream()<<"去"<<INDEX_TO_CHINESE_NUM[complement]).str();
        }
        drawNumOnAbacusOfSubtraction(minuend);
        drawStr(processHintPlaceHolder.c_str());
        getchar();

        /*再计算借位
         * 进一可能引起前面许多位都有进位，所以本质上是连续减法，使用递归调用解决此问题。
         * 这里当做另外一次减法来做，被减数：当前算盘的数，减数：1。
         * */
//        CARRYNUM carryNumber(n+1);
//
//        drawNumOnAbacusOfAddition(minuend);
//        drawStr("进一");
//        getchar();
//        simulateAddition(minuend, carryNumber.carry, n + 1);
    }
}
