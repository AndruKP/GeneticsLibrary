cmake_minimum_required(VERSION 3.30)

set(TARGET_NAME GeneticsLibrary)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
        src/sequence.cpp
        src/sequence.h
        src/dna.cpp
        src/dna.h
        src/rna.cpp
        src/rna.h
        src/constants.h
        src/SequenceWrapper.cpp
        src/SequenceWrapper.h
        src/Protein.cpp
        src/Protein.h
        src/Aminoacid.cpp
        src/Aminoacid.h
        src/Validators.cpp
        src/Validators.h
        src/ErrorsConstants.h
        src/record.cpp
        src/record.h
        src/FASTAReader.cpp
        src/FASTAReader.h
)

set(TEST_FILES
        tests/testSequence.cpp
        tests/testDNA.cpp
        tests/testRNA.cpp
        tests/testRecord.cpp
        tests/testFASTAReader.cpp
        tests/testAminoacid.cpp
        tests/testProtein.cpp
        tests/testValidators.cpp
        tests/testSequenceWrapper.cpp
)

set(GTEST_SOURCE_FILES
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

add_library(tests OBJECT ${TEST_FILES})
add_library(gtest OBJECT ${GTEST_SOURCE_FILES})

find_package(Threads REQUIRED)

include_directories(GoogleTest)
include_directories(src)
add_executable(${TARGET_NAME} ${SOURCE_FILES} ${TEST_FILES} ${GTEST_SOURCE_FILES})
target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(TARGET GeneticsLibrary PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/data/Cryptosporidium hominis/ncbi_dataset/data/GCA_000006425.2/GCA_000006425.2_ASM642v2_genomic.fna"
        #        ${CMAKE_SOURCE_DIR}/subtitlesWithWrong.srt
        #        ${CMAKE_SOURCE_DIR}/The_Matrix.srt
        $<TARGET_FILE_DIR:GeneticsLibrary>
        VERBATIM)
add_custom_command(TARGET GeneticsLibrary PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data/croppedContig"
        "$<TARGET_FILE_DIR:GeneticsLibrary>/croppedContig"
        VERBATIM)