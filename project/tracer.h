#pragma once
#include <vector>
#include "grid_cell.h"

namespace core {

	/**
	\brief a struct to pass stats about a parcour
	*/
	struct parcour_res {
		int nb_depl;
		bool has_reach;
		/**
		\return a string like : 
			"nombre de deplacement : 9\n
			 A atteint la sortie"
		*/
		operator std::string() const;
	};

	/**
	\brief internal class, public usage isn't intended
	*/
	class tracer
	{
		std::vector<Directions> trace;
		bool has_reach;
	public:
		tracer() : has_reach(false) {};
		~tracer();
		void add_to_trace(Directions);
		void has_find_end(bool);
		parcour_res get_stats() const;
	};
}


