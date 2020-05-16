project(pyparser)

cmake_minimum_required(VERSION 2.6)

include_directories(/usr/local/include/antlr4-runtime ./target/generated-sources/antlr4 .)
link_directories(/usr/local/lib)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11 -O3")

set(sources 
  ./target/generated-sources/antlr4/Python3BaseListener.cpp
  ./target/generated-sources/antlr4/Python3Listener.cpp
  ./target/generated-sources/antlr4/Python3Lexer.cpp
  ./target/generated-sources/antlr4/Python3Parser.cpp
  Main.cpp
  )
add_executable(pyparser ${sources})
target_link_libraries(pyparser antlr4-runtime)
