/*
 * WorkThread.cpp
 *
 *  Created on: Apr 23, 2014
 *      Author: wang
 */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "WorkThread.h"
#include "ThreadPool.h"
void WorkThread::run(){
	while(true)
	{
		int socket_fd ;
		if(-1 == (socket_fd = socket(AF_INET , SOCK_DGRAM , 0))){
				throw std::runtime_error("socket");
		}
		Task task ;
		bool ret = _p_thread_pool->get_task_queue(task) ;
		if(ret == false)
			return ;
		std::cout<<"get task : "<< task.req_buf << " deal with  " ;
		float result = compute_task(task.req_buf) ;
		sendto(socket_fd, result, sizeof(float), 0,(struct sockaddr *)&(task.m_clinet_addr) , sizeof(task.m_clinet_addr)) ;
	}
	std::cout<<"end working"<<std::endl;
}
float WorkThread::compute_task(char *buf){
	char op ;
	float operate1;
	float operate2 ;
	float result = 0.0;

	sscanf(buf , "%f%c%f",operate1 , &op , operate2) ;
	switch(op)
	{
	case '+' :
		result = operate1 + operate2 ;
		break;
	case '-' :
		result = operate1 - operate2 ;
		break;
	case '*' :
		result = operate1 * operate2 ;
		break;
	case '/' :
		if(operate2==0)
		{
			throw std::runtime_error("divide cannot be zero");
		}
		result = operate1 / operate2 ;
		break;
	}
	return result ;
}
void WorkThread::register_thread_pool(ThreadPool *p_thread_pool){
		_p_thread_pool = p_thread_pool ;
}
