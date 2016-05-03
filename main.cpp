
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "model.h"
#include "step.h"
#include "draw.h"

#define INIT_WIDTH 800
#define INIT_HEIGHT 600

int main( int argc, char** argv) {
	glutInit( &argc, argv);

	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize( INIT_WIDTH, INIT_HEIGHT);
	glutInitWindowPosition( 0, 0);
	glutCreateWindow( argv[0]);

	// Initialize model.
	Model::init( INIT_WIDTH, INIT_HEIGHT);

	// Initialize stepper.
	Step::init();

	// Initialize drawer.
	Draw::init();

	// Set callbacks.
	glutDisplayFunc( Draw::draw);
	//glutReshapeFunc( Step::resize);
	glutKeyboardFunc( Step::keyboard);
	glutMotionFunc( Step::mouseDrag);
	glutPassiveMotionFunc( Step::mouseMove);
	glutMouseFunc( Step::mouseClick);
	glutIdleFunc( Step::step);

	glutMainLoop();
	return 0;
}

