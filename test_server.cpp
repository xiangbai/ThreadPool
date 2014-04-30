#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include "Server.h"
#include "ThreadPool.h"

int main(int argc , char **argv)
{
	std::ifstream fin(argv[1]);
    std::string ip, port ;
    fin>>ip>>port;
	Server server(ip , port) ;  //连接服务器，并开启服务器
	ThreadPool p(10) ;    //创建线程池
	p.start_thread_pool() ;   //启动线程

	char buf[1024];
	bzero(buf , 1024);
	while(true)
	{
		Task task ;
		server.recv_message(buf , 1024);   //接收客户端发送过来的任务消息
		task.m_clinet_addr=server.get_client_addr();   //获取客户端的ip地址和port号
		task.req_buf = buf ;   //客户端发送过来的命令请求
		p.add_task_queue(task) ;   //线程池将任务添加到线程池中，有工作线程来执行任务
		sleep(1);
	}
	return 0 ;
}
