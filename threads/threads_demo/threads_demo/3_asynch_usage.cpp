#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
#include <chrono>

std::mutex m;
std::mutex g_display_mutex;


class Integer {
    int* m_pInt;
public:
    Integer() {
        std::cout << ">>Normal default ctor Integer()" << std::endl;
        m_pInt = new int(0);
    }

    Integer(int value) {
        std::cout << ">>Normal Paramaterizied ctor Integer(int)" << std::endl;
        m_pInt = new int(value);
    }

    Integer(const Integer& obj) {
        std::cout << ">>Copy Ctor Integer(const Integer&)" << std::endl;
        m_pInt = new int(*obj.m_pInt);
    }

    Integer(Integer&& obj) {
        std::cout << ">>Move ctor Integer(int&&)" << std::endl;
        m_pInt = obj.m_pInt;
        obj.m_pInt = nullptr;
    }

    int GetValue() const {
        return *m_pInt;
    }

    void SetValue(int value) {
        *m_pInt = value;
    }

    ~Integer() {
        std::cout << ">>Destructor ~Integer()" << std::endl;
        delete m_pInt;
    }

};

struct X {
    void foo(Integer j, const std::string& str) {
        //std::lock_guard<std::mutex> lk(m);
        //std::cout << str << ' ' << i << '\n';
        for (int i = 0; i < 10; i++)
        {
            std::thread::id this_id = std::this_thread::get_id();
            

            g_display_mutex.lock();
            std::cout << "thread foo = " << this_id << " sleeping...\n";

            g_display_mutex.unlock();
            

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    void bar(const std::string& str) {
       // std::lock_guard<std::mutex> lk(m);
       // std::cout << str << '\n';
        for (int i = 0; i < 10; i++)
        {
            std::thread::id this_id = std::this_thread::get_id();

            g_display_mutex.lock();
            std::cout << "thread bar = " << this_id << " sleeping...\n";
            g_display_mutex.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    int operator()(int i) {
        std::lock_guard<std::mutex> lk(m);
        std::cout << i << '\n';
        return i + 10;
    }
};

template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
    auto len = end - beg;
    if (len < 1000)
        return std::accumulate(beg, end, 0);

    RandomIt mid = beg + len / 2;
    auto handle = std::async(std::launch::async,
        parallel_sum<RandomIt>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}

int main()
{
    std::thread::id this_id = std::this_thread::get_id();

    g_display_mutex.lock();
    std::cout << "Main Thread = " << this_id << " sleeping...\n";
    g_display_mutex.unlock();


    std::vector<int> v(10000, 1);
    std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';

    X x;
    // Calls (&x)->foo(42, "Hello") with default policy:
    // may print "Hello 42" concurrently or defer execution
    //Integer lvalue = 42;
    auto a1 = std::async(std::launch::async, &X::foo, &x, 43, "Hello");



    
    // Calls x.bar("world!") with deferred policy
    // prints "world!" when a2.get() or a2.wait() is called
    //auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
   // auto a2 = std::async(std::launch::deferred, &X::bar, x, "world!");
   // a2.wait();
    a1.wait();
    
    g_display_mutex.lock();
    std::cout << "Main Thread2 = " << this_id << " sleeping...\n";
    g_display_mutex.unlock();
   

    
    // Calls X()(43); with async policy
    // prints "43" concurrently
    //auto a3 = std::async(std::launch::async, X(), 43);
    //a2.wait();                     // prints "world!"
   // std::cout << a3.get() << '\n'; // prints "53"
    getchar();
} // if a1 is not done at this point, destructor of a1 prints "Hello 42" here