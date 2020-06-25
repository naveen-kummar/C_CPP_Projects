//https://www.geeksforgeeks.org/sharing-queue-among-three-threads/

#include <iostream> 
#include <queue> 
#include <thread>
#include <memory>
#include <mutex>

std::mutex GLOBAL_MUTEX;
std::condition_variable GLOBAL_CONDITION_VARIABLE;
constexpr unsigned int max_buffer_size = 100;
std::queue<int> GLOBAL_QUEUE;

// Declaring global variables 
int sum_B = 0, sum_C = 0;
int consumerCount1 = 0;
int consumerCount2 = 0;


class RandomNumberGenerator
{
public:
	RandomNumberGenerator(std::shared_ptr<std::queue<int>> q) : producer_queue{q}
	{
			
	}
	void AddRandomNumbers()
	{
		static int producer_count = 0;

		while (true)
		{
			std::unique_lock<std::mutex> locker(GLOBAL_MUTEX);
			GLOBAL_CONDITION_VARIABLE.wait(locker, []() {return (GLOBAL_QUEUE.size() < max_buffer_size); });

			// Getting the random number 
			int num = rand() % 10 + 1;
			std::cout << "Produced:  " << num << std::endl;

			GLOBAL_QUEUE.push(num);

			++producer_count;
			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();
		}
		
	}

private:

std::shared_ptr<std::queue<int>> producer_queue;
};

class ProcesEvenNumbers
{
public:
	ProcesEvenNumbers(std::shared_ptr<std::queue<int>> q) : even_consumer{ q }
	{

	}

	void ProcessEvenNumbers()
	{
		while (true)
		{
			std::unique_lock<std::mutex> locker(GLOBAL_MUTEX);
			GLOBAL_CONDITION_VARIABLE.wait(locker, []() {return (GLOBAL_QUEUE.size() > 0); });
			int val = GLOBAL_QUEUE.front();
			std::cout << "B thread processing: " << val << std::endl;
			if ((val & 1) == 0)
			{
				GLOBAL_QUEUE.pop();
				sum_B += val;
				std::cout << "B thread consumed: " << val << std::endl;
				++consumerCount1;
			}


			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

		}
	}

private:

	std::shared_ptr<std::queue<int>> even_consumer;
};


class ProcesOddNumbers
{
public:
	ProcesOddNumbers(std::shared_ptr<std::queue<int>> q) : odd_consumer{ q }
	{

	}

	void ProcessOddNumbers()
	{
		while (true)
		{
			std::unique_lock<std::mutex> locker(GLOBAL_MUTEX);
			GLOBAL_CONDITION_VARIABLE.wait(locker, []() {return (GLOBAL_QUEUE.size() > 0); });
			int val = GLOBAL_QUEUE.front();
			std::cout << "C thread processing: " << val << std::endl;
			if ((val & 1) == 1)
			{
				GLOBAL_QUEUE.pop();
				sum_C += val;
				std::cout << "C thread consumed: " << val << std::endl;
				++consumerCount2;
			}

			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

		}
	}

private:

	std::shared_ptr<std::queue<int>> odd_consumer;
};