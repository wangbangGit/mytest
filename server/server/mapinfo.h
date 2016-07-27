/*
*
*	地图数据
*
*/

/*
	表中读到的地图信息
*/

#pragma once
#include "string"

class mapinfo
{
public:
	mapinfo();
	~mapinfo();

	bool init(std::string bar_filename);
	bool load();
	void addbar(int row,int col); //添加阻挡点

private:
	int m_mapid;
	int m_width;
	int m_height;

	bool *m_barinfo; //阻挡信息
	std::string m_bar_filename;
};