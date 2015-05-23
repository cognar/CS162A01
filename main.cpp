/*
Name: Connor McCloskey
Date: 4/12/2015
Assignment: Assignment 1
Description: Reads a text file and stores the text in an array of user defined Word objects
utilizing dynamic memory allocation and pointers, can echo contents of array and
remove words based on the first character.
Sources: cplusplus.com, stackoverflow.com, cppreference.com
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Word.h"

using namespace std;

const int   FILE_PATH_SZ = 512, LINE_SIZE = 128;
Word        **g_wordArray;
int         g_arrSz;

void freeWordArray()
{
    if (g_wordArray != 0)   //do nothing if g_wordArray is already empty
    {
        for( int i = 0; i < g_arrSz; i++)
        {
            if(g_wordArray[i] != 0) //do nothing if entry is already empty
            {
                delete g_wordArray[i];
            }
        }
        delete [] g_wordArray;
        g_arrSz = 0;
    }
}

int main()
{
    char        filePath [FILE_PATH_SZ] = {}, usrIn = ' ', lineBuf [LINE_SIZE] = {};
    bool        endProg = false;
    int         wordCount = 0;
    ifstream    inFile;
    g_arrSz     = 0;
    g_wordArray = 0;

    while (!endProg)
    {
        cout << "a) Read a text file \nb) Remove words starting with letter \nc) Print words to console \nd)Quit \n";
        cin >> usrIn;
        usrIn = tolower(usrIn);     //makes selection case insensitive
        switch (usrIn)
        {
            case 'a':   //reads words to array
                cout << "Please enter the file path: ";
                cin >> filePath;
                inFile.open(filePath);
                if (!inFile)    //throw an error is inFile fails to open
                {
                    cout <<"\nFile could not be found\n";
                }
                else
                {
                    wordCount = 0;
                    while(inFile >> lineBuf)    //count words
                    {
                        wordCount++;
                    }
                    freeWordArray();    //clear array of any previous data
                    inFile.close();
                    g_arrSz = wordCount;    //set size of array
                    inFile.clear(std::ios_base::goodbit);
                    g_wordArray = new Word *[g_arrSz];  //allocate array
                    for(int j = 0; j < g_arrSz; j++)    //initialize array to 0's
                    {
                        g_wordArray[j] = 0;
                    }
                    inFile.open(filePath);
                    int i = 0;
                    while(inFile >> lineBuf)
                    {
                        g_wordArray[i] = new Word(lineBuf);     //add word to array
                        i++;
                    }
                    cout << "Successfully loaded " << wordCount << " words.\n";
                }

                break;
            case 'b':   //removes all words in array starting with usrIn
                wordCount = 0;
                usrIn = ' ';
                cout << "Please enter a letter: ";
                cin >> usrIn;
                usrIn = tolower(usrIn);
                if (isalpha(usrIn))    //only accept alphabetical characters
                {
                    for(int i = 0; i < g_arrSz; i++)
                    {
                        if(g_wordArray[i] != 0)     //skip any previously deleted entries
                        {
                            if(g_wordArray[i]->GetFirstLetter() == usrIn)       //checks first letter of word
                            {
                                g_wordArray[i]->~Word();    //cals decontructor on the matching word
                                wordCount++;
                            }
                        }
                    }
                    cout << wordCount << " words starting with " << usrIn << " were removed.\n";
                }
                break;
            case 'c':   //print all words
            {
                for(int i = 0; i < g_arrSz; i++)    //calls GetWord method for every non-zero (not removed) word
                {
                    if (g_wordArray[i] != 0)    //don't try and call GetWord() if word has been deleted
                    {
                        cout << g_wordArray[i]->GetWord() << " ";
                    }

                }
                cout << "\n";
                break;
            }
            case 'd':   //quit program
            {
                endProg = true;
                break;
            }
            default:    //returns to begining if usrIn is not a valid selection
            {
                cout << "Please choose a valid selection (a-d).\n";
            }
        }
    }
    return 0;
}
