//https://www.geeksforgeeks.org/sharing-queue-among-three-threads/

#include <iostream> 
#include <queue> 
#include <thread>
#include <memory>
#include <mutex>
#include <chrono>

std::mutex GLOBAL_MUTEX;
std::condition_variable GLOBAL_CONDITION_VARIABLE;
constexpr unsigned int max_buffer_size = 10000;
std::shared_ptr<std::queue<int>> GLOBAL_QUEUE;

// Declaring global variables 
int sum_B = 0, sum_C = 0;
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
			int num = producer_count;// rand();
			std::cout << "Produced:  " << num << std::endl;

			producer_queue->push(num);

			++producer_count;
			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

			if (producer_count >= max_buffer_size)
			{
				std::cout << "Producer Loop about to exit as producer_count is  " << producer_count << std::endl;
				break;
			}

			//std::cout << "While loop Producer - Shared ptr count = " << producer_queue.use_count() << std::endl;
		}

		std::cout << "Producer Loop exited: " << std::endl;
		std::cout << "Final Producer queue size =  " << producer_queue->size() << std::endl;
		
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

	void PopEvenNumbers()
	{
		while (true)
		{
			std::unique_lock<std::mutex> locker(GLOBAL_MUTEX);
			GLOBAL_CONDITION_VARIABLE.wait(locker, [this]() {return (even_consumer->size() > 0) || (consumerCount1 + consumerCount2 == max_buffer_size); });

			if (even_consumer->size() > 0)
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds(150));
				int val = even_consumer->front();
				//std::cout << "B thread processing: " << val << std::endl;
				if ((val & 1) == 0)
				{
					even_consumer->pop();
					sum_B += val;
					std::cout << "B thread consumed: " << val << std::endl;
					++consumerCount1;
				}
			}
			else
			{
				std::cout << "############Danger Even queue zero############## " << std::endl;
			}

			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

			if ((consumerCount1 + consumerCount2 == max_buffer_size))//if (producer_in_prog == false)
			{
				std::cout << "Even Consumer Loop about to exit: " << std::endl;
				break;
			}

			//std::cout << "While loop EvenConsumer - Shared ptr count = " << even_consumer.use_count() << std::endl;
			//std::cout << "EvenConsumer queue size = " << even_consumer->size() <<  std::endl;

		}

		std::cout << "Even Consumer Loop exited: "  << std::endl;
		std::cout << "Final Even Consumer queue size =  " << even_consumer->size() << std::endl;
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

	void PopOddNumbers()
	{
		while (true)
		{
			std::unique_lock<std::mutex> locker(GLOBAL_MUTEX);
			GLOBAL_CONDITION_VARIABLE.wait(locker, [this]() {return (odd_consumer->size() > 0) || (consumerCount1 + consumerCount2 == max_buffer_size); });

			if (odd_consumer->size() > 0)
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds(100));
				int val = odd_consumer->front();
				//std::cout << "C thread processing: " << val << std::endl;
				if ((val & 1) == 1)
				{
					odd_consumer->pop();
					sum_C += val;
					std::cout << "C thread consumed: " << val << std::endl;
					++consumerCount2;
				}
			}
			else
			{
				std::cout << "############Danger Odd queue zero############## " << std::endl;
			}


			locker.unlock();
			GLOBAL_CONDITION_VARIABLE.notify_one();

			if ((consumerCount1 + consumerCount2 == max_buffer_size))//if (producer_in_prog == false)
			{
				std::cout << "Odd Consumer Loop about to exit: " << std::endl;
				break;
			}
				
			//std::cout << "While loop OddConsumer - Shared ptr count = " << odd_consumer.use_count() << std::endl;
			//std::cout << "OddConsumer queue size = " << odd_consumer->size() << std::endl;
		}

		std::cout << "Odd Consumer Loop exited: " << std::endl;
		std::cout << "Final Odd Consumer queue size =  " << odd_consumer->size() << std::endl;
	}

private:

	std::shared_ptr<std::queue<int>> odd_consumer;
};

int main()
{
	GLOBAL_QUEUE = std::make_shared<std::queue<int>>();

	std::unique_ptr<RandomNumberGenerator> random_gen = std::make_unique<RandomNumberGenerator>(GLOBAL_QUEUE);
	std::unique_ptr<ProcesEvenNumbers> even_proc = std::make_unique<ProcesEvenNumbers>(GLOBAL_QUEUE);
	std::unique_ptr<ProcesOddNumbers> odd_proc = std::make_unique<ProcesOddNumbers>(GLOBAL_QUEUE);

	std::thread t_producer(&RandomNumberGenerator::AddRandomNumbers, random_gen.get());
	std::thread t_even_proc(&ProcesEvenNumbers::PopEvenNumbers, even_proc.get());
	std::thread t_odd_proc(&ProcesOddNumbers::PopOddNumbers, odd_proc.get());

	t_producer.join();
	t_even_proc.join();
	t_odd_proc.join();

	// Checking for the final value of thread 
	std::cout << ">>>> consumerCount1: " << consumerCount1 << " and consumerCount2:" << consumerCount2 << " <<<<" << std::endl;
	std::cout << "Final queue size is = " << GLOBAL_QUEUE->size() << std::endl;
	if (sum_C > sum_B)
		std::cout << "Winner is  Thread C" << std::endl;
	else if (sum_C < sum_B)
		std::cout << "Winner is  Thread B" << std::endl;
	else
		std::cout << "Both has same score" << std::endl;

	return 0;

}