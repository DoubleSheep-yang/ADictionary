#ifndef _DICT_H
#define _DICT_H
#include <string>
#include <vector>                                                                                                                                                                                                                                                                                                                        
#define file_location "E:\\编程\\C++代码\\CppPractice\\data\\"
#define DICT_ENGLISH_CHINESE "english_chinese.18030.txt" 
#define DICT_CHINESE_ENGLISH "chinese_english.18030.txt"
#define IDIOMS_DICT_FILE "chengyudacidian.18030.txt"

using namespace std;


// 字典结构体
typedef struct
{
	string filename;
	bool loaded;
	vector<string> words; // 一个词典很多单词，是一个数组 
	vector< vector<string> > meanings; // 单词的释义，和单词是一一对应的 
}Dictionary;

// 我们总共有 3 个字词典：英汉、汉英、成语词典
// 同时我们也有三个生词本 
extern Dictionary dictionaries[4];
extern Dictionary unfamiliarDictionaries[4];
// 下面的这些宏表示字典序号 1 英汉、2 汉英、3 成语词典、4 新华字典 
// 定义宏是为了容易记忆且不易出错
#define ENGLISH_CHINESE 0 
#define CHINESE_ENGLISH 1 
#define CHENGYUCIDIAN 2 
#define XINGHUAZIDIAN 3
//装载词库 

void idioms_dict();
//加载函数
void dict_load(Dictionary* dict, const string& filename);
//查字典 
vector<string> dict_lookup(Dictionary* dict, const string& word, bool& find);
////输出单词/词语 释义
//void meaning_display(const vector<string>& meaning);
void dict_ui();
void dict_ui_mean_of_idiom();

#endif // !_DICT_H