#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdexcept>

int main(int argc , char **argv)
{
	int server_fd = socket(AF_INET, SOCK_DGRAM ,  0 );
	if(server_fd == -1)
	{
		throw std::runtime_error("socket");
	}
	struct sockaddr_in server_addr ;
	server_addr.sin_family = AF_INET ;
	server_addr.sin_port = htons(6688);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int result ;
	socklen_t len = sizeof(server_addr) ;
	std::string word ;
	while(std::cin >> word)
	{
		int iret =sendto(server_fd, word.c_str(),word.size(), 0, (struct sockaddr*)&server_addr, 16);
		recvfrom(server_fd, &result, 4, 0, NULL, NULL);
		std::cout <<"result: " << result << std::endl ;
	}
	return 0 ;
}
