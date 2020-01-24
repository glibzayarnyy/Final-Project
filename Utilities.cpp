// Name: Kenneth Yue
// Seneca Student ID: 127932176
// Seneca email: kyue3@myseneca.ca
// Date of completion: November 14, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Utilities.h"
#include <string>

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t FW) {
    m_widthField = FW;
}

size_t Utilities::getFieldWidth() const {
    return m_widthField;
}

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
    
    if (!more) throw std::string("*** Nothing to extract!! ***");
    // check if it is the last character
    if (next_pos + 1u >= str.size()) throw int(-1);


    size_t cur_pos = next_pos;
    // search for next delimiter
    size_t end_pos = str.find(m_delimiter, cur_pos);
    
    std::string substr;
    
    // check if final delimiter
    if (end_pos == std::string::npos) {
        more = false;
        substr = str.substr(cur_pos);
        // pop_back any "next line" characters
        if (substr.back() == '\n' || substr.back() == '\r')
            substr.pop_back();
    } else {
        more = true;
        next_pos = end_pos + 1u;
        if (end_pos == cur_pos)        
            throw std::string("*** Nothing between delimiters ***");
        substr = str.substr(cur_pos, end_pos-cur_pos);
    }

    if (substr.size() > m_widthField) 
        m_widthField = substr.size();

    return substr;
}

void Utilities::setDelimiter(const char& DL) {
    Utilities::m_delimiter = DL;
}

const char Utilities::getDelimiter() const {
    return m_delimiter;
}