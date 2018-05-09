#include "stdafx.h"
#include "Menu.h"

#include <iostream>


Menu::Menu()
{
	showMainMenu();
}

Menu::~Menu()
{
}

void Menu::showMainMenu()
{
	std::cout << "Badanie efektywnosci algorytmow grafowych" << std::endl;
	std::cout << "1 - algorytm Prima" << std::endl;
	std::cout << "2 - algorytm Dijikstry" << std::endl;
	std::cout << "3 - WYJSCIE" << std::endl;
	std::cout << "//> ";
}


