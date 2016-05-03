
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include "draw.h"
#include "model.h"
#include "camera.h"
#include "RGBpixmap.h"

#define SKY 10000.0

GLuint Draw::textures[8];

void Draw::bindTexture( char *file, int i) {
	glBindTexture( GL_TEXTURE_2D, textures[i]);

	RGBpixmap *tex = new RGBpixmap( 1024, 1024);
	tex->readBMPFile( file);
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, 1024, 1024, GL_RGB, GL_UNSIGNED_BYTE, tex->getImageArray());
	delete tex;
}

void Draw::init() {
	// Set clear color.
	glClearColor( 0.0, 1.0, 0.0, 0.0);

	// Enable depth and textures.
	glEnable( GL_DEPTH_TEST);

	// Cull front face only.
	glEnable( GL_CULL_FACE);
	glCullFace( GL_FRONT);

	// Load textures.
	glGenTextures( 8, textures);
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	for ( int i = 0; i < 6; i++) {
		char file[30];
		sprintf( file, "stormydays_%d.bmp", i);

		bindTexture( file, i);
	}

	char *lightFile = "light-wood.bmp";
	bindTexture( lightFile, 6);

	char *darkFile = "dark-wood.bmp";
	bindTexture( darkFile, 7);
	
	// Set up lighting.
	glEnable( GL_NORMALIZE);
	glEnable( GL_LIGHTING);
	glEnable( GL_COLOR_MATERIAL);
	glEnable( GL_LIGHT0);
	//glEnable( GL_BLEND);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel( GL_SMOOTH);

}

GLfloat Draw::lightPosition[4] = { -5.0, -6.0, 5.0, 0.0};
void Draw::setupLight() {
	GLfloat ambientIntensity[4] = {0.5, 0.5, 0.5, 1.0};
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambientIntensity);

	glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0);
	glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);

	GLfloat intensity[4] = {1.25, 1.20, 1.15, 1.0};
	glLightfv( GL_LIGHT0, GL_DIFFUSE, intensity);
	glLightfv( GL_LIGHT0, GL_SPECULAR, intensity);

	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
}

void drawAxis() {
	glDisable( GL_LIGHTING);
	glPointSize( 4.0);
	glBegin( GL_LINES);
	glColor4f( 1.0, 0.0, 0.0, 1.0); // x
	glVertex3f( -10000.0,0.0,0.0);
	glVertex3f( 10000.0,0.0,0.0);
	glEnd();
	glBegin( GL_LINES);
	glColor4f( 0.0, 1.0, 0.0, 1.0); // y
	glVertex3f( 0.0,-10000.0,0.0);
	glVertex3f( 0.0,10000.0,0.0);
	glEnd();
	glBegin( GL_LINES);
	glColor4f( 0.0, 0.0, 1.0, 1.0); // z
	glVertex3f( 0.0,0.0,-10000.0);
	glVertex3f( 0.0,0.0,10000.0);
	glEnd();
	glEnable( GL_LIGHTING);
}

void drawSquare() {
	float x = GRID / 2.0;
	glBegin( GL_POLYGON);
	glNormal3f( 0.0, 0.0, -1.0);
	glTexCoord2f( 0.0, 0.0);
	glVertex3f( -x, -x, 0.0);
	glTexCoord2f( 0.0, 1.0);
	glVertex3f( x, -x, 0.0);
	glTexCoord2f( 1.0, 1.0);
	glVertex3f( x, x, 0.0);
	glTexCoord2f( 1.0, 0.0);
	glVertex3f( -x, x, 0.0);
	glEnd();
}

void drawSide() {
	float d = GRID / 2.0;
	glBegin( GL_POLYGON);
	glNormal3f( 0.0, -1.0, 0.0);
	glTexCoord2f( 0.25, 0.0);
	glVertex3f( -d, 0.0, 0.0);
	glTexCoord2f( 0.0, 0.0);
	glVertex3f( -d, 0.0, HEIGHT);
	glTexCoord2f( 0.0, 0.25);
	glVertex3f( d, 0.0, HEIGHT);
	glTexCoord2f( 0.25, 0.25);
	glVertex3f( d, 0.0, 0.0);
	glEnd();
}

//GLfloat dark[4] = { 0.22, 0.22, 0.22, 1.0};
//GLfloat light[4] = { 0.62, 0.62, 0.62, 1.0};

void bindHover( int j, int i) {
	if ( Model::selected && Model::selected->first == i && Model::selected->second == j)
		glColor4f( 0.1, 0.6, 0.6, 1.0);
	else if ( Model::hover && Model::hover->first == i && Model::hover->second == j)
		glColor4f( 0.6, 0.2, 0.5, 1.0);
}

void unbindHover( int j, int i) {
	if ( Model::selected && Model::selected->first == i && Model::selected->second == j)
		glColor4f( 1.0, 1.0, 1.0, 1.0);
	else if ( Model::hover && Model::hover->first == i && Model::hover->second == j)
		glColor4f( 1.0, 1.0, 1.0, 1.0);
}

void Draw::drawBoard() {
	// Set stenciling behavior.
	glStencilFunc( GL_ALWAYS, 1, 1);
	glStencilOp( GL_KEEP, GL_KEEP, GL_REPLACE);

	glEnable( GL_TEXTURE_2D);
	glColor4f( 1.0, 1.0, 1.0, 1.0);
	float d = GRID / 2.0;

	for ( int i = 0; i < 8; i++) {
		for ( int j = 0; j < 8; j++) {
			if ( (i + j) & 1) {
				glBindTexture( GL_TEXTURE_2D, textures[6]);
			}
			else {
				glBindTexture( GL_TEXTURE_2D, textures[7]);
			}

			float ex = (i - 4) * GRID;
			float ey = (j - 4) * GRID;
			float dx = ex + d;
			float dy = ey + d;

			bindHover( i, j);

			// Draw bottom.
			glPushMatrix();
			glTranslatef( dx, dy, 0.0);
			drawSquare();

			// Draw top.
			glTranslatef( 0.0, 0.0, HEIGHT);
			glRotatef( 180.0, 1.0, 0.0, 0.0);
			glEnable( GL_STENCIL_TEST);
			drawSquare();
			glDisable( GL_STENCIL_TEST);
			glPopMatrix();

			// Draw sides
			if ( j == 0) {
				glPushMatrix();
				glTranslatef( dx, ey, 0.0);
				drawSide();
				glPopMatrix();
			}
			else if ( j == 7) {
				glPushMatrix();
				glTranslatef( dx, ey + GRID, 0.0);
				glRotatef( 180.0, 0.0, 0.0, 1.0);
				drawSide();
				glPopMatrix();
			}
			if ( i == 0) {
				glPushMatrix();
				glTranslatef( ex, dy, 0.0);
				glRotatef( -90.0, 0.0, 0.0, 1.0);
				drawSide();
				glPopMatrix();
			}
			else if ( i == 7) {
				glPushMatrix();
				glTranslatef( ex + GRID, dy, 0.0);
				glRotatef( 90.0, 0.0, 0.0, 1.0);
				drawSide();
				glPopMatrix();
			}

			unbindHover( i, j);
		}
	}

	glDisable( GL_TEXTURE_2D);
}

void Draw::drawSky() {
	glDisable( GL_LIGHTING);
	glEnable( GL_TEXTURE_2D);
	glColor4f( 1.0, 1.0, 1.0, 1.0);

	// Draw top.
	glBindTexture( GL_TEXTURE_2D, textures[0]);
	glBegin( GL_POLYGON);
	glTexCoord2d(0.0,1.0);
	glVertex3f( SKY, SKY, SKY);
	glTexCoord2d(1.0,1.0);
	glVertex3f( -SKY, SKY, SKY);
	glTexCoord2d(1.0,0.0);
	glVertex3f( -SKY, -SKY, SKY);
	glTexCoord2d(0.0,0.0);
	glVertex3f( SKY, -SKY, SKY);
	glEnd();

	// Draw bottom.
	glBindTexture( GL_TEXTURE_2D, textures[5]);
	glBegin( GL_POLYGON);
	glTexCoord2d(0.0,0.0);
	glVertex3f( SKY, SKY, -SKY);
	glTexCoord2d(0.0,1.0);
	glVertex3f( SKY, -SKY, -SKY);
	glTexCoord2d(1.0,1.0);
	glVertex3f( -SKY, -SKY, -SKY);
	glTexCoord2d(1.0,0.0);
	glVertex3f( -SKY, SKY, -SKY);
	glEnd();

	// Draw left.
	glBindTexture( GL_TEXTURE_2D, textures[1]);
	glBegin( GL_POLYGON);
	glTexCoord2d(1.0,1.0);
	glVertex3f( SKY, SKY, SKY);
	glTexCoord2d(1.0,0.0);
	glVertex3f( SKY, SKY, -SKY);
	glTexCoord2d(0.0,0.0);
	glVertex3f( -SKY, SKY, -SKY);
	glTexCoord2d(0.0,1.0);
	glVertex3f( -SKY, SKY, SKY);
	glEnd();

	// Draw front.
	glBindTexture( GL_TEXTURE_2D, textures[2]);
	glBegin( GL_POLYGON);
	glTexCoord2d(1.0,1.0);
	glVertex3f( -SKY, SKY, SKY);
	glTexCoord2d(1.0,0.0);
	glVertex3f( -SKY, SKY, -SKY);
	glTexCoord2d(0.0,0.0);
	glVertex3f( -SKY, -SKY, -SKY);
	glTexCoord2d(0.0,1.0);
	glVertex3f( -SKY, -SKY, SKY);
	glEnd();

	// Draw right.
	glBindTexture( GL_TEXTURE_2D, textures[3]);
	glBegin( GL_POLYGON);
	glTexCoord2d(0.0,1.0);
	glVertex3f( SKY, -SKY, SKY);
	glTexCoord2d(1.0,1.0);
	glVertex3f( -SKY, -SKY, SKY);
	glTexCoord2d(1.0,0.0);
	glVertex3f( -SKY, -SKY, -SKY);
	glTexCoord2d(0.0,0.0);
	glVertex3f( SKY, -SKY, -SKY);
	glEnd();

	// Draw back.
	glBindTexture( GL_TEXTURE_2D, textures[4]);
	glBegin( GL_POLYGON);
	glTexCoord2d(0.0,1.0);
	glVertex3f( SKY, SKY, SKY);
	glTexCoord2d(1.0,1.0);
	glVertex3f( SKY, -SKY, SKY);
	glTexCoord2d(1.0,0.0);
	glVertex3f( SKY, -SKY, -SKY);
	glTexCoord2d(0.0,0.0);
	glVertex3f( SKY, SKY, -SKY);
	glEnd();

	glDisable( GL_TEXTURE_2D);
	glEnable( GL_LIGHTING);
}

GLfloat Draw::shadowProjection[] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	-lightPosition[0]/lightPosition[2], -lightPosition[1]/lightPosition[2], 0.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

void Draw::draw() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();
	Point3d camera = Vector3d::sphericalToCartesian( Camera::position);
	gluLookAt( camera[0], camera[1], camera[2], 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective( 60.0, Camera::aspectRatio, Camera::position[0] / 2.0, 10000000.0);
	gluPerspective( 45.0, Camera::aspectRatio, 1.0, 20000000000.0);
	glMatrixMode( GL_MODELVIEW);

	// drawAxis();
	
	// Draw sky.
	drawSky();
	
	// Set up light.
	setupLight();

	// Draw board.
	drawBoard();

	// Draw pawns.
	for ( int i = 0; i < 8; i++)
		for ( int j = 0; j < 8; j++)
			if (Model::board[i][j]) {
				Model::board[i][j]->setColor();
				Model::board[i][j]->draw();
			}
	
	for ( std::set<Pawn *>::iterator it = Model::moving.begin(); it != Model::moving.end(); it++) {
		(*it)->setColor();
		(*it)->draw();
	}

	for ( std::set<Pawn *>::iterator it = Model::deleting.begin(); it != Model::deleting.end(); it++) {
		(*it)->setColor();
		(*it)->draw();
	}

	// Draw their shadows.
	glPushMatrix();
	glTranslatef( -48.0, -57.0, HEIGHT + 5.0);
	glMultMatrixf( shadowProjection);
	glDisable( GL_LIGHTING);
	glEnable( GL_BLEND);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilFunc( GL_EQUAL, 1, 1);
	glStencilOp( GL_KEEP, GL_KEEP, GL_ZERO);
	glEnable( GL_STENCIL_TEST);
	glColor4f( 0.1, 0.1, 0.1, 0.3);
	for ( int i = 0; i < 8; i++)
		for ( int j = 0; j < 8; j++)
			if (Model::board[i][j]) {
				Model::board[i][j]->draw();
			}

	for ( std::set<Pawn *>::iterator it = Model::deleting.begin(); it != Model::deleting.end(); it++)
		(*it)->draw();

	for ( std::set<Pawn *>::iterator it = Model::moving.begin(); it != Model::moving.end(); it++)
		(*it)->draw();
	glDisable( GL_STENCIL_TEST);
	glDisable( GL_BLEND);
	glEnable( GL_LIGHTING);
	glPopMatrix();

	glutSwapBuffers();
}
