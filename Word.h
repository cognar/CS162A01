#ifndef WORD_H
#define WORD_H

class Word
{
    private:
        char *ptr_;
        int len_;
    public:
        Word(const char *word);
        ~Word();
        char GetFirstLetter();
        char *GetWord();
};

#endif
