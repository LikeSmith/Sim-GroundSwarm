/*
 * main.cpp
 * Author: Kyle Crandall
 *
 * Description: Simulates a swarm of ground robots
 */

// Includes
// general includes
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

// opencv includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// custom includes
#include <SwarmSim/Map.h>
#include <SwarmSim/Robot.h>

// Macros
#ifndef __CYGWIN__
#define MAPS_DIR "../../../maps/"
#else
#define MAPS_DIR "../maps/"
#endif

using namespace std;
using namespace cv;
using namespace SwarmSim;


// Macros
#define PI 3.14159265359

// main method
int main(int argc, char** argv)
{
	cout << "Starting Ground Swarm Simulation..." << endl;

	Mat img;
	Map m(0.01);
	string map = MAPS_DIR;
	map += "example1.map";

	cout << "Loading map..." << endl;
	m.from_file(map);

	namedWindow("Map");

	cout << "Initilizing robot..." << endl;
	Phys_Robot rob(1, 1, 0, 0.25, 0.24, &m, PI/2, PI/20, 2);

	bool done = false;

	cout << "Simulation Starting..." << endl;
	while(!done)
	{
		double out[21];

		m.draw_map(img);
		rob.get_scan(out);

		rob.draw(img);
		rob.draw_scan(img);
		rob.draw_range(img);

		imshow("Map", img);

		char key = waitKey(1);
		double vr = 0;
		double vl = 0;

		switch (key)
		{
		case 'a':
			vr = 0.01;
			vl = -0.01;
			break;
		case 'd':
			vr = -0.01;
			vl = 0.01;
			break;
		case 'w':
			vr = 0.05;
			vl = 0.05;
			break;
		case 's':
			vr = -0.05;
			vl = -0.05;
			break;
		case'q':
			done = true;
			break;
		}

		rob.Drive(vr, vl, 1);
	}

	return 0;
}
