/*
 * blockingQueue.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include <list>
#include <utility>

#include "semaphore.hpp"

namespace thesis {

template <class E>
class BlockingQueue {
public:
	BlockingQueue():
		mtx(),
		sem(0),
		queue() {};

	virtual ~BlockingQueue() {}


	BlockingQueue(const BlockingQueue&) = delete;
	BlockingQueue(BlockingQueue&&) = delete;
	BlockingQueue& operator=(const BlockingQueue&) = delete;
	BlockingQueue& operator=(BlockingQueue&&) = delete;

	E take() {
		sem.down();
		mtx.down();
		E element = queue.front();
		queue.pop_front();
		mtx.up();
		return element;
	}

	void add(const E& element) {
		mtx.down();
		queue.push_back(element);
		mtx.up();
		sem.up();
	}

	void add(E&& element) {
		mtx.down();
		queue.push_back(std::forward<E>(element));
		mtx.up();
		sem.up();
	}

	template<class Func>
	void forEach(const Func& fn) {
		mtx.down();
		for(auto&& element : queue)
			fn(element);
		mtx.up();
	}

private:
	std::list<E> queue;
	Semaphore mtx;
	Semaphore sem;
};

} /* namespace thesis */
