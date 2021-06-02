cmake_minimum_required(VERSION 3.19)
project(g)

set(CMAKE_CXX_STANDARD 20)

add_executable(g main.cpp DataStream.h g.h Nullable.h Number.h Util.h Value.h Lexer/Lexer.h Lexer/Token.h Parser/Parser.h Parser/Chunk.h Lexer/LineTemplates.h)
target_link_libraries(g stdc++fs)