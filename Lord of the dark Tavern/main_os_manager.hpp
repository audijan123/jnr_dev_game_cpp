#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <SFML\Graphics.hpp>
#include <boost/random.hpp>
#include <ctime>
#include "enumStructs.hpp"
#include <Windows.h>
namespace osm
{
	void call(const std::string &text);
	int si(const std::string &text);
	uint8_t sB(const std::string &text);
	void t_s_ms(const short &ms);
	bool sprite_pressed(const sf::Sprite *sprite, const sf::Vector2f &m);
	int genZufallsZahl();
	int genZufallsZahl(const int& min, const int& rnd);
	int genZufallsZahl(const int& min,const int& max, const int& rnd);
	std::string convertEnumToString(const GAMESTRUCTS::item_rare& r);
	std::wstring s2ws(const std::string& s);
}
