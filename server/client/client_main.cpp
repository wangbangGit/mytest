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
	//初始化网络库
	if (!lxnet::net_init(512, 1, 1024 * 32, 100, 1, 4, 1))
	{
		std::cout << "init network error!" << std::endl;
		system("pause");
		return 0;
	}

	//创建socket
	lxnet::Socketer *newclient = lxnet::Socketer::Create();

	//每100毫秒尝试连接
	while (!newclient->Connect("127.0.0.1", 30012))
	{
		delaytime(100);
	}

	std::cout << " connect succeed!" << std::endl;

	MessagePack *recvpack;

	MsgPing msg;
	MsgEnd endmsg;

	int sendnum = 0;
	int64 begin, end;
	begin = get_millisecond();
	//发送消息
	newclient->SendMsg(&msg);
	//真正的发送，每次sendmsg之后，进行该操作才会真正的把消息发送出去
	newclient->CheckSend();
	//投递接受消息，该操作之后，就可以收到来自服务端的消息了
	newclient->CheckRecv();
	sendnum++;

	//死循环
	while (1)
	{
		//尝试获取服务端发来的消息
		recvpack = (MessagePack *)newclient->GetMsg();
		if (recvpack)
		{
			//收到服务端的消息的时候
			//给服务端发送ping消息
			newclient->SendMsg(&msg);
			newclient->CheckSend();
			sendnum++;
			if (sendnum == 10000)
			{
				//当发送次数到1W的时候，发送endmsg
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

		//当连接断开的时候跳出
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