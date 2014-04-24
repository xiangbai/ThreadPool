# 线程池

标签（空格分隔）： 项目描述
---

##知识点
 - 多线程编程
 - 线程同步与互斥
 - C++面向对象编程的思想
##思路

> 在面向对象编程中，创建和销毁对象是很费时间的，因为创建一个对象要获取内存资源或者其它更多资源。线程撤销时需要回收内存资源。所以提高服务程序效率的一个手段就是尽可能减少创建和销毁对象的次数，特别是一些很耗资源的对象创建和销毁。
##过程
**一般而言,线程池有以下几个部分:**
1.完成主要任务的一个或多个线程.
2.用于调度管理的管理线程.
3.要求执行的任务队列.

**涉及到的类**

 - MutexLock类用于线程互斥使用任务队列
 - Condition类用于线程的同步，任务队列中有任务时通知线程去执行任务，无任务时线程处于等待状态
 - Thread类是一个抽象类，实现了线程的创建，回收等操作，具体做什么任务有其继承类来完成
 - WorkThread类继承了Thread类，线程具体完成的任务由其来实现
 - ThreadPool类用于封装线程的工作，实现线程池的启动，撤销，添加任务队列，获取任务对列等工作
##类的设计

> noncopyable.h   --->为了防止复制和赋值操作

```
#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_
#include <iostream>
class noncopyable{
protected:
	noncopyable(){
	}
	~noncopyable(){
	}
private:
	noncopyable(const noncopyable &);
	noncopyable &operator=(const noncopyable &);
};
#endif

```
> MutexLock.h

```
#ifndef MUTEXLOCK_H_
#define MUTEXLOCK_H_
#include <iostream>
#include <pthread.h>
#include "noncopyable.h"

class Condition ;
class MutexLock:public noncopyable{
	friend class Condition ;
	private:
		pthread_mutex_t _mutex ;
	public:
		MutexLock();
		~MutexLock();
		void lock();
		void unlock();
};
//这里用到了智能执针的思想
class GuardLock{
public:
	GuardLock(MutexLock *lock):_lock(lock){
		_lock->lock() ;
	}
	~GuardLock(){
		_lock->unlock();
	}
private:
	MutexLock *_lock ;
};
#endif

```

> Condition.h

```
#ifndef CONDITION_H_
#define CONDITION_H_
#include <iostream>
#include <pthread.h>
#include "MutexLock.h"

class Condition:public noncopyable{
	private:
		pthread_cond_t _cond ;
		MutexLock *_p_mutex ;
	public:
		Condition(MutexLock *p_mutex);
		~Condition() ;
		void wait() ;
		void notify() ;
		void notifyAll() ;
};
#endif

```

> Thread.h

```
#ifndef THREAD_H_
#define THREAD_H_
#include <iostream>
#include <pthread.h>
class Thread{
	private:
		pthread_t _pth ;
	public:
		Thread() ;
		virtual ~Thread() ;
		void start() ;
		void join() ;
		static void *thread_handle(void *arg) ;
		virtual void run() = 0 ;
		pthread_t get_tid() const ;
};
#endif

```

> WorkThread.h

```
#ifndef WORKTHREAD_H_
#define WORKTHREAD_H_
#include <pthread.h>
#include "Thread.h"

class ThreadPool ;
class WorkThread :public Thread{
public:
	void run() ; //线程所要完成的任务
	void compute_task(int num); //计算的任务
	void register_thread_pool(ThreadPool *p_thread_pool) ;  //用于注册线程池，使线程可以从此线程池中取得任务

private:
	ThreadPool *_p_thread_pool ;

};

#endif /* WORKTHREAD_H_ */

```

> ThreadPool.h

```
#ifndef THREADPOOL_H_
#define THREADPOOL_H_
#include <queue>
#include <vector>
#include "WorkThread.h"
#include "MutexLock.h"
#include "Condition.h"
#include "noncopyable.h"
struct Task{
	int _num ;
};
class ThreadPool :public noncopyable{
public:
	ThreadPool(std::vector<WorkThread>::size_type max_thread);
    virtual ~ThreadPool();
    // let the thread pool work
	void start_thread_pool() ;
    // stop the thread pool  
	void stop_thread_pool() ;      
     // add the task
	bool add_task_queue(Task task) ; 
     // get a task to deal with 
	bool get_task_queue(Task &task) ;  
    // whether there are tasks
	bool is_task_queue_empty() const  ;
     // get the size of task queue  
	std::queue<Task>::size_type get_task_queue_size() const ; 

private:
     //task queue
	std::queue<Task> _task_queue ; 
      //the number of thread
	std::vector<WorkThread>::size_type _max_thread ; 
      // thread vector
	std::vector<WorkThread> _thread_vector ;   
      //the signal of thread pool
	bool _is_started ; 
	mutable MutexLock _lock ;   // mutex
	mutable Condition _cond ;    //cond
};
#endif /* THREADPOOL_H_ */

```


