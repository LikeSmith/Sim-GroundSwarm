/*
 * Line.cpp
 * Author: Kyle Crandall
 * Description: Implimentation file for Line.h
 */

// includes
#include <SwarmSim/Shape.h>
#include <SwarmSim/Line.h>
#include <math.h>
#include <vector>

using namespace std;
using namespace cv;
using namespace SwarmSim;

Line::Line()
{
	type = 3;
}

Line::Line(double _p1_x, double _p1_y, double _p2_x, double _p2_y)
{
	p1_x = _p1_x;
	p1_y = _p1_y;
	p2_x = _p2_x;
	p2_y = _p2_y;

	type = 3;
}

void Line::set(double _p1_x, double _p1_y, double _p2_x, double _p2_y)
{
	p1_x = _p1_x;
	p1_y = _p1_y;
	p2_x = _p2_x;
	p2_y = _p2_y;
}
double Line::ray_trace(double x, double y, double theta, double d_max)
{
	double del_Vx = p2_x - p1_x;
	double del_Vy = p2_y - p1_y;
	double del_Px = d_max * cos(theta);
	double del_Py = d_max * sin(theta);

	double det = -del_Px * del_Vy + del_Py * del_Vx;

	if (det == 0)
	{
		return d_max;
	}

	double t1  =(-del_Vy * (p1_x - x) + del_Vx * (p1_y - y)) / det;
	double t2 = (-del_Py * (p1_x - x) + del_Px * (p1_y - y)) / det;

	if (t1 >= 0 && t2 > 0 && t1 <= 1 && t2 <= 1)
	{
		return t1 * d_max;
	}
	else
	{
		return d_max;
	}
}

void Line::draw(Mat& I, float scale)
{
	line(I, Point(scale*p1_x, I.rows - scale*p1_y), Point(scale*p2_x, I.rows - scale*p2_y), Scalar(255, 255, 255), 3);
}

bool Line::col_check(double x, double y, double r)
{
	double a = x - p1_x;
	double b = p2_x - p1_x;
	double c = y - p1_y;
	double d = p2_y - p1_y;

	double im = 4 * pow(a*b + c*d, 2) - 4 * (b*b + d*d) * (a*a + c*c- r*r);
	double re = 2 * (a * b + c * d);
	double den = 2 * (b * b + d * d);

	if (im < 0)
	{
		return false;
	}

	double t1 = (re + sqrt(im)) / den;
	double t2 = (re - sqrt(im)) / den;

	if ((t1 >= 0 && t1 <= 1) || (t2 >=0 && t2 <= 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}
