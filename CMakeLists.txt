cmake_minimum_required(VERSION 3.22)
project(SDL2_gfxPrimitives)

set(CMAKE_C_STANDARD 99)
set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(include)

set(TARGET_NAME "SDL2_gfxPrimitives")
add_library(${TARGET_NAME} src/SDL2_gfxPrimitives.c include/SDL2_gfxPrimitives.h src/SDL2_rotozoom.c include/SDL2_rotozoom.h include/SDL2_gfxPrimitives_font.h)

# Blacklist method for warnings
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    target_compile_options(${TARGET_NAME} PRIVATE -Weverything -Werror
            -Wno-reserved-identifier -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-double-promotion
            -Wno-bad-function-cast -Wno-float-conversion -Wno-unused-parameter -Wno-conditional-uninitialized
            -Wno-documentation-html -Wno-cast-align -Wno-implicit-int-float-conversion -Wno-implicit-float-conversion
            -Wno-float-equal -Wno-shadow -Wno-unused-macros -Wno-unused-function)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(${TARGET_NAME} PRIVATE)
    execute_process(COMMAND bash -c
            "${CMAKE_CXX_COMPILER} -Q --help=warning | sed -e 's/^\\s*\\(\\-\\S*\\)\\s*\\[\\w*\\]/\\1 /gp;d' | tr -d '\\n'"
            OUTPUT_VARIABLE all_warnings)

    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wformat -Werror ${all_warnings} \
        -Wno-abi -Wno-system-headers -Wno-conversion -Wno-sign-conversion -Wno-double-promotion -Wno-switch-default \
        -Wno-cast-align -Wno-float-conversion -Wno-float-equal -Wno-shadow -Wno-shadow=local -Wno-unused-macros \
        -Wno-unused-parameter -Wno-unused-function -Wno-traditional -Wno-traditional-conversion \
        -Wno-unsuffixed-float-constants -Wno-bad-function-cast")
else()
    message(WARNING "Unknown compiler")
endif()

target_link_libraries(${TARGET_NAME} SDL2)