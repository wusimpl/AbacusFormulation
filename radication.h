﻿//
// Created by andy on 2022/5/26.
//

#ifndef ABACUS_RADICATION_H
#define ABACUS_RADICATION_H

#include "base.h"

void drawNumOnAbacusOfRadication(Num *sa, Num* result);
void simulateRadication(size_t dotLocation,int originalLen, int convertedLen);
size_t getDotLocation(const char* cStr);

#endif //ABACUS_RADICATION_H
