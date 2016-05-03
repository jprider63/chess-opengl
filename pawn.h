#ifndef Pawn_INCLUDED
#define Pawn_INCLUDED

#include <list>
#include "Vector3d.h"
#include "color.h"
#include "animator.h"

class Pawn {
	public:
		Point3d position;
		std::pair<int,int> boardPos;
		Color color;
		float scale;
		std::list<Animator *> animators;

		Pawn( int i, int j);
		~Pawn();
		void setColor();
		void draw();
		void moveTo( int i, int j);
		void step( int dt);
};

#endif
