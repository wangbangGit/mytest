#include"stdfx.h"

#ifdef _WIN32
#include <windows.h>

#define delaytime(v)	Sleep(v)
#else
#include <unistd.h>

#define delaytime(v)	usleep(v * 1000)
#define system(a)
#endif

int64 g_currenttime;
bool g_run;
void run()
{
	int delay;
	while (g_run)
	{
		g_currenttime = get_millisecond();
		lxnet::net_run();
		clientmgr::Instance().run();
		clientmgr::Instance().endrun();
		delay = static_cast<int>(get_millisecond() - g_currenttime);
		if (delay < 100)
			delaytime(100 - delay);
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
	g_run = true;
	run();
	clientmgr::Instance().release();
	delaytime(1000);

	lxnet::net_release();
	system("pause");
	return 0;
}