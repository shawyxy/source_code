#pragma once
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
namespace xy
{

    //定义比较方式以确定结构为大堆或小堆
    template<class T>
            class less
            {
                bool operator()(const T& x, const T& y)
                {
                    return  x < y;
                }
            };
    template<class T>
            class greater
            {
                bool operator()(const T& x, const T& y)
                {
                    return  x > y;
                }
            };
    //定义优先级队列
    template<class T, class Container = vector<T>, class Compare = less<T>>
            class priority_queue
            {
            public:
                void push(const T& x)
                {
                    _con.push_back(x);
                    adjust_up(_con.size() - 1);
                    //因为是用vector,所以头插也可以,但是这样就要向下调整,时间复杂度更高
                }
                //弹出优先级队列(大小堆)的堆顶元素
                void pop()
                {
                    //将堆顶元素和堆尾元素互换
                    swap(_con[0], _con[_con.size() - 1]);
                    //弹出
                    _con.pop_back();
                    //从现有堆的第一个元素向下调整(此时没有"堆顶"可言)
                    adjust_down(_con.size(), 0);
                }
                T& top()
                {
                    return _con[0];
                }
                const T& top() const
                {
                    return _con[0];
                }
                const size_t size() const
                {
                    return _con.size();
                }
                bool empty()
                {
                    return _con.empty();
                }
                //向上调整
                void adjust_up(int child)
                {
                    int parent = (child - 1) / 2;
                    while(child > 0)//即使child=0,parent也是0,所以还要比较一次
                    {
                        if(_cmp(_con(parent), _con(child)))
                        {
                            //父子结点交换
                            swap(_con(parent), _con(child));
                            //更新父子结点,比较范围向上移动
                            //先修改下面的,即child
                            child = parent;
                            parent = (child - 1) / 2;
                        }
                        else
                            break;
                    }
                }
                //向下调整
                void adjust_down(int n, int parent)
                {
                    int child = 2 * parent + 1;
                    while (child < n)
                    {
                        if (child + 1 < n&&_comp(_con[child], _con[child + 1]))
                        {
                            child++;
                        }
                        if (_comp(_con[parent], _con[child]))
                        {
                            //父子结点交换
                            swap(_con[child], _con[parent]);
                            //继续向下
                            parent = child;
                            child = 2 * parent + 1;
                        }
                        else
                            break;
                    }
                }
            private:
                Container _con;//定义底层实现的容器
                Compare _cmp;//定义比较方式
            };
}