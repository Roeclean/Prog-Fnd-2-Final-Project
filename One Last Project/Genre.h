#pragma once

#include <iostream> 
#include <string> 

using namespace std;

// This class stores the movies' genre
class Genre : public Movie {
public:
	// get function
	string get_genre()
	{
		return genre;
	}

	// set value function
	void Set_genre(string text)
	{
		genre = text;
	}

	// Variables are made public so the functions can access them in cpp file
	string genre;

};