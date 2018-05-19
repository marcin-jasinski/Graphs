#include "stdafx.h"
#include "DijikstraMenu.h"


DijikstraMenu::DijikstraMenu()
{
}


DijikstraMenu::~DijikstraMenu()
{
}

void DijikstraMenu::showDijikstraMenu()
{
	system("cls");
	std::cout << "Wybierz Ÿród³o danych: " << std::endl;
	std::cout << "1 - wczytanie z pliku." << std::endl;
	std::cout << "2 - losowy graf" << std::endl;
	std::cout << "\\>";

	int userChoice;
	std::cin >> userChoice;
}
