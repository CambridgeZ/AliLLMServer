#include "../include/LLMApi.hpp"

// /Users/mac/anaconda3/lib/python3.11/site-packages/pybind11/include
// 编译命令
// g++ -std=c++11 -I/Users/mac/anaconda3/include/python3.11 -I/Users/mac/anaconda3/lib/python3.11/site-packages/pybind11/include -Iinclude tests/testLLMApi.cpp -o tests/testLLMApi -L/Users/mac/anaconda3/lib -lpython3.11

int main(){
    LLMApi llm;
    std::string response = llm.getResponse("为我介绍一下你自己");
    std::cout << response << std::endl;
    return 0;
}