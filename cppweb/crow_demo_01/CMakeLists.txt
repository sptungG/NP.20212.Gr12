cmake_minimum_required(VERSION 3.7)

project(crow_demo_01)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(crow_demo_01 main.cpp)
target_link_libraries(crow_demo_01 ${Boost_LIBRARIES} Threads::Threads)
