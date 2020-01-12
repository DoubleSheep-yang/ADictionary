#include "ui.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

using namespace std;

void pos(int x, int y);//确定光标位置
void blue_border();//边框颜色
void white_back();//白颜色字体
void cyan_choose();//字体颜色
void on_Select();//选中时样式
void on_choose(int x, int y);//确定坐标
void star();//初始化界面
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄
void main_ui()
{
    system("color 7F");//设置控制台背景颜色
    system("mode con cols=100 lines=40");/*初始化缓冲区大小*/
    SetConsoleTitle(L"OurProgram");
    cout << endl << "                             ";
    cout << "上下左右键控制光标选择；空格 确定";

    blue_border();
    pos(5, 5);
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>";
    pos(5, 25);
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
    for (int i = 5, j = 6; j < 25; j++) //左边框
    {
        pos(i, j);
        cout << "|";
    }
    for (int i = 85, j = 6; j < 25; j++) //右边框
    {
        pos(i, j);
        cout << "|";
    }

    cyan_choose();
    pos(65, 10);
    cout << "2. 字词考试 ";
    pos(25, 20);
    cout << "3. 生词复习 ";
    pos(65, 20);
    cout << "4. 退出系统 ";
    on_Select();
    pos(25, 10);
    cout << "1. 字词查询 ";

    //上下左右键控制光标对进行自由选择
    int x = 25, y = 10;
    char sel;
    sel = _getch();
    while (sel != ' ')
    {
        star();
        switch (sel)
        {
        case 72:
            y = y - 10;
            break;
        case 80:
            y = y + 10;
            break;
        case 75:
            x = x - 40;
            break;
        case 77:
            x = x + 40;
            break;
        }
        //防止超出范围
        if (x >= 65)
        { 
            x = 65;
        }
        if (y >= 20)
        {
            y = 20;
        }
        if (x <= 25)
        {
            x = 25;
        }
        if (y <= 10)
        {
            y = 10;
        }
        pos(x, y);
        on_choose(x, y);
        sel = _getch();
    }
    pos(0, 30);
    white_back();//还原默认字体
    CloseHandle(hOut);//关闭标准输出句柄;
    string op;
    std::getline(cin, op);
    if (op == " ")
    {
        if (x <= 60 && y == 10)
        {

        }
        if (x >=61 && y == 10)
        {

        }
        if (x <=60 && y == 20)
        {

        }
        if (x >=61 && y == 20)
        {
            return;
        }
    }
}
//设置光标位置

void pos(int x, int y)
{
    COORD posPoint = { x,y }; //设置坐标
    SetConsoleCursorPosition(hOut, posPoint);
}
void blue_border()
{
    WORD blue = FOREGROUND_GREEN | FOREGROUND_BLUE;
}
void white_back()
{
    WORD white = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hOut, white);
}
void cyan_choose()
{
    WORD cyan = FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE;
    SetConsoleTextAttribute(hOut, cyan);
}
void on_Select()
{
    WORD select = FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED;
    SetConsoleTextAttribute(hOut, select);
}
void on_choose(int x, int y)
{
    if (x == 25 && y == 10)
    {
        on_Select();
        cout << "1. 字词查询 ";
    }
    else if (x == 25 && y == 20)
    {
        on_Select();
        cout << "3. 生词复习 ";
    }
    else if (x == 65 && y == 10)
    {
        on_Select();
        cout << "2. 生词考试 ";
    }
    else if (x == 65 && y == 20)
    {
        on_Select();
        cout << "4. 退出系统 ";
    }
}
//选择时格式
void star()
{
    cyan_choose();
    pos(25, 10);
    cout << "1. 字词查询 ";
    pos(65, 10);
    cout << "2. 字词考试 ";
    pos(25, 20);
    cout << "3. 生词复习 ";
    pos(65, 20);
    cout << "4. 退出系统 ";
}
//初始化界面
void init_console()
{
    system("mode con cole-64 lines=30");
    system("chcp 936");
    system("color f0");
    CLEAR();
}
//次级ui界面格式

const string main_ui_prompt =
"\n\n"
"\t|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n"
"\t|*                  欢迎使用 我的词典               *|\n"
"\t|*---------------------------------------------------|\n"
"\t|*  请选择：                                         |\n"
"\t|*           1 英汉词典                              |\n"
"\t|*           2 汉英词典                              |\n"
"\t|*           3 成语词典                              |\n"
"\t|*           0 返回上一级                            |\n"
"\t|<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<|\n"
"\t    请输入(1,2,3或0)"
"      请输入:";
//次级的ui界面
