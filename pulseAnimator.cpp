
#include "pulseAnimator.h"

#include "pawn.h"

#define TMAX 50

PulseAnimator::PulseAnimator( Pawn *p) {
	callback = NULL; // Cause repeat.
	t = 0;
	tmax = TMAX;

	pawn = p;
}

void PulseAnimator::step( int dt) {
	t += dt;

	if ( t > tmax) {
		//printf("pulse: %p\n", this);
		//printf("\tcallback: %p\n", callback);
		if ( callback) {
			callback( pawn);
			return;
		}
		else
			tmax += TMAX;
	}

	pawn->scale = 1 - 0.15 * sinf( 6.28318530718 * t / TMAX);
}
