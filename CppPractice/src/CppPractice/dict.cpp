#include "dict.h"
#include <string>
#include <iostream>
#include "ui.h"
#include <fstream>
#include <vector>

using namespace std;

Dictionary dictionaries[4];
Dictionary unfamiliarDictionaries[4];

void dict_ui()
{
	CLEAR();

}

//实现成语词典功能
void idioms_dict()
{
	CLEAR();
	const string dict4_struct =
		"\n\n"
		"\t|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>|\n"
		"\t|*               成语字典                  |\n"
		"\t|------------------------------------------|\n"
		"\t请输入你想查询的成语：";
	cout << dict4_struct;
	string word = "";
	std::getline(cin, word);
	if (word == "")
	{
		dict_ui_mean_of_idiom();
		return;
	}
}

void dict_load(Dictionary* dict, const string& filename)
{
	if (dict->loaded)
	{
		return;
	}
	fstream in(filename, ios::in);
	if (!in)
	{
		cerr << "打不开词典文件:" << filename << endl;
		PAUSE();
		exit(1);
	}
	dict->filename = filename;

	int wordscount;
	string line;
	std::getline(in, line);//得到单词/短语个数 
	wordscount = atoi(line.c_str());//读取出来的是字符串，要将他转成整数才行，atoi 函数
	//多次重复，将所有字符串转成整数
	for (int i = 0; i < wordscount; i++)
	{
		std::getline(in, line);//读取单词 
		dict->words.push_back(line);//单词保存到内存中的字典数据结构里 
		vector<string> meaning;
		std::getline(in, line);// 一个单词的解释有很多行，读取行数 
		int linecount = atoi(line.c_str());
		for (int j = 0; j < linecount; j++)// 多行释义的读取
		{
			std::getline(in, line);
			meaning.push_back(line);// 每读一行，都将它存到单词释义的数组里 

		}
		dict->meanings.push_back(meaning);// 每一个单词有一个释义，释义是多行的，放进内存里面去 
	}
	in.close();
	dict->loaded = true;
}

vector<string> dict_lookup(Dictionary* dict, const string& word, bool& find)
{
	vector<string> result;
	result.push_back("运气不好，没有找到！");
	//这个查询就是按顺序来，一个个比较， 
	//如果匹配成功，就表示查到了这个单词，返回相应的解释 
	for (unsigned int i = 0; i < dict->words.size(); i++)
	{
		if (word == dict->words[i])
		{
			result = dict->meanings[i];
			find = true;
			return result;
		}
	}
	// 如果没查到，程序就到这里来了
	find = false;
	return result;
}

void dict_ui_mean_of_idiom()
{
	dict_load(&dictionaries[CHENGYUCIDIAN], file_location IDIOMS_DICT_FILE);
	CLEAR();
	dict_ui_mean_of_idiom();
}