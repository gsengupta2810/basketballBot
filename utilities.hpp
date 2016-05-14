#ifndef UTILS
#define UTILS

#include <iostream>

namespace Utils
{
	using namespace std;

	template <typename T>
	struct Point2D
	{
		T x;
		T y;
	};

	template <typename T>
	struct Point3D
	{
		T x;
		T y;
		T z;
	};
}

#endif