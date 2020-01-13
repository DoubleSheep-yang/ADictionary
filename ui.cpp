#include<iostream>
#include "ui.h"
void init_console()
{
	system("mode con cols=64 lines=30");
	system("chcp 936");
	system("color 7d");
	system("cls");
}

const string main_ui_prompt =
"\n\n"
"\t|***********************************|\n"
"\t|*   欢迎使用  我的词典 <*-*>      *|\n"
"\t|***********************************|\n"
"\t|*   1 字词查询                    *|\n"
"\t|*   2 字词考试                    *|\n"
"\t|*   3 生词复习                    *|\n"
"\t|*   0 退出系统                    *|\n"
"\t|***********************************|\n"
"\t   请输入(1，2，3或0):"
;

void main_ui()
{
	CLEAR();
	cout << main_ui_prompt;
	string op;
	std::getline(cin, op);
	if (op == "1")
	{
		dict_ui();
	}
	else if (op == "2")
	{
		exam_ui();
	}
	else if (op == "3")
	{

	}
	else if (op == "0")
	{
		return;
	}

	main_ui();
}
string get_input_string(const string& prompt)
{
	cout << prompt;
	string word;
	std::getline(cin, word);
	return word;
}