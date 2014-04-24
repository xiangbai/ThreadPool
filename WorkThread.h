/*
 * WorkThread.h
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */

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
