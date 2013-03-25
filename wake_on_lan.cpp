/*
**	该程序的功能是：局域网远程开机。
**	首先需要设置bios，需要bios支持远程开机。 
**  注：2002年以后的主板一般都支持远程开机启动。以华硕主板为例：开机后猛按del键，然后设置power on ring.
**  详情见：http://service.oray.com/question/1106.html
**  程序现支持linux和windows系统。
**  使用方式：
**  linux: ./execute_file_name pysical_address.
**  windows: ./execute_file_name
**  athor: nemo1937
**  email: zxqj2011@163.com
**  @created 2013-03-25
*/  

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#ifdef __linux__
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#define port 6000

using namespace std;


int main(int argc, char **argv)
{

	std::string HWaddr;

#ifdef __linux__
	if (argc != 2)
	{
		printf("usage: ./wake_on_lan harder_ware_address \n");	
		return 0;
	}

	HWaddr = argv[1];
#else
	
	printf("input pysical address:");
	std::cin >> HWaddr;
#endif
	int hwad[6] = {0};
	int i;

	/* windows system's physical address */
	if (HWaddr.find("-"))
	{
		i = sscanf(HWaddr.c_str(), "%2x-%2x-%2x-%2x-%2x-%2x", &hwad[0], &hwad[1], 
									  &hwad[2], &hwad[3], &hwad[4], &hwad[5]);
	} else if(HWaddr.find(":")) /* linux or unix system's physical address */
	{
		i = sscanf(HWaddr.c_str(), "%2x:%2x:%2x:%2x:%2x:%2x", &hwad[0], &hwad[1], 
									  &hwad[2], &hwad[3], &hwad[4], &hwad[5]);
	} else
	{
		std::cout << "incorrect pysical address" << std::endl;
		return 1;
	}

	if (i != 6)
	{
		std::cout << "incorrect pysical address  format"  << std::endl;	
		return 0;
	} else
	{
		printf("[+] pysical address \n");
	}

	unsigned char eth_addr[6] = {0};
	for (int i = 0; i < 6; i ++)
	{
		eth_addr[i] = hwad[i];
	}

	/* make magic packet */
	unsigned char magic_packet[256];
	memset(magic_packet, 0x00, sizeof(magic_packet));
	memset(magic_packet, 0xff, 6);
	
	int step_size = 6;
	for (int i = 0; i < 16; i++)
	{
		memcpy(magic_packet + step_size, eth_addr, sizeof(eth_addr));
		step_size += 6;
	}

#ifdef _WIN32
	/* 启动WSA */
	WSADATA WSAData;   
	if (WSAStartup( MAKEWORD(2, 0), &WSAData)!=0)   
	{   
		fprintf(stderr, "WSAStartup failed: %d\n", GetLastError());   
		return 1;   
	}

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);		
	if (sock == INVALID_SOCKET)
	{
		perror("socket error");
		printf("%d \n", GetLastError());
		exit(1);
	}


	bool optval = true;

	/* set socket broadcast */
	SOCKET set_sock = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&optval, sizeof(bool));

	if (set_sock == SOCKET_ERROR)
	{
		closesocket(sock);
		WSACleanup();
		perror("setsockopt error");
		exit(1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	addr.sin_port = htons(port);

	/* send magic packet */
	if (sendto(sock, (const char *)magic_packet, sizeof(magic_packet), 0, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		perror("sendto error");
	} else
	{
		printf("[+] send magic packet success \n");
	}

	closesocket(sock);
	WSACleanup(); 

	Sleep(5000);

#else

	int sock = socket(AF_INET, SOCK_DGRAM, 0);		
	if (sock == -1)
	{
		perror("socket error");
		exit(1);
	}

	int optval = 1;
	/* set socket broadcast */
	int set_sock = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(int));

	if (set_sock == -1)
	{
		perror("setsockopt error");
		exit(1);
	}

	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	addr.sin_port = htons(port);

	/* send magic packet */
	if (sendto(sock, (const char *)magic_packet, sizeof(magic_packet), 0, 
			                	(struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("sendto error");
		exit(1);
	} else
	{
		printf("[+] send magic packet success \n");
	}

#endif

	return 0;
}

