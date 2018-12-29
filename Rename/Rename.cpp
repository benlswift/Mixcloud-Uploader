// Rename.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;
void scriptWriter(string,int,string);
string rename(string, string);
string getDay(int);
string getName(string,string);

int main()
{
	//system("file.sh"); //run the script
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	string name;
	string date;
	string fly;
	string time;
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1; // Month is 0 – 11, add 1 to get a jan-dec 1-12 concept
	int year = aTime->tm_year + 1900; // Year is # years since 1900
	int hour = aTime->tm_hour;
	int min = aTime->tm_min;
	int dayOfWeek = aTime->tm_wday;
	string theDay = std::to_string(day);
	string theMonth = std::to_string(month);
	string theYear = std::to_string(year);
	string theHour = std::to_string(hour-1);
	string dayName = getDay(dayOfWeek);
	//cout << hour -1<< "00" << "-FLYFM-" << day << month << year << ".mp3";
	date = theDay + theMonth + theYear;
	fly = "-FLYFM-";
	time = theHour + "00";
	name = time + fly + date + ".mp3";
	cout << name << endl;
	scriptWriter(name,dayOfWeek,theHour);
	//getName();
    return 0;
}

void scriptWriter(string filename, int dayOfWeek,string hour)
{
	ofstream script;
	script.open("file.sh");
	script << "curl -F mp3=@" << filename <<" \\\n";//add in slashes at end
	script << "\t " << getName(getDay(dayOfWeek),hour) << "\n";
	/*script << "\t -F \"tags-0-tag=Test\" \\\n";
	script << "\t -F \"tags-1-tag=API\" \\\n";
    script << "\t -F \"sections-0-chapter=Introduction\" \\\n";
    script << "\t -F \"sections-0-start_time=0\" \\\n";
    script << "\t -F \"sections-1-artist=Artist Name\" \\\n";
	script << "\t -F \"sections-1-song=Song Title\" \\\n";
	script << "\t -F \"sections-1-start_time=10\" \\\n";
	script << "\t -F \"description=My test upload\" \\\n";*/
	script << "\t https://api.mixcloud.com//upload/?access_token=AWUhw5rG4Mf5gqhYVwYZDEKfeCp8gF3C";//change to flyondemand access token
}

string rename(string day, string hour)
{
	ifstream schedule("schedule.txt");
	return " ";
}

string getDay(int dayOfWeek)
{
	string day;
	switch (dayOfWeek) {
	case 1: day = "Monday";
		break;       
	case 2: day = "Tuesday";
		break;
	case 3: day = "Wednesday";
		break;
	case 4: day = "Thursday";
		break;
	case 5: day = "Friday";
		break;
	case 6: day = "Saturday";
		break;
	case 7: day = "Sunday";
		break;
	}
	return day;
}

string getName(string day, string time)
{
	//-F "name=API Upload" \ 
	ifstream schedule(day+".txt");
	string name;
	string showName;
	
	while (schedule)
	{
		getline(schedule, name);
		if (name == time)
		{
			getline(schedule, name);
			cout << name << endl;
		}
	}

	showName = "-F \"name=" + name + "\" \\";
	return showName;
}