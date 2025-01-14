#pragma once

#include <iostream> 
#include <string> 

using namespace std;

// This class stores the earnings of the respecitve movies
// in millions (represented with 3-digit numbers)
class Financial : public Actors, public Genre {
public:
	// get function
	double get_earnings()
	{
		return earnings;
	}

	// set value function
	void Set_earnings(double number)
	{
		earnings = number;
	}

	// Variables are made public so the functions can access them in cpp file
	double earnings;
};
//  a variable to store the box office gross (in millions, such as 100, 125.5, 475).