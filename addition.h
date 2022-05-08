//
// Created by andy on 2022/5/6.
//

#ifndef ABACUS_ADDITION_H
#define ABACUS_ADDITION_H

#include "base.h"



typedef struct CARRYNUM{
    Num carry[PLACES_NUM];

    CARRYNUM(int digit){ //digit belongs to 0-14
        for(int i=0;i<PLACES_NUM;i++){
            carry[i] = {0,0};
        }
        carry[digit] = {0,1};
    }
}CARRYNUM;

void drawAdditionMnemonicRhyme(); //绘制加法口诀表
void displayDraftCalculationOfAddition(); //显示列式计算的结果
void drawNumOnAbacusOfAddition(Num *sa); //绘制一个数的盘式
void simulateAddition(Num* au, Num* ad, int n); //可视化模拟一位加法

#endif //ABACUS_ADDITION_H
