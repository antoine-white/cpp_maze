#pragma once
#include <string>
#include <functional>
#include "grid_cell.h"
#include "tracer.h"
#include "player.h"

namespace core {
	
	/**
	\brief internal enum, public usage isn't intended
	*/
	enum class Directions {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	/**
	\brief internal class, public usage isn't intended
	*/
	class move_handler {
		std::string _name;
		std::function<tracer(player*)> fun;
		move_handler(std::string, std::function<tracer(player*)>);
	public:
		static const int max_ite = 100000;
		static move_handler turn_left;
		static move_handler turn_right;
		static move_handler stairs;
		static move_handler random;
		//to move to grid_cell
		tracer operator()(player*)const;
		std::string name() const;
	};
}