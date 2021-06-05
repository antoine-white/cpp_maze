#pragma once
#include <string>

namespace core{

	enum class Directions;

	class grid;

	static const char DEFAULT_CHAR_WALL = '#';
	static const char DEFAULT_CHAR_EMPTY = ' ';
	static const char DEFAULT_CHAR_EMPTY_TAGGED = '=';

	/**
	\brief internal abstract class, public usage isn't intended
	*/
	class grid_cell
	{
	protected:
		grid_cell* _left;
		grid_cell* _right;
		grid_cell* _up;
		grid_cell* _down;
		char character;
		bool _accesible;
		grid_cell(char c, bool a); // in order to do an abstract class
		friend class grid;
	public: 
		virtual ~grid_cell();
		operator std::string() const;
		const bool accessible() const;
		core::grid_cell* next(core::Directions D);
	};
	
	/**
	\brief internal class, public usage isn't intended
	*/
	class wall : public grid_cell
	{
		static const bool VISIBILITY = false;
	public:
		wall() : grid_cell(core::DEFAULT_CHAR_WALL,VISIBILITY) {};
	};

	/**
	\brief internal class, public usage isn't intended
	*/
	class empty_cell : public grid_cell
	{
		static const bool VISIBILITY = true;
	public : 
		empty_cell() : grid_cell(core::DEFAULT_CHAR_EMPTY,VISIBILITY) {};
		void tag();
		void untag();
	};

	/**
	\brief internal class, public usage isn't intended
	*/
	class start_cell : public empty_cell{
		public :
			start_cell() : empty_cell() {};
	};
	
	/**
	\brief internal class, public usage isn't intended
	*/
	class end_cell : public empty_cell{
		public :
			end_cell() : empty_cell() {};
	};

	// helper function
	bool isGoable(core::grid_cell* cell);
}
