/*
 * Polygon.h
 * Author: Kyle Crandall
 *
 * Descritpion: represents a polygonal obstacle
 */

//Includes
#include <SwarmSim/Shape.h>
#include <SwarmSim/Line.h>

#ifndef POLYGON_H_
#define POLYGON_H_

namespace SwarmSim
{
class Polygon: public Shape
{
protected:
	int n_verts;
	double* verts_x;
	double* verts_y;
	Line* edges;
public:
	/*
	 * Rectangle(double _p_x, double _p_y, double _l1, double _l2, double _phi)
	 * Description defines rectangle by defining bottom left corner, the length of the
	 * sides and its rotation from the x axis
	 *
	 * Inputs:
	 *  n - number of verticies
	 *  _verts_x - x values of the verticies
	 *  _verts_y - y values of the verticies
	 */
	Polygon(int n, double* _verts_x, double* _verts_y);

	/*
	 * ~Polygon()
	 * Description: Default Destructor
	 */
	~Polygon();

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

#endif /* POLYGON_H_ */
