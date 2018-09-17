/*
 * semaphore.hpp
 *
 *  Created on: 12 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

//#include <functional>

namespace thesis {

//class BinarySemaphore {
//public:
//	BinarySemaphore();
//	BinarySemaphore(bool unlocked);
//	virtual ~BinarySemaphore();
//
//	//deleted:
//	BinarySemaphore(const BinarySemaphore&) = delete;
//	BinarySemaphore(BinarySemaphore&&) = delete;
//	BinarySemaphore& operator=(const BinarySemaphore&) = delete;
//	BinarySemaphore& operator=(BinarySemaphore&&) = delete;
//
//	void up();
//	void down();
//private:
//	std::mutex mtx;
//	bool unlocked;
//	std::queue< std::function<void()> > q;
//};
//
//class CountingSemaphore {
//public:
//	CountingSemaphore();
//	CountingSemaphore(int val);
//	virtual ~CountingSemaphore();
//
//	//deleted:
//	CountingSemaphore(const CountingSemaphore&) = delete;
//	CountingSemaphore(CountingSemaphore&&) = delete;
//	CountingSemaphore& operator=(const CountingSemaphore&) = delete;
//	CountingSemaphore& operator=(CountingSemaphore&&) = delete;
//
//	void up();
//	void down();
//private:
//	BinarySemaphore mtx;
//	BinarySemaphore sem;
//	int val;
//};

class Semaphore {
public:
	Semaphore();
	Semaphore(int permits);

	Semaphore(const Semaphore&) = delete;
	Semaphore(Semaphore&&) = delete;
	Semaphore& operator=(const Semaphore&) = delete;
	Semaphore& operator=(Semaphore&&) = delete;

	void up();
	void down();
	bool tryDown();

	virtual ~Semaphore();

private:
	volatile int permits;
	std::condition_variable cv;
	std::mutex mtx;
};

} /* namespace thesis */

