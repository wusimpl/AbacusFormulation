//
// Created by andy on 2022/7/23.
//

#ifndef ABACUS_DIVISION_H
#define ABACUS_DIVISION_H

#include "base.h"
void drawExpressionOfDivision();
void drawNumOnAbacusOfDivision(Num*);
void lookUpDivisionTable(int _product, int placeOfFirstDigit, Num* product);
void simulateDivision(size_t integerLen1, size_t integerLen2);
void drawDivisionRhymeProduct(const char* oneToNExpressionStrInfo,const char* str);
void draw1toNExpression(const char* str);

#endif //ABACUS_DIVISION_H
