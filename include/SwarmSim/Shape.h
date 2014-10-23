/*
 * Shape.h
 * Author: Kyle Crandall
 *
 * Descritpion: Shape is a parent object for the obstacles that make up the map
 */

// Includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#ifndef SHAPE_H_
#define SHAPE_H_

using namespace std;

namespace SwarmSim
{
class Shape
{
protected:
	int type;
public:
	Shape(){ type = 0; }
	virtual ~Shape(){}
	virtual double ray_trace(double x, double y, double theta, double d_max){ return d_max;}
	virtual void draw(cv::Mat& I, float scale) {}
	virtual bool col_check(double x, double y, double r){ return false; }
};
}

#endif /* SHAPE_H_ */
