#include <thread>
#include <mutex>
#include <iostream>
#include <semaphore>
#include <chrono>
#include <ctime>

using namespace std;

enum state {
    eating,
    hungry,
    thinking
};

int N = 5;
int philosophers[N];

#define left (= (phindex + 1) % N)
#define right (= (phindex + N - 1) % N)

void eat(int i){
    cout << "Phliosopher " << i << "started eating" << endl;
    // every philosopher will eat for 100 milliseconds
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Philosopher " << i << "stopped eating" << endl;
}

void think(int i){
    int time = rand()%1000 + 300;
    cout << "Philosopher " << i << "thinking..." << endl;
    this_thread::sleep_for(chrono::milliseconds(time));
}

int main(){
    srand(time(NULL));
    for(int i=0; i<N; i++) {
        philosophers[i] = i;
    }
}