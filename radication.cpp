//
// Created by andy on 2022/5/26.
//

#include "radication.h"
#include <cmath>

void drawNumOnAbacusOfRadication(Num *sa, Num* result) {
    cleardevice(); //清空屏幕内容
    drawAbacus(sa,AbacusParams()); //绘制第一个算盘，用于展示余数的变化
    AbacusParams param = {{50,400},
                          800,
                          100,
                          275,
                          50,
                          12.5,
                          12.5,
                          13};
    drawAbacus(result, param); //绘制第二个算盘，用于展示开方结果的变化
}

void simulateRadication(size_t dotLocation,int originalLen, int convertedLen){
    int integralDigitsCount = 0; //开方结果的整数的位数
    //根据小数点的位置确定integralDigitsCount
    if(dotLocation == 0){//整数
        integralDigitsCount = ceil(originalLen/2.0); //上取整
    }else{//小数
        integralDigitsCount = ceil(dotLocation/2.0);
    }

}

size_t getDotLocation(const char cStr[]){
    for (int i = 0; i < 15; ++i) {
        if(cStr[i]=='.'){
            return i;
        }else if(cStr[i] == '\0'){
            return 0;
        }
    }
    return 0;
}