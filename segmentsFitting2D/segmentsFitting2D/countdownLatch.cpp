/*
 * countdownLatch.cpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#include "countdownLatch.hpp"

thesis::CountdownLatch::CountdownLatch(): CountdownLatch(0) {}

thesis::CountdownLatch::CountdownLatch(int count):
	sleepingLock(0),
	mtx(),
	count(count) {}

thesis::CountdownLatch::~CountdownLatch() {}

void thesis::CountdownLatch::wait() {
	mtx.down();
	for(int i = 0; i < count; ++i)
		sleepingLock.down();
	count = 0;
	mtx.up();
}

void thesis::CountdownLatch::operator++() {
	mtx.down();
	++count;
	mtx.up();
}

void thesis::CountdownLatch::add(int n) {
	mtx.down();
	count += n;
	mtx.up();
}

void thesis::CountdownLatch::operator--() {
	sleepingLock.up();
}

void thesis::CountdownLatch::sub(int n) {
	for(int i = 0; i < n; ++i)
		sleepingLock.up();
}



