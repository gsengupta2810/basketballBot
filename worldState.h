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
	using namespace std;
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
			void setbool2true();
			static void MouseCallback(int event, int x, int y, int flags, void * param);
			void doMouseCallback(int,int,int,int);
			Mat filterImage(Mat*);
			void colorSelect(Mat*);
			Mat colorDetect(Mat*,int,int,int);
			void changeColorModel(Mat,Mat*);
			void findcentralvalue(void); 
			void findDepth(Mat*,std::vector<Utils::Point2D<int> >);
		private:
			int centralcolors[3];
			enum colorSpace
			{
				HSV,
				HLS,
				YCbCr
			};	
			colorSpace cSpace;
	};
}

#endif