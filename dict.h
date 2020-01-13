#ifndef _DICT_H
#define _DICT_H
#include <string>  
#include <vector>

//下面的宏定义了字（词）库所对应的文件
#define DICT_PATH "E:\\CppPractice\\data\\" 
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
	vector<string>words;                //一个词典很多单词，是一个数组
	vector< vector<string> >meanings;     //单词的释义，和单词是一一对应的 
}Dictionary,New_Dictionary; 

//我们总共有四个词典：英汉、汉英、成语词典、新华字典 
//同时我们也有四个生词本 
//extern表示这是在别处定义的一个变量，我们想提前使用它 
extern Dictionary dictionaries[4];
extern Dictionary unfamiliardictionaries[4]; 

//下面这些宏表示字典序号 1、英汉 2、汉英 3、成语词典 4、新华字典 
//定义宏是为了容易记忆且不易记错 
#define ENGLISH_CHINESE 0 
#define CHINESE_ENGLISH 1 
#define CHENGYUDACIDIAN 2 
#define XINHUAZIDIAN    3 

//装载词库
void dict_load(Dictionary*dict,const string&filename); 

//查字典 
vector<string>dict_lookup(Dictionary*dict,const string&word,bool&find);
vector<string>dict_lookup(Dictionary*dict,const string&word); 

//输出单词/词语 释义 
void meaning_display(const vector<string>&meaning); 
void meaning_display_special(const vector<string>&meaning);
void dict_ui();
void dict_ui_english_to_chinese();
void dict_ui_chinese_to_english();
void dict_ui_chengyudacidian(); 

#endif// !_DICT_H
