/*
 * executor.hpp
 *
 *  Created on: 12 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <utility>
#include <exception>
#include <stdexcept>

#include "blockingQueue.hpp"
#include "countdownLatch.hpp"

namespace thesis {
using ExecutorHandler = void*;

class Executor {
	typedef std::function<void()> TaskType;

public:
	Executor();
	Executor(int num);

	Executor(const Executor&) = delete;
	Executor(Executor&&) = delete;
	Executor& operator=(const Executor&) = delete;
	Executor& operator=(Executor&&) = delete;

	void shutDown();
	ExecutorHandler beginTasksSession();
	void endTasksSession(ExecutorHandler handler);

	template <class Fn, class... Args>
	void addTask(ExecutorHandler handler, Fn&& fn, Args&&... args) {
		assertActivity(!shuttedDown, "Can't add task to executor, executor is shutted down.");

		auto func = std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);
		
		CountdownLatch* latch = (CountdownLatch*)handler;
		++(*latch);
		
		tasks.add([=]() mutable {
			func();
			--(*latch);
		});
	}

	virtual ~Executor();

private:
	std::vector<std::thread> threads;
	BlockingQueue<TaskType> tasks;
	volatile std::atomic<bool> stop;
	bool shuttedDown;
	int activeSessions;

	static void assertActivity(bool pred, const char* msg);
};

} /* namespace thesis */

