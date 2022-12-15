#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <assert.h>
using namespace std;
#include "BitSet.h"

void bitset_test1()
{
	xy::bitset<30> bs1;
	bs1.set(8);
	bs1.set(9);
	bs1.set(7);
	bs1.set(27);
	bs1.set(20);
	bs1.Print();
	cout << bs1.count() << endl;

	bs1.reset(8);
	bs1.reset(9);
	bs1.reset(20);
	bs1.Print();

	cout << bs1.count() << endl;
	cout << bs1.any() << endl;

	bs1.reset(7);
	bs1.reset(27);
	bs1.Print();
	cout << bs1.none() << endl;
}
void bitset_test2()
{
	bitset<-1> bs1;
}
int main()
{
	bitset_test1();
	//bitset_test2();


	return 0;
}