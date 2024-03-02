cmake_minimum_required (VERSION 3.10)

project (dynamic)

set (DYNAMIC_SRC
    src/test.cpp
    include/test.h
)

set (MAIN_SRC
    src/main.cpp
    include/test.h
)

include_directories (.)

# generate a dynamic library
add_library (test SHARED ${DYNAMIC_SRC})

# generate a executable file
link_directories (build)
add_executable (main ${MAIN_SRC})
target_link_libraries (main test)
