
#include "moveAnimator.h"
#include "Vector3d.h"
#include "model.h"

#include "pawn.h"

using std::pair;

MoveAnimator::MoveAnimator( Pawn *p, pair<int, int> pos) {
	pawn = p;
	position = pos;

	callback = Animator::doneCallback;
}

void MoveAnimator::step( int dt) {
	pawn->boardPos = position;
	pawn->position = Geom::Point( GRID * (position.first - 3.5), GRID * (position.second - 3.5), 50.0);;

	if ( callback)
		callback( pawn);
}
