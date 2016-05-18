#include <iostream>
#include <unistd.h>
#include "worldState.h"

#define MEDIAN
#define BOARDCOLORED

#include <fstream>

using namespace std;

namespace State
{
	Mat imageforcallbackrgb;
	Mat imageforcallbackcolorchanged;
	Utils::Point3D<int> point;
	bool mouseClicked;
	std::vector<Utils::Point3D<int> > tempcolorCallbackPoints;

	void WorldState::update(const Mat* img)  //this function will update the world state on every iteration
	{
		imshow("WorldState::update",*img);
		
		//*******************color selection**********************
		Mat img1=img->clone();
		point.x=point.y=point.z=0;
		mouseClicked=false;
		colorSelect(&img1);	
		if(!colorCallbackPoints.empty())
		{
			//this arrangement is for still images
			findcentralvalue();
			cout<<"centralcolors: "<<centralcolors[0]<<","<<centralcolors[1]<<","<<centralcolors[2]<<endl;
			fstream file;
			file.open("points.txt",fstream::out);
			for (int i = 0; i < colorCallbackPoints.size(); ++i)
			{
				file<<colorCallbackPoints[i].x<<","<<colorCallbackPoints[i].y<<","<<colorCallbackPoints[i].z<<endl;
			}
			file.close();
		}	
		else 
		{
			cout<<"colorCallbackPoints is empty "<<endl;
			return;
		}
		
		//********************color detection*********************
		// in the trackbars keep thresh_1 small and vary other two thresholds for best results
		
		if(!colorCallbackPoints.empty())
		{
			Mat img2=img->clone();
			int thresh_1,thresh_2,thresh_3;
			namedWindow("color detected Binary",WINDOW_AUTOSIZE);
			createTrackbar("track_1","color detected Binary",&thresh_1,100);
			createTrackbar("track_2","color detected Binary",&thresh_2,100);
			createTrackbar("track_3","color detected Binary",&thresh_3,100);
			while(1)
			{
				Mat colorBinary=colorDetect(&img2,thresh_1,thresh_2,thresh_3);
				imshow("color detected Binary",colorBinary);
				if(waitKey(10)>0) break;	
			}
		}
		else cout<<"colorCallbackPoints is empty "<<endl;
		
	}
	
	bool myfunction (int i,int j) 
	{ 
		return (i<j); 
	}
	
	void WorldState::findcentralvalue()
	{
		#ifdef MEDIAN
			cout<<"Median"<<endl;
			for (int i = 0; i < 3; ++i)
			{
				vector<int> temp;
				for (int j = 0; j < colorCallbackPoints.size(); ++j)
				{
					switch(i)
					{
						case 0:
							temp.push_back(colorCallbackPoints[j].x);
							break;
						case 1:
							temp.push_back(colorCallbackPoints[j].y);
							break;
						case 2:
							temp.push_back(colorCallbackPoints[j].z);
							break;
					}
					
				}
				std::sort (temp.begin(), temp.end(),myfunction);
				if(colorCallbackPoints.size()%2==0)
				{
					centralcolors[i]=0.5*(temp[temp.size()/2]+temp[temp.size()/2+1]);
				}
				else
				{
					centralcolors[i]=temp[temp.size()/2];
				}
			}
		#endif

		#ifdef MEAN
			cout<<"Mean"<<endl;
			for (int i = 0; i < 3; ++i)
			{
				vector<int> temp;
				int sum=0;
				for (int j = 0; j < colorCallbackPoints.size(); ++j)
				{
					switch(i)
					{
						case 0:
							temp.push_back(colorCallbackPoints[j].x);
							break;
						case 1:
							temp.push_back(colorCallbackPoints[j].y);
							break;
						case 2:
							temp.push_back(colorCallbackPoints[j].z);
							break;
					}
					sum+=temp[j];

				}
				centralcolors[i]=sum/temp.size();	
			}
		#endif	

	}

	void WorldState::changeColorModel(Mat source,Mat* dest)
	{
		switch(cSpace)
		{
			case HSV:
			{
				cvtColor(source,*dest,CV_BGR2HSV,3);
				//imshow("HSV",*dest);
				break;
			}
			case YCbCr:
			{
				cvtColor(source,*dest,CV_BGR2YCrCb,3);
				//imshow("YCbCr",*dest);
				break;
			}
			case HLS:
			{
				cvtColor(source,*dest,CV_BGR2HLS,3);
				//imshow("HLS",*dest);
				break;
			}
		}

	}

	float variance(int three[])
	{	
		float mean=(three[0]+three[1]+three[2])/3;
		return ((three[0]-mean)*(three[0]-mean)+(three[1]-mean)*(three[1]-mean)+(three[2]-mean)*(three[2]-mean))/3;
	}

	void WorldState::setbool2true()
	{
		cout<<"setting bool to true "<<endl;
		mouseClicked=true;
	}

	void WorldState::doMouseCallback(int event, int x, int y, int flags)
	{
		 if  ( event == EVENT_LBUTTONDOWN )
		 {
		 	//setbool2true();
		 	mouseClicked=true;
		 	//cout<<"returned"<<endl;
		 	cout<<"mouse values : "<<(int)imageforcallbackcolorchanged.at<Vec3b>(y,x)[0]<<":"<<(int)imageforcallbackcolorchanged.at<Vec3b>(y,x)[1]<<":"<<(int)imageforcallbackcolorchanged.at<Vec3b>(y,x)[2]<<endl;
		 	
		 	//******************checing for grey noise*****************
		 	#ifdef BOARDCOLORED
		 	int three[3];
		 	three[0]=(int)imageforcallbackrgb.at<Vec3b>(y,x)[0];
		 	three[1]=(int)imageforcallbackrgb.at<Vec3b>(y,x)[1];
		 	three[2]=(int)imageforcallbackrgb.at<Vec3b>(y,x)[2];
		 	if(variance(three)<100) 
	 		{
	 			cout<<"gray : "<<variance(three)<<endl;
	 			return;
	 		}
		 	#endif

		 	point.x=(int)imageforcallbackcolorchanged.at<Vec3b>(y,x)[0];
		 	point.y=(int)imageforcallbackcolorchanged.at<Vec3b>(y,x)[1];
		 	point.z=(int)imageforcallbackcolorchanged.at<Vec3b>(y,x)[2];
		 	tempcolorCallbackPoints.push_back(point);
		  }
		  else if ( event == EVENT_MOUSEMOVE )
	     {
	     	cout<<"hovering"<<endl;
	         return;
	     }
	}


    void WorldState::MouseCallback(int event, int x, int y, int flags, void * param)  //used to create a list of clicked points 
	{
		WorldState *self = static_cast<WorldState*>(param);
  		self->doMouseCallback(event, x, y, flags);
  		
	}

	Mat WorldState::filterImage(Mat*)
	{
		cout<<"here "<<endl;
	}

	void WorldState::colorSelect(Mat* img)
	{
		Mat img1=(img)->clone();
		imshow("colorSelect",*img);
		imageforcallbackrgb=(*img).clone();
		cSpace=HSV;
		changeColorModel(imageforcallbackrgb,&imageforcallbackcolorchanged);
		setMouseCallback("colorSelect", MouseCallback, NULL);
		waitKey(0);
		cout<<"mouse clicked :"<<mouseClicked<<","<<point.x<<","<<point.y<<","<<point.z<<endl;
		if(mouseClicked==true)
		{
			for (int i = 0; i < tempcolorCallbackPoints.size(); ++i)
			{
				colorCallbackPoints.push_back(tempcolorCallbackPoints[i]);
			}
		}
		
	}

	Mat WorldState::colorDetect(Mat* img,int thresh_1,int thresh_2,int thresh_3)
	{
		cSpace=HSV;
		Mat colorChangedImg;
		Mat binary((*img).rows,(*img).cols,CV_8UC1,Scalar(0));
		changeColorModel(*img,&colorChangedImg);
		imshow("huha",colorChangedImg);
		for (int i = 0; i < (*img).rows; ++i)
		{
			for (int j = 0; j < (*img).cols; ++j)
			{
				if(abs(colorChangedImg.at<Vec3b>(i,j)[0]-centralcolors[0])<thresh_1 && abs(colorChangedImg.at<Vec3b>(i,j)[1]-centralcolors[1])<thresh_2 && abs(colorChangedImg.at<Vec3b>(i,j)[2]-centralcolors[2])<thresh_3)
				{
					binary.at<uchar>(i,j)=255;
				}
			}
		}
		return binary;
	}

	void WorldState::findDepth(Mat* img,std::vector<Utils::Point2D<int> > searchMatrix)   // finds depth only of the selected region
	{

	}
}