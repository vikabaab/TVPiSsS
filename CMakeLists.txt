cmake_minimum_required(VERSION 3.22)
project(TVPiS)

set(CMAKE_CXX_STANDARD 17)

add_executable(TVPiS main.cpp Allocator.cpp include.hpp List.hpp ListNode.hpp Deque.hpp Queue.hpp Stack.hpp Utils.hpp HashTable.hpp)
