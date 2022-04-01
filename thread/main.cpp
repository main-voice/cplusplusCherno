#include <chrono>         // std::chrono::seconds
#include <iostream>
#include <thread>
bool isFinished = false;
void doWork() {
	while (!isFinished)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << "We started the thread id = " << std::this_thread::get_id() << "\n";
		std::cout << "Working...\n";
	}
}
int main()
{
	std::cout << "We started the thread id = " << std::this_thread::get_id() << "\n";
	std::thread worker(doWork);
	
	std::cout << "press enter, and the thread will end\n";
	std::cin.get();
	isFinished = true;

	worker.join();

	std::cout << "this thread end\n";

	return 0;
}

