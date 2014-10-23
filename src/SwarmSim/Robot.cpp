/*
 * Robot.cpp
 * Author: Kyle Crandall
 *
 * Description: Implimentation file for Robot.h
 */

// Includes
#include <SwarmSim/Robot.h>
#include <SwarmSim/Map.h>

#include <math.h>

using namespace cv;
using namespace SwarmSim;

// Macros
#define PI 3.14159265359

Phys_Robot::Phys_Robot()
{
	x = 0;
	y = 0;
	theta = 0;
	r = 1;
	w_b = 0.9;
	scan_half_angle = PI/2;
	scan_interval = PI/5;
	scan_max = 1;
	map = NULL;

	n_scan = (int)(2 * scan_half_angle / scan_interval) + 1;
	scan = new double[n_scan];
}

Phys_Robot::Phys_Robot(double _x, double _y, double _theta, double _r, double _w_b, Map* _map, double _scan_half_angle, double _scan_interval, double _scan_max)
{
	x = _x;
	y = _y;
	theta = _theta;
	r = _r;
	w_b = _w_b;
	map = _map;
	scan_half_angle = _scan_half_angle;
	scan_interval = _scan_interval;
	scan_max = _scan_max;

	n_scan = (int)(2 * scan_half_angle / scan_interval) + 1;
	scan = new double[n_scan];
}

Phys_Robot::~Phys_Robot()
{
	delete[] scan;
}

void Phys_Robot::set_state(double _x, double _y, double _theta)
{
	x = _x;
	y = _y;
	theta = _theta;
}

void Phys_Robot::set_size(double _r, double _w_b)
{
	r = _r;
	w_b = _w_b;
}

void Phys_Robot::set_map(Map* _map)
{
	map = _map;
}

void Phys_Robot::set_scan(double _scan_half_angle, double _scan_interval, double _scan_max)
{
	scan_half_angle = _scan_half_angle;
	scan_interval = _scan_interval;
	scan_max = _scan_max;
	n_scan = (int)(2 * scan_half_angle / scan_interval) + 1;

	delete[] scan;
	scan = new double[n_scan];
}

bool Phys_Robot::Drive(double vr, double vl, double del_t)
{
	double x_k = x + 0.5 * (vr + vl) * cos(theta) * del_t;
	double y_k = y + 0.5 * (vr + vl) * sin(theta) * del_t;
	double theta_k = theta + atan((vr - vl) / w_b) * del_t;

	if (!map->col_test(x_k, y_k, r))
	{
		x = x_k;
		y = y_k;
		theta = theta_k;
		return true;
	}
	else
	{
		return false;
	}
}

bool Phys_Robot::Drive(double vr, double vl, double del_t, int n_times)
{
	double x_k = x;
	double y_k = y;
	double theta_k = theta;

	for (int i = 0; i < n_times; i++)
	{
		x_k += 0.5 * (vr + vl) * cos(theta_k) * del_t;
		y_k += 0.5 * (vr + vl) * sin(theta_k) * del_t;
		theta_k += atan((vr - vl) / w_b) * del_t;

		if (map->col_test(x_k, y_k, r))
		{
			return false;
		}
	}

	x = x_k;
	y = y_k;
	theta = theta_k;

	return true;
}

void Phys_Robot::get_cur_state(double* _x, double* _y, double* _theta)
{
	*_x = x;
	*_y = y;
	*_theta = theta;
}

void Phys_Robot::get_scan(double* out)
{
	map->scan(x, y, theta, scan_half_angle, scan_interval, scan_max, scan);

	for (int i = 0; i < n_scan; i++)
	{
		out[i] = scan[i];
	}
}

void Phys_Robot::draw(Mat& I)
{
	int rows = I.rows;
	double scale = map->get_scale();

	circle(I, Point(scale*x, rows - scale*y), scale*r, Scalar(0, 255, 0));
	line(I, Point(scale*x, rows - scale*y), Point(scale*(x + r * cos(theta)), rows - scale*(y + r * sin(theta))), Scalar(0, 255, 0));
}

void Phys_Robot::draw(Mat& I, Scalar color)
{
	int rows = I.rows;
	double scale = map->get_scale();

	circle(I, Point(scale*x, rows - scale*y), scale*r, color);
	line(I, Point(scale*x, rows - scale*y), Point(scale*(x + r * cos(theta)), rows - scale*(y + y * sin(theta))), color);
}

void Phys_Robot::draw_scan(Mat& I)
{
	int rows = I.rows;
	double scale = map->get_scale();

	for (int i = 0; i < n_scan; i++)
	{
		double s_x = x + scan[i] * cos(theta + scan_interval * i - scan_half_angle);
		double s_y = y + scan[i] * sin(theta + scan_interval * i - scan_half_angle);

		circle(I, Point(scale*s_x, rows - scale * s_y), 3, Scalar(255, 0, 0));
	}
}

void Phys_Robot::draw_scan(Mat& I, Scalar color)
{
	int rows = I.rows;
	double scale = map->get_scale();

	for (int i = 0; i < n_scan; i++)
	{
		double s_x = x + scan[i] * cos(theta + scan_interval * i - scan_half_angle);
		double s_y = y + scan[i] * sin(theta + scan_interval * i - scan_half_angle);

		circle(I, Point(scale*s_x, rows - scale * s_y), 3, color);
	}
}

void Phys_Robot::draw_range(Mat& I)
{
	int rows = I.rows;
	double scale = map->get_scale();

	circle(I, Point(scale * x, rows - scale * y), scale * scan_max, Scalar(0, 0, 255));
}

void Phys_Robot::draw_range(Mat& I, Scalar color)
{
	int rows = I.rows;
	double scale = map->get_scale();

	circle(I, Point(scale * x, rows - scale * y), scale * scan_max, color);
}
