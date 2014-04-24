#include "Thread.h"
Thread::Thread():_pth(0){

}
Thread::~Thread() {

}

void Thread::start()
{
	pthread_create(&_pth , NULL , thread_handle , this);
}
void Thread::join()
{
	pthread_join(_pth , NULL) ;
}

void *Thread::thread_handle(void *arg)
{
	Thread *p = static_cast<Thread *>(arg) ;
	p->run() ;
	return NULL ;
}
pthread_t Thread::get_tid() const
{
	return _pth ;
}
