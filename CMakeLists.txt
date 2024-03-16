cmake_minimum_required(VERSION 3.10)
project(TensorJ)

set(CMAKE_CXX_STANDARD 17)

find_package(TensorFlow REQUIRED)
find_package(ANTLR REQUIRED)

include_directories(${TENSORFLOW_INCLUDE_DIRS})
include_directories(${ANTLR4_INCLUDE_DIRS})

add_custom_target(
    GenerateParser
    COMMAND antlr4 -Dlanguage=Cpp J.g4
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

add_executable(TensorJ main.cpp jtensorflow_builer.h ${ANTLR4_J_CXX_OUTPUTS})

add_dependencies(TensorJ GenerateParser)

target_link_libraries(TensorJ ${TENSORFLOW_LIBRARIES})
target_link_libraries(TensorJ ${ANTLR4_LIBRARIES} antlr4-runtime)