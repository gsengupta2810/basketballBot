#ifndef MOTION
#define MOTION

#include <iostream>
#include "worldState.h"

namespace Motion
{
	using namespace std;
	using namespace State;

	class motion : public WorldState
	{
		private:
			
		public:
			void plan();
			motion(State::WorldState);

	};
}

#endif