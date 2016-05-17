#include <iostream>

#include "worldState.h"
#include "motion.h"
#include "utilities.hpp"

using namespace std;
using namespace State;
using namespace Motion;
using namespace Utils;


int main()
{
	WorldState state;
	motion mot(state);
	Mat img=imread("./images/test.jpg",CV_LOAD_IMAGE_COLOR);
	while(1)
	{
		state.update(&img);
		if(waitKey(10)==32) break;
	}
	
	return 0;
}