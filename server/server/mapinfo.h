/*
*
*	地图数据
*
*/

#pragma once

struct cellinfo
{
	bool isbar; //是否阻挡点
};

class mapinfo
{
public:
	mapinfo();
	~mapinfo();

	bool init(int mapid, int width, int height);
	bool load();
	void addbar(int row,int col);

private:
	int m_mapid;
	int m_width;
	int m_height;

	cellinfo *m_cellinfo;
};