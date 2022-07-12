//
// Created by andy on 2022/5/6.
//

#ifndef ABACUS_ADDITION_H
#define ABACUS_ADDITION_H

#include "base.h"

void drawAdditionMnemonicRhyme(); //绘制加法口诀表
void displayDraftCalculationOfAddition(); //显示列式计算的结果
void drawNumOnAbacusOfAddition(Num *sa); //绘制一个数的盘式
void simulateAddition(Num* au, Num* ad, int n); //可视化模拟一位加法

#endif //ABACUS_ADDITION_H
