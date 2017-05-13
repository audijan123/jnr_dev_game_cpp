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
#include "main_base.hpp"


class dungeon_manager
{
public:
	dungeon_manager(const int &m_power,const std::string &path,const JNR::main_base* pbase);
	~dungeon_manager();


	bool check_dungeon() { return dungeon_atkiv; };
	int enviroment_id() { return enviro_id; };


	void render(sf::RenderWindow *rw) const;


private:


	void fill_dungeon();
	void load_dungeon();
	

	int diffculty = 1;
	int floors = 0;
	int floor_a = 0;
	int enviro_id = 0;
	bool dungeon_atkiv = false;

	JNR::main_base p_memory_allocator;

	sf::Font *pfont;
	struct mob
	{
		sf::Image *image = new sf::Image;
		sf::Texture *p_texture = new sf::Texture;
		sf::Sprite *p_sprite = new sf::Sprite;

		sf::Texture *p_life_t = new sf::Texture;
		sf::Sprite *p_life = new sf::Sprite;

		sf::Text *text = new sf::Text;

		int life = 10;
		int dmg = 10;
	};

	std::string m_path;

	std::time_t now;

	std::vector<struct mob> mob_this_dungeons;


	std::vector<int> mob_per_floor;



};