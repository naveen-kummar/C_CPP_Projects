//https://www.geeksforgeeks.org/sharing-queue-among-three-threads/

#include <iostream> 
#include <queue> 
#include <thread>
#include <memory>
#include <mutex>
#include <chrono>
#include <future>

std::mutex GLOBAL_MUTEX;
std::condition_variable GLOBAL_CONDITION_VARIABLE;
constexpr unsigned int max_buffer_size = 10000;
std::shared_ptr<std::queue<int>> GLOBAL_QUEUE;

// Declaring global variables 
int consumerCount1 = 0;
int consumerCount2 = 0;

using ull = long long int;

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
			GLOBAL_CONDITION_VARIABLE.wait(locker, [this]() {return ((producer_queue->size() < max_buffer_size) && (producer_count < max_buffer_size)); });

			// Getting the random number 
			int num = producer_count;
			producer_queue->push(num);

			++producer_count;
			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

			if (producer_count >= max_buffer_size)
			{
				break;
			}
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
		even_sum = 0;
	}

	void PopEvenNumbers(std::promise<ull>&& EvenSum)
	{
		while (true)
		{
			std::unique_lock<std::mutex> locker(GLOBAL_MUTEX);
			GLOBAL_CONDITION_VARIABLE.wait(locker, [this]() {return (even_consumer->size() > 0) || (consumerCount1 + consumerCount2 == max_buffer_size); });

			if (even_consumer->size() > 0)
			{
				int val = even_consumer->front();
				if ((val & 1) == 0)
				{
					even_consumer->pop();
					even_sum += val;
					++consumerCount1;
				}
			}

			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

			if ((consumerCount1 + consumerCount2 == max_buffer_size))
			{
				EvenSum.set_value(even_sum);
				break;
			}
		}
	}

private:

	std::shared_ptr<std::queue<int>> even_consumer;
	ull even_sum;
};


class ProcesOddNumbers
{
public:
	ProcesOddNumbers(std::shared_ptr<std::queue<int>> q) : odd_consumer{ q }
	{
		odd_sum = 0;
	}

	void PopOddNumbers(std::promise<ull>&& OddSum)
	{
		while (true)
		{
			std::unique_lock<std::mutex> locker(GLOBAL_MUTEX);
			GLOBAL_CONDITION_VARIABLE.wait(locker, [this]() {return (odd_consumer->size() > 0) || (consumerCount1 + consumerCount2 == max_buffer_size); });

			if (odd_consumer->size() > 0)
			{
				int val = odd_consumer->front();
				if ((val & 1) == 1)
				{
					odd_consumer->pop();
					odd_sum += val;
					++consumerCount2;
				}
			}

			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

			if ((consumerCount1 + consumerCount2 == max_buffer_size))
			{
				OddSum.set_value(odd_sum);
				break;
			}
		}
	}

private:

	std::shared_ptr<std::queue<int>> odd_consumer;
	ull odd_sum;
};

int main()
{
	GLOBAL_QUEUE = std::make_shared<std::queue<int>>();

	std::promise<ull> EvenSum;
	std::future<ull> EvenFuture = EvenSum.get_future();

	std::promise<ull> OddSum;
	std::future<ull> OddFuture = OddSum.get_future();

	std::unique_ptr<RandomNumberGenerator> random_gen = std::make_unique<RandomNumberGenerator>(GLOBAL_QUEUE);
	std::unique_ptr<ProcesEvenNumbers> even_proc = std::make_unique<ProcesEvenNumbers>(GLOBAL_QUEUE);
	std::unique_ptr<ProcesOddNumbers> odd_proc = std::make_unique<ProcesOddNumbers>(GLOBAL_QUEUE);

	std::thread t_producer(&RandomNumberGenerator::AddRandomNumbers, random_gen.get());
	std::thread t_even_proc(&ProcesEvenNumbers::PopEvenNumbers, even_proc.get(), std::move(EvenSum));
	std::thread t_odd_proc(&ProcesOddNumbers::PopOddNumbers, odd_proc.get(), std::move(OddSum));

	t_producer.join();
	//t_even_proc.join();
	//t_odd_proc.join();

	ull sum_B = EvenFuture.get();
	ull sum_C = OddFuture.get();

	std::cout << "Even Sum value = " << sum_B << std::endl;
	std::cout << "Odd Sum value = " << sum_C << std::endl;

	// Checking for the final value of thread 
	std::cout << ">>>> consumerCount1: " << consumerCount1 << " and consumerCount2:" << consumerCount2 << " <<<<" << std::endl;

	if (sum_C > sum_B)
		std::cout << "Winner is  Thread C" << std::endl;
	else if (sum_C < sum_B)
		std::cout << "Winner is  Thread B" << std::endl;
	else
		std::cout << "Both has same score" << std::endl;

	return 0;

}