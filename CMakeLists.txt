cmake_minimum_required(VERSION 2.8)

project(libtexty)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -stdlib=libstdc++ -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

include_directories(
	/usr/local/include
    /usr/include/python2.7
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/smhasher/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/utfcpp/source
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/pybind11/include
)

link_directories(
	/usr/local/lib
)

set(LIBSTEMMER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_danish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_danish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_dutch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_dutch.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_english.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_english.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_finnish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_finnish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_french.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_french.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_german.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_german.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_hungarian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_hungarian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_italian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_italian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_norwegian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_norwegian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_porter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_porter.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_portuguese.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_portuguese.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_2_romanian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_romanian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_KOI8_R_russian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_russian.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_spanish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_spanish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_ISO_8859_1_swedish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_swedish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/src_c/stem_UTF_8_turkish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/runtime/api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/runtime/utilities.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/libstemmer/libstemmer/libstemmer.c
)

add_library(libstemmer
    ${LIBSTEMMER_SOURCES}
)

set(LIBS
    libstemmer
    folly
    mitie
    glog
    atomic
    pthread
)

set(BASE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Language.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hashing/hash_funcs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/misc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stemming/BaseStemmer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stemming/Utf8Stemmer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/Utf8View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/TokenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/ShingleView2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/smhasher/src/City.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/smhasher/src/MurmurHash3.cpp
)

set(RUNNER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${BASE_SOURCES}
)

add_executable(runner ${RUNNER_SOURCES})

target_link_libraries(runner ${LIBS})
