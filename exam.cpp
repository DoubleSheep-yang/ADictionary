#include "exam.h"
#include "ui.h"
#include <iostream>
#include <string>
#include "stdlib.h"
#include "time.h"
using namespace std;

static const string exam_ui_prompt=
"\n\n"
"\t|********************************************|\n"
"\t|*   请选择考试类别                         *|\n"
"\t|********************************************|\n"
"\t|*            1 看中文写英文                *|\n"
"\t|*            2 看英文写中文                *|\n"
"\t|*            3 看解释写成语                *|\n" 
"\t|*            0 返回上级                    *|\n" 
"\t|********************************************|\n"   
"\t  请输入（1，2，3或0）："
;

//生成一个[min,max)之间的随机整数
static int random_index(int min,int max) 
{ 
  return (int)(min+(double)rand()/(double)RAND_MAX*(max-min)); 
} 

//从字典中随机生成一个试卷
void exam_create(Examination* exam,Dictionary* dict)
{ 
  srand(time(NULL)); 
  int wordcount=dict->words.size(); 
  int itemcount=wordcount<10?wordcount:10;        
  for(int i=0;i<itemcount;i++) 
  { 
    int idx=random_index(0,wordcount); 
    exam->words.push_back(dict->words[idx]); 
    exam->meanings.push_back(dict->meanings[idx]); 
  } 
}

//看中文写英文 
void exam_ui_english_for_chinese()
{
  //装载词库 
  dict_load(&dictionaries[ENGLISH_CHINESE],DICT_PATH DICT_ENGLISH_CHINESE);

  //生成考试题目 
  Examination exam; 
  exam_create(&exam,&dictionaries[ENGLISH_CHINESE]);
  
  //定义一个计数量统计正确题数 
  int correct_num;

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
       correct_num++;
       cout<<"\t 正确！！！"<<endl; 
       string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
       if(op=="0"){ 
       break; 
       } 
    }
    else if(word=="0"){ 
      break; 
    }
    else{
      cout<<"\t 错误,继续加油哦"<<endl;
	  string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
      if(op=="0"){
	  break;}    
    }
  } 
  cout<<"\t 本次考试的成绩(满分100)是："<<correct_num*10<<endl;
  cout<<"\t "<<endl;
  string op=get_input_string("\t 请输入(任意键 退出)：");  
}

//看英文写中文 
void exam_ui_chinese_for_english()
{
  //装载词库 
  dict_load(&dictionaries[CHINESE_ENGLISH],DICT_PATH DICT_CHINESE_ENGLISH);

  //生成考试题目 
  Examination exam; 
  exam_create(&exam,&dictionaries[CHINESE_ENGLISH]);
  
  //定义一个计数量统计正确题数 
  int correct_num;

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
       correct_num++;
       cout<<"\t 正确！！！"<<endl; 
       string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
       if(op=="0"){ 
       break; 
       } 
    }
    else if(word=="0"){ 
      break; 
    }
    else{
      cout<<"\t 错误,继续加油哦"<<endl;
	  string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
      if(op=="0"){
	  break;}    
    }
  } 
  cout<<"\t 本次考试的成绩(满分100)是："<<correct_num*10<<endl;
  cout<<"\t "<<endl;
  string op=get_input_string("\t 请输入(任意键 退出)：");  
}

//看释义写成语 
void exam_ui_chengyudacidian()
{
  //装载词库 
  dict_load(&dictionaries[CHENGYUDACIDIAN],DICT_PATH DICT_CHENGYUDACIDIAN);

  //生成考试题目 
  Examination exam; 
  exam_create(&exam,&dictionaries[CHENGYUDACIDIAN]);
  
  //定义一个计数量统计正确题数 
  int correct_num;

  for (int i=0;i<exam.words.size();i++)
  { 
    CLEAR(); 
    cout<<"\n\n"; 
    cout<<"\t|********************************************|\n"; 
    meaning_display_special(exam.meanings[i]); 
    cout<<"\n"; 
    cout<<"\t|********************************************|\n"; 
    string word=get_input_string("\t 请输入中文答案(0 退出）：");
    
    //cout << "\t 请输入中文答案(0 退出） ："; 
    //string word; 
    //std::getline(cin, word); 
    if(word==exam.words[i])
    { 
       correct_num++;
       cout<<"\t 正确！！！"<<endl; 
       string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
       if(op=="0"){ 
       break; 
       } 
    }
    else if(word=="0"){ 
      break; 
    }
    else{
      cout<<"\t 错误,继续加油哦"<<endl;
	  string op=get_input_string("\t 请输入( 0 退出, 其他 下一题)："); 
      if(op=="0"){
	  break;}    
    }
  } 
  cout<<"\t 本次考试的成绩(满分100)是："<<correct_num*10<<endl;
  cout<<"\t "<<endl;
  string op=get_input_string("\t 请输入(任意键 退出)：");  
}

void exam_ui() 
{
  CLEAR();
  cout<<exam_ui_prompt;
  string op;
  std::getline(cin, op);
  if(op=="1"){
  exam_ui_english_for_chinese();
  }
  else if(op=="2"){
  exam_ui_chinese_for_english();
  }
  else if(op=="3"){
  exam_ui_chengyudacidian();
  }
  else if(op=="0"){
  return;
  }
  exam_ui();
}
