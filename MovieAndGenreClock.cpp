/*
Name: Marcus Gerard Riccio
MovieAndGenreClock.cpp
Description: Simple C++ class that simulates a user to pick a movie,
as well as a corresponding timeslot to reserve.
*/

#include <iostream>
#include <string>

using namespace std;

//Struct for Time
//h = Hours
//M = mins
struct Time
{
	int h; //hour
	int m; //min


};

//Movie Genre
enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

//struct Movie
//contains:
//movie title, movie genre, time duration
struct Movie {
    string title;
    Genre genre;     // only one genre per movie
    int duration;    // in minutes
};

//struct TimeSlot
//contains:
//movie info, time at which movie starts
struct TimeSlot {
    Movie movie;     // what movie
    Time startTime;  // when it starts
};

//minutesSinceMidnight(Time time)
//purpose:
//computes newMinute, which is time + midnight time
//returns x minutes from midnight at 00:00
int minutesSinceMidnight(Time time) {

	//midnight = 00:00
	//time = h:m
	Time midnight;
	midnight.h = 00;
	midnight.m = 00;
	
	Time newTime;
	newTime.h = midnight.h + time.h;
	newTime.m = midnight.m + time.m;

	int newHour;
	newHour = time.h * 60;
	int newMinute;
	newMinute = newTime.m + newHour;
	
	return newMinute;
}

//minutesUntil(Time earlier, Time later)
//Computes the difference between showtimes, taking an
//earlier showtime and comparing it to a later showtime
//returns int diff btwn times
int minutesUntil(Time earlier, Time later) {

	//step1 get minutes1 == 00:00 earlier, call minutesSinceMidnight
		Time minutes1;
		minutes1.h = earlier.h;
		minutes1.m = earlier.m;

		int difference1 = minutesSinceMidnight(minutes1);
	//step2 get minutes 2 == 00:00 later call minutesSinceMidnight
		Time minutes2;
		minutes2.h = later.h;
		minutes2.m = later.m;

		int difference2 = minutesSinceMidnight(minutes2);
	
	return difference2 - difference1;
}

//addMinutes(Time time0, int min)
//simple function that adds minutes to comply with 00:00 format
Time addMinutes(Time time0, int min) {

	//time = 15:21
	//min = 100
	//time.h time.m
		Time time;
		time.h = time0.h;
		time.m = time0.m;
	//time.m += min
	time.m += min;
	//100 + 21 = 121 > 60
	if (time.m >= 60) {
		// 121/60 = 2
                time.h += time.m / 60;
		
		// 121 % 60 = 1
		time.m = time.m % 60;
        }
	// return newTime = time + min
	return time;
}

//printTime(Time time)
//simple helper function to print time in 00:00
void printTime(Time time);

//printMovie(Movie mv)
//simple helper function to print movie title
void printMovie(Movie mv);

//printTimeSlot(TimeSlot ts)
//simple helper function to print corr timeslot
void printTimeSlot(TimeSlot ts);

//scheduleAfter(TimeSlot ts, Movie nextMovie)
//Returns TimeSlot newtime, printing the movie title,
//and according showtime
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie) {
	Movie movie = ts.movie;

	Time start = ts.startTime;
	Time newtimer = addMinutes(start, movie.duration);

	TimeSlot newtime;
	newtime.movie = nextMovie;
	newtime.startTime = newtimer;
	printMovie(movie);
	return newtime;
}

//timeOverlap(TimeSlot ts1, Timeslot ts2)
//Compares two movies, Movie movie & Movie movie2,
//And their respective showtimes, returning boolean
//true if overlaps,
//false otherwise
bool timeOverlap(TimeSlot ts1, TimeSlot ts2) {
	Movie movie = ts1.movie;
	Movie movie2 = ts2.movie;

	Time start = ts1.startTime;
	//Time duration = movie.duration;
	//Time startTimer = minutesSinceMidnight(start);
	Time start2 = ts2.startTime;
	//Time duration2 =  movie2.duration;
	//Time secondTimer = minutesSinceMidnight(start2);

	if (minutesSinceMidnight(start) == minutesSinceMidnight(start2)) {
		return true;
	}
	if (minutesSinceMidnight(start2) <= minutesSinceMidnight(start) || minutesSinceMidnight(start2) >= minutesSinceMidnight(start)) {
		return true;
	}
	else {
		return false;
	}
}

//main function
//Has testing variables movie1, movie2
//TimeSlot morning for 9:00AM - 3:00PM
//TimeSlot daytime for 12:00PM - 3:00PM
//TimeSlot evening for 4:00PM - 12:00AM
//*
int main() {


Movie movie1 = {"Back to the Future", COMEDY, 116};
Movie movie2 = {"Black Panther", ACTION, 134};

TimeSlot morning = {movie1, {9, 15}};
TimeSlot daytime = {movie2, {12, 15}};
TimeSlot evening = {movie2, {16,24}};

printTimeSlot(morning);
printTimeSlot(daytime);
printTimeSlot(evening);

}

//printTime(Time time)
//prints time in hh:mm (00:00) format
void printTime(Time time) {
		cout << time.h << ":" << time.m;
}

//printMovie(Movie mv)
//prints movie genre based on corr genre,
//has genres, ACTION/COMEDY/DRAMA/ROMANCE/THRILLER
//does NOT return genre if not of the above choices
void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

//printTimeSlot(TimeSlot ts)
//prints corr movie timeslot, in format of
//"movie [starts at 00:00, ends by 00:00]"
void printTimeSlot(TimeSlot ts) {

	Movie movie = ts.movie;
	printMovie(movie);
	Time start = ts.startTime;

cout << " [starts at "; printTime(start);

	Time end = addMinutes(start, movie.duration);
	
cout << ", ends by"; printTime(end);
cout << "]" << endl;
}

//end MovieAndGenreClock.cpp