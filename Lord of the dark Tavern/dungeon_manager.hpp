#pragma once

#include <iostream>
#include <string>
#include <boost/random.hpp>
#include <ctime>
#include <cstdint>
#include <list>
#include <SFML\Graphics.hpp>
#include "dungeon_mob.hpp"
#include <Vector>


class dungeon_manager {
public:
	dungeon_manager(const int &m_power, std::string path, const std::vector<sf::Image*> &image);
	~dungeon_manager();


	bool check_dungeon() { return dungeon_atkiv; };
	int enviroment_id() { return enviro_id; };


	void render(sf::RenderWindow *rw);


private:


	void fill_dungeon(const std::vector<sf::Image*> &image);
	void load_dungeon();
	

	int diffculty = 1;
	int floors = 0;
	int floor_a = 0;
	int enviro_id = 0;
	bool dungeon_atkiv = false;

	std::string m_path;

	sf::Font *pfont;

	std::vector<mob*> mob_ebene_1;
	std::vector<sf::Image> image;

	std::vector<int> mob_per_floor;



};