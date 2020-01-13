#include <stdlib.h> 
#include <string>
#include <iostream>
#include <fstream>
#include "ui.h"
#include "dict.h"
#include "glossary.h"
using namespace std;

extern int words_count;
extern vector<Glossary> glossary;
Dictionary dictionaries[4];
Dictionary unfamiliarDictionaries[4]; 
Glossary vocabulary;

const string dict_ui_prompt=
"\n\n"
"\t|********************************************|\n"
"\t|*            请选择词典                    *|\n"
"\t|********************************************|\n"
"\t|*            1 英汉词典                    *|\n"
"\t|*            2 汉英词典                    *|\n"
"\t|*            3 成语词典                    *|\n" 
"\t|*            4 新华词典                    *|\n"
"\t|*            0 返回上级                    *|\n"
"\t|********************************************|\n"   
"\t  请输入（1，2，3，4或0）："
;

extern void dict_ui()
{
	CLEAR();
	cout<<dict_ui_prompt;
	string op;
	std::getline(cin,op);
	if(op=="1"){
		dict_ui_english_to_chinese();
	}
	else if(op=="2"){
		dict_ui_chinese_to_english();
	}
	else if(op=="3"){
		dict_ui_chengyudacidian();
	}
	else if(op=="4"){
	}
	else if(op=="0"){
		return;
	}
	dict_ui();
} 

void meaning_display(const vector<string>&meaning)
{
	cout<<"\n";
	for(unsigned int i=0;i<meaning.size();i++)
	{
		cout<<"\t"<<meaning[i]<<endl;
	}
}

void meaning_display_special(const vector<string>&meaning)
{
	cout<<"\n";
	for(unsigned int i=2;i<meaning.size();i++)
	{
		cout<<"\t"<<meaning[i]<<endl;
	}
}

//英译汉词典查询函数 
void dict_ui_english_to_chinese()
{ 
	dict_load(&dictionaries[ENGLISH_CHINESE],DICT_PATH DICT_ENGLISH_CHINESE);
	CLEAR();
	const string prompt=
	"\n\n"
    "\t|********************************************|\n"
    "\t|*   英汉词典                               *|\n"
    "\t|********************************************|\n"
    "\t     请输入英文：" 
	;
	cout<<prompt;
	string word=" ";
	std::getline(cin,word);
	if(word==" ")
	{
		dict_ui_english_to_chinese();
		return;
	} 
	bool find=false;
	vector<string>meaning=dict_lookup(&dictionaries[ENGLISH_CHINESE],word,find);
	if(find)
	{
		cout<<"\t 查询结果是："<<endl;
		meaning_display(meaning);
		cout<<"\t|********************************************|\n";
	    cout<<"\t   请选择（1 加入生词本，0返回上级，其他 继续）：";
	}
	else
	{
		meaning_display(meaning);
		cout<<"\t|********************************************|\n";
	    cout<<"\t   请选择（0返回上级，其他 继续）：";
	}
	string op;
	std::getline(cin,op);
	if(op=="1")
	{
		//只有查询得到的单词/词语才会需要加入生词本
		if(find)
		{
            vocabulary.word=word;
		    vocabulary.meaning.clear();
		    for(int i=0;i<meaning.size();i++)
		    {
			    vocabulary.meaning.push_back(meaning[i]);
		    }
	    	glossary.push_back(vocabulary);
		    //加入生词本 
		    ofstream fout(DICT_PATH DICT_NEW_ENGLISH_CHINESE,ios::in);
		    fout<<glossary.size()<<endl;
	        for(int i=0;i<glossary.size();i++)
    	    {
    		    fout<<glossary[i].word<<endl<<glossary[i].meaning.size()<<endl;
	    	    for(int j=0;j<glossary[i].meaning.size();j++)
		        {
			        fout<<glossary[i].meaning[j]<<endl; 
		        } 
	        }   
	        fout.close(); 
		} 
	} 
	else if(op=="0")
	{
		return;
	}
	dict_ui_english_to_chinese();
}

//汉译英词典查询函数 
void dict_ui_chinese_to_english()
{ 
	dict_load(&dictionaries[CHINESE_ENGLISH],DICT_PATH DICT_CHINESE_ENGLISH);
	CLEAR();
	const string prompt=
	"\n\n"
    "\t|********************************************|\n"
    "\t|*         汉英词典                         *|\n"
    "\t|********************************************|\n"
    "\t           请输入中文：" 
	;
	cout<<prompt;
	string word=" ";
	std::getline(cin,word);
	if(word==" ")
	{
		dict_ui_chinese_to_english();
		return;
	} 
	bool find=false;
	vector<string>meaning=dict_lookup(&dictionaries[CHINESE_ENGLISH],word,find);
	if(find)
	{
		cout<<"\t 查询结果是："<<endl;
		meaning_display(meaning);
		cout<<"\t|********************************************|\n";
	    cout<<"\t   请选择（1 加入生词本，0返回上级，其他 继续）：";
	}
	else
	{
		meaning_display(meaning);
		cout<<"\t|********************************************|\n";
	    cout<<"\t   请选择（0返回上级，其他 继续）：";
	}
	string op;
	std::getline(cin,op);
	if(op=="1")
	{
		//只有查询得到的单词/词语才会需要加入生词本
		if(find)
		{
            vocabulary.word=word;
		    vocabulary.meaning.clear();
		    for(int i=0;i<meaning.size();i++)
		    {
			    vocabulary.meaning.push_back(meaning[i]);
		    }
	    	glossary.push_back(vocabulary);
		    //加入生词本 
		    ofstream fout(DICT_PATH DICT_NEW_CHINESE_ENGLISH,ios::in);
		    fout<<glossary.size()<<endl;
	        for(int i=0;i<glossary.size();i++)
    	    {
    		    fout<<glossary[i].word<<endl<<glossary[i].meaning.size()<<endl;
	    	    for(int j=0;j<glossary[i].meaning.size();j++)
		        {
			        fout<<glossary[i].meaning[j]<<endl; 
		        } 
	        }   
	        fout.close(); 
		} 
	} 
	else if(op=="0")
	{
		return;
	}
	dict_ui_chinese_to_english();
}

//成语词典查询函数 
void dict_ui_chengyudacidian()
{
	
	dict_load(& dictionaries[CHENGYUDACIDIAN],DICT_PATH DICT_CHENGYUDACIDIAN );
	CLEAR();
	const string prompt=
   "\n\n"
   "\t|*********************************************|\n"
   "\t|*              成语词典                     *|\n"
   "\t|*********************************************|\n"
   "\t   请输入你要查询的成语 :"
   ;
   cout<<prompt;
   string word=" ";
   std::getline(cin,word);
   if(word==" ")
   {
       dict_ui_chengyudacidian();
       return;
   }
   bool find=false;
   vector<string>meaning=dict_lookup(&dictionaries[CHENGYUDACIDIAN],word,find);
   if(find)
   {
	   cout<<"\t  查询结果是："<<endl;
	   meaning_display(meaning);
	   cout<<"\t***********************************|\n";
	   cout<<"\t 请选择（1 加入生词本，0 返回上级，其他 继续："; 
   }
   else
   {
       meaning_display(meaning);
       cout<<"\t***********************************|\n";
       cout<<"\t 请选择（0 返回上级，其他 继续："; 
    }
    string op;
    std::getline(cin,op);
    if(op=="1")
    {
	    //只有查询得到的单词/词语才会需要加入生词本
		if(find)
		{
            vocabulary.word=word;
		    vocabulary.meaning.clear();
		    for(int i=0;i<meaning.size();i++)
		    {
			    vocabulary.meaning.push_back(meaning[i]);
		    }
	    	glossary.push_back(vocabulary);
		    //加入生词本 
		    ofstream fout(DICT_PATH DICT_NEW_CHENGYUDACIDIAN,ios::in);
		    fout<<glossary.size()<<endl;
	        for(int i=0;i<glossary.size();i++)
    	    {
    		    fout<<glossary[i].word<<endl<<glossary[i].meaning.size()<<endl;
	    	    for(int j=0;j<glossary[i].meaning.size();j++)
		        {
			        fout<<glossary[i].meaning[j]<<endl; 
		        } 
	        }   
	        fout.close(); 
		} 	
    }
    else if(op=="0")
    {
       return;
    }
    dict_ui_chengyudacidian();
}

//装载词典 
void dict_load(Dictionary* dict, const string& filename) 
{ 
  // 如果装载过了，就不要再读文件了
  if(dict->loaded)
  {
    return;
  }
  
  fstream in( filename.c_str(), ios::in); 
  if(!in)
  { 
    cerr<<"打不开词典文件:"<<filename<<endl;
    PAUSE(); 
    exit(1);
  }
  dict->filename=filename;
  
  //得到单词/短语个数 
  int wordscount;
  string line;
  std::getline(in,line);
  
  //读取出来的是字符串，要将他转成整数才行，atoi 函数 
  wordscount=atoi(line.c_str());
  
  //多次读单词 
  for(int i=0;i<wordscount;i++)
  { 
    //读取单词 
	std::getline(in, line); 
	
	//单词保存到内存中的字典数据结构里
    dict->words.push_back(line);
    vector<string>meaning;
    
    // 一个单词的解释有很多行，读取行数 
    std::getline(in,line); 
    int linecount=atoi(line.c_str());
    
    // 多行释义的读取
    for(int j=0;j<linecount;j++)
    {
	   std::getline(in, line);
	    
       //每读一行，都将它存到单词释义的数组里
	   meaning.push_back(line); 
    }
    // 每一个单词有一个释义，释义是多行的，放进内存里面去 
    dict->meanings.push_back(meaning);
  }
  in.close();
  // 装载成功了，更新一下装载成功的标志
  dict->loaded=true;
}

vector<string> dict_lookup(Dictionary* dict, const string& word, bool& find)
{ 
  vector<string> result; 
  result.push_back("词典君无法为您找到目标");
   
  //这个查询就是按顺序来，一个个比较， 
  //如果匹配成功，就表示查到了这个单词，返回相应的解释 
  for (unsigned int i=0;i<dict->words.size();i++) 
  { 
    if (word==dict->words[i]) 
    { 
      result=dict->meanings[i]; 
      find=true; 
      return result; 
    } 
  }
  //如果没查到,程序就到这里来了 
  find = false; 
  return result; 
}

// 下面调用了上面的那个带三个参数的同名函数 
vector<string> dict_lookup(Dictionary* dict, const string& word) 
{ 
  bool find=false; 
  return dict_lookup(dict,word,find); 
} 
