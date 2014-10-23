/*
 * Rectangle.h
 * Author: Kyle Crandall
 *
 * Descritpion: represents a circular obstacle
 */

// Includes
#include <SwarmSim/Shape.h>

#ifndef LINE_H_
#define LINE_H_

namespace SwarmSim
{
class Line : public Shape
{
protected:
	double p1_x;
	double p1_y;
	double p2_x;
	double p2_y;
public:
	/*
	 * Line()
	 * Description: default constructor
	 */
	Line();

	/*
	 * Line(double _p1_x, double _p1_y, double _p2_x, double _p2_y)
	 * Description defines a line
	 *
	 * Inputs:
	 *  _p1_x - x position of point 1
	 *  _p1_y - y position of point 1
	 *  _p2_x - x position of point 2
	 *  _p2_x - y position of point 2
	 */
	Line(double _p1_x, double _p1_y, double _p2_x, double _p2_y);

	/*
	 * set(double _p1_x, double _p1_y, double _p2_x, double _p2_y)
	 * Description: sets parameters
	 *
	 * Inputs:
	 *  _p1_x - x position of point 1
	 *  _p1_y - y position of point 1
	 *  _p2_x - x position of point 2
	 *  _p2_x - y position of point 2
	 */
	void set(double _p1_x, double _p1_y, double _p2_x, double _p2_y);

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

#endif /* LINE_H_ */
