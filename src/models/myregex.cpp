
#include "../../include/models/myregex.h"
#include <regex>

const char* MyRegex::PATTERN_NAME = "[_|A-Z|a-z]+[_|A-Z|a-z|0-9]+";
const char* MyRegex::PATTERN_EMAIL = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
const char* MyRegex::PATTERN_TEL = "^[0-9\\-\\+]{9,15}$";

bool MyRegex::name(char name[])
{
    std::regex pattern(MyRegex::PATTERN_NAME);
    return regex_match(name, pattern);
}

bool MyRegex::email(char email[])
{
    std::regex pattern(PATTERN_EMAIL);
    return regex_match(email, pattern);
}

bool MyRegex::tel(char tel[])
{
    std::regex pattern(PATTERN_TEL);
    return regex_match(tel, pattern);
}