//
// Created by 26685 on 2022-05-16 14:30.
// Description:String.h
//

#ifndef C___STRING_H
#define C___STRING_H

#include <iostream>
#include <cstring>

class String
{
    friend std::ostream &operator<<(std::ostream &os, const String &src);
public:
    String(const char *src = nullptr)
    {
        if (src == nullptr)
        {
            _pstr = new char[1];
            *_pstr = '\0';
        }
        else
        {
            _pstr = new char[strlen(src) + 1];
            strcpy(_pstr, src);
        }
    }

    ~String()
    {
        delete[] _pstr;
        _pstr = nullptr;
    }

    String(const String &src)
    {
        _pstr = new char[strlen(src._pstr) + 1];
        strcpy(_pstr, src._pstr);
    }

    bool operator>(const String &str) const
    {
        return strcmp(_pstr, str._pstr) > 0;
    }

    bool operator<(const String &str) const
    {
        return strcmp(_pstr, str._pstr) < 0;
    }

    bool operator==(const String &str) const
    {
        return strcmp(_pstr, str._pstr) == 0;
    }

    int length() const
    {
        return strlen(_pstr);
    }

    char &operator[](int index)
    {
        return _pstr[index];
    }

    char *c_str() const
    {
        return _pstr;
    }

private:
    char *_pstr;
};

inline std::ostream &operator<<(std::ostream &os, const String &src)
{
    os << src._pstr;
    return os;
}

inline String operator+(const String &l, const String &r)
{
    char *ptmp = new char[strlen(l.c_str()) + strlen(r.c_str()) + 1];
    strcpy(ptmp, l.c_str());
    strcat(ptmp, r.c_str());
    String temp(ptmp);
    delete[] ptmp;
    return temp;
}

#endif // C___STRING_