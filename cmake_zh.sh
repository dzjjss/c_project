#!/bin/bash

# 初始化函数：定义基本变量和创建必要目录
initialize() {
    clear # 清屏
    # 获取脚本当前工作目录
    workspacefolder="$(pwd)"
    src="${workspacefolder}/src"
    cache_folder="${workspacefolder}/.cache"
    cache_file="${cache_folder}/last_subdir.cache"
    timestamp=$(date +%y-%m-%d_%H:%M:%S)
    log_file="${workspacefolder}/tmp/log/${timestamp}.build.log"

    echo "初始化目录..."
    mkdir -p "${workspacefolder}/build" "${workspacefolder}/tmp/log" \
        "${workspacefolder}/bin" "${workspacefolder}/build/lib" "${workspacefolder}/build/arc" "${cache_folder}"
}

# 选择构建目录
choose_build_directory() {
    clear # 清屏
    echo "src目录下可用的子目录："
    ls "${src}"

    # 检查是否存在缓存文件并读取上次的选择
    last_subdir=""
    if [ -f "${cache_file}" ]; then
        last_subdir=$(cat "${cache_file}")
        echo "上次选择的子目录为: ${last_subdir}"
    fi

    while true; do
        echo "请输入您希望编译的子目录名称[${last_subdir}]："
        read -r subdir
        if [ -z "$subdir" ] && [ -n "${last_subdir}" ]; then
            subdir=${last_subdir}
        fi
        if [ -n "$subdir" ] && [ -d "${src}/${subdir}" ]; then
            clear # 有效输入后清屏
            echo "当前选择的子目录：${subdir}"
            break
        else
            clear # 无效输入后清屏
            echo "输入无效。请输入一个有效的子目录名称。"
            echo "src目录下可用的子目录："
            ls "${src}" # 再次显示目录列表
        fi
    done

    # 保存当前选择到缓存文件
    echo "${subdir}" >"${cache_file}"
}

# 生成CMakeLists.txt文件
generate_cmake_lists() {
    clear # 清屏
    cat <<EOF >"${workspacefolder}/CMakeLists.txt"
cmake_minimum_required(VERSION 3.0.0)
project(${subdir})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB SOURCES "\${PROJECT_SOURCE_DIR}/src/${subdir}/*.cpp")
include_directories("\${PROJECT_SOURCE_DIR}/include")
link_directories("\${PROJECT_SOURCE_DIR}/lib")
# 设置二进制文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/arc)
# 生成编译命令
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(\${PROJECT_NAME} \${SOURCES})
EOF

    echo "为子目录 ${subdir} 生成了CMakeLists.txt。"
}

# 构建过程
build_project() {
    clear # 清屏
    echo "开始构建过程..."
    cd "${workspacefolder}/build" || exit

    # 清除上一次构建的可执行文件
    rm -f "${workspacefolder}/bin/${subdir}"

    if cmake .. >"$log_file" 2>&1 && make >>"$log_file" 2>&1; then
        # 检查二进制文件是否成功生成
        if [ -f "${workspacefolder}/bin/${subdir}" ]; then
            clear # 构建成功后清屏
            if [ -f "compile_commands.json" ]; then
                mv compile_commands.json "${workspacefolder}/"
            fi
            echo "构建成功。可执行文件位于 ${workspacefolder}/bin。"
        else
            clear # 二进制文件未生成时清屏
            echo "构建失败，未找到可执行文件。请检查日志文件 $log_file 查看错误。"
        fi
    else
        clear # cmake 或 make 失败后清屏
        echo "构建失败。请检查日志文件 $log_file 查看错误。"
    fi
}

# 清理过程
clean_up() {
    clear # 清屏
    echo "您想要清理构建文件吗？ ([Y]/n):"
    read -r clean_build
    [ "${clean_build:-Y}" != "n" ] && rm -rf "${workspacefolder}/build"

    # 只有在构建成功的情况下才询问是否清理日志文件
    echo "您想要清理日志文件吗？ ([Y]/n/A for all):"
    read -r clean_log
    if [ "${clean_log:-Y}" = "A" ]; then
        echo "清理所有日志文件..."
        rm -f "${workspacefolder}/tmp/log/"*
    elif [ "${clean_log:-Y}" != "n" ]; then
        echo "清理当前日志文件..."
        rm -f "${log_file}"
    else
        echo "日志文件已保留以供调试: $log_file"
    fi
}

# 执行输出文件
execute_output() {
    clear # 清屏
    echo "是否执行输出文件？ ([Y]/n):"
    read -r execute
    if [ "${execute:-Y}" != "n" ]; then
        echo "执行输出文件..."
        "${workspacefolder}/bin/${subdir}"
    fi
}

# 主函数
main() {
    initialize
    choose_build_directory
    generate_cmake_lists
    build_project
    clean_up
    execute_output
    echo "\n脚本执行完毕。"
}
main
