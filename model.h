#ifndef Model_INCLUDED
#define Model_INCLUDED

#include <utility>
#include <set>
#include "camera.h"
#include "pawn.h"

#define GRID 500.0

class Model {
	public:
		//static Camera *camera;
		static std::pair<int,int> window;
		static Pawn *board[8][8];
		static std::pair<int,int> *hover;
		static std::pair<int,int> *selected;
		static std::set<Pawn *> deleting;
		static std::set<Pawn *> toDelete;
		static std::set<Pawn *> moving;
		static std::set<Pawn *> doneMoving;
		//static Pawn *selected;

		static void init( int width, int height);
		static std::pair<int,int> glutToGL( int x, int y);
};

#endif
