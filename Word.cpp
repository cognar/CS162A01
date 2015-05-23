#include <iostream>
#include <string.h>
#include "Word.h"

Word::Word(const char *word) //Constructor
{
    len_ = strlen(word);
    ptr_ = new char [len_+1];
    strncpy(ptr_, word, len_);
    ptr_[len_] = 0; //add terminating null character
}

char Word::GetFirstLetter()
{
    char charBuf = ' ';
    if (ptr_ != 0)
    {
        charBuf = ptr_[0];
    }
    return tolower(charBuf); //convert to lower case
}

char* Word::GetWord()
{
    char *retptr;
    if (ptr_ != 0)
    {
        retptr = ptr_;
    }
    return retptr;

}

Word::~Word()
{
    if(ptr_ != 0)
    {
        delete [] ptr_;
        len_ = 0;
        ptr_ = 0;
    }
}
