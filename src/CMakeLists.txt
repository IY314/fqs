cmake_minimum_required(VERSION 3.23)

set(FQS_SOURCES "main.cpp" "tok.cpp" "tokenizer.cpp" "error/error.cpp" "util/strop.cpp" "error/lex-error.cpp")

add_executable(fqs ${FQS_SOURCES})

target_include_directories(fqs PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
