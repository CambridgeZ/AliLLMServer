# 调用阿里 通义千问 接口的问答机器人

## 架构

```shell
.
├── CMakeLists.txt
├── include
│   ├── Acceptor.hpp
│   ├── EventLoop.hpp
│   ├── InetAddress.hpp
│   ├── LLMApi.hpp
│   ├── Socket.hpp
│   ├── SocketIO.hpp
│   └── TcpConnection.hpp
├── main.cpp
├── python_script
│   ├── getReply.py
│   ├── hello_qwen.py
│   ├── __pycache__
│   │   └── getReply.cpython-311.pyc
│   └── showPackage.py
├── README.md
├── source
│   ├── Acceptor.cpp
│   ├── EventLoop.cpp
│   ├── InetAddress.cpp
│   ├── Socket.cpp
│   ├── SocketIO.cpp
│   └── TcpConnection.cpp
└── tests
    ├── testLLMApi
    └── testLLMApi.cpp
```

## 部署

### 部署相关的python环境

python3.11 + Linux

```shell
pip3 install openai
pip3 install openai --upgrade
pip3 install pybind11
```

### 修改相关参数

将 /python_script/getReply line 10中的 api_key="" 当中填入相关的api_key
./CMakeLists.txt 相关包的位置改为本机上相关包的路径

### 构建

```shell
cmake -B build
cmake --build build
```

## 客户端使用方式

```
nc ip port
进行提问
```