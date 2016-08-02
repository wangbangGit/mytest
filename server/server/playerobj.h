#pragma once
#include<string>
#include"scene.h"

class scene;

class playerobj
{
public:
	playerobj();
	~playerobj();

	bool load(int mapid, int x, int y, std::string name, scene *_scene);
	bool moveto(int x, int y);
	void getnowpos(int &x, int &y);
	void setnowpos(const int &x, int const &y);
private:
	int m_now_mapid;
	int m_now_pos_x;
	int m_now_pos_y;

	scene *m_scene;
	std::string m_name;
};