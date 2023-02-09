#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string line)
{
std::set<std::string> result;
    std::stringstream ss(line);
    std::string word;
    while (ss >> word) {
        for (int i = 0, len = word.length(); i < len; i++) {
            if (ispunct(word[i])) {
                if (i == 0) {
                    word = word.substr(1);
                    i--;
                    len--;
                } else if (i == len - 1) {
                    word = word.substr(0, len - 1);
                } else {
                    std::string left = word.substr(0, i);
                    std::string right = word.substr(i + 1);
                    if (left.length() > 1) {
                        result.insert(left);
                    }
                    if (right.length() > 1) {
                        word = right;
                        i = -1;
                        len = right.length();
                    } else {
                        break;
                    }
                }
            }
        }
        if (word.length() > 1) {
            result.insert(word);
        }
    }
    return result;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
