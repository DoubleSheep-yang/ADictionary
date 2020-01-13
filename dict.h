#ifndef _DICT_H
#define _DICT_H

#include<string>
#include<vector>
#include<iostream>

//下面的宏定义了字（词）库所对应的文件
#define DICT_PATH "D:\\c\\src\\data\\" 
#define DICT_ENGLISH_CHINESE "english_chinese.18030.txt"
#define DICT_CHINESE_ENGLISH "chinese_english.18030.txt"
#define DICT_CHENGYUDACIDIAN "chengyudacidian.18030.txt"
#define DICT_XINHUAZIDIAN "xhzd.18030.txt"

using namespace std;
//字典结构体
typedef struct
{
	string filename;
	bool loaded;
	vector<string>words;             //一个词典很多单词，是一个数组 
	vector< vector<string> >meanings;  //单词的释义，和单词是一一对应的 
} Dictionary;
//我们总共有4个字词典：英汉、汉英、成语词典、新华字典
//同时我们也有四个生词本
//extern表示这是在别处定义的一个变量，我们只是想提前用一用它
extern Dictionary dictionaries[4];
extern Dictionary unfamiliarDictionaries[4];
//下面这些宏表示字典序号1英汉2汉英3成语词典4新华字典
//定义宏是为了容易记忆且不易出错
#define ENGLISH_CHINESE 0
#define CHINESE_ENGLISH 1
#define CHENGYUDACIDIAN 2
#define XINHUAZIDIAN    3


//装载词库
void dict_load(Dictionary* dict, const char* filename);
//查字典
vector<string>dict_lookup(Dictionary* dict, const string& word, bool& find);
//输出单词/词语 释义
void meaning_display(const vector<string>& meaning);
void meaning_display1(const vector<string>& meaning);
void dict_ui();
void dict_ui_english_to_chinese();
void dict_ui_chinese_to_english();
void dict_ui_chengyudacidian();
void dict_ui_xinhuazidian();
#endif // !_DICT_H 