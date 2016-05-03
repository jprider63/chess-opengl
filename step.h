#ifndef Step_INCLUDED
#define Step_INCLUDED

#include <utility>

class Step {
	public:
		static int time;
		static std::pair<int,int> *click;

		static void init();
		static std::pair<int,int> *pick( std::pair<int,int> p);
		static void hover( std::pair<int,int> p);
		
		static void keyboard( unsigned char c, int x, int y);
		static void mouseDrag( int x, int y);
		static void mouseMove( int x, int y);
		static void mouseClick( int b, int s, int x, int y);
		static void step();
};

#endif
