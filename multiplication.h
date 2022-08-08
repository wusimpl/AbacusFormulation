//
// Created by andy on 2022/7/18.
//

#ifndef ABACUS_MULTIPLICATION_H
#define ABACUS_MULTIPLICATION_H

#include "base.h"

void drawExpressionOfMultiplication();
void drawNumOnAbacusOfMultiplication(Num*);
void lookUpMultiplicationTable(int _product, int indexOfFirstDigit, Num* product);
void lookUpMultiplicationTableDivisionVersion(int _product, int indexOfFirstDigit, Num* product);
void simulateMultiplication(Num* result, int integerLen1, int integerLen2);
void simulateMultiplicationPureVersion(Num *fac, Num* mul,Num* result, int integerLen1, int integerLen2);
void drawMultiplicationRhymeProduct(const char* oneToNExpressionStrInfo,const char* str);
void draw1toNExpression(const char* str);

#endif //ABACUS_MULTIPLICATION_H
