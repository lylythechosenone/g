#ifndef G_PARSER_H
#define G_PARSER_H

#include "Chunk.h"

class ParserDataStream : public DataStreamBase<Chunk>
{
public:
    ParserDataStream(DataStream<TokenizedLine> *stream)
    {
        this->stream = stream;
    }

    Chunk parseChunk()
    {
        return Chunk();
    }

    Chunk get() override
    {
        return parseChunk();
    }

    bool done() override
    {
        return stream->done();
    }

    bool doneNow() override {
        return stream->doneNow();
    }

private:
    DataStream<TokenizedLine> *stream = nullptr;
};

class Parser
{
public:
    inline static DataStreamBase<Chunk> *stream = nullptr;

    static void cleanUp()
    {
        delete stream;
    }

    static DataStream<Chunk> parse(DataStream<TokenizedLine> *strm)
    {
        Parser::stream = new ParserDataStream(strm);
        return DataStream(Parser::stream);
    }
};

#endif //G_PARSER_H
