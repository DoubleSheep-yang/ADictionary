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

void exam_create(Examination* exam, Dictionary* dict);
//void exam_ui_display();
//void exam_ui_chinese_english();
void exam_ui_english_for_chinese();
void exam_ui_chinese_for_english();
void exam_ui_chengyu();
void exam_ui();


#endif // !_EXAM_H

