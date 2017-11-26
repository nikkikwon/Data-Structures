/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include<iostream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

	/* Your code goes here! */

	ifstream words(word_list_fname);
	string word;
	vector <string> Words;

	if(words.is_open()) 
	{
   		while(getline(words, word)) 
        {
			if(word.length() == 5)
				Words.push_back(word);
		}
	}

	for (unsigned long i = 0; i < Words.size(); i++)
	{
		string temp = Words[i].substr(1);
		string temp2;

		temp2.append(Words[i].substr(0, 1));
		temp2.append(Words[i].substr(2));
	
		if(d.homophones(Words[i], temp))
		{	
			if(d.homophones(Words[i], temp2))
			{
					tuple<string, string, string> key;
					get<0>(key) = Words[i]; 
					get<1>(key) = temp;
					get<2>(key) = temp2;
					ret.push_back(key);
			}	
		}			 
	}
    return ret;
}












