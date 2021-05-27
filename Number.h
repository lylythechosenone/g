#ifndef G_NUMBER_H
#define G_NUMBER_H

#include <math.h>
#include <climits>
#include "Util.h"

class Number
{
public:
    bool isSigned;
    size_t size() const
    {
        if (value.index() == 5)
        {
            return 4;
        }
        return pow(2, (int)(value.index() / 2.0f + 0.5f) - 1);
    }

    Number() {};

    Number(const std::string str) {*this = str;}

    Number(const unsigned int value) {*this = value;}

    Number(const signed int value) {*this = value;}

    Number(const std::variant<unsigned char, unsigned short, unsigned long, unsigned long long> value) {*this = value;}

    Number(const std::variant<signed char, signed short, signed long, signed long long> value) {*this = value;}

    Number &operator=(const std::string str)
    {
        if (str[0] == '-')
        {
            if (auto num = toLL(str); num <= CHAR_MAX && num >= CHAR_MIN)
            {
                this->value = (signed char)num;
            } else if (num <= SHRT_MAX && num >= SHRT_MIN)
            {
                this->value = (signed short)num;
            } else if (num <= INT_MAX && num >= INT_MIN)
            {
                this->value = (signed int)num;
            } else if (num <= LONG_MAX && num >= LONG_MIN)
            {
                this->value = (signed long)num;
            } else
            {
                this->value = num;
            }
            return *this;
        }

        if (auto num = toULL(str); num <= UCHAR_MAX)
        {
            this->value = (unsigned char)num;
        } else if (num <= USHRT_MAX)
        {
            this->value = (unsigned short)num;
        } else if (num <= UINT_MAX)
        {
            this->value = (unsigned int)num;
        } else if (num <= ULONG_MAX)
        {
            this->value = (unsigned long)num;
        } else
        {
            this->value = num;
        }
        return *this;
    }

    Number &operator=(const unsigned int val)
    {
        isSigned = true;
        if (val <= UCHAR_MAX)
        {
            value = (unsigned char)val;
        } else if (val <= USHRT_MAX)
        {
            value = (unsigned short)val;
        } else
        {
            value = (unsigned int)val;
        }
        return *this;
    }

    Number &operator=(const signed int val)
    {
        isSigned = true;
        if (val <= CHAR_MAX && val >= CHAR_MIN)
        {
            this->value = (signed char)val;
        } else if (val <= SHRT_MAX && val >= SHRT_MIN)
        {
            this->value = (signed short)val;
        } else
        {
            this->value = (signed int)val;
        }
        return *this;
    }

    Number &operator=(const std::variant<unsigned char, unsigned short, unsigned long, unsigned long long> val)
    {
        isSigned = false;
        std::visit([this](const auto &val)
                   {
                       this->value = val;
                   }, val);
        return *this;
    }

    Number &operator=(const std::variant<signed char, signed short, signed long, signed long long> val)
    {
        isSigned = true;
        std::visit([this](const auto &val)
                   {
                       this->value = val;
                   }, val);
        return *this;
    }

    bool operator==(const std::variant<signed char, unsigned char, signed short, unsigned short, signed int, unsigned int,
            signed long long, unsigned long long, signed long, unsigned long> value) const
    {
        return value == this->value;
    }

    std::string toString() const
    {
        std::string toReturn;
        std::visit([this, &toReturn](const auto &val)
                   {
                       toReturn = std::to_string(val);
                   }, value);
        return toReturn;
    }

private:
    std::variant<signed char, unsigned char, signed short, unsigned short, signed int, unsigned int,
            signed long long, unsigned long long, signed long, unsigned long> value;

    unsigned long long toULL(std::string str) {
        unsigned long long toReturn = 0;
        for (int i = 0; i < str.length(); i++) {
            if (!Util::isNumber(str[i])) {
                throw std::string("'") + str[i] + "' is not a number.";
            }
            toReturn += (str[i] - 48) * pow(10, i);
        }
        return toReturn;
    }

    long long toLL(std::string str) {
        if (str[0] == '-') {
            return -toULL(str.substr(1));
        } else {
            return toULL(str);
        }
    }
};

#endif //G_NUMBER_H
