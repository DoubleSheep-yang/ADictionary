#include<iostream>
#include<stdio.h>
#include<string>
#include<ctime>
#include<cstdlib>
#include<cstring>
#include<ctype.h>
#include"ui.h"
#include"exam.h"
#include"dict.h"
#include "ui.cpp"

using namespace std;


static const string exam_ui_prompt =
"\n\n"
"\t|***********************************|\n"
"\t|*     请选择考试类别              *|\n"
"\t|***********************************|\n"
"\t|*     1 看中文写英文              *|\n"
"\t|*     2 看英文写中文              *|\n"
"\t|*     3 看解释写成语              *|\n"
"\t|*     0 退出系统                  *|\n"
"\t|***********************************|\n"
"\t  请输入（1，2，3或0）："
;

void exam_ui()
{
	CLEAR();
	cout << exam_ui_prompt;
	string op;
	std::getline(cin, op);
	if (op == "1")
	{
		exam_ui_english_for_chinese();
	}
	else if (op == "2")
	{
		exam_ui_chinese_for_english();
	}
	else if (op == "3")
	{
		exam_ui_chengyu();
	}
	else if (op == "0")
	{
		return;
	}
	exam_ui();

}

void exam_ui_english_for_chinese()              //看英文写中文考试函数 
{
	dict_load(
		&dictionaries[0],    //装载英汉字典词库 
		DICT_PATH DICT_ENGLISH_CHINESE);

	Examination exam;
	exam_create(&exam, &dictionaries[0]);  //生成考试题目 
	for (int i = 0;i<exam.words.size();i++)
	{
		CLEAR();
		cout << "\n\n";
		cout << "\t|***********************************|\n";
		meaning_display1(exam.meanings[i]);
		cout << "\n";
		cout << "\t|***********************************|\n";
		string word =get_input_string("\t 请输入英文答案（0 退出）：");


		if (word == exam.words[i])
		{
			cout << "\t  正确！！！" << endl;
			string op =get_input_string("\t  请输入（0 退出，其他  下一题）：");
			if (op == "0")
			{
				break;
			}
		}
		else if (word == "0")
		{
			break;
		}
		else
		{
			cout << "\t   错误，继续加油哦" << endl;
			string op = get_input_string("\t  请输入（0 退出，1 换一题 ，2 继续尝试）：");
			if (op == "0")
			{
				break;
			}
			else if (op == "1")
			{
				exam_ui_english_for_chinese();
			}
			else if (op == "2")
			{
			}
			i--;
		}

	}
}


void exam_ui_chinese_for_english()                //看英文写中文函数 
{
	dict_load(                                     //装载词库 
		&dictionaries[1],
		DICT_PATH DICT_CHINESE_ENGLISH);

	Examination exam;
	exam_create(&exam, &dictionaries[1]);
	for (int i = 0;i < exam.words.size();i++)
	{
		CLEAR();
		cout << "\n\n";
		cout << "\t|***********************************|\n";
		meaning_display(exam.meanings[i]);
		cout << "\n";
		cout << "\t|***********************************|\n";
		string word = get_input_string("\t 请输入中文答案（0 退出）：");
		if (word == exam.words[i])
		{
			cout << "\t  正确！！！" << endl;
			string op = get_input_string("\t  请输入（0 退出，其他  下一题）：");
			if (op == "0")
			{
				break;
			}
		}
		else if (word == "0")
		{
			break;
		}
		else
		{
			cout << "\t   错误，继续加油哦" << endl;
			string op = get_input_string("\t  请输入（0 退出，1 换一题 ，2 继续尝试）：");
			if (op == "0")
			{
				break;
			}
			else if (op == "1")
			{
				exam_ui_chinese_for_english();
			}
			else if (op == "2")
			{
			}
			i--;
			getchar();
			getchar();
		}

	}
}

void exam_ui_chengyu()              //看释义写成语函数 
{
	dict_load(
		&dictionaries[2],    //装载成语词典词库 
		DICT_PATH DICT_CHENGYUDACIDIAN);

	Examination exam;
	exam_create(&exam, &dictionaries[2]);  //生成考试题目 
	for (int i = 0;i < exam.words.size();i++)
	{
		CLEAR();
		cout << "\n\n";
		cout << "\t|***********************************|\n";
		meaning_display1(exam.meanings[i]);
		cout << "\n";
		cout << "\t|***********************************|\n";
		string word = get_input_string("\t 请输入成语（0 退出）：");


		if (word == exam.words[i])
		{
			cout << "\t  正确！！！" << endl;
			string op = get_input_string("\t  请输入（0 退出，其他  下一题）：");
			if (op == "0")
			{
				break;
			}
		}
		else if (word == "0")
		{
			break;
		}
		else
		{
			cout << "\t   错误，继续加油哦" << endl;
			string op = get_input_string("\t  请输入（0 退出，1 换一题 ，2 继续尝试）：");
			if (op == "0")
			{
				break;
			}
			else if (op == "1")
			{
				exam_ui_chengyu();
			}
			else if (op == "2")
			{
			}
			i--;
			getchar();
			getchar();
		}

	}
}


static int random_index(int min, int max)                       //生成一个[min,max)之间的随机整数 
{
	return (int)(min + (double)rand() / (double)RAND_MAX * (max - min));
}

void exam_create(Examination* exam, Dictionary* dict)             //从字典中随机生成一个试卷 
{
	srand(time(nullptr));
	int wordcount = dict->words.size();

	int itemcount = wordcount < 10 ? wordcount : 10;
	for (int i = 0;i < itemcount;i++)
	{
		int idx = random_index(0, wordcount);
		exam->words.push_back(dict->words[idx]);
		exam->meanings.push_back(dict->meanings[idx]);
	}
}
