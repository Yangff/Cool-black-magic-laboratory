#pragma once
#include <atomic> 
#include <set>
#include <new>
#include <string>
#include <type_traits>
#include <thread>
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
		virtual std::string GetName() { return std::string("Toy::Object"); }; 
	};

	template<class T>
	class Ptr {
	private:
		typedef C std::enable_if<std::is_base_of<Object, T>, T>;
		C *obj;
		Ptr(){; }
	public:
		Ptr(C *obj):obj(obj) { obj->AddRef(); };
		~Ptr(){ obj->Release(); }
	};

	#define gcnew(context, type, ....) (([&](::Toy::Context *_cxt){ void* mem = _cxt->Alloc(sizeof(type)); type * _obj = new(mem) type(__VA_ARGS__); Ptr<type> ret(_obj); _cxt->GcReg(dynamic_cast<Object*>(_obj)); return ret; })())
	//Ptr<Some> xxx = gcnew(Context, XXX, 1, 2, 3);
	
	class GC;
	struct Query {
		Object *src, *ref;
		enum {
			ADD, REMOVE, REG, UREG, UNLOAD
		} _opt;
	};
	class Context : public Object {
	private:
		Query *Queue[_TOY_MAX_QUEUE_CONTEXT];
		uint32_t QueueHead, QueueTail;
		GC *gc;
	public:
		Context(GC *gc):gc(gc) { gc->MarkContext(this); };
		~Context(){ gc->release(this); } 
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
		void *Alloc(size_t sz){
			return gc->Alloc(sz);
		}
		bool GcReg(Object *obj){
			return Push(Queue(obj, NULL, Query::REG));
		}
		virtual std::string GetName() { return std::string("Toy::Context"); }; 
	};


	template<class T>
	class Container {
	private:
		typedef C std::enable_if<std::is_base_of<Object, T>, T>;
		Context * ctx;
		T *obj;
	public:
		Container(Context * ctx):ctx(ctx) { ctx->AddRef();};
		~Container() { ctx->Release(); }
	};


	template<class T>
	class NiceBoat {
	private:
		typedef C std::enable_if<std::is_base_of<Object, T>, T>;
		C *obj; Context *from; Context *to;
		bool begin;
		NiceBoat(){; }
	public:
		NiceBoat(C *obj, Context *from, Context *to):from(from), to(to), obj(obj), begin(false) { obj->AddRef(); from->AddRef(); to->AddRef(); };
		~NiceBoat(){ obj->Release(); from->Release(); to->Release(); }
		void Begin() { obj->AddRef();}
		Ptr<T> Fetch() { return Ptr<T>(obj); }
		void End() { to->Push(Query(obj, NULL, )) }
	};

}
