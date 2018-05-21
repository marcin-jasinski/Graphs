#include "stdafx.h"
#include "Menu.h"
#include "PrimMenu.h"
#include "DijikstraMenu.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Menu::Menu()
{
	showMainMenu();
}

Menu::~Menu()
{
}

void Menu::showMainMenu()
{
	std::cout << "<=== BADANIE EFEKTYWNO�CI ALGORYTMOW GRAFOWYCH ===>" << std::endl;
	std::cout << "1 - algorytm Prima (MST)" << std::endl;
	std::cout << "2 - algorytm Dijkstry" << std::endl;
	std::cout << "3 - Koniec" << std::endl;
	std::cout << "//> ";

	int userChoice;
	PrimMenu pm = PrimMenu();
	DijikstraMenu dm = DijikstraMenu();

	std::cin >> userChoice;
	switch (userChoice)
	{
	case 1:
		pm.showPrimsMenu();
		break;
	case 2:
		dm.showDijikstraMenu();
		break;
	case 3:
		std::cout << "Koniec..." << std::endl;
		break;
	default:
		std::cout << "Wrong input." << std::endl;
		break;
	}
}



