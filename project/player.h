#pragma once
#include "grid.h"
#include <array>
#include <stdexcept>

namespace core {

	class move_handler;

	/**
	\brief internal class, public usage isn't intended
	*/
	class player
	{
		grid* curr_grid;
	public:
		player() : curr_grid(nullptr) {};
		void load_grid(grid*);
		bool is_goable(core::Directions D) const;
		bool move(core::Directions D);
		bool is_end() const;
		void tag();
	};

}

