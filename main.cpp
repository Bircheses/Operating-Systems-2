#include <thread>
#include <mutex>
#include <iostream>
#include <semaphore>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

// Left and right philosopher
#define left ((philNum + 1) % N)
#define right ((philNum + N - 1) % N)

// Two output strings for two states
#define thinkString(philNum) cout << "Philosopher " << philNum << " is thinking..." << endl;
#define eatString(philNum) cout << "Philosopher " << philNum << " is eating..." << endl;

enum state {
    eating,
    hungry,
    thinking
};

int N = 5;
state *philState;
mutex criticalMutex;
binary_semaphore stateChanged{0};

string output;

void checkAvaibility(int philNum) {
    if (philState[philNum] == hungry && philState[left] != eating && philState[right] != eating) {
        int randTime = rand() % 2 + 1;
        philState[philNum] = eating;
        // Unlocking here because the philosopher had already changed his state, so other threads can have a access to critical section
        criticalMutex.unlock();
        // Starts eating from 1 to 2 seconds
        stateChanged.release(); // Send the signal to write function to refresh the output
        this_thread::sleep_for(chrono::seconds(randTime));
    } else {
        // Unlocking here also because we don't want to stop other philosophers from trying to grab the forks (maybe)
        criticalMutex.unlock();
    }
}

//Using dikstra's convention, which means that one philosopher will try to pick up two forks at the same time
void pickUpForks(int philNum) {
    criticalMutex.lock();
    philState[philNum] = hungry;
    checkAvaibility(philNum);
}

void releaseForks(int philNum) {
    int randTime = rand() % 5 + 2;
    philState[philNum] = thinking;
    // Starts thinking from 2 to 5 seconds
    stateChanged.release(); // Send the signal to write function to refresh the output
    this_thread::sleep_for(chrono::seconds(randTime));
}

void start(int thNum) {
    while (true) {
        pickUpForks(thNum);
        releaseForks(thNum);
    }
}

void write() {
    while(true) {
        stateChanged.acquire(); // Waits for signal from thread function to refresh output
        system("cls");
        for (int philNum = 0; philNum < N; philNum++) {
            switch (philState[philNum]) {
                case thinking:
                    thinkString(philNum);
                break;
                case eating:
                    eatString(philNum);
                break;
                default:
                    thinkString(philNum);
                break;
            }
        }
    }
}

int main() {
    srand(time(NULL));


    cout << "Wprowadz liczbe filozofow: " << endl;
    cin >> N;


    auto *threads = new thread[N];
    philState = new state[N];

    for (int i = 0; i < N; i++) {
        philState[i] = thinking;
        threads[i] = thread(start, i);
    }

    auto writeThread = new thread(write);

    for (int i = 0; i < N; i++) {
        threads[i].join();
    }

    delete [] threads;
    delete [] philState;

    return 0;
}
