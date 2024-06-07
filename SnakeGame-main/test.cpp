#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void test();
int main()
{
    auto start = chrono::steady_clock::now();

    this_thread::sleep_for(chrono::seconds(1));

    test();
    auto end = chrono::steady_clock::now();

    auto elapsed = end - start;

    cout << chrono::duration_cast<chrono::milliseconds>(elapsed).count() << endl;
}

void test(){
    cout << "dfsf" << endl;
}