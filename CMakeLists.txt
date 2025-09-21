cmake_minimum_required(VERSION 3.31)
project(local_search_engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(local_search_engine src/main.cpp
        src/FileCrawler.cpp
        src/FileCrawler.h)
