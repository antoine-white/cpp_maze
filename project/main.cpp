#include <iostream>
#include <string>
#include "game_facade.h"
#include "maze_loader.h"

using namespace std;

/**
	\mainpage  Project M1 COO 2020-2021
	\author    Antoine Blanco
	\author    Mehdi Ziar
	\date	   08/01/2021
*/

int main()
{
	cout << "Bienvenue sur ce programme d'exploration de labyrinthe\n" << endl;
	cout << "Veuillez choisir un labyrinthe dans la liste ci-dessous : " << endl;
	auto mazes = maze_loader::available_mazes();
	for (size_t i = 0; i < mazes.size(); i++)
	{
		cout << to_string(i) << " - " << mazes[i] << endl;
	}
	cout << "Entrez votre choix : ";
	std::string s;
	int choice;
	cin >> choice;
	try {
		s = maze_loader::maze_as_str(static_cast<size_t>(choice));
	}
	catch (...) {
		cerr << "\n\nChoix invalide\n\n ";
		return EXIT_FAILURE;
	}

	core::game_facade game(s);
	cout << "\n\nAffichage textuel du labyrinthe choisi \n\n\n";
	cout << game.display_grid() << endl;

	bool isOver = false;
	std::vector<core::parcour_res> res_stats;
	auto vecr = game.str_moves_types();
	cout << "\n\nLancement du jeu \n\n";
	while (!isOver)
	{
		cout << endl << "1 : afficher les stats" << endl;
		cout << "2 : parcours" << endl;
		cout << "3 : stopper le programme" << endl;
		cout << "Entrez votre choix : ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			res_stats = game.get_stats();
			for (size_t i = 0; i < res_stats.size(); i++)
			{
				cout << endl << "Methode : " << vecr[i] << endl;
				cout << static_cast<string>(res_stats[i]) << endl;
			}
			break;
		case 2:
			for (size_t i = 0; i < vecr.size(); i++)
				cout << to_string(i) << " - " << vecr[i] << endl;
			cout << "Entrez votre choix : ";
			int choice2;
			cin >> choice2;
			try {
				auto r = game.move(choice2);
				cout << endl << static_cast<string>(r.first) << endl;
				cout << endl << r.second << endl;
			}
			catch (...) {
				cerr << "\n\nChoix invalide\n\n ";
			}
			break;
		case 3:
			isOver = true;
			break;
		default:
			cerr << "\n\nChoix invalide\n\n ";
			break;
		}
	}

	return EXIT_SUCCESS; 
}