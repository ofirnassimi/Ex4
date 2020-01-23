cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 main.cpp Server.h MySerialServer.h ClientHandler.h MyTestClientHandler.h Solver.h CacheManager.h StringReverser.h Matrix.h FileCacheManager.h Searchable.h State.h)