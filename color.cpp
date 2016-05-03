
#include "color.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>

Color::Color( float r, float g, float b, float a) {
	this->setColor( r, g, b, a);
}

void Color::setColor( float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Color::set() {
	glColor4f( r, g, b, a);
}

//GLfloat white[] = { 1.0, 1.0, 1.0, 1.0};
//GLfloat black[] = { 0.0, 0.0, 0.0, 0.0};

/*
void Color::setMaterial() {
	//GLfloat color[] = { r, g, b, a};
	GLfloat color[] = { 0.1, 0.1, 0.1, 0.0};
	//GLfloat color[] = { 1.0, 1.0, 1.0, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
}
*/

bool Color::operator == (const Color& c) const {
	//return true;
	return r == c.r && g == c.g && b == c.b && a == c.a;
}

Color Color::random() {
	Color c[] = { Color( 0.0, 1.0, 0.0, 1.0), Color( 1.0, 0.75, 0.0, 1.0), Color( 0.0, 1.0, 1.0, 1.0), Color( 1.0, 0.0, 0.0, 1.0), Color( 0.0, 0.0, 1.0, 1.0)};
	int r = rand() % 5;
	return c[r];
}

