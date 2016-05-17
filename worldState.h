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
			void update(const Mat*);
		
			//***********predicates************** 
			bool basketOutOfView;
			bool basketToRight;
			bool basketToLeft;

		protected:
			std::vector<Utils::Point3D<int> > colorCallbackPoints;
			static void MouseCallback(int event, int x, int y, int flags, void * param);
			void doMouseCallback(int,int,int,int);
			Mat filterImage(Mat*);
			Mat colorDetect(Mat*);
			void findDepth(Mat*,std::vector<Utils::Point2D<int> >);
		private:
			Mat temp;		
	};
}

#endif