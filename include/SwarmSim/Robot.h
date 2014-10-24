/*
 * Robot.h
 * Author: Kyle Crandall
 *
 * Description: A class that models a robot in the Map environment
 */

// Includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <SwarmSim/Map.h>

using namespace cv;

#ifndef ROBOT_H_
#define ROBOT_H_

namespace SwarmSim
{
/*
 * Phys_Robot: Represents physical robot hardware.
 */
class Phys_Robot
{
private:
	double x;
	double y;
	double theta;
	double r;
	double w_b;
	double scan_half_angle;
	double scan_interval;
	double scan_max;
	double* scan;
	int n_scan;
	Map* map;
public:
	/*
	 * Phys_Robot()
	 * Description: Default Constructor
	 */
	Phys_Robot();

	/*
	 * Phys_Robot(double x, double y, double theta, double r, double w_b, Map* map,
	 *            double scan_half_angle, double scan_interval, double scan_max)
	 * Description: initilizer constructor
	 *
	 * Inputs:
	 *  x - x position
	 *  y - y position
	 *  theta - orientation
	 *  r - size
	 *  w_b - wheel base
	 *  map - pointer to map
	 *  scan_half_angle - half angle of scanner sweep
	 *  scan_interval - interval of scan;
	 *  scan_max - max value of the scanner
	 */
	Phys_Robot(double _x, double _y, double _theta, double _r, double _w_b, Map* _map, double _scan_half_angle, double _scan_interval, double _scan_max);

	/*
	 * ~Phys_Robot()
	 * Description: default destructor
	 */
	~Phys_Robot();

	/*
	 * set_state(double x, double y, double theta)
	 * Description: Allows the user to set the state of the robot
	 *
	 * Inputs:
	 *  x - x position
	 *  y - y position
	 *  theta - orientation
	 */
	void set_state(double _x, double _y, double _theta);

	/*
	 * set_size(double r, double w_b)
	 * Description: allows user to set the size of the robot
	 *
	 * Inputs
	 *  r - radius of the boundary circle
	 *  w_b - wheel base
	 */
	void set_size(double _r, double w_b);

	/*
	 * set_map(Map* map)
	 * Description: allows user to set the map used by the robot
	 *
	 * Inputs:
	 *  map - pointer to the map object to be used
	 */
	void set_map(Map* _map);

	/*
	 * set_scan(double scan_half_angle, double scan_interval, double scan_max)
	 * Descritption: Allows users to customize the scanner.
	 *
	 * Inputs:
	 *  scan_half_angle - half angle of scanner sweep
	 *  scan_interval - interval of scanner sweep
	 *  scan_max - maximum reading of scanner
	 */
	void set_scan(double _scan_half_angle, double _scan_interval, double _scan_max);

	/*
	 * Drive(double vr, double vl, double del_t, int n_times);
	 * Description: Drives the robot forward
	 *
	 * Input:
	 *  vr - velocity of right wheel in m/s
	 *  vl - velocity of left wheel in m/s
	 *  del_t - time step
	 *  n_times - number of times to apply control, optional, default=1
	 * Output:
	 *  returns false if obstacle was hit, if false, robot did not advance
	 */
	bool Drive(double vr, double vl, double del_t);
	bool Drive(double vr, double vl, double del_t, int n_times);

	/*
	 * get_cur_state(double* x, double* y, double* theta)
	 * Description: retrieves the current state of the robot;
	 *
	 * Outputs:
	 *  x - x position of the robot
	 *  y - y position of the robot
	 *  theta - orientation of the robot
	 */
	void get_cur_state(double* _x, double* _y, double* _theta);

	/*
	 * get_scan(double* out)
	 * Description: retrieves scan of map
	 *
	 * outputs:
	 *  out - array containing scan distances.
	 */
	void get_scan(double* out);

	/*
	 * draw(Mat% I, Scalar color)
	 * Description: draws robot a specific color
	 *
	 * Inputs:
	 *  I - image to draw robot to
	 *  color - color to draw robot (optional)
	 */
	void draw(Mat& I);
	void draw(Mat& I, Scalar color);

	/*
	 * draw_scan(Mat& I, Scalar color)
	 * Description: draws scan points
	 *
	 * Inputs:
	 *  I - image to draw to
	 *  color - color to draw (optional)
	 */
	void draw_scan(Mat& I);
	void draw_scan(Mat& I, Scalar color);

	/*
	 * draw_range(Mat& I, Scalar, color)
	 * Description: draws circle representing sensor range
	 *
	 * Inputs:
	 *  I - image to draw to
	 *  color - color to draw (optional)
	 */
	void draw_range(Mat& I);
	void draw_range(Mat& I, Scalar color);
};
}

#endif /* ROBOT_H_ */
