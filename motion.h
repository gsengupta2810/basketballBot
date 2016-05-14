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
			motion(State::WorldState);
		public:
			void plan();

	};
}

#endif