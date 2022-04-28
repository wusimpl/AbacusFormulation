#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <cstdio>
#include <Windows.h>
#include <cstring>
#include<graphics.h>
#include <conio.h>
using namespace std;

#define PLACES_NUM 15 //挡位数
#define MAX_NUM_OF_PLACE 9 //一档所能表示的最大数

//表示算盘上的一档
typedef struct
{
    int high; //梁上入珠数
    int low; //梁下入珠数
} Num;

Num ab_augend[PLACES_NUM], ab_addend[PLACES_NUM]; //数的算盘形式
char augend[PLACES_NUM], addend[PLACES_NUM]; //数的形式

typedef struct CARRYNUM{
    Num carry[PLACES_NUM];

    CARRYNUM(int digit){ //digit belongs to 0-14
        for(int i=0;i<PLACES_NUM;i++){
            carry[i] = {0,0};
        }
        carry[digit] = {0,1};
    }
}CARRYNUM;
//绘制算珠（椭圆形状）
void drawOneBead(float x, float y)
{
    fillellipse(x - 20, y - 12.5, x + 20, y + 12.5); //left:椭圆外切矩形的左上角 x 坐标
}

//绘制加法口诀表
void drawAdditionMnemonicRhyme()
{
    for (int i = 0; i < 12; ++i)
        line(50, 400 + 25 * i, 600, 400 + 25 * i);
    line(50, 400, 50, 675);
    line(100, 400, 100, 675);
    line(200, 400 + 25, 200, 675);
    line(300, 400, 300, 675);
    line(450, 400 + 25, 450, 675);
    line(600, 400, 600, 675);

    char a[][8] = { "加数", "一", "二", "三", "四" ,"五", "六", "七", "八", "九" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 50, 425 + 25 * i, 100, 450 + 25 * i };
        drawtext(a[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
    RECT r = { 100, 400, 300, 425 };
    drawtext("不进位的加", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r1 = { 300, 400, 600, 425 };
    drawtext("进位的加", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    char b[11][12] = { "直加", "一上一", "二上二", "三上三", "四上四" ,"五上五", "六上六", "七上七", "八上八", "九上九" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 100, 425 + 25 * i, 200, 450 + 25 * i };
        drawtext(b[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char c[11][20] = { "满五加", "一下五去四", "二下五去三", "三下五去二", "四下五去一" };
    for (int i = 0; i < 5; ++i)
    {
        RECT r = { 200, 425 + 25 * i, 300, 450 + 25 * i };
        drawtext(c[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char d[11][20] = { "进十加", "一去九进一", "二去八进一", "三去七进一", "四去六进一" ,"五去五进一", "六去四进一", "七去三进一", "八去二进一", "九去一进一" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 300, 425 + 25 * i, 450, 450 + 25 * i };
        drawtext(d[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }

    char e[11][32] = { "破五进十加", " ", " ", " ", " " ," ", "六上一去五进一", "七上二去五进一", "八上三去五进一", "九上四去五进一" };
    for (int i = 0; i < 10; ++i)
    {
        RECT r = { 450, 425 + 25 * i, 600, 450 + 25 * i };
        drawtext(e[i], &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

//显示列式计算的结果
void displayDraftCalculation()
{ //显示被加数、加数、结果
    RECT r1 = { 900, 100, 1000, 125 };
    char ta[17];
    sprintf(ta, "%.2f", atoi(augend) * 1.0 / 100);
    drawtext(ta, &r1, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    char tmp[190];
    sprintf(tmp, "+%17.2f", atoi(addend) * 1.0 / 100);

    RECT r2 = { 900, 125, 1000, 150 };
    drawtext(tmp, &r2, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    line(900, 150, 1000, 150);
    RECT r3 = { 900, 150, 1000, 175 };
    int ans = atoi(augend) + atoi(addend);
    //	char sans[10];
    //	itoa(ans, sans, 10);
    char tans[17];
    sprintf(tans, "%.2f", ans * 1.0 / 100);
    drawtext(tans, &r3, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

    //显示个位位置
    RECT r4 = { 692, 25, 707, 50 };
    char m[6] = "个";
    drawtext(m, &r4, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
    RECT r5 = { 692, 50, 707, 75 };
    char n[10] = "位";
    drawtext(n, &r5, DT_VCENTER | DT_RIGHT | DT_SINGLELINE);
}

//绘制算盘
void drawAbacus(Num *sa) {
    int k;
    line(50, 100, 850, 100); //上框
    line(50, 200, 850, 200); //中框（梁）
    line(50, 375, 850, 375); //下框
    fillellipse(725 - 5, 200 - 5, 725 + 5, 200 + 5); //小数点

    for (int i = 0; i < 17; ++i) //左框+右框+档
    {
        line(50 + i * 50, 100, 50 + i * 50, 375);
    }

    for (int i = 0, j = 14; i < PLACES_NUM; ++i, --j) //绘制梁上算珠
    {
        for (k = 0; k < sa[j].high; ++k) //未入珠
            drawOneBead(100 + 50 * i, 187.5 - 25 * k);
        for (k = 0; k < 1 - sa[j].high; ++k) //入珠
            drawOneBead(100 + 50 * i, 112.5 + 25 * k);
    }

    for (int i = 0, j = 14; i < PLACES_NUM; ++i, --j) //绘制梁下算珠
    {
        for (int k = 0; k < sa[j].low; ++k) //入珠
            drawOneBead(100 + 50 * i, 212.5 + 25 * k);
        for (int k = 0; k < 4 - sa[j].low; ++k) //未入珠
            drawOneBead(100 + 50 * i, 362.5 - 25 * k);
    }
    drawAdditionMnemonicRhyme(); //绘制加法口诀表
}

//绘制一个数的盘式
void initialize(Num *sa)
{
    cleardevice(); //清空屏幕内容
    displayDraftCalculation(); // 绘制列式计算的结果
    drawAbacus(sa); //绘制算盘
}

//阿拉伯数字转换为算盘式数字
void toAbacusForm(Num *s, char *t, int len)
{
    for (int i = len - 1, k = 0; i >= 0; i--, k++)
    {
        int x = t[i] - '0';
        s[k].high = x / 5;
        s[k].low = x % 5;
    }
}

//算盘某档转为阿拉伯数字
int toNumberForm(Num *s){
    return s->high*5 + s->low;
}

//可视化模拟一位加法
void simulate(Num* au, Num* ad, int n){
    Num* aug = &au[n];
    Num* add = &ad[n];
    Num* tmp = aug; //当前被加数的指针
    int augNumber = toNumberForm(aug); //被加数
    int addNumber = toNumberForm(add); //加数

    if (addNumber + augNumber <= 9){ //直接加或者凑五加
        if(4-(aug->low) < addNumber && addNumber<5){//凑五加：被加数下框离梁珠<加数 && 加数<5
            //凑五加：下五去凑五数
            tmp->high += 1; //下五
            tmp->low -= 5-addNumber; //去凑五数
            initialize(au);
            getchar();
        }else{ //直接加
            //直接加：加数>=5则梁上下五，梁下上加数-5；加数<5则梁下上加数
            if(addNumber >=5){
                tmp->high += 1;
                tmp->low += addNumber - 5;
            }else{
                tmp->low += addNumber;
            }
            initialize(au);
            getchar();
        }
    }else{ //进十加或者破五进十加
        int complement = 10-addNumber;//加数的补数
        /*先计算本位*/
        if(tmp->low < complement){//破五进十加：被加数下框入珠数小于补数
            //去五，上（5-补数）
            tmp->high -= 1;
            tmp->low += 5-complement;
        }else{ //进十加
            //去补
            tmp->high -= int(complement/5);
            tmp->low -= complement%5;
        }
        initialize(au);
        getchar();

        /*再计算进位
         * 进一可能引起前面许多位都有进位，所以本质上是连续加法，使用递归调用解决此问题。
         * 这里当做另外一次加法来做，被加数：当前算盘的数，加数：1。
         * */
        CARRYNUM carryNumber(n+1);
        simulate(au,carryNumber.carry,n+1);
    }

}

//判断是否为小数,如果为小数，则去掉小数点
void isDecimal(char *x)
{
    int i;
    for (i = 0; i < strlen(x); i++)
        if (x[i] == '.')
        {
            x[i] = x[i + 1];
            if (x[i + 2] == '\0')
                x[i + 1] = '0';
            x[i + 1] = x[i + 2];
            x[i + 2] = '\0';
            return;
        }
    x[i] = x[i + 1] = '0';
    x[i + 2] = '\0';
}

void drawFinished(){
    RECT r1 = { 900, 250, 1000, 275 };
//    initialize(ab_augend);
    drawtext("计算结束", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

int main()
{
    printf("\n*******算盘加法的演算过程********\n请输入两个长度不超过14位的数(被加数和加数，允许两位小数)：");
    scanf("%s %s", augend, addend);
    isDecimal(augend);//判断是否为小数
    isDecimal(addend);
    int len1 = strlen(augend);
    int len2 = strlen(addend);
    int len = len1 > len2 ? len1 : len2;
    if (len > 14){
        printf("您输入的数过大！\n");
        return -1;
    }

    toAbacusForm(ab_augend, augend, len1);
    toAbacusForm(ab_addend, addend, len2);
    initgraph(1100, 700); //初始化绘图环境
    setbkcolor(WHITE); //设置背景颜色
    setcolor(BROWN); //设置前景颜色
    setfillstyle(BLACK); //设置填充样式
    setlinestyle(PS_SOLID, 2); //设置直线样式

    initialize(ab_augend); //初始化算盘（绘制算盘、列式、口诀表）


    for (int i = 0; i < len; i++){ //从左到右按位依次加法
//        simulateAbacusAddition(ab_augend, ab_addend, i);
        getchar();
        if(toNumberForm(&ab_augend[i]) !=0 || toNumberForm(&ab_addend[i]) != 0){ //本位的加数和被加数不都为零
            simulate(ab_augend,ab_addend,i);
        }
    }

    drawFinished(); //绘制“计算结束”
    _getch(); //按任意键继续
    closegraph(); //释放绘图资源
}

