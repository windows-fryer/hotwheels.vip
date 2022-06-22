# thank you to cristeigabriel for helping me with this!
cmake_minimum_required(VERSION 3.21)
project(hotwheels_bf4)

set(CMAKE_CXX_STANDARD 23)

# we probably dont need this many, only 1 should be fine. this looks funni
file(GLOB_RECURSE SRC
        "project/*.h" ,
        "project/*.hpp" ,
        "project/*.c" ,
        "project/*.cpp" ,
        "project/*.inl" ,
        "project/**/*.h" ,
        "project/**/*.hpp" ,
        "project/**/*.c" ,
        "project/**/*.cc" ,
        "project/**/*.cpp" ,
        "project/**/*.inl" ,
        )


add_library(${PROJECT_NAME} SHARED ${SRC})

find_library(FREETYPE_LIBRARY freetype.lib PATHS "project/dependencies/freetype")

message(${FREETYPE_LIBRARY})

target_link_libraries(${PROJECT_NAME} "${FREETYPE_LIBRARY}")

target_link_directories(${PROJECT_NAME} PRIVATE "project/dependencies/freetype")
target_include_directories(${PROJECT_NAME} PRIVATE "project/dependencies/freetype/include")

#add_definitions(/MP)
#add_compile_options(/DEBUG FULL)