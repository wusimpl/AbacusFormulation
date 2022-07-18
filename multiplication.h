//
// Created by andy on 2022/7/18.
//

#ifndef ABACUS_MULTIPLICATION_H
#define ABACUS_MULTIPLICATION_H

#include "base.h"

void drawExpressionOfMultiplication();
void drawNumOnAbacusOfMultiplication(Num*);
void lookUpMultiplicationTable(int fac, int mul, int placeOfFirstDigit, Num* product);
void simulateMultiplication(Num* result, int len1, int len2);

#endif //ABACUS_MULTIPLICATION_H
