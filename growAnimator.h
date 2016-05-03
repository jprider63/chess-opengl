#ifndef GrowAnimator_INCLUDED
#define GrowAnimator_INCLUDED

#include "animator.h"

class GrowAnimator : public Animator {
	public:
		int t, tmax;
		GrowAnimator( Pawn *);
		void step( int dt);
};

#endif
