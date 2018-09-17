/*
 * semaphore.cpp
 *
 *  Created on: 12 Sep 2018
 *      Author: hatsil
 */

#include "semaphore.hpp"

//thesis::BinarySemaphore::BinarySemaphore(): BinarySemaphore(true) {}
//
//thesis::BinarySemaphore::BinarySemaphore(bool unlocked):
//		mtx(),
//		unlocked(unlocked),
//		q() {}
//
//thesis::BinarySemaphore::~BinarySemaphore() {}
//
//void thesis::BinarySemaphore::down() {
//	std::unique_lock<std::mutex> lk(mtx);
//	if(unlocked)
//		unlocked = false;
//	else {
//		std::condition_variable cv;
//		bool isAwake = false;
//
//		q.push([&] {
//			isAwake = true;
//			mtx.unlock();
//			cv.notify_one();
//		});
//
//		cv.wait(lk, [&] {
//			return isAwake;
//		});
//	}
//}
//
//void thesis::BinarySemaphore::up() {
//	mtx.lock();
//	if(q.empty()) {
//		unlocked = true;
//		mtx.unlock();
//	} else {
//		std::function<void()> foo(q.front());
//		q.pop();
//		foo(); // unlock mtx...
//	}
//}
//
//
//thesis::CountingSemaphore::CountingSemaphore(): CountingSemaphore(1) {}
//
//thesis::CountingSemaphore::CountingSemaphore(int val):
//		mtx(),
//		sem(val > 0),
//		val(val) {}
//
//thesis::CountingSemaphore::~CountingSemaphore() {}
//
//void thesis::CountingSemaphore::down() {
//	sem.down();
//	mtx.down();
//	if(--val > 0)
//		sem.up();
//	mtx.up();
//}
//
//void thesis::CountingSemaphore::up() {
//	mtx.down();
//	if(++val == 1)
//		sem.up();
//	mtx.up();
//}

thesis::Semaphore::Semaphore(): Semaphore(1) {}

thesis::Semaphore::Semaphore(int permits):
		permits(permits),
		cv(),
		mtx() {}

thesis::Semaphore::~Semaphore() {}

void thesis::Semaphore::up() {
	mtx.lock();
	++permits;
	mtx.unlock();
	cv.notify_one();
}

void thesis::Semaphore::down() {
	std::unique_lock<std::mutex> lk(mtx);
	while(permits <= 0)
		cv.wait(lk);
	--permits;
}

bool thesis::Semaphore::tryDown() {
	std::unique_lock<std::mutex> lk(mtx);
	if(permits > 0) {
		--permits;
		return true;
	}
	return false;
}
