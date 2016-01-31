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
    ${CMAKE_CURRENT_SOURCE_DIR}/external/json/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src
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


set(LIBGUMBO_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/attribute.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/char_ref.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/error.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/parser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/string_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/string_piece.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/tag.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/tokenizer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/utf8.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/util.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/gumbo-parser/src/vector.c
)

add_library(libgumbo
    ${LIBGUMBO_SOURCES}
)


set(LIBS
    libstemmer
    libgumbo
    folly
    mitie
    glog
    double-conversion
    atomic
    pthread
)

set(BASE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Language.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cleaning/basic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hashing/hash_funcs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/misc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/ScopeGuard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util/fs.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/unicode/UnicodeBlock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/unicode/support.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stemming/Utf8Stemmer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stemming/SbStemmerWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stemming/StemmerManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stemming/ThreadSafeStemmerManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/StopwordFilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/MultiLanguageStopwordFilter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/english_stopwords.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/french_stopwords.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/german_stopwords.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/italian_stopwords.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/russian_stopwords.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stopwords/spanish_stopwords.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/Utf8View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/Utf8Iterator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/RandomAccessNGramView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/RandomAccessUtf8View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/TokenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/ShingleView2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/LanguageProfiles.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/GlobalLanguageProfiles.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/DetectionRunner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/OwningLanguageDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/GlobalLanguageDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/NonOwningLanguageDetector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/HtmlDom.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/Node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/Tag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/GumboVectorWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/GumboOutputWrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/MetaTags.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/goose/GooseContentExtractor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/goose/GooseOptions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/goose/StupidStopwordCounter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/goose/TextCleaner.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/goose/util.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/smhasher/src/City.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/smhasher/src/MurmurHash3.cpp
)

add_library(texty
    ${BASE_SOURCES}
)
target_link_libraries(texty ${LIBS})

add_executable(runner
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(runner texty ${LIBS})

set(GTEST_LIB
    ${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/googletest/src/gtest-all.o
)

add_executable(unit_test_runner
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/test/unit/test_Utf8View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/test/unit/test_TokenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/test/unit/test_ShingleView2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/string_views/test/unit/test_RandomAccessUtf8View.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/test/unit/test_LanguageProfiles.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/html/test/unit/test_HtmlDomAndNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/testing/run_tests.cpp
)
target_link_libraries(unit_test_runner texty ${GTEST_LIB} ${LIBS})

add_executable(func_test_runner
    ${CMAKE_CURRENT_SOURCE_DIR}/src/language_detection/test/functional/test_language_detection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/testing/run_tests.cpp    
)

target_link_libraries(func_test_runner texty ${GTEST_LIB} ${LIBS})

