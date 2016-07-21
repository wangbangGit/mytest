#include<iostream>
#include"lxnet.h"
#include "crosslib.h"
#include"msgdef.h"

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

	lxnet::Socketer *newclient = lxnet::Socketer::Create();

	//每100毫秒尝试连接
	while (!newclient->Connect("127.0.0.1", 30012))
	{
		delaytime(100);
	}

	std::cout << " connect succeed!" << std::endl;

	MessagePack sendpack;
	MessagePack *recvpack;
	char neirong[1024 * 30] = "a1234567";
	int size = sizeof(neirong);
	sendpack.PushBlock(neirong, size);

	MsgPing msg;
	MsgEnd endmsg;

	int sendnum = 0;
	int64 begin, end;
	begin = get_millisecond();
	newclient->SendMsg(&msg);
	newclient->CheckSend();
	newclient->CheckRecv();
	sendnum++;

	while (1)
	{
		recvpack = (MessagePack *)newclient->GetMsg();
		if (recvpack)
		{
			newclient->SendMsg(&msg);
			newclient->CheckSend();
			sendnum++;
			if (sendnum == 10000)
			{
				newclient->SendMsg(&endmsg);
				newclient->CheckSend();
				end = get_millisecond();
				std::cout << "end - begin:" << (int)(end - begin) << std::endl;
				break;
			}
		}
		else
		{
			delaytime(0);
		}

		if (newclient->IsClose())
			break;

		lxnet::net_run();
	}
	delaytime(1000);

	lxnet::Socketer::Release(newclient);
	lxnet::net_release();
	system("pause");
	return 0;
}