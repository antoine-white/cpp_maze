#pragma once
#include "moves.h"

namespace core {
	/**
	* \brief facade of the game
	*  
	* This is the only class that the user should instantiate.
	* It uses facade design pattern
	*/
	// We may want to consider turing this class into a singleton
	// because only one game_facade is required
	class game_facade
	{
		std::array<core::move_handler, 4> move_handlers;
		core::player* p;
		core::grid* g;
	public:
		/** 
		\brief create a new game with a given maze as an string

		the string must contain only core::DEFAULT_CHAR_WALL for the walls and 
		core::DEFAULT_CHAR_EMPTY for the empty cell, without a empty line at the end 
		nor at the start.		
		\see core::grid
		*/
		game_facade(std::string grid_str);
		~game_facade();
		/**
		\return list of all the available moves the player can use to move around the maze
		*/
		std::vector<std::string> str_moves_types() const;
		/**
		\brief move the player according to the choosen move strategy

		\details given a value according to #str_moves_types() you wish to use
		for instance if you wish to use the second of move type from #str_moves_types()
		\p index will be 1.

		\return The pair contains a core::parcour_res and a string containg the maze 
		according to \link core::grid operator std::string()
		*/
		std::pair<core::parcour_res, std::string> move(size_t index);
		/**
		\return the statistics of all the move strategies following the order previously 
		set by #str_moves_types()
		*/
		std::vector<core::parcour_res> get_stats();
		/**
			display the maze according to \link core::grid operator std::string()
		*/
		std::string display_grid() const;
	};

}