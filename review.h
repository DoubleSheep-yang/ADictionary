#ifndef _REVIEW_H
#define _REVIEW_H
#include <string> 
#include <vector>
#include "glossary.h"
#include "exam.h"
#include "dict.h"

void review_ui();
void review_english_to_chinese();
void review_chinese_to_english();
void review_chengyudacidian();
void exam_new_create(Examination* exam, New_Dictionary* dict);
void dict_new_load(Dictionary* dict, const string& filename);
 
#endif // !_REVIEW_H
