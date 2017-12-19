#pragma once

#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include <Vector>
#include "enviroment_loader.hpp"
#include "enumStructs.hpp"
#include <boost/random.hpp>
#include <ctime>


class dungeon_manager
{
public:
	dungeon_manager(const int &iPower,const std::vector<sf::Texture>& vMobTexture);
	~dungeon_manager();


	void render(sf::RenderWindow *rw);


private:


	void fill_dungeon();
	

	int diffculty = 1;
	int floors = 0;
	int floor_a = 0;
	int enviro_id = 0;

	//Hintergrund Lader
	enviroment_loader	*pHintergrundLader;

	sf::Texture p_life_t;
	const std::vector<sf::Texture> p_texture;
	std::vector<GAMESTRUCTS::mob> mob_this_dungeons;


	std::vector<int> mob_per_floor;



};