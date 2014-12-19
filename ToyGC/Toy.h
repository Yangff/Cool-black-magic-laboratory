#pragma once
#include <atomic> 
#include <set>
#ifndef _TOY_MAX_QUEUE_CONTEXT
#define _TOY_MAX_QUEUE_CONTEXT 1000
#endif
#ifndef _TOY_HUNGINGUP
#define _TOY_HUNGINGUP {_sleep(10);} while(0);
#endif
namespace Toy {

	class Object {
	private:
		std::atomic_uint ObjectCounting;
		std::set<Object*> ObjectReferd;
		bool flag;
	public:
		void AddRef() {
			ObjectCounting++;
		}
		void Release() {
			ObjectCounting--;
		}
	};

	template<class T>
	class Container {

	};

	template<class T>
	class Boat {

	};

	class Context : Object {
	public:
		struct Query {
			Object *src, *ref;
			enum {
				ADD, REMOVE
			} _opt;
		};
	private:
		Query Queue[_TOY_MAX_QUEUE_CONTEXT];
		uint32_t QueueHead, QueueTail;
	public:
		bool Push(Query q) {
			std::atomic_thread_fence(std::memory_order_acquire);
			while ((QueueTail + 1) % _TOY_MAX_QUEUE_CONTEXT == QueueHead) _TOY_HUNGINGUP; // 
			Queue[QueueTail] = q;
			QueueTail = (QueueTail + 1) % _TOY_MAX_QUEUE_CONTEXT;
			std::atomic_thread_fence(std::memory_order_release);
			return true;
		}
		bool Pop(Query &q) {
			if (QueueHead == QueueTail)
				return false;
			std::atomic_thread_fence(std::memory_order_acquire);
			q = Queue[QueueHead];
			QueueHead = (QueueHead + 1) % _TOY_MAX_QUEUE_CONTEXT;
			std::atomic_thread_fence(std::memory_order_release);
			return true;
		}
	};
}
