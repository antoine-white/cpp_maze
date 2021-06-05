#pragma once

#include "grid_cell.h"
#include <vector>

namespace core {
	/**
	\brief internal class, public usage isn't intended
	*/
	class grid
	{
		start_cell* start;
		end_cell* end;
		grid_cell* current;
		std::vector<empty_cell*> tagged;
		void parse_string(std::string);
	public:
		grid(std::string s);
		/**
		 \brief display the grid
		 display every cell in the grid with the coresponding char : 
		 - wall => core::DEFAULT_CHAR_WALL 
		 - empty_cell(untagged) => core::DEFAULT_CHAR_EMPTY
		 - empty_cell(tagged) => core::DEFAULT_CHAR_EMPTY_TAGGED
		 
		 (defined in grid_cell.h)
		*/
		operator std::string () const;
		void tag_curr();
		void untag_all();
		bool is_goable(core::Directions D) const;
		bool move(core::Directions D);
		bool is_end() const;
		void reset();
	};
}

