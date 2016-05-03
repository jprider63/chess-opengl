
#include "growAnimator.h"

#include "pawn.h"

#define TMAX 50

GrowAnimator::GrowAnimator( Pawn *p) {
	callback = Animator::doneCallback;
	t = 0;
	tmax = TMAX;

	pawn = p;
}

void GrowAnimator::step( int dt) {
	t += dt;

	if ( t > tmax) {
		if ( callback) {
			callback( pawn);
		}

		return;
	}

	pawn->scale = sinf( 1.57079632679 * t / TMAX);
}
