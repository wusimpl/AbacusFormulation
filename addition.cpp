#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include<graphics.h>
#include <conio.h>

using namespace std;

//表示算盘上的一档
typedef struct
{
    int high; //梁上入珠数
    int low; //梁下入珠数
} Num;
Num ab_augend[15], ab_addend[15]; //数的算盘形式
char augend[15], addend[15]; //数的形式

//绘制算珠（椭圆形状）
void drawOneBead(float x, float y)
{
    fillellipse(x - 20, y - 12.5, x + 20, y + 12.5); //left:椭圆外切矩形的左上角 x 坐标
}


void addpro()  ///加法口诀表
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

void show()
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

void initial(Num sa[])    //初始化
{
    cleardevice();
    show();
    int i, j, k;
    line(50, 100, 850, 100);
    line(50, 200, 850, 200);
    line(50, 375, 850, 375);
    fillellipse(725 - 5, 200 - 5, 725 + 5, 200 + 5);

    for (int i = 0; i < 17; ++i)
    {
        line(50 + i * 50, 100, 50 + i * 50, 375);
    }

    for (int i = 0, j = 14; i < 15; ++i, --j)
    {
        for (k = 0; k < sa[j].high; ++k)
            drawOneBead(100 + 50 * i, 187.5 - 25 * k);
        for (k = 0; k < 2 - sa[j].high; ++k)
            drawOneBead(100 + 50 * i, 112.5 + 25 * k);
    }

    for (int i = 0, j = 14; i < 15; ++i, --j)
    {
        for (k = 0; k < sa[j].low; ++k)
            drawOneBead(100 + 50 * i, 212.5 + 25 * k);
        for (k = 0; k < 5 - sa[j].low; ++k)
            drawOneBead(100 + 50 * i, 362.5 - 25 * k);
    }
    addpro();
}

void toAbacusForm(Num *s, char *t, int len)  //阿拉伯数字转换为算盘式数字
{
    for (int i = len - 1, k = 0; i >= 0; i--, k++)
    {
        int x = t[i] - '0';
        s[k].high = x / 5;
        s[k].low = x % 5;
    }
}

void add(Num sa[], Num sb[], int n)   //加法
{
    int high = sa[n].high;
    int low = sa[n].low;
    int h = sb[n].high;
    int l = sb[n].low;
    int th = high + h;
    int tl = low + l;
    char shuwei[12][8] = { "百分", "十分", "个", "十", "百", "千", "万", "十万", "百万", "千万", "亿", "十亿" };
    char s[12];
    strcpy(s, shuwei[n]);
    strcat(s, "位相加");

    if (tl == 5)
    {
        sa[n].low = 5;
        initial(sa);
        RECT r1 = { 900, 250, 1000, 275 };
        drawtext(s, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        //Sleep(1000);
        getchar();
    }

    low = tl % 5;
    int r = (th + tl / 5) / 2;
    high = (th + tl / 5) % 2;
    sa[n].low = low;

    if ((th + tl / 5) == 2)
    {
        sa[n].high = 2;
        initial(sa);
        RECT r1 = { 900, 250, 1000, 275 };
        drawtext(s, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        //Sleep(1000);
        getchar();
    }

    sa[n].high = high;


    initial(sa);
    RECT r1 = { 900, 250, 1000, 275 };
    drawtext(s, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    //Sleep(1000);
    getchar();

    int i = n + 1;
    while (r > 0)
    {
        int h1 = sa[i].high;
        int l1 = sa[i].low;
        char s1[12];
        strcpy(s1, shuwei[i]);
        strcat(s1, "位进位");


        if ((l1 + r) == 5)
        {
            sa[i].low = 5;
            initial(sa);
            RECT r1 = { 900, 250, 1000, 275 };
            drawtext(s, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            RECT r2 = { 900, 275, 1000, 300 };
            drawtext(s1, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            //Sleep(1000);
            getchar();
        }

        h1 = h1 + (l1 + r) / 5;
        l1 = (l1 + r) % 5;
        sa[i].low = l1;

        if (h1 == 2)
        {
            sa[i].high = 2;
            initial(sa);
            RECT r1 = { 900, 250, 1000, 275 };
            drawtext(s, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            RECT r2 = { 900, 275, 1000, 300 };
            drawtext(s1, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            //Sleep(1000);
            getchar();
        }

        r = h1 / 2;
        h1 = h1 % 2;
        sa[i].high = h1;

        initial(sa);
        RECT r1 = { 900, 250, 1000, 275 };
        drawtext(s, &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        RECT r2 = { 900, 275, 1000, 300 };
        drawtext(s1, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        //Sleep(1000);
        getchar();
        i++;
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

int main()
{
    printf("\n*******此程序实现的是算盘加法的演算过程********\n************程序开始后按任意键继续*************\n请输入两个长度不超过14位的数(被加数和加数，允许两位小数)：\n");
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
    setlinestyle(PS_SOLID, 2);
    initial(ab_augend);

    getchar();
    getchar();
    for (int i = 0; i < len; i++)
        add(ab_augend, ab_addend, i);
    RECT r1 = { 900, 250, 1000, 275 };
    initial(ab_augend);
    drawtext("计算结束", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    _getch();               // 按任意键继续
    closegraph();
}//
// Created by andy on 2022/4/26.
//

