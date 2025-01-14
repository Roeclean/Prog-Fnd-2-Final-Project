#pragma once

#include <iostream> 
#include <string> 

using namespace std;

class Movie {  // Super class- holds the movies ratings
public:
	// get function
	string get_Movie_Rating()
	{
		return Movie_Rating;
	}
	string get_Movie_Nm()
	{
		return Movie_Nm;
	}

	// set value function
	void Set_Movie_Rating(string text)
	{
		// stores the movie's rating (G, PG, PG-13, R)
		Movie_Rating = text;
	}
	void Set_Movie_Name(string text)
	{
		Movie_Nm = text;
	}

	// Variables are made public so the functions can access them in cpp file
	string Movie_Rating, Movie_Nm;

};