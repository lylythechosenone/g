#ifndef G_NULLABLE_H
#define G_NULLABLE_H

template<typename T>
class Nullable
{
public:
    Nullable(T val)
    {
        this->val = val;
        null = false;
    }

    Nullable(decltype(nullptr)): val() {}

    Nullable(): val() {}

    T get()
    {
        return val;
    }

    bool isEqual(T other)
    {
        if (null)
        {
            return false;
        }
        if (val == other)
        {
            return true;
        }
        return false;
    }

    bool operator==(T other)
    {
        return isEqual(other);
    }

    bool operator==(decltype(nullptr)) const
    {
        return null;
    }

    bool operator!=(T other)
    {
        return !isEqual(other);
    }

    bool operator!=(decltype(nullptr)) const
    {
        return !null;
    }

    Nullable &operator=(T other)
    {
        val = other;
        null = false;
        return *this;
    }

    Nullable &operator=(decltype(nullptr))
    {
        null = true;
        return *this;
    }

private:
    bool null = true;
    union
    {
        T *val;
    };
};

#endif //G_NULLABLE_H
