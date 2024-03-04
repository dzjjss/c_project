#!/bin/bash

echo "正在更新APT软件包列表..."
apt update

# 检查g++是否安装
echo "检查g++安装情况..."
if ! [ -x "$(command -v g++)" ]; then
    echo "g++未安装，开始安装..."
    sudo apt install g++
else
    echo "g++已安装."
fi

# 检查cmake是否安装
echo "检查cmake安装情况..."
if ! [ -x "$(command -v cmake)" ]; then
    echo "cmake未安装，开始安装..."
    sudo apt install cmake
else
    echo "cmake已安装."
fi

echo "检查完成."
