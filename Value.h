#include <variant>
#include <string>

#include "Number.h"

#ifndef G_VALUE_H
#define G_VALUE_H

class Value
{
public:
    Value() {}

    Value(const Number val)
    {
        value = val;
    }

    Value(const std::string val)
    {
        value = val;
    }

    Value(const char val)
    {
        value = std::string("") + val;
    }

    Value(const bool val)
    {
        value = val;
    }

    void set(const Number val)
    {
        value = val;
    }

    void set(const std::string val)
    {
        value = val;
    }

    void set(const char val)
    {
        value = std::string("") + val;
    }

    void set(const bool val)
    {
        value = val;
    }

    Number getNum() const
    {
        if (value.index() == 2)
        {
            const bool val = std::get<2>(value);
            return val ? 1 : 0;
        }
        if (value.index() == 0) return std::get<0>(value);

        return std::get<1>(value);
    }

    std::string getString() const
    {
        if (value.index() == 2)
        {
            const bool val = std::get<2>(value);
            return val ? "true" : "false";
        }
        if (value.index() == 1) return std::get<1>(value).toString();

        return std::get<0>(value);
    }

    bool getBool() const
    {
        if (value.index() == 1) return std::get<1>(value) == 1;
        if (value.index() == 0) return std::get<0>(value) == "true";

        return std::get<2>(value);
    }

private:
    std::variant<std::string, Number, bool> value;
};

#endif //G_VALUE_H
