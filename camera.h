#ifndef Camera_INCLUDED
#define Camera_INCLUDED

#import "Vector3d.h"

class Camera {
	public:
		static Point3d position;
		static double aspectRatio;

		static void init( int width, int height);
		static void move( int dx, int dy);
		static void zoomIn();
		static void zoomOut();
};

#endif
