#include <iostream>
#include "worldState.h"

using namespace std;

namespace State
{
	void WorldState::update(const Mat* img)  //this function will update the world state on every iteration
	{
		imshow("WorldState::update",*img);
		Mat img1=(*img).clone();
		img1=colorDetect(&img1);
	}

    void WorldState::MouseCallback(int event, int x, int y, int flags, void * param)  //used to create a list of clicked points 
	{
		// if  ( event == EVENT_LBUTTONDOWN )
		//  {
		//  	cout<<x<<":"<<y<<":"<<endl;
		//  	// colorCallbackPoints.push_back(Utils::Point3D<int> (img.at<Vec3b>(x,y)[0],img.at<Vec3b>(x,y)[1],img.at<Vec3b>(x,y)[2]));
		//  	// cout<<img.at<Vec3b>(x,y)[0]<<","<<img.at<Vec3b>(x,y)[1]<<","<<img.at<Vec3b>(x,y)[2]<<endl;
		//   }
		WorldState *self = static_cast<WorldState*>(param);
  		self->doMouseCallback(event, x, y, flags);
	}

	void WorldState::doMouseCallback(int event, int x, int y, int flags)
	{
		 if  ( event == EVENT_LBUTTONDOWN )
		 {
		 	cout<<x<<":"<<y<<":"<<" "<<temp.at<Vec3b>(x,y)[0]<<endl;
		 	// colorCallbackPoints.push_back(Utils::Point3D<int> (img.at<Vec3b>(x,y)[0],img.at<Vec3b>(x,y)[1],img.at<Vec3b>(x,y)[2]));
		 	// cout<<img.at<Vec3b>(x,y)[0]<<","<<img.at<Vec3b>(x,y)[1]<<","<<img.at<Vec3b>(x,y)[2]<<endl;
		  }
	}

	Mat WorldState::filterImage(Mat* img)
	{

	}

	Mat WorldState::colorDetect(Mat* img)
	{
		//Mat img1=(img).clone();
		imshow("colorDetect",*img);
		temp=img;
		setMouseCallback("colorDetect", MouseCallback, NULL);
		return *img;
	}

	void WorldState::findDepth(Mat* img,std::vector<Utils::Point2D<int> > searchMatrix)   // finds depth only of the selected region
	{

	}
}