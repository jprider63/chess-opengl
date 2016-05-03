
#include "camera.h"

#define RHO_FACTOR 200.0
#define THETA_FACTOR -0.01
#define PHI_FACTOR 0.005

#define RHO_MAX 10000.0
#define RHO_MIN 3000.0

Point3d Camera::position;
double Camera::aspectRatio;

void Camera::init( int w, int h) {
	position = Geom::Vector( 7000.0, 0.0, 1.0);
	aspectRatio = ((double) w) / ((double) h);
}

void Camera::move( int dx, int dy) {
	position += Geom::Vector( 0.0, THETA_FACTOR * dx, PHI_FACTOR * dy);

	// Bound phi.
	if ( position[2] <= 0.5)
		position[2] = 0.5;
	if ( position[2] >= Geom::PI - 0.5)
		position[2] = Geom::PI - 0.5;
}

void Camera::zoomIn() {
	position -= Geom::Vector( RHO_FACTOR, 0.0, 0.0);
	if ( position[0] <= RHO_MIN)
		position[0] = RHO_MIN;
}

void Camera::zoomOut() {
	position += Geom::Vector( RHO_FACTOR, 0.0, 0.0);
	if ( position[0] >= RHO_MAX)
		position[0] = RHO_MAX;
}

