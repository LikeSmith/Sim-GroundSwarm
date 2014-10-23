/*
 * Map.h
 * Author: Kyle Crandall
 * Description: Class that contains the map of the environment
 */

#include "../include/SwarmSim/Shape.h"
#include <vector>
#include <string>
#include <random>

#ifndef MAP_H_
#define MAP_H_

using namespace std;
using namespace cv;

namespace SwarmSim
{
class Map
{
private:
	vector<Shape*> obs;
	default_random_engine gen;
	normal_distribution<double>* dist;
	float scale;
	int height;
	int width;
public:
	/*
	 * Map()
	 * Description: default constructor
	 */
	Map();

	/*
	 * Map(double sensor_var)
	 * Description: constructor, allows specification of sensor noise
	 *
	 * Inputs:
	 *  sensor_std - standard deviation of sensor noise
	 */
	Map(double sensor_std);

	/*
	 * ~Map()
	 * Description: default destructor
	 */
	~Map();

	/*
	 * set_size(int height, int width, float scale)
	 * Description: allows users to set the scale of the image for drawing.
	 *
	 * Inputs:
	 *  height - height of map
	 *  width - width of map
	 *  scale - number of meters per pixel
	 */
	void set_size(int _height, int _width, float _scale);

	/*
	 * add_obs(Shape* to_add)
	 * Description: allows user to add obstacles to the map manually
	 *
	 * Inputs:
	 *  to_add - shape object to add to map
	 */
	void add_obs(Shape* to_add);

	/*
	 * from_file(string file)
	 * Description: Reads map from file
	 *
	 * Inputs:
	 *  file - path to file to read map from
	 */
	void from_file(string file);

	/*
	 * scan(double x, double y, double theta, double, half_angle, double interval, double sensor_mas, double* out);
	 * Description: Runs a distance sensor scan of the map, includes sensor noise into the estimate
	 *
	 * Inputs:
	 *  x - x position of the scanner
	 *  y - y position of the scanner
	 *  theta - orientation of the scanner
	 *  half_angle - half of the angle of the sensor sweep.  Sensor will sweep a half angle on either side of theta
	 *  interval - the angular interval at which to scan
	 *  sensor_max - the maximum value the sensor will return
	 * Outputs:
	 *  out - array of outputs. distance to nearest obstacle for each ray starting at theta - half_angle
	 *        and proceeding by interval to theta + half_angle.
	 */
	void scan(double x, double y, double theta, double half_angle, double interval, double sensor_max, double* out);

	/*
	 * col_test(double x, double y, double r)
	 * Description: Does a colision test against obstacles in the map
	 *
	 * Inputs:
	 *  x - robot x position
	 *  y - robot y position
	 *  r - radius of bounding circle
	 */
	bool col_test(double x, double y, double r);

	/*
	 * draw_map(Mat& I)
	 * Description: draws map, clears image passed to it, call this one first.
	 *
	 * Inputs:
	 *  I - image to draw map to.
	 */
	void draw_map(Mat& I);

	/*
	 * get_scale()
	 * Description: gets the scale for drawing
	 *
	 * Outputs:
	 *  returns scale.
	 */
	double get_scale();
};
}

#endif /* MAP_H_ */
