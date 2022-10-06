#include "myPriorityQueue.h"
void STL_priority_queue_test()
{
    priority_queue<int> pq;
    pq.push(1);
    pq.push(5);
    pq.push(9);
    pq.push(7);
    pq.push(10);
    pq.push(3);
    pq.push(0);
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}
void my_priority_queue_test()
{
    xy:priority_queue<int> pq;
    pq.push(1);
    pq.push(5);
    pq.push(9);
    pq.push(7);
    pq.push(10);
    pq.push(3);
    pq.push(0);
    while (!pq.empty())
    {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}
int main()
{
    STL_priority_queue_test();
    cout << "------------------" << endl;
    my_priority_queue_test();
    return 0;
}