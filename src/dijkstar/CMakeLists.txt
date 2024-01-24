cmake_minimum_required(VERSION 3.12)
project(PathPlanning)

# 设置 C++ 标准版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 寻找并包含 OpenCV
find_package(OpenCV REQUIRED)


# 添加源文件
set(SOURCES dijk.cpp )

# 生成可执行目标
add_executable(dijkstar_out ${SOURCES})

# 链接 OpenCV 库
target_link_libraries(dijkstar_out ${OpenCV_LIBS})


