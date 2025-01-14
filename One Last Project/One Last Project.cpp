/* One Last Project
** Name:Roemon Christian
*  Date:5-6-24
*  Program Description: Uses 4 classes with related variables that are all used to initialize 
** 4 vectors with Movie data. A simple menu is then used to let the user decide how they
** want to process the data. The user can process the data in numerous ways as many times as they
** want, since the menu is in a while loop that only closes when a specific option is chosen
*/

// Libraries used 
#include <iostream>
#include <string>
#include <fstream>
#include <vector> 
#include <iomanip>
#include "MovieClass.h" // super class

// Derived classes from super class
#include "Genre.h"
#include "Actors.h"
// Joint class from derived classes
#include "Financial.h"

using namespace std;

// Function Declerations -
// Main Functions
int Get_MovieData(vector<Movie>& Name, vector<Genre>& MovieType,
				vector<Actors>& Starring_per, vector<Financial>& Earned, ifstream& Fin);
void TheMenu(vector<Movie>& Name, vector<Genre>& MovieType,
			 vector<Actors>& Starring_per, vector<Financial>& Earned, int Cnt);
void IsFile_here(ifstream& iFile, string FileName);

// Supporting Functions
void MenuPrint_line(string Sentence, int Col1, int Col2, int counting);
int HighestNum(vector<Financial>Num, int counter);
void SortingMenu(vector<Movie>& Name, vector<Genre>& MovieType,
				 vector<Actors>& Starring_per, vector<Financial>& Earned, int CntS); 
void Swap_values(vector<Movie>& Nm, vector<Genre>& MovieType,
			     vector<Actors>& Starring_per, vector<Financial>& Earned, int a, int b);
void Print_ToScreen(vector<Movie>& Name, vector<Genre>& MovieType,
	vector<Actors>& Starring_per, vector<Financial>& Earned, int Counter);
void GetThat_Count(vector<Movie>& Rating, vector<Financial>& MoneyGrossed, char Switch, int Count);


int main()
{
	// File stream variable for file reading function
	ifstream fin;

	// Opens file used in program
	fin.open("Movies'_Information.txt"); // PUT DATA IN THERE (4 SETS

	// Checks for file
	IsFile_here(fin, "Movies'_Information.txt"); 

	// These vectors are used to utilize the 
	// classes used in this program
	vector<Movie> Movie_Nm;
	vector<Genre> Movie_genre;
	vector<Actors> Movie_Actor;
	vector<Financial> MoneyGrossed;

	// This counter variable stores the total amount of data sets from the input file
	// and the Get Movie data function also initializes the 4 vectors used 
	// in this program
	int Counters = Get_MovieData(Movie_Nm, Movie_genre, Movie_Actor, MoneyGrossed, fin);
	
	// This function opens a simple menu that the user will use to decide how they
	// want to process the data from the input file
	TheMenu(Movie_Nm, Movie_genre, Movie_Actor, MoneyGrossed, Counters);

	fin.close();
	return 0;
}
// MAKE SURE TO DELETE THE MANY COMMENTS UNDER THE FUNCTIONS. 
// Function Definitions -------------------------------------------------

// Makes sure the file is found 
void IsFile_here(ifstream& iFile, string FileName)
{
	// Checks for file in program 
	if (!iFile.is_open())
	{
		cout << FileName << " could not be found.";
		exit(1); // ends program if file is not found in the program
	}
}

// Initializes vectors with Movie Data
int Get_MovieData(vector<Movie>& Name, vector<Genre>& MovieType, 
			   vector<Actors>& Starring_per, vector<Financial>& Earned, ifstream& Fin)
{
	// stores the amt of people read in from the input file
	int counterS = 0; 

	// These are all temporary variables for their respective class
	Movie S_Temp1;
	Genre S_Temp2;
	Actors S_Temp3;
	Financial N_Temp;


	while (!Fin.eof())
	{
		// Movie_Name data
		Fin >> S_Temp1.Movie_Rating;
		Fin.ignore();

		getline(Fin, S_Temp1.Movie_Nm);
		Name.push_back(S_Temp1);

		// Movie Type data
		Fin >> S_Temp2.genre;
		MovieType.push_back(S_Temp2);

		// Actor Name data
		Fin >> S_Temp3.Act_Fname;
		Fin >> S_Temp3.Act_Lname;
		Starring_per.push_back(S_Temp3);

		// Financial data
		Fin >> N_Temp.earnings;
		Earned.push_back(N_Temp);

		counterS++;
	}

	return counterS;
}

// 
void TheMenu(vector<Movie>& Name, vector<Genre>& MovieType,
			vector<Actors>& Starring_per, vector<Financial>& Earned, int Cnt)
{
	// These variables hold the Column widths
	int COL1 = 3, COL2 = 52; // May need to change 

	int User_Opts = 0;   // Stores the User option number

	int HighNum_pos = 0; // stores position for the highest grossing movie

	// These variables used to find the average box office earnings across all movies
	// in case 3
	double totalMovie_earnings = 0;
	double BoxOffice_avg = 0; 

	int Menu_lnCount = 0; // Stores the curr line number in the menu function

	char Switch; // Determines what version of the count function will run


	while (User_Opts != 6)
	{
		cout << endl;
		// Main Menu for user options
		cout << "\tMain Menu\n";

		Menu_lnCount++;
		MenuPrint_line("Open Sorting menu", COL1, COL2, Menu_lnCount);
		Menu_lnCount++; 
		MenuPrint_line("Output the highest box office grossing Movie", COL1, COL2, Menu_lnCount);
		Menu_lnCount++; 
		MenuPrint_line("Output the average box office gross for all movies", COL1, COL2, Menu_lnCount);
		Menu_lnCount++; 
		MenuPrint_line("Output a count of movie ratings", COL1, COL2, Menu_lnCount);
		Menu_lnCount++;
		MenuPrint_line("Output a count of movies that made over 100 million at the box office", COL1, 
																							  COL2, Menu_lnCount);
		Menu_lnCount++; 		
		MenuPrint_line("Exit Menu", COL1, COL2, Menu_lnCount);

		Menu_lnCount = 0; // sets menu line count to 0 for another iteration

		cout << endl;
		cout << "Enter selection (1-6): ";
		cin >> User_Opts;
		cout << endl; 

		switch (User_Opts) // Menu Options
		{
		case 1: // Sort Menu
			SortingMenu(Name, MovieType, Starring_per, Earned, Cnt);
			break;
		case 2:	// Output the highest box office grossing Movie	// add the other parts later.........
			HighNum_pos = HighestNum(Earned, Cnt);

			cout << fixed << setprecision(2);
			cout << endl;
			cout << "movie:\t\t" << Name[HighNum_pos].Movie_Nm << endl
				<< "Starring Actor:\t" << Starring_per[HighNum_pos].Act_Fname
				<< " " << Starring_per[HighNum_pos].Act_Lname << endl
				<< "genre:\t\t" << MovieType[HighNum_pos].genre << endl
				<< "rating:\t\t" << Name[HighNum_pos].Movie_Rating << endl
				<< "Box Office Gross (in millions): $" << Earned[HighNum_pos].earnings << endl;
			break;
		case 3: // Outputs the average box office gross for all movies
			for (int j = 0; j < Cnt; j++)
				totalMovie_earnings += Earned[j].earnings;

			BoxOffice_avg = totalMovie_earnings / Cnt;

			cout << fixed << setprecision(2);
			cout << "\nThe average box office earnings from every movie is $" << BoxOffice_avg
				 << " million.\n\n";
			break;
		case 4: // Output a count of movie ratings

			Switch = 'S';
			GetThat_Count(Name, Earned, Switch, Cnt);
			break;
		case 5: // Output a count of movies that made over 100 million at the box office

			Switch = 'N';
			GetThat_Count(Name, Earned, Switch, Cnt);
			break;
		}

	}
}

// This function creates a count with 2 coloumns that displays the amount of movies
// with a specific rating and can also output the count of movies that
// made over 100 million at the Box Office
void GetThat_Count(vector<Movie>& Rating, vector<Financial>& MoneyGrossed, char Switch, int Count)
{

	// These variables store the amt of movies with the same rating
	int Rating_G = 0, Rating_PG = 0, Rating_PG_13 = 0;
	int Rating_R = 0;

	// This variable stores the count of movies that had a box office
	// gross at or over $100 million 
	int Movie_cnt = 0;

	int Col1 = 10, Col2 = 8;

	// This loop initializes the varibles for movie ratings or box office gross over 
	// 100 million using the data from their respective vector
	for (int k = 0; k < Count; k++)
	{
		if (Switch == 'S') // S standing for string (i.e Rating)
		{
			if (Rating[k].Movie_Rating == "G")
				Rating_G++;			
			else if (Rating[k].Movie_Rating == "PG")
				Rating_PG++;			
			else if (Rating[k].Movie_Rating == "PG-13")
				Rating_PG_13++;			
			else if (Rating[k].Movie_Rating == "R")
				Rating_R++;	
		}
		else if (Switch == 'N') // N standing for number (i.e MoneyGrossed)
		{
			if (MoneyGrossed[k].earnings >= 100)
				Movie_cnt++;
		}
	}
	
	// These if statements print out the corresponding processed data from the 
	// loop above this. 
	if (Switch == 'S')
	{
		// Movie Rating columns
		cout << setw(Col1) << "Rating" << left <<  setw(Col2) << "Count" << endl;

		cout << setw(Col1) << "G" << left << setw(Col2) << Rating_G << endl;
		cout << setw(Col1) << "PG" << left << setw(Col2) << Rating_PG << endl;
		cout << setw(Col1) << "PG-13" << left << setw(Col2) << Rating_PG_13 << endl;
		cout << setw(Col1) << "R" << left << setw(Col2) << Rating_R << endl;
	}
	else if (Switch == 'N')
	{
		cout << "The amount of movies that made over $100 million"
			 << " is " << Movie_cnt << ".\n";
	}

}


// This function is a template for creating a single line in a menu list
// to reduce repetivity in the menu functions.
// It creates a line based on the col widths specified, and has to be 
// incremented manually
void MenuPrint_line(string Sentence, int Col1, int Col2, int counting)
{
	cout << right << setw(Col1) << counting << " - " << left << setw(Col2) << Sentence << endl;
}


// A sorting menu the lets the user choose how they want to sort the 
// movie data
void SortingMenu(vector<Movie>& Name, vector<Genre>& MovieType,
	vector<Actors>& Starring_per, vector<Financial>& Earned, int CntS)
{
	// These variables hold the Column widths
	int COL1 = 3, COL2 = 51;

	int User_sortOpt = 0; // Stores the Users sorting option 

	int MenuCount = 0; // keeps current count for the menu line

	while (User_sortOpt != 11)
	{
		// Sort Menu
		cout << "\tSort Menu\n";

		MenuCount++;
		MenuPrint_line("Sort Movie Names (A to Z)", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Sort Movie Names (Z to A)", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Sort Movie Ratings ('G' to 'R')", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Sort Movie Ratings ('R' to 'G')", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Sort Movie Genres (A to Z)", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Sort Movie Genres (Z to A)", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Sort Actors (Last, First)", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Sort Actors (First, Last)", COL1, COL2, MenuCount);
		MenuCount++;		
		MenuPrint_line("Sort Movies box office gross (Highest to Lowest)", COL1, COL2, MenuCount);
		MenuCount++;		
		MenuPrint_line("Sort Movies box office gross (Lowest to Highest)", COL1, COL2, MenuCount);
		MenuCount++;
		MenuPrint_line("Exit Sort Menu", COL1, COL2, MenuCount);

		MenuCount = 0; // sets to 0 for a new loop

		cout << endl;
		cout << "Enter a selection (1-11): ";
		cin >> User_sortOpt;
		cout << endl;

		// These sort options use similar for loops, due to the complexity of 
		// the loop making it difficult to implement into a function. 
		// '>' is used to compare from 'A to Z' and '<' is used to compare from 'Z to A'
		// '>' is then used to sort from Biggest to least, 
		// and '<' is used to sort from least to biggest
		switch (User_sortOpt) // Menu Options
		{
		case 1: // Sorts Movie names from A to Z
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Name[i].Movie_Nm > Name[j].Movie_Nm)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 2:	// Sorts Movie names from Z to A
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Name[i].Movie_Nm < Name[j].Movie_Nm)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 3: // Sort Movie Ratings  ('G' to 'R')
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Name[i].Movie_Rating > Name[j].Movie_Rating)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 4: // Sort Movie Ratings ('R' to 'G')
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Name[i].Movie_Rating < Name[j].Movie_Rating)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 5: // Sort Movie Genres (A to Z)
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (MovieType[i].genre > MovieType[j].genre)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 6: // Sort Movie Genres (Z to A)
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (MovieType[i].genre < MovieType[j].genre)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 7: // Sort Actors (Last, First)
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Starring_per[i].Act_Lname > Starring_per[j].Act_Lname)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			// Function is manually put here so the data is sorted based off the 
			// last name
			for (int k = 0; k < CntS; k++)
			{
				cout << "movie:\t\t" << Name[k].Movie_Nm << endl
					<< "Starring Actor:\t" << Starring_per[k].Act_Lname
					<< ", " << Starring_per[k].Act_Fname << endl
					<< "genre:\t\t" << MovieType[k].Movie_Rating << endl
					<< "rating:\t\t" << Name[k].Movie_Rating << endl
					<< "Box Office Gross (in millions): $" << Earned[k].earnings << endl;
				cout << endl;
			}
			break;
		case 8: // Sort Actors (First, Last)
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Starring_per[i].Act_Fname > Starring_per[j].Act_Fname)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 9: // Sort Movies box office gross (Highest to Lowest)
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Earned[i].earnings > Earned[j].earnings)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		case 10: // Sort Movies box office gross (Lowest to Highest)
			for (int i = 0; i < CntS; i++)
			{
				for (int j = i + 1; j < CntS; j++)
				{
					if (Earned[i].earnings < Earned[j].earnings)
						Swap_values(Name, MovieType, Starring_per, Earned, j, i);
				}
			}
			Print_ToScreen(Name, MovieType, Starring_per, Earned, CntS);
			break;
		}
	}
}

// Print function that prints all of the movie data into a easy to read format
void Print_ToScreen(vector<Movie>& Name, vector<Genre>& MovieType,
	vector<Actors>& Starring_per, vector<Financial>& Earned, int Counter)
{
	cout << endl;
	cout << fixed << setprecision(2);
	for (int j = 0; j < Counter; j++)
	{
		cout << "movie:\t\t" << Name[j].Movie_Nm << endl
			<< "Starring Actor:\t" << Starring_per[j].Act_Fname
			<< " " << Starring_per[j].Act_Lname << endl
			<< "genre:\t\t" << MovieType[j].genre << endl
			<< "rating:\t\t" << Name[j].Movie_Rating << endl
			<< "Box Office Gross (in millions): $" << Earned[j].earnings << endl
			<< endl;
	}
}


// Finds the highest grossing movie position in the vector
int HighestNum(vector<Financial>Num, int counter)
{
	//Initalizes the position of the biggest number
	int BigNum_pos = 0;

	for (int k = 1; k < counter; k++) // starts loop at position 1
	{
		if (Num[k].earnings > Num[BigNum_pos].earnings)
			BigNum_pos = k; // updates vector position when a bigger value is found
	}
	return BigNum_pos;
}

// This is a very important function that swaps the value positions based
// on what is being sorted. This is the base of a sorting function
void Swap_values(vector<Movie>& Nm, vector<Genre>& MovieType,
	vector<Actors>& Starring_per, vector<Financial>& Earned, int a, int b)
{
	// Temp variables to hold values before they are switched
	string TempS;
	double Temp_Num;

	// The swapping structure used to match all the corresponding
	// variables in the vectors position so the data matches

	// Movie_Nm swapped data
	TempS = Nm[a].Movie_Rating;
	Nm[a].Movie_Rating = Nm[b].Movie_Rating;
	Nm[b].Movie_Rating = TempS;
	
	TempS = Nm[a].Movie_Nm;
	Nm[a].Movie_Nm = Nm[b].Movie_Nm;
	Nm[b].Movie_Nm = TempS;
	
	// MovieType swapped data
	TempS = MovieType[a].genre;
	MovieType[a].genre = MovieType[b].genre;
	MovieType[b].genre = TempS;

	// Actor Name swapped data
	TempS = Starring_per[a].Act_Fname;
	Starring_per[a].Act_Fname = Starring_per[b].Act_Fname;
	Starring_per[b].Act_Fname = TempS;

	TempS = Starring_per[a].Act_Lname;
	Starring_per[a].Act_Lname = Starring_per[b].Act_Lname;
	Starring_per[b].Act_Lname = TempS;

	// Financial swapped data
	Temp_Num = Earned[a].earnings;
	Earned[a].earnings = Earned[b].earnings;
	Earned[b].earnings = Temp_Num;

}