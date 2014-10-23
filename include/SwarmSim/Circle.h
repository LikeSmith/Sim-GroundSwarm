/*
 * Rectangle.h
 * Author: Kyle Crandall
 *
 * Descritpion: represents a circular obstacle
 */

// Includes
#include <SwarmSim/Shape.h>

#ifndef CIRCLE_H_
#define CIRCLE_H_

namespace SwarmSim
{
class Circle: public Shape
{
protected:
	double p_x;
	double p_y;
	double r;

public:
	/*
	 * Circle(double _p_x, double _p_y, double _r)
	 * Description defines a circle with a center point and a radius
	 *
	 * Inputs:
	 *  _p_x - x position of center
	 *  _p_y - y position of center
	 *  _r  - radius of circle
	 */
	Circle(double _p_x, double _p_y, double _r);

	/*
	 * double ray_trace(double x, double y, double theta)
	 * Finds distance to shape along a ray
	 *
	 * Inputs:
	 *  x     - x position of ray start
	 *  y     - y position of ray start
	 *  theta - direction of ray extension
	 *  d_max - maximum length of ray
	 * Output:
	 *  distance to shape, d_max if no intersection
	 */
	double ray_trace(double x, double y, double theta, double d_max);

	/*
	 * void draw()
	 * Draws shape onto an image
	 *
	 * Input:
	 *  I - image to draw to
	 *  scale - scaling for image
	 */
	void draw(cv::Mat& I, float scale);

	/*
	 * bool col_check(double x, double y, double theta)
	 * collision check between circle and this shape
	 *
	 * Input:
	 *  x - x position of the circle
	 *  y - y position of the circle
	 *  r - r radius of the circle
	 * Output:
	 *  boolean representing if there was a collision or not
	 */
	bool col_check(double x, double y, double r);
};
}

#endif
