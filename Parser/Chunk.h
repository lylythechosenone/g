#include <vector>
#include "../Nullable.h"

#ifndef G_CHUNK_H
#define G_CHUNK_H

enum class ChunkType
{
    BLOCK,
    LINE
};

struct Chunk
{
    int startingLine;
    int endingLine;
    ChunkType type;
    std::vector<Chunk> children;
    Nullable<Chunk> parent;
};

#endif //G_CHUNK_H
