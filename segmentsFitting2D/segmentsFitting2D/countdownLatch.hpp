/*
 * countdownLatch.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include "semaphore.hpp"

namespace thesis {

class CountdownLatch {
public:
	CountdownLatch();
	CountdownLatch(int count);

	CountdownLatch(const CountdownLatch&) = delete;
	CountdownLatch(CountdownLatch&&) = delete;
	CountdownLatch& operator=(const CountdownLatch&) = delete;
	CountdownLatch& operator=(CountdownLatch&&) = delete;

	void wait();

	void operator++();
	void add(int n);

	void operator--();
	void sub(int n);

	virtual ~CountdownLatch();

private:
	Semaphore sleepingLock;
	Semaphore mtx;
	volatile int count;
};

} /* namespace thesis */
