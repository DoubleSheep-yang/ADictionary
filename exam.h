#ifndef _EXAM_H
#define _EXAM_H
#include <string> 
#include <vector>
#include "dict.h"

using namespace std;

typedef struct
{
	vector<string>words;
	vector< vector<string> >meanings;
}Examination;

void exam_creat(Examination* exam, Dictionary* dict);
 
void exam_ui();
void exam_ui_english_for_chinese();
void exam_ui_chinese_for_english();
void exam_ui_chengyudacidian();

#endif //!_EXAM_H
