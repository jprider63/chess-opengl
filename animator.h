
#ifndef Animator_INCLUDED
#define Animator_INCLUDED

class Pawn;

class Animator {
	public:
		Pawn *pawn;
		void (*callback)( Pawn *pawn); // animator?
		virtual ~Animator() {};
		virtual void step( int dt) = 0;

		static void doneCallback( Pawn *pawn);
		static void deleteCallback( Pawn *pawn);
		static void addToBoardCallback( Pawn *pawn);
};

#endif

