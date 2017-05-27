#include <iostream>
#include <SFML\Graphics.hpp>
#include <thread>  
#include "main_frame.hpp"
void enviroment_t1();
void datenbank_t2();
main_frame *frm;

int main(int argc, char* argv[])
{
	frm = new main_frame(*argv);
	std::thread t_1(enviroment_t1);
	std::thread t_2(datenbank_t2);
	frm->run();
	t_1.join();
	t_2.join();
}


void enviroment_t1()
{
	while (true)
	{
		frm->enviroment_t();
	}
}

void datenbank_t2()
{
	frm->datenbank_t();
}