#ifndef PulseAnimator_INCLUDED
#define PulseAnimator_INCLUDED

#include "animator.h"

class PulseAnimator : public Animator {
	public:
		//Pawn *pawn;
		//void (*callback)( Pawn *);
		int t, tmax;
		PulseAnimator( Pawn *);
		void step( int dt);
};

#endif
