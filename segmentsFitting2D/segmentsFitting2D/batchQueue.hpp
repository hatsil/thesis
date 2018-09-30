/*
 * blockingQueue.hpp
 *
 *  Created on: 13 Sep 2018
 *      Author: hatsil
 */

#pragma once

#include <list>
#include <utility>
#include <list>

#include "semaphore.hpp"

namespace thesis {

template <class E>
class BatchQueue {
public:
	BatchQueue():
		mtx(),
		sem(0),
		releaser(0),
		batch(nullptr) {}

	virtual ~BatchQueue() {}

	BatchQueue(const BatchQueue&) = delete;
	BatchQueue(BatchQueue&&) = delete;
	BatchQueue& operator=(const BatchQueue&) = delete;
	BatchQueue& operator=(BatchQueue&&) = delete;

	std::list<E>* take() {
		sem.down();
		mtx.down();
		std::list<E>* volatile ans = batch;
		batch = nullptr;
		mtx.up();
		if(!ans)
			releaser.up();
		return ans;
	}

	void add(const E& element) {
		mtx.down();
		if(!batch) {
			batch = new std::list<E>();
			sem.up();
		}
		batch->push_back(element);
		mtx.up();
	}

	void add(E&& element) {
		mtx.down();
		if(!batch) {
			batch = new std::list<E>();
			sem.up();
		}
		batch->push_back(std::forward<E>(element));
		mtx.up();
	}

	void releaseTaker() {
		sem.up();
		releaser.down();
	}

private:
	std::list<E>* volatile batch;
	Semaphore mtx;
	Semaphore sem;
	Semaphore releaser;
};

} /* namespace thesis */
