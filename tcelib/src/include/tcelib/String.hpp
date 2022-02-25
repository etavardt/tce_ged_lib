#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cerr;
using std::cout;
using std::endl;

using std::size_t;

// the following produce a strange error in VS Code editor
//using StringStream = std::stringstream;
//typedef std::stringstream StringStream;

typedef std::string String;
typedef std::vector<String> ArrayOfStrings;
typedef std::shared_ptr<String> SharedStringPointer;

template<typename T>
inline String toString(T n) { return std::to_string(n); }

inline SharedStringPointer makeSharedString() { return std::make_shared<String>(); }

inline ArrayOfStrings toArrayOfStrings(const String &str, const char delim) {
    ArrayOfStrings newArrayOfStrings;
    // cout << "str: " << str << endl << "delim: " << delim << endl;
    size_t found = str.find_first_of(delim);
    size_t startPos = 0;
    size_t i = 0;
    while (found != String::npos) {
        newArrayOfStrings.push_back(str.substr(startPos, found - startPos));
        cout << "newArrayOfStrings[" << i << "]: " << newArrayOfStrings[i] << endl;
        startPos = found + 1;
        found = str.find_first_of(delim, startPos);
        i++;
    }

    // cout << "newArrayOfStrings.size(): " << newArrayOfStrings.size() << endl
    // << "i: " << i << endl;
    return newArrayOfStrings;
}

inline String eraseAllMatching(const String &str, const String &remStr) {
    // cout << "str: " << str << endl << "remStr: " << remStr << endl;
    String newString = str;
    size_t found = newString.find_first_of(remStr);
    // cout << "found: " << found << endl;
    while (found != String::npos) {
        newString.erase(found, 1);
        found = newString.find_first_of(remStr);
        // cout << "found: " << found << endl;
    }

    return newString;
}
inline String &trimfnc(String &str) {
    const String typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
    str.erase(0, str.find_first_not_of(typeOfWhitespaces));
    return str;
}
/*
Example Code to convert to lowercase

#include <algorithm>
#include <iostream>
using namespace std;

int main() {
   string my_str = "Hello WORLD";

   cout << "Main string: " << my_str << endl;
   transform(my_str.begin(), my_str.end(), my_str.begin(), ::tolower);

   cout << "Converted String: " << my_str;
}
Output
Main string: Hello WORLD
Converted String: hello world
*/
