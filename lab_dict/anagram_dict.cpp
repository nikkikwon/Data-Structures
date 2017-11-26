/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream words(filename);
    vector<string> Words;
    string word;
    auto val = dict.find(word);
    
    if (!words.is_open())
        return;
    while (getline(words, word))
    {
        sort(word.begin(), word.end());
        if (val == dict.end())
		{
			Words.push_back(word);
            dict.insert(make_pair(word, Words));
        }
		else
		{
			(val->second).push_back(word);
		}
    }	
}


/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    vector<string> word;
    for (unsigned long i = 0; i < words.size(); i++)
    {
        word.push_back(words[i]);
        string temp = word[i];
        
        sort(temp.begin(), temp.end());
        auto val = dict.find(temp);

        if (val == dict.end())
        {
            vector<string> word2;
			word2.push_back(word[i]);
            dict.insert(make_pair(temp, word2));
        }
        
        else
        {
            (val -> second).push_back(word[i]);
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */

    string temp = word;
   	sort(temp.begin(), temp.end());
    auto val = dict.find(temp);
    vector<string> retval = val -> second;

    if (val == dict.end())
        return vector<string>();
    return retval;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector< vector <string>> temp;
    for (auto i = dict.begin(); i != dict.end(); i++)
    {
        if (!((i->second).size() < 2))
    	temp.push_back(i->second);
    }
    return temp;
}

