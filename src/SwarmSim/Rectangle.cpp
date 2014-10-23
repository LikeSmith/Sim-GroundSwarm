/*
 * Rectangle.cpp
 * Author: Kyle Crandall
 * Description: Implimentation file for Rectangle.h
 */

// includes
#include <SwarmSim/Shape.h>
#include <SwarmSim/Rectangle.h>
#include <math.h>
#include <vector>

using namespace std;
using namespace cv;
using namespace SwarmSim;

Rectangle::Rectangle(double _p_x, double _p_y, double _l1, double _l2, double _phi)
{
	p_x = _p_x;
	p_y = _p_y;
	l1 = _l1;
	l2 = _l2;
	phi = _phi;

	type = 1;
}

double Rectangle::ray_trace(double x, double y, double theta, double d_max)
{
	double d = 1;

	// find all verticies
	double verts_x[] = {p_x, p_x + l1 * cos(phi), p_x + l1 * cos(phi) - l2 * sin(phi), p_x - l2 * sin(phi), p_x};
	double verts_y[] = {p_y, p_y + l1 * sin(phi), p_y + l1 * sin(phi) + l2 * cos(phi), p_y + l2 * cos(phi), p_y};

	// find segment ends
	double del_Px = d_max * cos(theta);
	double del_Py = d_max * sin(theta);

	for (int i = 0; i < 4; i++)
	{
		// find t1 and t2
		double del_Vx = verts_x[i+1] - verts_x[i];
		double del_Vy = verts_y[i+1] - verts_y[i];

		double det = -del_Px * del_Vy + del_Py * del_Vx;

		// if no intersection
		if  (det == 0)
		{
			continue;
		}

		double t1 = (-del_Vy * (verts_x[i] - x) + del_Vx * (verts_y[i] - y)) / det;
		double t2 = (-del_Py * (verts_x[i] - x) + del_Px * (verts_y[i] - y)) / det;

		if (t1 > 0 && t2 > 0 && t1 < 1 && t2 < 1 && t1 < d)
		{
			d = t1;
		}
	}

	return d * d_max;
}

void Rectangle::draw(Mat& I, float scale)
{
	int rows = I.rows;
	vector<Point> pts_v;
	pts_v.push_back(Point(scale*p_x, rows - scale*p_y));
	pts_v.push_back(Point(scale*(p_x + l1 * cos(phi)), rows - scale*(p_y + l1 * sin(phi))));
	pts_v.push_back(Point(scale*(p_x + l1 * cos(phi) - l2 * sin(phi)), rows - scale*(p_y + l1 * sin(phi) + l2 * cos(phi))));
	pts_v.push_back(Point(scale*(p_x - l2 * sin(phi)), rows - scale*(p_y + l2 * cos(phi))));

	const Point* pts = (const Point*)Mat(pts_v).data;
	int npts = Mat(pts_v).rows;

	polylines(I, &pts, &npts, 1, true, Scalar(255, 255, 255), 3);
}

bool Rectangle::col_check(double x, double y, double r)
{
	double verts_x[] = {p_x, p_x + l1 * cos(phi), p_x + l1 * cos(phi) - l2 * sin(phi), p_x - l2 * sin(phi), p_x};
	double verts_y[] = {p_y, p_y + l1 * sin(phi), p_y + l1 * sin(phi) + l2 * cos(phi), p_y + l2 * cos(phi), p_y};

	for (int i = 0; i < 4; i++)
	{
		double a = x - verts_x[i];
		double b = verts_x[i+1] - verts_x[i];
		double c = y - verts_y[i];
		double d = verts_y[i+1] - verts_y[i];
		double im = 4 * pow(a*b + c*d, 2) - 4 * (b*b + d*d) * (a*a + c*c - r*r);
		double re = 2 * (a * b + c * d);
		double den = 2 * (b * b + d * d);

		if (im < 0)
		{
			continue;
		}

		double t1 = (re + sqrt(im)) / den;
		double t2 = (re - sqrt(im)) / den;

		if ((t1 >= 0 && t1 <=1) || (t2 >= 0 && t2 <= 1))
		{
			return true;
		}
	}

	return false;
}
