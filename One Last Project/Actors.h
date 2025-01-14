#pragma once

#include <iostream> 
#include <string> 

using namespace std;

// This class stores the main actor of each respective movie
// first and last name
class Actors : public Movie {
public:
	// get function
	string get_Act_Fname()
	{
		return Act_Fname;
	}
	string get_Act_Lname()
	{
		return Act_Lname;
	}

	// set value function
	void Set_Act_Fname(string text)
	{
		Act_Fname = text;
	}
	void Set_Act_Lname(string text)
	{
		Act_Lname = text;
	}

	// Variables are made public so the functions can access them in cpp file
	string Act_Fname, Act_Lname;
};