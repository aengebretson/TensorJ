cmake_minimum_required(VERSION 3.10)
project(TensorJ)

set(CMAKE_CXX_STANDARD 17)

# find_package(TENSORFLOW REQUIRED)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(JParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
flex_target(JLexer lexer.l ${CMAKE_CURRENT_BINARY_DIR})

ADD_FLEX_BISON_DEPENDENCY(JLexer JParser)

include_directories(${TENSORFLOW_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(TensorJ 
    main.cpp 
    ${BISON_JParse_OUTPUTS} 
    ${FLEX_JLexer_OUTPUTS}
)

#add_dependencies(TensorJ GenerateParser)

#target_link_libraries(TensorJ ${TENSORFLOW_LIBRARIES})
target_link_libraries(TensorJ ${FLEX_LIBRARIES} ${BISON_LIBRARIES})