#!/bin/bash

# 初期化関数：基本変数の定義と必要なディレクトリの作成
initialize() {
    clear # 画面クリア
    # スクリプトの現在の作業ディレクトリを取得
    workspacefolder="$(pwd)"
    src="${workspacefolder}/src"
    timestamp=$(date +%y-%m-%d_%H:%M:%S)
    log_file="${workspacefolder}/tmp/log/${timestamp}.build.log"

    echo "ディレクトリを初期化しています..."
    mkdir -p "${workspacefolder}/build" "${workspacefolder}/tmp/log" \
        "${workspacefolder}/bin" "${workspacefolder}/build/lib" "${workspacefolder}/build/arc"
}

# ビルドディレクトリを選択
choose_build_directory() {
    clear # 画面クリア
    echo "srcディレクトリに利用可能なサブディレクトリ："
    ls "${src}"

    while true; do
        echo "ビルドするサブディレクトリの名前を入力してください："
        read -r subdir
        if [ -n "$subdir" ] && [ -d "${src}/${subdir}" ]; then
            clear # 有効な入力後に画面クリア
            break
        else
            clear # 無効な入力後に画面クリア
            echo "無効な入力です。有効なサブディレクトリの名前を入力してください。"
            echo "srcディレクトリに利用可能なサブディレクトリ："
            ls "${src}" # ディレクトリリストを再表示
        fi
    done
}

# CMakeLists.txtファイルを生成
generate_cmake_lists() {
    clear # 画面クリア
    cat <<EOF >"${workspacefolder}/CMakeLists.txt"
cmake_minimum_required(VERSION 3.0.0)
project(${subdir} VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
file(GLOB SOURCES "\${PROJECT_SOURCE_DIR}/src/${subdir}/*.cpp")
include_directories("\${PROJECT_SOURCE_DIR}/include")
link_directories("\${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY \${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/arc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(\${PROJECT_NAME} \${SOURCES})
EOF

    echo "サブディレクトリ ${subdir} にCMakeLists.txtを生成しました。"
}

# ビルドプロセス
build_project() {
    clear # 画面クリア
    echo "ビルドプロセスを開始します..."
    cd "${workspacefolder}/build" || exit
    if cmake .. >"$log_file" 2>&1 && make >>"$log_file" 2>&1; then
        clear # ビルド成功後に画面クリア
        echo "ビルドに成功しました。実行ファイルは ${workspacefolder}/bin にあります。"
    else
        clear # ビルド失敗後に画面クリア
        echo "ビルドに失敗しました。エラーは $log_file を確認してください。"
    fi
}

# クリーンアッププロセス
clean_up() {
    clear # 画面クリア
    echo "ビルドファイルをクリーンアップしますか？ ([Y]/n):"
    read -r clean_build
    [ "${clean_build:-Y}" != "n" ] && rm -rf "${workspacefolder}/build"

    echo "ログファイルをクリーンアップしますか？ ([Y]/n):"
    read -r clean_log
    [ "${clean_log:-Y}" != "n" ] && rm -f "${log_file}"
}

# 出力ファイルの実行
execute_output() {
    clear # 画面クリア
    echo "出力ファイルを実行しますか？ ([Y]/n):"
    read -r execute
    if [ "${execute:-Y}" != "n" ]; then
        echo "出力ファイルを実行しています..."
        "${workspacefolder}/bin/${subdir}"
    fi
}

# メイン関数
main() {
    initialize
    choose_build_directory
    generate_cmake_lists
    build_project
    clean_up
    execute_output
    echo "\nスクリプトの実行が完了しました。"
}
main
