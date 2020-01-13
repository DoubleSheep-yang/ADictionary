#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h> 
#include "glossary.h"
#include "dict.h"

int word_count=0;
vector<Glossary> glossary;

//加载生词本文件 
void load_glossary()
{
	//打开文件
	ifstream fin(DICT_PATH DICT_NEW_ENGLISH_CHINESE);
	//如果文件不存在,就创建一个文件
	if(!fin)
	{
		ofstream fout(DICT_NEW_ENGLISH_CHINESE);
		fout.close();
		fin.open(DICT_NEW_ENGLISH_CHINESE);
	} 
	string line;
	Glossary vocabulary;
	while(!fin.eof())
	{
		//读取单词
		std::getline(fin,line);
		
		//如果为空，则文件为空，结束读取
		if(line==" ") break;
		 
		//单词保存到内存的字典数据结构里
		vocabulary.word=line;
		vocabulary.meaning.clear();      //消除上次的读取结果
		
		//一个单词的解释有多行，读取行数
		std::getline(fin,line);
		int linecount=atoi(line.c_str());
		
		//多行释义的读取
		for(int j=0;j<linecount;j++)
		{
			std::getline(fin,line);
			//每读一行，都将它存到单词释义的数组里
			vocabulary.meaning.push_back(line); 
	    }
	    glossary.push_back(vocabulary);
	}
	fin.close();
}

void save_glossary()
{
	ofstream fout(DICT_NEW_ENGLISH_CHINESE,ios::in);
	for(int i=0;i<glossary.size();i++)
	{
		fout<<glossary[i].word<<endl<<glossary[i].meaning.size()<<endl;
		for(int j=0;j<glossary[i].meaning.size();j++)
		{
			fout<<glossary[i].meaning[i]<<endl; 
		}
	} 
	fout.close();
}

void remove_glossary(string word)
{
	for(vector<Glossary>::iterator i=glossary.begin(); i!=glossary.end();i++)
	{
		Glossary vocabulary=(Glossary)*i;
		if(vocabulary.word==word)
		{
			glossary.erase(i);
			i--;
		}
	}
}
