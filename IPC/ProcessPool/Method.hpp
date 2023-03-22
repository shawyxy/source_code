#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include <functional>

typedef std::function<void()> func; // 定义函数包装器类型

std::vector<func> MethodList; // 保存函数指针

std::unordered_map<int, std::string> desc; // 保存方法的信息

void Method1()
{
    std::cout << "child process[" << getpid() << " ] Method1" << std::endl;
}

void Method2()
{
    std::cout << "child process[" << getpid() << " ] Method2" << std::endl;
}

void Method3()
{
    std::cout << "child process[" << getpid() << " ] Method3" << std::endl;
}

void load()
{
    desc.insert({MethodList.size(), "Method1"});
    MethodList.push_back(Method1);

    desc.insert({MethodList.size(), "Method2"});
    MethodList.push_back(Method2);

    desc.insert({MethodList.size(), "Method3"});
    MethodList.push_back(Method3);
}

void PrintMethod() // 打印方法信息
{
    for(const auto &it : desc )
    {
        std::cout << it.first << "  " << it.second << std::endl;
    }
}

int MethodNum() // 获取方法总数
{
    return MethodList.size();
}