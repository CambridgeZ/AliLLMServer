import os
from openai import OpenAI

class getReply:
    __string = ""
    __client = None

    def __init__(self, string):
        self.__string = string
        self.__client = OpenAI(
            api_key="sk-33e5dc94c26a4da49f17b676293cf19a",
            base_url="https://dashscope.aliyuncs.com/compatible-mode/v1",
        )
        
    def getReply(self, string):
        self.__string = string
        try:
            completion = self.__client.chat.completions.create(
                model="qwen-plus",
                messages=[
                    {'role': 'system', 'content': 'You are a helpful assistant.'},
                    {'role': 'user', 'content': self.__string}
                    ]
            )
            return completion.choices[0].message.content
        except Exception as e:
            return f"错误信息：{e}"
            return "请参考文档：https://help.aliyun.com/zh/model-studio/developer-reference/error-code"
        
# Usage:
# from python_script.getReply import getReply

