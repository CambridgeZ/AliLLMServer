cmake_minimum_required(VERSION 3.5)

project(Basic_ReactorV2)

set(DIR1 "./source")

file(GLOB SOURCES "${DIR1}/*.cpp")

# 添加可执行文件
add_executable(Basic_ReactorV2 main.cpp ${SOURCES})

# 设置编译选项
target_compile_options(Basic_ReactorV2 PRIVATE -std=c++11)

# 添加包含目录
target_include_directories(Basic_ReactorV2 PRIVATE
    /Users/mac/anaconda3/include/python3.11
    /Users/mac/anaconda3/lib/python3.11/site-packages/pybind11/include
    include
)

# 链接库
target_link_libraries(Basic_ReactorV2 PRIVATE
    /Users/mac/anaconda3/lib/libpython3.11.dylib
)