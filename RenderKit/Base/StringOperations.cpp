

#include <iostream>
#include <string>
#include <memory>
#include <stdarg.h>
#include <cstring>
#include <sys/signal.h>
#include <sstream>

#include "StringOperations.hpp"



bool StringOperations::beginWith( const std::string &stringToTest , const std::string &stringToFind)
{
    return !stringToTest.compare(0, stringToFind.size(), stringToFind);
    
}

std::string StringOperations::trim(const std::string& str , const std::string& whitespace )
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content
    
    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    
    return str.substr(strBegin, strRange);
}

std::string StringOperations::reduce(const std::string& str, const std::string& fill, const std::string& whitespace )
{
    // trim first
    auto result = trim(str, whitespace);
    
    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;
        
        result.replace(beginSpace, range, fill);
        
        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }
    
    return result;
}

/*
std::string StringOperations::stringWithFormat(const std::string fmt_str, ...)
{
    try
    {
        int final_n, n = ((int)fmt_str.size()) * 2;
        std::string str = 0;
        std::unique_ptr<char[]> formatted = 0;
        va_list ap = {};
        
        while(1)
        {
            formatted.reset(new char[n]);
            strcpy(&formatted[0], fmt_str.c_str());
            
            va_start(ap, fmt_str);
            final_n = vsnprintf( &formatted[0], n, fmt_str.c_str(), ap);
            va_end(ap);
            
            if (final_n < 0 || final_n >= n)
                n += abs(final_n - n + 1);
            else
                break;
        }
        return std::string(formatted.get());
    }
    
    catch ( std::logic_error &err)
    {
        printf("\n std::logic_error caught");
    }
    return "ERR_";
}
 */

std::vector<std::string> &StringOperations::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    
    return elems;
}




std::vector<std::string> StringOperations::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


std::ostream& StringOperations::operator<<( std::ostream& o, const Formatter& a )
{
    o.fill( a.fill );
    o.width( a.width );
    return o;
}





