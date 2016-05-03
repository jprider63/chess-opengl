#ifndef MoveAnimator_INCLUDED
#define MoveAnimator_INCLUDED

#include <utility>
#include "animator.h"

class MoveAnimator : public Animator {
	public:
		std::pair<int,int> position;
		MoveAnimator( Pawn *, std::pair<int, int>);
		void step( int dt);
};

#endif
