#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>


// Using the machine clock to demostrate threads instead of using a file or the console.
// a file or the console "cout" could create a race condition among threads, reading the clock not

using namespace std;

chrono::time_point<chrono::steady_clock> start;
vector<chrono::duration<long, ratio<1, 1000000000>>> globalTP(10'000);
void getTimePoints() {
    for (int i = 0; i < 10'000; ++i) {
        globalTP[i] = chrono::steady_clock::now() - start;
    }
}

vector<chrono::duration<long, ratio<1, 1000000000>>> globalTP2(10'000);
void getTimePoints2() {
    for (int i = 0; i < 10'000; ++i) {
        globalTP2[i] = chrono::steady_clock::now() - start;
    }
}

int main() {
    cout << "Hello World!\n";
    chrono::time_point<chrono::steady_clock> startLocal{ chrono::steady_clock::now() };
    start = startLocal;

    thread th1(getTimePoints);
    thread th2(getTimePoints2);
    
    vector<chrono::duration<long, ratio<1, 1000000000>>> localTP(10'000);
    for (int i = 0; i < 10'000; ++i) {
        localTP[i] = chrono::steady_clock::now() - start;
    }

    th1.join();
    th2.join();

    ofstream ofs("my_output.txt");
    for (int i = 0; i < 10'000; ++i) {
        ofs << setw(8) << globalTP[i].count() << ' ' 
            << setw(8) << globalTP2[i].count() << ' ' 
            << setw(8) << localTP[i].count() << '\n';
    }
 
}
