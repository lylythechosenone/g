#ifndef G_DATASTREAM_H
#define G_DATASTREAM_H

#include <memory>

template<typename T>
class DataStreamBase
{
public:
    virtual ~DataStreamBase() = default;
    virtual T get() = 0;
    virtual bool done() = 0;
};

template<typename T>
class DataStream
{
public:
    explicit DataStream(DataStreamBase<T> *_class)
    {
        this->callbacks = _class;
    }

    explicit DataStream(std::unique_ptr<DataStreamBase<T>> _class): callbacks{std::move(_class)} {}

    T get()
    {
        if (callbacks.index() == 0)
        {
            auto callbacksValue = std::get<0>(callbacks);
            return callbacksValue->get();
        } else
        {
            auto callbacksValue = std::get<1>(std::move(callbacks));
            return callbacksValue->get();
        }
    }

    bool done()
    {
        if (callbacks.index() == 0)
        {
            auto callbacksValue = std::get<0>(callbacks);
            return callbacksValue->done();
        } else
        {
            auto callbacksValue = std::get<1>(std::move(callbacks));
            return callbacksValue->done();
        }
    }

    DataStream *operator>>(T &dest)
    {
        dest = get();
        return this;
    }

private:
    std::variant<DataStreamBase<T> *, std::unique_ptr<DataStreamBase<T>>> callbacks;
};

template<typename T>
T &operator<<(T &dest, DataStream<T> &src)
{
    dest = src.get();
    return dest;
}


#endif //G_DATASTREAM_H
