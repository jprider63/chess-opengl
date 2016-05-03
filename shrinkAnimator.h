#ifndef ShrinkAnimator_INCLUDED
#define ShrinkAnimator_INCLUDED

#include "animator.h"

class ShrinkAnimator : public Animator {
	public:
		int t, tmax;
		ShrinkAnimator( Pawn *);
		void step( int dt);
};

#endif
