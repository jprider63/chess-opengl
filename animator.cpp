
#include "animator.h"

#include "pawn.h"
#include "model.h"

void Animator::doneCallback( Pawn *pawn) {
	//printf( "done\n");
	if ( pawn->animators.empty())
		return;
	
	delete pawn->animators.front();
	pawn->animators.pop_front();
}

void Animator::addToBoardCallback( Pawn *pawn) {
	// Add to board.
	Model::board[pawn->boardPos.first][pawn->boardPos.second] = pawn;
	
	// Remove from moving set.
	Model::doneMoving.insert( pawn);

	Animator::doneCallback( pawn);
}

void Animator::deleteCallback( Pawn *p) {
	Model::toDelete.insert( p);

	delete p;
}

