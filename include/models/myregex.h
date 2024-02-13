#ifndef MYREGEX_H
#define MYREGEX_H

class MyRegex 
{
    private:
        static const char* PATTERN_NAME;
        static const char* PATTERN_EMAIL;
        static const char* PATTERN_TEL;

	public:
		static bool name(char*);
		static bool email(char*);
		static bool tel(char*);
};

#endif