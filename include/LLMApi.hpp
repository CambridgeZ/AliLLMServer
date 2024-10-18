#ifndef __LLMAPI_HPP__
#define __LLMAPI_HPP__

#include <iostream>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;
using std::string;

class LLMApi{
public:
    string getResponse(string input){
        py::scoped_interpreter guard{};  // 初始化 Python 解释器

        // 动态添加模块搜索路径
        py::module sys = py::module::import("sys");
        sys.attr("path").attr("append")("/Users/mac/Basic_ReactorV2/python_script");

        // 打印 Python 模块路径
        py::print(sys.attr("path"));

        // 导入模块
        py::module llm = py::module::import("getReply");
        py::object reply_class = llm.attr("getReply")(input);
        py::object response = reply_class.attr("getReply")(input);
        return response.cast<string>();
    }
};

#endif // __LLMAPI_HPP__