#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include"ui.h"
#include"dict.h"
#include "glossary.h"

using namespace std;

Dictionary dictionaries[4];
Dictionary unfamiliarDictionaries[4];
const string dict_ui_prompt =
"\n\n"
"\t|***********************************|\n"
"\t|*   请选择（字）词典              *|\n"
"\t|***********************************|\n"
"\t|*   1 英汉词典                    *|\n"
"\t|*   2 汉英词典                    *|\n"
"\t|*   3 成语词典                    *|\n"
"\t|*   4 新华字典                    *|\n"
"\t|*   0 返回上级                    *|\n"
"\t|***********************************|\n"
"\t   请输入(1，2，3，4或0):"
;

extern void dict_ui()
{
	CLEAR();
	cout << dict_ui_prompt;
	string op;
	std::getline(cin, op);
	if (op == "1")
	{
		dict_ui_english_to_chinese();
	}
	else if (op == "2")
	{
		dict_ui_chinese_to_english();
	}
	else if (op == "3")
	{
		dict_ui_chengyudacidian();
	}
	else if (op == "4")
	{
		dict_ui_xinhuazidian();
	}
	else if (op == "0")
	{
		return;
	}

	dict_ui();

}
void meaning_display(const vector<string>& meaning)
{
	cout << "\n";
	for (unsigned int i = 0;i < meaning.size();i++)
	{
		cout << "\t" << meaning[i] << endl;
	}
}
void dict_load(Dictionary* dict, const char* filename)
{
	//如果装载过了就不要再读文件了
	if (dict->loaded)
	{
		return;
	}
	fstream infile;
	infile.open(filename, ios_base::in);
	if (!infile)
	{
		cerr << "打开词典文件：" << filename << "失败" << endl;
		PAUSE();
		exit(1);
	}
	dict->filename = filename;
	//得到单词/短语个数
	int wordscount;
	string line;
	std::getline(infile, line);
	//读取出来的是字符串，要将它转成整数才行，atoi函数
	wordscount = atoi(line.c_str());
	//有这么多单词，当然要这么多次
	for (int i = 0;i < wordscount;i++)
	{
		//读取单词
		std::getline(infile, line);
		//单词保存到内存中的字典数据结构里
		dict->words.push_back(line);
		vector<string> meaning;
		//一个单词的解释有很多行，读取行数
		std::getline(infile, line);
		int linecount = atoi(line.c_str());
		//多行释义的读取
		for (int j = 0;j < linecount;j++)
		{
			std::getline(infile, line);
			//每读一行，都将它存到单词释义的数组里
			meaning.push_back(line);
		}
		//每一个单词有一个释义，释义是多行的，放进内存里
		dict->meanings.push_back(meaning);
	}

	infile.close();
	//装载成功了，更新一下装载成功的标志
	dict->loaded = true;
}

void dict_ui_english_to_chinese()
{
	dict_load(&dictionaries[0], DICT_PATH DICT_ENGLISH_CHINESE);
	CLEAR();
	const string prompt =
		"\n\n"
		"\t|***********************************|\n"
		"\t|*   欢迎使用  英汉词典            *|\n"
		"\t|***********************************|\n"
		"\t|*   请输入英文： ～(￣▽￣～)~    *|\n"
		;
	cout << prompt;
	cout << "\t|*   ";
	string word = " ";
	std::getline(cin, word);
	if (word == " ")
	{
		dict_ui_english_to_chinese();
		return;
	}
	bool find = false;
	vector<string> meaning = dict_lookup(&dictionaries[0], word, find);
	if (find)
	{
		cout << "\t  查询结果是：" << endl;
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：1 加入生词本            *|\n";
		cout << "\t|          2 继续查词              *|\n";
		cout << "\t|          0 返回上级，其他 继续   *|\n";
		cout << "\t|***********************************|\n";
	}
	else
	{
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：0 返回上级 其他 继续    *|\n";
	}

	string op;
	std::getline(cin, op);
	if (op == "1")
	{
		//只有查询得到的单词/词语才会需要加入生词本
		if (find)
		{
			load_glossary();
			save_glossary();
			
			cout << "加入成功，正在为您跳转至查词界面" << endl;
			dict_ui_english_to_chinese();
			//加入生词本 
		}
	}
	else if (op == "2")
	{
		dict_ui_english_to_chinese();
	}
	else if (op == "0")
	{
		return;
	}
	dict_ui_english_to_chinese();
}

void dict_ui_chinese_to_english()
{
	dict_load(&dictionaries[1], DICT_PATH DICT_CHINESE_ENGLISH);
	CLEAR();
	const string prompt =
		"\n\n"
		"\t|***********************************|\n"
		"\t|*   欢迎使用  汉英词典 (′×ω×`)*|\n"
		"\t|***********************************|\n"
		"\t|*   请输入中文：～(￣▽￣～)~     *|\n"
		;
	cout << prompt;
	cout << "\t|*   ";
	string word = " ";
	std::getline(cin, word);
	if (word == " ")
	{
		dict_ui_chinese_to_english();
		return;
	}
	bool find = false;
	vector<string> meaning = dict_lookup(&dictionaries[1], word, find);
	if (find)
	{
		cout << "\t  查询结果是：" << endl;
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：1 加入生词本            *|\n";
		cout << "\t|          2 继续查词              *|\n";
		cout << "\t|          0 返回上级，其他 继续   *|\n";
		cout << "\t|***********************************|\n";
	}
	else
	{
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：0 返回上级 其他 继续    *|\n";
	}

	string op;
	std::getline(cin, op);
	if (op == "1")
	{
		//只有查询得到的单词/词语才会需要加入生词本
		if (find)
		{
			//加入生词本 
		}
	}
	else if (op == "2")
	{
		dict_ui_chinese_to_english();
	}
	else if (op == "0")
	{
		return;
	}
	dict_ui_chinese_to_english();
}

void dict_ui_chengyudacidian()
{
	dict_load(&dictionaries[2], DICT_PATH DICT_CHENGYUDACIDIAN);
	CLEAR();
	const string prompt =
		"\n\n"
		"\t|***********************************|\n"
		"\t|*   欢迎使用  成语词典  (≧ω≦)  *|\n"
		"\t|***********************************|\n"
		"\t|*   请输入成语：  ～(￣▽￣～)~   *|\n"
		;
	cout << prompt;
	cout << "\t|*   ";
	string word = " ";
	std::getline(cin, word);
	if (word == " ")
	{
		dict_ui_chengyudacidian();
		return;
	}
	bool find = false;
	vector<string> meaning = dict_lookup(&dictionaries[2], word, find);
	if (find)
	{
		cout << "\t  查询结果是：" << endl;
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：1 加入生词本            *|\n";
		cout << "\t|          2 继续查成语            *|\n";
		cout << "\t|          0 返回上级，其他 继续   *|\n";
		cout << "\t|***********************************|\n";
	}
	else
	{
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：0 返回上级 其他 继续    *|\n";
	}

	string op;
	std::getline(cin, op);
	if (op == "1")
	{
		//只有查询得到的单词/词语才会需要加入生词本
		if (find)
		{
			//加入生词本 
		}
	}
	else if (op == "2")
	{
		dict_ui_chengyudacidian();
	}
	else if (op == "0")
	{
		return;
	}
	dict_ui_chengyudacidian();
}

void dict_ui_xinhuazidian()
{
	dict_load(&dictionaries[3], DICT_PATH DICT_XINHUAZIDIAN);
	CLEAR();
	const string prompt =
		"\n\n"
		"\t|***********************************|\n"
		"\t|*   欢迎使用  新华字典   (=^▽^=) *|\n"
		"\t|***********************************|\n"
		"\t|*   请输入汉字：   ～(￣▽￣～)~  *|\n"
		;
	cout << prompt;
	cout << "\t|*   ";
	string word = " ";
	std::getline(cin, word);
	if (word == " ")
	{
		dict_ui_xinhuazidian();
		return;
	}
	bool find = false;
	vector<string> meaning = dict_lookup(&dictionaries[3], word, find);
	if (find)
	{
		cout << "\t  查询结果是：" << endl;
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：1 加入生词本            *|\n";
		cout << "\t|          2 继续查字              *|\n";
		cout << "\t|          0 返回上级，其他 继续   *|\n";
		cout << "\t|***********************************|\n";
	}
	else
	{
		meaning_display(meaning);
		cout << "\t|***********************************|\n";
		cout << "\t|  请选择：0 返回上级 其他 继续    *|\n";
	}

	string op;
	std::getline(cin, op);
	if (op == "1")
	{
		//只有查询得到的单词/词语才会需要加入生词本
		if (find)
		{
			//加入生词本 
		}
	}
	else if (op == "2")
	{
		dict_ui_xinhuazidian();
	}
	else if (op == "0")
	{
		return;
	}
	dict_ui_xinhuazidian();
}

/*void meaning_display(const vector<string>& meaning)     //输出所要查找的单词的意思 
{
	cout << "\n";
	for (unsigned int i = 0;i < meaning.size();i++)
	{
		cout << "\t" << meaning[i] << endl;
	}
}
*/

void meaning_display1(const vector<string>& meaning)    //用于成语考试时，看释义猜成语 
{
	cout << "\n";
	for (unsigned int i = 2;i < meaning.size();i++)           //输出时跳过前两行 
	{
		cout << "\t" << meaning[i] << endl;
	}
}

vector<string> dict_lookup(Dictionary* dict, const string& word, bool& find)
{
	vector<string> result;
	result.push_back("运气不好，没有找到（#——#）");
	//这个查询就是按顺序来，一个个比较，
	//如果匹配成功，就表示查到了这个单词，返回相应的解释
	for (unsigned int i = 0;i < dict->words.size();i++)
	{
		if (word == dict->words[i])
		{
			result = dict->meanings[i];
			find = true;
			return result;
		}
	}
	// 如果没查到，程序就到这里了
	find = false;
	return result;
}

vector<string> dict_lookup(Dictionary* dict, const string& word)
{
	bool find = false;
	return dict_lookup(dict, word, find);
}