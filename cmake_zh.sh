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

    echo "\033[36m初始化目录...\033[0m"
    mkdir -p "${workspacefolder}/build" "${workspacefolder}/tmp/log" \
        "${workspacefolder}/bin" "${workspacefolder}/build/lib" "${workspacefolder}/build/arc" "${cache_folder}"
}

# 选择构建目录
choose_build_directory() {
    clear # 清屏
    echo "\033[34msrc目录下可用的子目录：\033[0m"
    ls "${src}"

    # 检查是否存在缓存文件并读取上次的选择
    last_subdir=""
    if [ -f "${cache_file}" ]; then
        last_subdir=$(cat "${cache_file}")
        echo "\033[33m上次选择的子目录为: \033[32m${last_subdir}\033[0m"
    fi

    while true; do
        echo "\033[33m请输入您希望编译的子目录名称[\033[32m${last_subdir}\033[33m]：\033[0m"
        read -r subdir
        if [ -z "$subdir" ] && [ -n "${last_subdir}" ]; then
            subdir=${last_subdir}
        fi
        if [ -n "$subdir" ] && [ -d "${src}/${subdir}" ]; then
            clear # 有效输入后清屏
            echo "\033[32m当前选择的子目录：${subdir}\033[0m"
            break
        else
            clear # 无效输入后清屏
            echo "\033[31m输入无效。请输入一个有效的子目录名称。\033[0m"
            echo "\033[34msrc目录下可用的子目录：\033[0m"
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

    echo "\033[32m为子目录 ${subdir} 生成了CMakeLists.txt。\033[0m"
}

# 构建过程
build_project() {
    clear # 清屏
    echo "\033[36m开始构建过程...\033[0m"
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
            echo "\033[32m构建成功。可执行文件位于 ${workspacefolder}/bin。\033[0m"
            build_success=true # 设置构建成功标志
        else
            clear # 二进制文件未生成时清屏
            echo "\033[31m构建失败，未找到可执行文件。请检查日志文件 $log_file 查看错误。\033[0m"
            build_success=false # 设置构建失败标志
        fi
    else
        clear # cmake 或 make 失败后清屏
        echo "\033[31m构建失败。请检查日志文件 $log_file 查看错误。\033[0m"
        build_success=false # 设置构建失败标志
    fi
}

# 清理过程
clean_up() {
    if [ "$build_success" = true ]; then
        echo "\033[36m清理选项：\033[0m"
        echo "1. \033[33m同时清理构建和日志文件\033[0m"
        echo "2. \033[33m清理构建文件\033[0m"
        echo "3. \033[33m不进行清理\033[0m"
        echo "\033[36m请选择一个选项 ([1]/2/3)：\033[0m"
        read -r cleanup_option

        # 检查是否为空输入，设置默认选项为1
        if [ -z "$cleanup_option" ]; then
            cleanup_option=1
        fi

        case $cleanup_option in
        1)
            echo "\033[32m正在同时清理构建和日志文件...\033[0m"
            rm -rf "${workspacefolder}/build"
            rm -f "${workspacefolder}/tmp/log/"*
            ;;
        2)
            echo "\033[32m正在清理构建文件...\033[0m"
            rm -rf "${workspacefolder}/build"
            ;;
        3)
            echo "\033[32m未进行任何清理。\033[0m"
            ;;
        *)
            echo "\033[31m选项无效。未进行任何清理。\033[0m"
            ;;
        esac
    else
        echo "\033[36m您想要清理构建文件吗？ ([Y]/n)：\033[0m"
        read -r clean_build
        if [ "${clean_build:-Y}" != "n" ]; then
            echo "\033[32m正在清理构建文件...\033[0m"
            rm -rf "${workspacefolder}/build"
        fi
        echo "\033[33m日志文件已保留以供调试：$log_file\033[0m"
    fi
}

# 执行输出文件
execute_output() {
    clear # 清屏
    echo "\033[36m是否执行输出文件？ ([Y]/n):\033[0m"
    read -r execute
    if [ "${execute:-Y}" != "n" ]; then
        echo "\033[32m执行输出文件...\033[0m"
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
    echo "\033[32m\n脚本执行完毕。\033[0m"
}
main
