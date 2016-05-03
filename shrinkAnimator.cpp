
#include "shrinkAnimator.h"

#include "pawn.h"

#define TMAX 50

ShrinkAnimator::ShrinkAnimator( Pawn *p) {
	callback = Animator::doneCallback;
	t = 0;
	tmax = TMAX;

	pawn = p;
}

void ShrinkAnimator::step( int dt) {
	t += dt;

	if ( t > tmax) {
		if ( callback) {
			callback( pawn);
		}

		return;
	}

	pawn->scale = 1 - sinf( 1.57079632679 * t / TMAX);
}
