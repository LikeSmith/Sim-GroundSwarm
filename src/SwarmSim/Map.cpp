/*
 * Map.cpp
 * Author: Kyle Crandall
 * Descrtiption: Implementation file for Map.h
 */

#include <SwarmSim/Map.h>
#include <SwarmSim/Shape.h>
#include <SwarmSim/Circle.h>
#include <SwarmSim/Line.h>
#include <SwarmSim/Rectangle.h>
#include <SwarmSim/Polygon.h>

#include <string.h>
#include <fstream>

using namespace std;
using namespace cv;
using namespace SwarmSim;

Map::Map()
{
	dist = new normal_distribution<double>(0, 0.1);
	scale = 1;
}

Map::Map(double sensor_std)
{
	dist = new normal_distribution<double>(0, sensor_std);
	scale = 1;
}

Map::~Map()
{
	for (int i = 0; i < obs.size(); i++)
	{
		delete obs[i];
	}

	delete dist;
}

void Map::set_size(int _height, int _width, float _scale)
{
	height = _height;
	width = _width;
	scale = _scale;
}

void Map::add_obs(Shape* to_add)
{
	obs.push_back(to_add);
}

void Map::from_file(string file)
{
	ifstream f_in;
	f_in.open(file.c_str());

	f_in >> height;
	f_in >> width;
	f_in >> scale;

	char line[256];
	while (f_in.good())
	{
		f_in.getline(line, 256);

		if (line[0] == '#')
		{
			continue;
		}

		if (!strcmp(line, "Line"))
		{
			double p1x, p2x, p1y, p2y;
			f_in >> p1x;
			f_in >> p1y;
			f_in >> p2x;
			f_in >> p2y;

			obs.push_back(new Line(p1x, p1y, p2x, p2y));
		}
		else if (!strcmp(line, "Circle"))
		{
			double x, y, r;
			f_in >> x;
			f_in >> y;
			f_in >> r;

			obs.push_back(new Circle(x, y, r));
		}
		else if (!strcmp(line, "Rectangle"))
		{
			double x, y, l1, l2, phi;
			f_in >> x;
			f_in >> y;
			f_in >> l1;
			f_in >> l2;
			f_in >> phi;

			obs.push_back(new Rectangle(x, y, l1, l2, phi));
		}
		else if (!strcmp(line, "Poly"))
		{
			int n;
			double* verts_x;
			double* verts_y;
			f_in >> n;

			verts_x = new double[n];
			verts_y = new double[n];

			for (int i = 0; i < n; i++)
			{
				f_in >> verts_x[i];
				f_in >> verts_y[i];
			}

			obs.push_back(new Polygon(n, verts_x, verts_y));

			delete[] verts_x;
			delete[] verts_y;
		}
	}
}

void Map::scan(double x, double y, double theta, double half_angle, double interval, double sensor_max, double* out)
{
	for (int i = 0; i <= (2 * half_angle / interval); i++)
	{
		double phi = -half_angle + i * interval;

		out[i] = sensor_max;

		for (int j = 0; j < obs.size(); j++)
		{
			double d = obs[j]->ray_trace(x, y, theta + phi, sensor_max);

			if (d < out[i])
			{
				out[i] = d;
			}
		}

		// add noise

		out[i] += (*dist)(gen);
	}
}

bool Map::col_test(double x, double y, double r)
{
	bool col = false;

	for (int i = 0; i < obs.size(); i++)
	{
		col = obs[i]->col_check(x, y, r);

		if (col)
		{
			break;
		}
	}

	return col;
}

void Map::draw_map(Mat& I)
{
	I = Mat::zeros(scale*height, scale*width, CV_8UC3);

	for (int i = 0; i < obs.size(); i++)
	{
		obs[i]->draw(I, scale);
	}
}

double Map::get_scale()
{
	return scale;
}
