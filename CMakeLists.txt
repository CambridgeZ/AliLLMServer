cmake_minimum_required(VERSION 3.8)

project(AliLLMServer)

set(DIR1 "${CMAKE_CURRENT_SOURCE_DIR}/source")

# 显式列出源文件，或保持 GLOB
file(GLOB SOURCES "${DIR1}/*.cpp")

# 添加可执行文件
add_executable(AliLLMServer main.cpp ${SOURCES})

# 设置编译选项
target_compile_options(AliLLMServer PRIVATE -std=c++11)

# 添加包含目录
target_include_directories(AliLLMServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /Users/mac/anaconda3/include/python3.11
    /Users/mac/anaconda3/lib/python3.11/site-packages/pybind11/include
)

# 链接库
target_link_libraries(AliLLMServer PRIVATE
    /Users/mac/anaconda3/lib/libpython3.11.dylib
)