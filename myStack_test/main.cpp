#include <stack>
#include <vector>
#include "myStack.h"
//默认情况下使用deque
void test1()
{
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    cout << "size:" << st.size() << endl;
    while(!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}
//也可以指定适配器为vector或list
//需要包含相应头文件
void test2()
{
    stack<int, vector<int>> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    st.push(6);

    cout << "size:" << st.size() << endl;
    while(!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;
}
void STL_stack_test()
{
    test1();
    test2();
}
void my_stack_test()
{
    xy::test1();
}
int main() {


    STL_stack_test();
    cout << "----------------" << endl;
    my_stack_test();
    return 0;
}
