
// References: http://www.firstobject.com/getmillicount-milliseconds-portable-c++.htm

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <sys/timeb.h>
#include <cstdio>

#include "model.h"
#include "step.h"
#include "draw.h"
#include "pulseAnimator.h"

#define STEP_RATE 20

using std::pair;

int Step::time;
pair<int,int> *Step::click;

int GetMilliCount()
{
  // Something like GetTickCount but portable
  // It rolls over every ~ 12.1 days (0x100000/24/60/60)
  // Use GetMilliSpan to correct for rollover
  timeb tb;
  if ( ftime( &tb ))
		printf( "Failed to retrieve time from system.\n");

  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}

pair<int,int> GetMilliSpan( int nTimeStart )
{
	int end = GetMilliCount();
  int nSpan = end - nTimeStart;
  if ( nSpan < 0 )
    nSpan += 0x100000 * 1000;

  return std::make_pair( end, nSpan);
}

void Step::init() {
	time = GetMilliCount();
	click = NULL;
}

void Step::keyboard( unsigned char c, int x, int y) {
	switch (c) {
		case 'q':
		case  27:
			exit(0);
			break;
		case 'o':
			Camera::zoomOut();
			break;
		case 'i':
			Camera::zoomIn();
			break;
	}

	glutPostRedisplay();
}

// Pick the board position given the mouse location.
pair<int,int> *Step::pick( pair<int,int> p) {
	Vector3d camera = Vector3d::sphericalToCartesian( Camera::position);
	//printf( "camera: %g,%g,%g\n", camera[0], camera[1], camera[2]);
	float nc = (float) (Model::window).first;
	float nr = (float) (Model::window).second;
	float alpha = Camera::aspectRatio;
	float theta = 0.785398163; // 45 degrees
	float h = 2 * tanf( theta / 2);
	float w = h * alpha;
	//printf( "nc, nr: %g, %g\n", nc, nr);
	//printf( "w, h: %g, %g\n", w, h);

	Vector3d at = Vector3d::zero();
	Vector3d view = at - camera;
	view.normalize();
	Vector3d up = Vector3d::zUnit();

	Vector3d vz = at - view;
	Vector3d vx = Vector3d::cross( view, up);
	vx.normalize();
	Vector3d vy = Vector3d::cross( vz, vx);

	//printf("vz: ");
	//vz.print();
	//printf("vx: ");
	//vx.print();
	//printf("vy: ");
	//vy.print();

	float ay = h * ( p.second / nr - 0.5);
	float ax = w * ( p.first / nc - 0.5);

	//printf( "ax, ay: %g, %g\n", ax, ay);

	Vector3d u = ax * vx + ay * vy - vz;
	u.normalize();

	//printf( "u: ");
	//u.print();

	if ( u[2] == 0.0)
		return NULL;
	
	float t = - ( camera[2] - HEIGHT) / u[2];
	//printf( "%g\n", t);
	
	if ( t < 0.0)
		return NULL;

	Vector3d r = camera + t * u;
	//printf( "r: ")
	//r.print();

	pair<int,int> *res = (pair<int,int> *) malloc( sizeof(pair<int,int>));

	if ( std::abs( r[0]) >= GRID * 4 || std::abs( r[1]) >= GRID * 4)
		return NULL;

	res->first = (int) (r[1] / GRID + 4.0);
	res->second = (int) (r[0] / (GRID) + 4.0);

	//printf( "res: %d, %d\n", res->first, res->second);

	return res;
}

void Step::hover( pair<int,int> p) {
	// Remove the previous position if it exists
	if ( Model::hover)
		free( Model::hover);
	
	Model::hover = Step::pick( p);
}

void Step::mouseDrag( int x, int y) {
	pair<int,int> p = Model::glutToGL( x, y);

	// Update the hover.
	Step::hover( p);

	// Drag around the screen if there is a previous click.
	if ( !click)
		return;

	int dx = p.first - click->first;
	int dy = p.second - click->second;

	Camera::move( dx, dy);

	*click = p;

	glutPostRedisplay();
}

void Step::mouseMove( int x, int y) {
	pair<int,int> p = Model::glutToGL( x, y);

	// Update the hover.
	Step::hover( p);

	//printf( "%d, %d\n", x, y);
	glutPostRedisplay();
}

void Step::mouseClick( int b, int s, int x, int y) {
	pair<int,int> p = Model::glutToGL( x, y);

	if ( b == GLUT_LEFT_BUTTON && s == GLUT_DOWN) {
		click = (pair<int,int> *) malloc( sizeof(pair<int,int>));
		*click = p;
	}
	else if ( b == GLUT_LEFT_BUTTON && s == GLUT_UP) {
		free( click);
		click = NULL;
	}
	else if ( b == GLUT_RIGHT_BUTTON && s == GLUT_UP) {
 		pair<int,int> *sel = Step::pick( p);

		// Check if there was a selection.
		if ( sel) {
			// Check if there was a previous selection.
			if ( Model::selected) {
				// Check that not in the same spot.
				if ( *sel != *Model::selected) {
					// Move selected pawn.
					Pawn *new_piece = Model::board[Model::selected->second][Model::selected->first];
					new_piece->moveTo( sel->second, sel->first);
					
					// Set selected to nothing.
					free( Model::selected);
					Model::selected = NULL;
				}

				free( sel);
				sel = NULL;
			}
			else {
				Pawn *piece = Model::board[sel->second][sel->first];
	
				if ( piece) {
					// Set animation.
					PulseAnimator *anim =  new PulseAnimator( piece);
					piece->animators.push_back( anim);

					// Mark as selected.
					Model::selected = sel;
				}
				else {
					free( sel);
					sel = NULL;
				}
			}
		}
	}

	glutPostRedisplay();
}

void Step::step() {
	pair<int,int> timer = GetMilliSpan( time);
	int dt = timer.second;
	// if ( dt == 0)
	if ( dt < STEP_RATE)
		return;

	dt = dt / STEP_RATE;
	time = timer.first;

	for ( int i = 0; i < 8; i++)
		for ( int j = 0; j < 8; j++)
			if (Model::board[i][j]) {
				Model::board[i][j]->step( dt);
			}
	
	for ( std::set<Pawn *>::iterator it = Model::moving.begin(); it != Model::moving.end(); it++)
		(*it)->step( dt);

	for ( std::set<Pawn *>::iterator it = Model::deleting.begin(); it != Model::deleting.end(); it++)
		(*it)->step( dt);

	for ( std::set<Pawn *>::iterator it = Model::doneMoving.begin(); it != Model::doneMoving.end(); it++)
		Model::moving.erase( *it);

	Model::doneMoving.clear();

	for ( std::set<Pawn *>::iterator it = Model::toDelete.begin(); it != Model::toDelete.end(); it++)
		Model::deleting.erase( *it);
	
	Model::toDelete.clear();
	
	glutPostRedisplay();
}

