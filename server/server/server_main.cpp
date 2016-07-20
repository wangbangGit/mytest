#include"stdfx.h"

#ifdef _WIN32
#include <windows.h>

#define delaytime(v)	Sleep(v)
#else
#include <unistd.h>

#define delaytime(v)	usleep(v * 1000)
#define system(a)
#endif

void run()
{
	while (1)
	{
		lxnet::net_run();
		clientmgr::Instance().run();
		delaytime(100);
		clientmgr::Instance().endrun();
	}
}

int main(void)
{
	if (!config::Instance().init())
	{
		std::cout << "init config error!" << std::endl;
		system("pause");
		return 0;
	}
	//³õÊ¼»¯
	if (!lxnet::net_init(512, 1, 1024 * 32, 100, 1, 4, 1))
	{
		std::cout << "init network error!" << std::endl;
		system("pause");
		return 0;
	}
	clientmgr::Instance().init(config::Instance().GetListenPort());
	run();
	clientmgr::Instance().release();
	delaytime(1000);

	lxnet::net_release();
	system("pause");
	return 0;
}