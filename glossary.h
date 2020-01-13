#ifndef _GLOSSARY_H
#define _GLOSSARY_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#define GLOSSARY_FILE "glossry.txt"

using namespace std;
//生词本结构体
struct Glossary
{
	string word;             //单词 
	vector<string>means;      //单词解释 
};
//单词数量
extern int words_count;
extern vector <Glossary> glossary;

void load_glossary();
void save_glossary();
void remove_glossary(string word);

#endif // !_GLOSSSARY_HPP