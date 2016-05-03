#ifndef Draw_INCLUDED
#define Draw_INCLUDED

#define HEIGHT 50.0

class Draw {
	static GLuint textures[8];
	static GLfloat lightPosition[4];
	static GLfloat shadowProjection[];

	static void drawSky();
	static void bindTexture( char *file, int i);
	static void setupLight();
	static void drawBoard();
	public:
		static void init();
		static void draw();
};

#endif
