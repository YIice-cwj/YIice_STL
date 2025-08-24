cmake_minimum_required(VERSION 3.10)
project(yiice_stl VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置构建类型（如果没有指定的话）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 包含目录
include_directories(include)

# 编译选项函数
function(set_compile_options target_name)
    target_compile_options(${target_name} PRIVATE 
        $<$<CXX_COMPILER_ID:GNU,Clang>:
            -Wall           # 启用所有警告
            -Wextra         # 启用额外警告
            -Wpedantic      # 启用严格的 ISO C++ 警告
            -Wno-sign-compare               # 禁用有符号/无符号比较警告
            -Wno-unused-but-set-variable    # 禁用"变量设置但未使用"警告
            -Wno-array-bounds               # 禁用数组边界检查警告
        >
        $<$<CXX_COMPILER_ID:MSVC>:
            /W4             # 启用 Level 4 警告
            /permissive-    # 禁用非标准扩展
        >
        $<$<CONFIG:Debug>:
            $<$<CXX_COMPILER_ID:GNU,Clang>:-g -O0>
            $<$<CXX_COMPILER_ID:MSVC>:/Od /Zi>
        >
        $<$<CONFIG:Release>:
            $<$<CXX_COMPILER_ID:GNU,Clang>:-O3 -DNDEBUG>
            $<$<CXX_COMPILER_ID:MSVC>:/O2 /DNDEBUG>
        >
    )
endfunction()

# 创建测试可执行文件的函数
function(add_test_executable test_name source_file)
    add_executable(${test_name} test/${source_file})
    set_compile_options(${test_name})
    set_target_properties(${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    )
    
    # 启用测试
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# 添加测试可执行文件
add_test_executable(test_type_traits test_type_traits.cc)
add_test_executable(test_utility test_utility.cc)
add_test_executable(test_functional test_functional.cc)
add_test_executable(test_array test_array.cc)
add_test_executable(test_vector test_vector.cc)

# 启用测试
enable_testing()

# 添加自定义目标来运行所有测试
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_type_traits test_utility test_memory test_functional test_string
    COMMENT "Running all tests"
)

# 添加清理目标
add_custom_target(clean_tests
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/bin
    COMMENT "Cleaning test executables"
)

# 信息输出
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Output Directory: ${CMAKE_SOURCE_DIR}/bin")

# 编译器特定警告（可选）
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0")
        message(WARNING "GCC version ${CMAKE_CXX_COMPILER_VERSION} may not fully support C++14")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.4")
        message(WARNING "Clang version ${CMAKE_CXX_COMPILER_VERSION} may not fully support C++14")
    endif()
endif()

# 可选：添加代码覆盖率支持（仅在 Debug 模式下）
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    option(ENABLE_COVERAGE "Enable code coverage" OFF)
    if(ENABLE_COVERAGE)
        message(STATUS "Code coverage enabled")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()
endif()

# 可选：添加静态分析支持
option(ENABLE_CLANG_TIDY "Enable clang-tidy analysis" OFF)
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
    else()
        message(WARNING "clang-tidy not found")
    endif()
endif()