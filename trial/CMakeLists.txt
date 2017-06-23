cmake_minimum_required(VERSION 3.7)
project (SFML-lib)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED network audio graphics window system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(SOURCE_FILES sfml.cpp)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_INCLUDE_DIR} ~/.brew/Cellar/sfml/2.4.2/lib/ )
    ADD_LIBRARY(SFML SHARED ${SOURCE_FILES})
    target_link_libraries(SFML ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
