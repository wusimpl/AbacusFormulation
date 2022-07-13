//
// Created by andy on 2022/5/26.
//

#ifndef ABACUS_RADICATION_H
#define ABACUS_RADICATION_H

#include "base.h"

void drawNumOnAbacusOfRadication(Num *sa, Num* result);
void simulateRadication(char* original_c_first_operand,size_t dotLocation,int originalLen, int convertedLen);
size_t getDotLocation(const char* cStr);
void getHead(const char *strNum, int length, size_t dotLocation, char *head);
void drawExpressionOfRadication();
#endif //ABACUS_RADICATION_H
