/*
 * Polygon.cpp
 * Author: Kyle Crandall
 * Implimentation file for Polygon.h
 */

//Includes
#include <SwarmSim/Shape.h>
#include <SwarmSim/Line.h>
#include <SwarmSim/Polygon.h>

using namespace std;
using namespace cv;
using namespace SwarmSim;

Polygon::Polygon(int n, double* _verts_x, double* _verts_y)
{
	n_verts = n;

	verts_x = new double[n_verts];
	verts_y = new double[n_verts];
	edges = new Line[n_verts];

	for (int i = 0; i < n_verts; i++)
	{
		verts_x[i] = _verts_x[i];
		verts_y[i] = _verts_y[i];

		if (i > 0)
		{
			edges[i-1].set(verts_x[i-1], verts_y[i-1], verts_x[i], verts_y[i]);
		}
	}

	edges[n_verts-1].set(verts_x[n_verts-1], verts_y[n_verts-1], verts_x[0], verts_y[0]);
}

Polygon::~Polygon()
{
	delete[] verts_x;
	delete[] verts_y;
	delete[] edges;
}

double Polygon::ray_trace(double x, double y, double theta, double d_max)
{
	double d = d_max;

	for (int i = 0; i < n_verts; i++)
	{
		double d_i = edges[i].ray_trace(x, y, theta, d_max);

		if (d_i < d)
		{
			d = d_i;
		}
	}

	return d;
}

void Polygon::draw(cv::Mat& I, float scale)
{
	for (int i = 0; i < n_verts; i++)
	{
		edges[i].draw(I, scale);
	}
}

bool Polygon::col_check(double x, double y, double r)
{
	for (int i = 0; i < n_verts; i++)
	{
		if (edges[i].col_check(x, y, r))
		{
			return true;
		}
	}

	return false;
}
