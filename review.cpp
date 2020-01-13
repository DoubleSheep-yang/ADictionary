#include "review.h"
#include "ui.h"
#include <iostream>
#include <string>
#include <fstream>
#include "stdlib.h"
#include "time.h"
#include "exam.h"
#include "glossary.h"
#include "dict.h"
using namespace std;

static const string review_ui_prompt=
"\n\n"
"\t|********************************************|\n"
"\t|*            请选择复习类别                *|\n"
"\t|********************************************|\n"
"\t|*            1 英汉词典复习                *|\n"
"\t|*            2 汉英词典复习                *|\n"
"\t|*            3 成语词典复习                *|\n" 
"\t|*            0 返回上级                    *|\n" 
"\t|********************************************|\n"   
"\t  请输入（1，2，3或0）："
;

//生成一个[min,max)之间的随机整数
static int random_index(int min,int max) 
{ 
  return (int)(min+(double)rand()/(double)RAND_MAX*(max-min)); 
} 

//从生词本中随机生成一道题 
void exam_new_create(Examination* exam,Dictionary* dict)
{ 
  srand(time(NULL)); 
  int wordcount=dict->words.size();         
  int idx=random_index(0,wordcount); 
  exam->words.push_back(dict->words[idx]); 
  exam->meanings.push_back(dict->meanings[idx]); 
}

//英汉词典复习函数 
void review_english_to_chinese()
{
  //装载生词本 
  dict_load(&dictionaries[ENGLISH_CHINESE],DICT_PATH DICT_NEW_ENGLISH_CHINESE);

  //生成考试题目 
  Examination exam; 
  exam_new_create(&exam,&dictionaries[ENGLISH_CHINESE]);
  
  for (int i=0;i<exam.words.size();i++)
  {
    CLEAR(); 
    cout<<"\n\n"; 
    cout<<"\t|********************************************|\n"; 
    meaning_display(exam.meanings[i]); 
    cout<<"\n"; 
    cout<<"\t|********************************************|\n"; 
    string word=get_input_string("\t 请输入英文答案(0 退出）：");
    
    //cout << "\t 请输入英文答案(0 退出） ："; 
    //string word; 
    //std::getline(cin, word); 
    if(word==exam.words[i])
    { 
      cout<<"\t 正确！！！"<<endl; 
      string op=get_input_string("\t 请输入( 0 从生词本去除, 其他 下一题)：");
	  cout<<endl; 
      if(op=="0"){ 
      remove_glossary(word); 
      string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)：");
      if(op=="0")
        { 
      	    break;
	    }
      } 
    }
    else if(word=="0"){ 
    break; 
    }
    else 
    {cout<<"\t 错误,继续加油哦"<<endl;
	  string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
      if(op=="0"){
	  break;}    
    }
  }
}

//汉英词典复习函数 
void review_chinese_to_english()
{
  //装载生词本 
  dict_load(&dictionaries[CHINESE_ENGLISH],DICT_PATH DICT_NEW_CHINESE_ENGLISH);

  //生成考试题目 
  Examination exam; 
  exam_new_create(&exam,&dictionaries[CHINESE_ENGLISH]);
  
  for (int i=0;i<exam.words.size();i++)
  {
    CLEAR(); 
    cout<<"\n\n"; 
    cout<<"\t|********************************************|\n"; 
    meaning_display(exam.meanings[i]); 
    cout<<"\n"; 
    cout<<"\t|********************************************|\n"; 
    string word=get_input_string("\t 请输入中文答案(0 退出）：");
    
    //cout << "\t 请输入中文答案(0 退出） ："; 
    //string word; 
    //std::getline(cin, word); 
    if(word==exam.words[i])
    { 
      cout<<"\t 正确！！！"<<endl; 
      string op=get_input_string("\t 请输入( 0 从生词本去除, 其他 下一题)：");
	  cout<<endl; 
      if(op=="0"){ 
      remove_glossary(exam.words[i]); 
      string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)：");
      if(op=="0")
        { 
      	    break;
	    }
      } 
    }
    else if(word=="0"){ 
    break; 
    }
    else 
    {cout<<"\t 错误,继续加油哦"<<endl;
	  string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
      if(op=="0"){
	  break;}    
    }
  }
}

//成语词典复习函数 
void review_chengyudacidian()
{
  //装载生词本 
  dict_load(&dictionaries[CHENGYUDACIDIAN],DICT_PATH DICT_NEW_CHENGYUDACIDIAN);

  //生成考试题目 
  Examination exam; 
  exam_new_create(&exam,&dictionaries[CHENGYUDACIDIAN]);
  
  for (int i=0;i<exam.words.size();i++)
  {
    CLEAR(); 
    cout<<"\n\n"; 
    cout<<"\t|********************************************|\n"; 
    meaning_display_special(exam.meanings[i]); 
    cout<<"\n"; 
    cout<<"\t|********************************************|\n"; 
    string word=get_input_string("\t 请输入答案(0 退出）：");
    
    //cout << "\t 请输入答案(0 退出） ："; 
    //string word; 
    //std::getline(cin, word); 
    if(word==exam.words[i])
    { 
      cout<<"\t 正确！！！"<<endl; 
      string op=get_input_string("\t 请输入( 0 从生词本去除, 其他 下一题)：");
	  cout<<endl; 
      if(op=="0"){ 
      remove_glossary(exam.words[i]); 
      string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)：");
      if(op=="0")
        { 
      	    break;
	    }
      } 
    }
    else if(word=="0"){ 
    break; 
    }
    else 
    {cout<<"\t 错误,继续加油哦"<<endl;
	  string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
      if(op=="0"){
	  break;}    
    }
  }
}

//选择复习类别界面
void review_ui() 
{
  CLEAR();
  cout<<review_ui_prompt;
  string op;
  std::getline(cin, op);
  if(op=="1"){
    review_english_to_chinese();
  }
  else if(op=="2"){
  	review_chinese_to_english();
  }
  else if(op=="3"){
  	review_chengyudacidian();
  }
  else if(op=="0"){
    return;
  }
  review_ui();
}
