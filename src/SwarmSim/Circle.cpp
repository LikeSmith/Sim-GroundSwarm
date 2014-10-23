/*
 * Rectangle.cpp
 * Author: Kyle Crandall
 * Description: Implimentation file for Circle.h
 */

// includes
#include <SwarmSim/Circle.h>
#include <math.h>
#include <vector>

using namespace std;
using namespace cv;
using namespace SwarmSim;

Circle::Circle(double _p_x, double _p_y, double _r)
{
	p_x = _p_x;
	p_y = _p_y;
	r = _r;

	type = 2;
}

double Circle::ray_trace(double x, double y, double theta, double d_max)
{
	double a = p_x - x;
	double b = d_max * cos(theta);
	double c = p_y - y;
	double d = d_max * sin(theta);

	double im = 4 * pow(a*b + c*d, 2) - 4*(b*b + d*d)*(a*a + c*c - r*r);
	double re = 2 * (a * b + c * d);
	double den = 2 * (b * b + d * d - r * r);

	// no real solution
	if  (im < 0)
	{
		return d_max;
	}

	double t1 = (re + sqrt(im)) / den;
	double t2 = (re - sqrt(im)) / den;

	// if located inside obstacle,
	if (t1 * t2 < 0)
	{
		if (t1 > 0)
		{
			return t1 * d_max;
		}
		else
		{
			return t2 * d_max;
		}
	}

	if (t1 < 0)
	{
		return d_max;
	}

	if (t2 < t1)
	{
		return d_max * t2;
	}
	else
	{
		return d_max * t1;
	}
}

void Circle::draw(cv::Mat& I, float scale)
{
	circle(I, Point(scale*p_x, I.rows - scale*p_y), scale*r, Scalar(255, 255, 255), 3);
}

bool Circle::col_check(double x, double y, double r_rob)
{
	double d2 = pow(p_x - x, 2) + pow(p_y - y, 2);

	if (pow(r + r_rob, 2) >= d2 && pow(r - r_rob, 2) <= d2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
