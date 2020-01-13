#ifndef _UI_H
#define _UI_H

#include<string>

#define PAUSE() system("pause")
#define CLEAR() system("cls")

using namespace std;

void init_console();
void main_ui();
void dict_ui();
void exam_ui();
#endif // !_UI_H