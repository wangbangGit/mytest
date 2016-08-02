/*
*
*	Server��main����
*
*/

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
		//��ȡ��ǰ֡ʱ��
		g_currenttime = get_millisecond();
		//�����run
		lxnet::net_run();
		//clientmgr run �߼���صĶ�����������
		clientmgr::Instance().run();
		//clientmgr endrun  ��Ҫ�ǽ�ǰ��ӵ������е�msg�����ʵ�ʵķ��ͳ�ȥ
		clientmgr::Instance().endrun();
		//��⵱ǰ֡ʹ��ʱ�䣬δ�ﵽ��Сֵ��ʱ��sleep
		delay = static_cast<int>(get_millisecond() - g_currenttime);
		if (delay < 100)
			delaytime(100 - delay);
		else
			std::cout << "run time out :" << delay << std::endl;
	}
}

bool init()
{
	if (!mapconfig::Instance().init())
	{
		std::cout << "init map failed!" << std::endl;
		return false;
	}

	return true;
}

int main(void)
{
	std::cout << "server start!" << std::endl;

	//��ȡ�����ļ�
	if (!config::Instance().init())
	{
		std::cout << "init config error!" << std::endl;
		system("pause");
		return 0;
	}
	//��ʼ�������
	if (!lxnet::net_init(512, 1, 1024 * 32, 100, 1, 4, 1))
	{
		std::cout << "init network error!" << std::endl;
		system("pause");
		return 0;
	}
	//���ü����˿ڣ�����listener
	if (!clientmgr::Instance().init(config::Instance().GetListenPort(), config::Instance().GetClientOverTime()))
	{
		std::cout << "init clientmgr error!" << std::endl;
		system("pause");
		return 0;
	}

	if (!init())
	{
		std::cout << "server init failed!" << std::endl;
		system("pause");
		return 0;
	}
	
	g_run = true;
	//��ѭ��
	run();
	//ѭ�����������Դ�ͷ�
	clientmgr::Instance().release();
	delaytime(1000);

	lxnet::net_release();
	system("pause");
	return 0;
}