#include"mapinfo.h"

mapinfo::mapinfo()
{
	m_cellinfo = nullptr;
}

mapinfo::~mapinfo()
{
	if (m_cellinfo)
	{
		delete m_cellinfo;
		m_cellinfo = nullptr;
	}
}

bool mapinfo::init(int mapid,int width,int height)
{
	m_mapid = mapid;
	m_width = width;
	m_height = height;

	m_cellinfo = new cellinfo[m_width * m_height];
	return true;
}

bool mapinfo::load()
{

	return true;
}

void mapinfo::addbar(int row, int col)
{
	if (m_cellinfo)
	{
		if (row >= 0 && row < m_width)
		{
			if (col >= 0 && col < m_height)
			{
				m_cellinfo[row * col].isbar = true;
			}
		}
	}
}