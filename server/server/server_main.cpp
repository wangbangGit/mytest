#include<iostream>
#include"lxnet.h"
#include"msgbase.h"

#ifdef _WIN32
#include <windows.h>

#define delaytime(v)	Sleep(v)
#else
#include <unistd.h>

#define delaytime(v)	usleep(v * 1000)
#define system(a)
#endif

int main(void)
{
	//初始化
	if (!lxnet::net_init(512, 1, 1024 * 32, 100, 1, 4, 1))
	{
		std::cout << "init network error!" << std::endl;
		system("pause");
		return 0;
	}

	lxnet::Listener *list = lxnet::Listener::Create();
	if (!list || !list->Listen(30012, 10))
	{
		std::cout << "listen error!" << std::endl;
		system("pause");
		return 1;
	}

	std::cout << "listen succeed!" << std::endl;

	MessagePack sendpack;
	MessagePack *recvpack;
	char neirong[1024 * 30] = "a1234567";
	int size = sizeof(neirong);
	sendpack.PushBlock(neirong, size);

	//新连接
	lxnet::Socketer *newclient = NULL;
	while (1)
	{
		delaytime(100);

		lxnet::net_run();
		if(!list->CanAccept())
			continue;

		if(!(newclient = list->Accept()))
			continue;

		std::cout << "accept succeed!" << std::endl;
		break;
	}

	newclient->SetSendLimit(-1);
	newclient->CheckRecv();

	while (1)
	{
		recvpack = (MessagePack *)newclient->GetMsg();
		if (recvpack)
		{
			newclient->SendMsg(&sendpack);
			newclient->CheckSend();
		}
		else
		{
			delaytime(0);
		}

		if (newclient->IsClose())
		{
			lxnet::Socketer::Release(newclient);
			newclient = NULL;
			break;
		}

		lxnet::net_run();
	}

	delaytime(1000);

	lxnet::Listener::Release(list);
	lxnet::net_release();
	system("pause");
	return 0;
}