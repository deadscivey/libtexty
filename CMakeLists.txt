cmake_minimum_required(VERSION 2.8)

project(lochs)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -stdlib=libstdc++ -Wall -cxx-isystem=/usr/include/c++/5")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

include_directories(
	/usr/local/include
    /usr/include/python2.7
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/smhasher/src
    ${CMAKE_CURRENT_SOURCE_DIR}/utfcpp/source
)

link_directories(
	/usr/local/lib
)

set(LIBS
	folly
    mitie
    glog
    atomic
    pthread
)

set(BASE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lf/Barrier.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lf/Post.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lf/HPSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lf/HPDeleter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hashing.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shingle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texty/texty_util.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texty/Utf8View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texty/TokenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texty/ShingleView2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texty/simple_interface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/smhasher/src/City.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/smhasher/src/MurmurHash3.cpp
)

set(RUNNER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${BASE_SOURCES}
)

add_executable(runner ${RUNNER_SOURCES})

target_link_libraries(runner ${LIBS})

set(TEXTYPY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texty/python_interface.cpp
    ${BASE_SOURCES}
)

add_library(textypy SHARED
    ${TEXTYPY_SOURCES}
)

target_link_libraries(textypy
    ${LIBS}
)

