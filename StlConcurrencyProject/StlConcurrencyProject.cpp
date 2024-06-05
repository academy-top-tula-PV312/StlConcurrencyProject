#include <iostream>
#include <thread>
#include <mutex>
#include <future>

using namespace std;

void Example1();

int amount{};
std::mutex m;


class Calculate
{
public:
    int sumGauss(int n)
    {
        int sum{};
        for (int i{}; i <= n; i++)
            sum += i;
        std::this_thread::sleep_for(1000ms);
        return sum;
    }
};

void func(int n)
{
    
    for (int i{}; i < n; i++)
    {
        //std::lock_guard<std::mutex> lock(m);
        std::cout << "\t" << std::this_thread::get_id() << " for : " << i << "\n";
    }
}

void inc()
{
    for (int i{}; i < 10000; i++)
    {
        //std::lock_guard<std::mutex> lock(m);
        //m.lock();
        ++amount;
        //std::this_thread::sleep_for(5ms);
        //m.unlock();
    }
        
}

void sum1000(std::promise<int> promise_result)
{
    std::cout << "current thread id: " 
              << std::this_thread::get_id() << "\n";
    int sum{};
    for (int i{}; i <= 1000; i++)
        sum += i;
    std::this_thread::sleep_for(1000ms);
    promise_result.set_value(sum);
}

int sumGauss(int n)
{
    int sum{};
    for (int i{}; i <= n; i++)
        sum += i;
    std::this_thread::sleep_for(1000ms);
    return sum;
}

int main()
{


    /*std::promise<int> promise_result;
    std::future<int> future_result = promise_result.get_future();

    jthread th1(func, 200);
    jthread th2(sum1000, std::move(promise_result));

    future_result.wait();
    std::cout << "sum result = " << future_result.get() << "\n";

    th1.detach();*/

    //jthread th1(func, 200);
    
    //auto result_void = std::async(std::launch::async, func, 100);
    auto result = std::async(std::launch::async, &sumGauss, 1000);
    auto result2 = std::async(std::launch::async, &Calculate::sumGauss, new Calculate(), 2000);

    /*for (int i{}; i < 10; i++)
    {
        std::cout << "main for: " << i << "\n";
    }*/

    result2.wait();
    std::cout << "result 2 = " << result2.get() << "\n";
    result.wait();
    std::cout << "result = " << result.get() << "\n";
    
    
}

void Example1()
{
    std::jthread th1(func, 150);
    //std::thread th2(func, 100);

    for (int i{}; i < 100; i++)
    {
        std::cout << "main for: " << i << "\n";
    }

    //th1.detach();

    //th2.join();

    //std::thread thInc1(inc);
    //std::thread thInc2(inc);
    ////inc();

    //thInc1.join();
    //thInc2.join();

    //std::cout << amount << "\n";
}
