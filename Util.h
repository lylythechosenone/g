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

    template<typename T>
    static bool includes(std::vector<std::vector<T>> arrs, T item)
    {
        for (const auto &arr : arrs) {
            for (int i = 0; i < arr.size(); i++)
            {
                if (arr[i] == item)
                {
                    return true;
                }
            }
        }
        return false;
    }

    static std::vector<std::string> split(std::string str, std::string delimiter) {
        std::vector<std::string> toReturn;

        auto start = 0U;
        auto end = str.find(delimiter);
        while (end != std::string::npos)
        {
            toReturn.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }
        toReturn.push_back(str.substr(start, end));
        return toReturn;
    }

    static std::string replace(std::string str, std::string token, std::string value) {
        auto split = Util::split(str, token);
        std::string toReturn;
        for (int i = 0; i < split.size(); i++) {
            toReturn += split[i] + value;
        }
        return toReturn;
    }
};

#endif //G_UTIL_H
