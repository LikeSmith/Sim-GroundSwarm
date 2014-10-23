/*
 * Rectangle.h
 * Author: Kyle Crandall
 *
 * Descritpion: represents a rectangular obstacle
 */

// Includes
#include <SwarmSim/Shape.h>

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

namespace SwarmSim
{
class Rectangle: public Shape
{
protected:
	double l1;
	double l2;
	double phi;
	double p_x;
	double p_y;
public:
	/*
	 * Rectangle(double _p_x, double _p_y, double _l1, double _l2, double _phi)
	 * Description defines rectangle by defining bottom left corner, the length of the
	 * sides and its rotation from the x axis
	 *
	 * Inputs:
	 *  _p_x - x position of bottom left corner
	 *  _p_y - y position of bottom left corner
	 *  _l1  - length of side in x direction
	 *  _l2  - length of side in y direction
	 *  _phi - rotation from x axis
	 */
	Rectangle(double _p_x, double _p_y, double _l1, double _l2, double _phi);

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

#endif /* RECTANGLE_H_ */
