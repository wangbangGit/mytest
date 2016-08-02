/*
*
*	��ͼ����
*
*/

/*
	���ж����ĵ�ͼ��Ϣ
*/

#pragma once
#include "string"

class mapinfo
{
public:
	mapinfo();
	~mapinfo();

	bool init(int mapid, std::string bar_filename);
	bool loadbar();	//����赲��
	void getmapbirthpoint(int &x, int &y); //��ȡ������
	int  getmapid(); //��ȡ��ͼid
	void getmapwidthandheight(int &x, int &y); //��ȡ��ͼ���
private:
	int m_mapid;
	int m_width;
	int m_height;

	int m_birth_point_x;
	int m_birth_point_y;

	bool *m_barinfo; //�赲��Ϣ
	std::string m_bar_filename;
};