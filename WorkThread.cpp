/*
 * WorkThread.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */
#include <iostream>
#include "WorkThread.h"
#include "ThreadPool.h"
void WorkThread::run(){
	while(true)
	{
		Task task ;
		bool ret = _p_thread_pool->get_task_queue(task) ;
		if(ret == false)
			return ;
		std::cout<<"get task : "<< task._num << " deal with  " ;
		compute_task(task._num) ;
	}
	std::cout<<"end working"<<std::endl;
}
void WorkThread::compute_task(int num){
		std::cout<<num * num <<std::endl;
}
void WorkThread::register_thread_pool(ThreadPool *p_thread_pool){
		_p_thread_pool = p_thread_pool ;
}
