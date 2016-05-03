
#ifndef Color_INCLUDED
#define Color_INCLUDED

class Color {
	float r, g, b, a;
	public:
		Color() {};
		Color( float, float, float, float);
		void setColor( float, float, float, float);
		void set();
		//void setMaterial();
		bool operator == (const Color& c2) const;
		static Color random();
};

#endif

