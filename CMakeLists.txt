cmake_minimum_required(VERSION 3.0)

project(2fa)

SET(CMAKE_BUILD_TYPE "Debug") #Release
# add_compile_options(-I/opt/homebrew/Cellar/nlohmann-json/3.9.1_1/include -std=c++11)
include_directories(include)

aux_source_directory(. ROOT)
aux_source_directory(src SRCDIR)

#add_executable(CPPLearn source/main.cpp)

message("tests----------------------")

add_executable(2fa ${ROOT} ${SRCDIR})
