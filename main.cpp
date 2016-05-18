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
	Mat img=imread("./images/colortest.jpg",CV_LOAD_IMAGE_COLOR);
	state.update(&img);
	waitKey(0);
	return 0;
}