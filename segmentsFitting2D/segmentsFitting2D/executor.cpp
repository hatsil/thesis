/*
 * executor.cpp
 *
 *  Created on: 12 Sep 2018
 *      Author: hatsil
 */

#include <iostream>

#include "executor.hpp"

thesis::Executor::Executor(): Executor(1){}

thesis::Executor::Executor(int num):
threads(),
tasks(),
stop(false),
shuttedDown(false),
activeSessions(0) {
	for(int i = 0; i < num; ++i) {
		threads.emplace_back([&] {
			while(!stop)
				tasks.take()();
			tasks.add([] {});
		});
	}
}

thesis::Executor::~Executor() {
	assertActivity(shuttedDown, "Can't destroy executor, executor is still active.");
}

void thesis::Executor::shutDown() {
	assertActivity(!shuttedDown, "Can't shut down executor, executor is shutted down.");
	assertActivity(!activeSessions, "Can't shut down executor, threre are still active tasks sessions.");
	tasks.add([&] {
		stop = true;
	});

	for(std::thread& thread : threads)
		thread.join();

	shuttedDown = true;
}

thesis::ExecutorHandler thesis::Executor::beginTasksSession() {
	assertActivity(!shuttedDown, "Can't begin tasks session, executor is shutted down.");
	++activeSessions;
	return new CountdownLatch;
}

void thesis::Executor::endTasksSession(ExecutorHandler handler) {
	assertActivity(!shuttedDown, "Can't end tasks session, executor is shutted down.");
	assertActivity(activeSessions > 0, "Can't end tasks session, threre are no active tasks sessions.");
	CountdownLatch* latch = (CountdownLatch*)handler;
	latch->wait();
	delete latch;
	--activeSessions;
}

void thesis::Executor::assertActivity(bool pred, const char* msg) {
	if(!pred) {
		std::cerr << msg << std::endl;
		throw std::runtime_error(msg);
	}
}


