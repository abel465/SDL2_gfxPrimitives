cmake_minimum_required(VERSION 3.22)
project(SDL2_gfxPrimitives)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

set(TARGET_NAME "SDL2_gfxPrimitives")
add_library(${TARGET_NAME} src/SDL2_gfxPrimitives.cpp include/SDL2_gfxPrimitives.hpp
        src/SDL2_rotozoom.cpp include/SDL2_rotozoom.hpp include/SDL2_gfxPrimitives_font.hpp)

# Blacklist method for warnings
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    target_compile_options(${TARGET_NAME} PRIVATE -Weverything -Werror
            -Wno-reserved-identifier -Wno-implicit-int-conversion -Wno-sign-conversion -Wno-double-promotion
            -Wno-bad-function-cast -Wno-float-conversion -Wno-unused-parameter -Wno-conditional-uninitialized
            -Wno-documentation-html -Wno-cast-align -Wno-implicit-int-float-conversion -Wno-implicit-float-conversion
            -Wno-float-equal -Wno-shadow -Wno-unused-macros -Wno-unused-function -Wno-c++98-compat)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(${TARGET_NAME} PRIVATE)
    execute_process(COMMAND bash -c
            "${CMAKE_CXX_COMPILER} -Q --help=warning | sed -e 's/^\\s*\\(\\-\\S*\\)\\s*\\[\\w*\\]/\\1 /gp;d' | tr -d '\\n'"
            OUTPUT_VARIABLE all_warnings)

    # Remove non c++ warnings
    string(REPLACE "-Wabsolute-value " "" all_warnings ${all_warnings})
    string(REPLACE "-Wbad-function-cast " "" all_warnings ${all_warnings})
    string(REPLACE "-Wc++-compat " "" all_warnings ${all_warnings})
    string(REPLACE "-Wdesignated-init " "" all_warnings ${all_warnings})
    string(REPLACE "-Wdiscarded-array-qualifiers " "" all_warnings ${all_warnings})
    string(REPLACE "-Wdiscarded-qualifiers " "" all_warnings ${all_warnings})
    string(REPLACE "-Wduplicate-decl-specifier " "" all_warnings ${all_warnings})
    string(REPLACE "-Wimplicit " "" all_warnings ${all_warnings})
    string(REPLACE "-Wincompatible-pointer-types " "" all_warnings ${all_warnings})
    string(REPLACE "-Wint-conversion " "" all_warnings ${all_warnings})
    string(REPLACE "-Wjump-misses-init " "" all_warnings ${all_warnings})
    string(REPLACE "-Wmissing-parameter-type " "" all_warnings ${all_warnings})
    string(REPLACE "-Wmissing-prototypes " "" all_warnings ${all_warnings})
    string(REPLACE "-Wnested-externs " "" all_warnings ${all_warnings})
    string(REPLACE "-Wold-style-declaration " "" all_warnings ${all_warnings})
    string(REPLACE "-Woverride-init " "" all_warnings ${all_warnings})
    string(REPLACE "-Woverride-init-side-effects " "" all_warnings ${all_warnings})
    string(REPLACE "-Wpointer-sign " "" all_warnings ${all_warnings})
    string(REPLACE "-Wpointer-to-int-cast " "" all_warnings ${all_warnings})
    string(REPLACE "-Wstrict-prototypes " "" all_warnings ${all_warnings})
    string(REPLACE "-Wtraditional " "" all_warnings ${all_warnings})
    string(REPLACE "-Wtraditional-conversion " "" all_warnings ${all_warnings})
    string(REPLACE "-Wunsuffixed-float-constants " "" all_warnings ${all_warnings})

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat -Werror ${all_warnings} \
        -Wno-abi -Wno-system-headers -Wno-conversion -Wno-sign-conversion -Wno-double-promotion -Wno-switch-default \
        -Wno-cast-align -Wno-float-conversion -Wno-float-equal -Wno-shadow -Wno-shadow=local -Wno-unused-macros \
        -Wno-unused-parameter -Wno-unused-function -Wno-shadow=compatible-local")
else()
    message(WARNING "Unknown compiler")
endif()

target_link_libraries(${TARGET_NAME} SDL2)