
#include <cstddef>
#include "model.h"
#include "pawn.h"

using std::pair;

std::pair<int,int> Model::window;
Pawn *Model::board[8][8];
std::pair<int,int> *Model::hover;
std::pair<int,int> *Model::selected;
std::set<Pawn *> Model::deleting;
std::set<Pawn *> Model::toDelete;
std::set<Pawn *> Model::moving;
std::set<Pawn *> Model::doneMoving;

#define WHITE (Color( 0.7, 0.7, 0.7, 1.0))
#define BLACK (Color( 0.1, 0.1, 0.1, 1.0))

void Model::init( int w, int h) {
	window = std::make_pair( w, h);
	moving = std::set<Pawn *>();
	doneMoving = std::set<Pawn *>();
	deleting = std::set<Pawn *>();
	toDelete = std::set<Pawn *>();

	// Initialize camera.
	Camera::init( w, h);

	// Initialize the board state.
	selected = NULL;
	hover = NULL;
	for ( int i = 0; i < 8; i++) {
		int j = 0;
		board[i][j] = new Pawn( i, j);// GRID * (j - 3.5) , GRID * (i - 3.5));
		board[i][j++]->color = BLACK;
		board[i][j] = new Pawn( i, j);//GRID * (j - 3.5) , GRID * (i - 3.5));
		board[i][j++]->color = BLACK;
		for ( ; j < 6; j++) {
			board[i][j] = NULL;
		}
		board[i][j] = new Pawn( i, j);//GRID * (j - 3.5) , GRID * (i - 3.5));
		board[i][j++]->color = WHITE;
		board[i][j] = new Pawn( i, j);//GRID * (j - 3.5) , GRID * (i - 3.5));
		board[i][j++]->color = WHITE;
	}
}

pair<int,int> Model::glutToGL( int x, int y) {
  return std::make_pair( x, window.second - y);
}

