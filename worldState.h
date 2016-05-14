#ifndef WORLDSTATE
#define WORLDSTATE

#include <iostream>

#include "utilities.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector> 

namespace State
{
	using namespace cv;

	class WorldState
	{
		public:
			Utils::Point2D<int> centerOfBasket;
			void update(Mat);

			//***********predicates************** 
			bool basketOutOfView;
			bool basketToRight;
			bool basketToLeft;

		protected:
			std::vector<Utils::Point3D<int> > colorCallbackPoints;
			void MouseCallback();
			Mat filterImage(Mat);
			Mat colorDetect(Mat);
			void findDepth(Mat,std::vector<Utils::Point2D<int> >);
	};
}

#endif