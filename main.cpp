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
state philState[N];
mutex m;

#define left ((philNum + 1) % N)
#define right ((philNum + N - 1) % N)

void eat(int philNum){
    cout << "Phliosopher " << philNum << "started eating" << endl;
    // every philosopher will eat for 2 seconds
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Philosopher " << philNum << "stopped eating" << endl;
}

void think(int philNum){
    int time = rand()%5 + 2;
    cout << "Philosopher " << philNum << "thinking..." << endl;
    this_thread::sleep_for(chrono::seconds(time));
}

void checkAvaibility(int philNum) {
    if (philState[philNum] == hungry && philState[left] != eating && philState[right] != eating){
        philState[philNum] = eating;
        eat(philNum);
    }
}

//Using dikstra's convention, which means that one philosopher will try to pick up two forks at the same time
void pickUpForks(int philNum) {
    m.lock();
    philState[philNum] = hungry;
}

void releaseForks(int phnum) {

}

int main(){
    srand(time(NULL));

    for(int i=0; i<N; i++) {
        philState[i] = thinking;
    }
}