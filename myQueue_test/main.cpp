#include "myQueue.h"
#include <list>

void STL_queue_test()
{
    queue<int, list<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    cout << "size:" << q.size() << endl; //4
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl; //1 2 3 4
}
void my_queue_test()
{
    xy::test1();
}
int main()
{
    STL_queue_test();
    cout << "----------------" << endl;
    my_queue_test();
    return 0;
}