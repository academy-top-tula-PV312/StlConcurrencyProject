#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int amount{};

std::mutex m;

void func(int n)
{
    
    for (int i{}; i < n; i++)
    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "\t" << std::this_thread::get_id() << " for : " << i << "\n";
    }
}

void inc()
{
    for (int i{}; i < 10000; i++)
    {
        std::lock_guard<std::mutex> lock(m);
        ++amount;
        //std::this_thread::sleep_for(5ms);
    }
        
}

int main()
{
    std::thread th1(func, 150);
    //std::thread th2(func, 100);

    for (int i{}; i < 100; i++)
    {
        std::cout << "main for: " << i << "\n";
    }
    
    //th2.join();

    //std::thread thInc1(inc);
    //std::thread thInc2(inc);
    ////inc();

    //thInc1.join();
    //thInc2.join();

    //std::cout << amount << "\n";
}
