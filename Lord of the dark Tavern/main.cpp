#include <iostream>
#include <SFML\Graphics.hpp>
#include <thread>  
#include "main_frame.hpp"
std::string test;
void enviroment();
void datenbank();
main_frame *frm;

int main(int argc, char* argv[])
{
	test = *argv;
	std::cin;
	frm = new main_frame(test);
	std::thread t_1(enviroment);
	std::thread t_2(datenbank);
	frm->run();
	t_1.join();
	t_2.join();
}


void enviroment()
{
	while (true)
	{
		frm->enviroment();
	}
}

void datenbank()
{
	frm->datenbank();
}