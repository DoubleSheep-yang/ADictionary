#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<stdlib.h> 
#include<fstream>
#include<cstring>
#include<ctype.h>

#include "glossary.h"

int words_count = 0;
vector <Glossary> glossary;

/*
加载生词本文件
*/
void load_glossary()
{
	//打开文件
	ifstream fin(GLOSSARY_FILE);
	//如果文件不存在，则创建之
	if (!fin)
	{
		ofstream fout(GLOSSARY_FILE);
		fout.close();
		fin.open(GLOSSARY_FILE);
	}
	string line;
	Glossary vocabulary;
	while (!fin.eof())
	{
		//读取单词
		std::getline(fin, line);
		//如果为空，则文件为空，结束读取
		if (line == " ")
		{
			break;
		}
		//单词保存到内存中的字典数据结构里
		vocabulary.word = line;
		vocabulary.means.clear();  //清除上次读取结果
		vector<string> meaning;
		//一个单词的解释有很多行，读取行数
		std::getline(fin, line);
		int linecount = atoi(line.c_str());
		//多行释义的读取
		for (int j = 0;j < linecount;j++)
		{
			std::getline(fin, line);
			//每读一行，都将它存到单词释义的数组里
			vocabulary.means.push_back(line);
		}
		//每一个单词有一个释义，释义是多行的，放进内存里
		glossary.push_back(vocabulary);
	}
	fin.close();//保存生词本
}

/**
思考1 读取生词本之后，如何排序，有何好处
思考2 添加生词时。判断生词本中是否已有
**/

void save_glossary()
{
	fstream fout(GLOSSARY_FILE, ios::trunc);
	for (int i = 0;i < glossary.size();i++)
	{
		fout << glossary[i].word << endl;
		fout << glossary[i].means.size() << endl;
		for (int j = 0;j < glossary[i].means.size();j++)
		{
			fout << glossary[i].means[j] << endl;
		}
	}
	fout.close();
}
/** 移除单词*
 /*remove_glossary(word); @param word  要移除的单词
 **/
void remove_glossary(string word)
{
	for (auto i = glossary.begin();i != glossary.end();i++)
	{
		Glossary vocabulary = (Glossary) * i;
		if (vocabulary.word == word)
		{
			glossary.erase(i);
			i--;
		}
	}
}
