#ifndef G_UTIL_H
#define G_UTIL_H

class Util
{
public:
    static bool isNumber(std::string str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] < 48 || str[i] > 57)
            {
                return false;
            }
        }
        return true;
    }

    static bool isNumber(char chr)
    {
        if (chr < 48 || chr > 57)
        {
            return false;
        }
        return true;
    }

    template<typename T>
    static bool includes(std::vector<T> arr, T item)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i] == item)
            {
                return true;
            }
        }
        return false;
    }
};

#endif //G_UTIL_H
