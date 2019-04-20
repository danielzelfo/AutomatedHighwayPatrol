/*  Program: Automated Highway Patrol V1.1
Author: Daniel Zelfo
Class: CSCI 110
Date: 10/22/2018
Description:
Calculates and Displays the appropriate ticket price for each vehicle given the current speed and the speed limit in the current zone.
Displays calculated statistics for all analyzed vehicles at the end of the program.
v1.1: modified on 10/23/2018 to work with two times at two checkpoints. Also formats time in 12 hour format with am/pm

I certify that the code below is my own work.
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//prototypes
void inputD(string output, double& input);
void inputI(string output, int& input);
void inputS(string output, string& input);
double getFee(double overLimit);
double calcTicketPrice(double speed, double speedLimit, int base);
void outputTicket(int type, string plateNumber, string timeFormated, double ticketPrice = 0);
void outputStats(int numTicketed, int numVehicles, double totalTicketPrices);
string getTime(int time);
int main()
{
	string plateNumber, timeFormated;
	double speed, speedLimit, ticketPrice, totalTicketPrices = 0;
	const int base = 150;
	const double distance = 5.0;
	int timeA, timeB, numVehicles = 0, numTicketed = 0;
	cout << "Automated Highway Patrol Program V1.1 (EXTRA CREDIT)\nAuthor: Daniel Zelfo\n\n";
	inputS("Enter a license plate number  --> ", plateNumber);
	while (plateNumber != "QUIT")
	{
		inputI("Enter time at checkpoint A    --> ", timeA);
		inputI("Enter time at checkpoint B    --> ", timeB);
		inputD("Enter speed limit in the zone --> ", speedLimit);
		numVehicles += 1;
		speed = distance * 60 / (timeB - timeA);
		timeFormated = getTime(timeB);
		if (speed - 50 > speedLimit)
		{
			numTicketed += 1;
			totalTicketPrices += 1000;
			outputTicket(1, plateNumber, timeFormated);
		}
		else if (speed - 5 >= speedLimit)
		{
			numTicketed += 1;
			ticketPrice = calcTicketPrice(speed, speedLimit, base);
			totalTicketPrices += ticketPrice;
			outputTicket(2, plateNumber, timeFormated, ticketPrice);
		}
		else
		{
			outputTicket(3, plateNumber, timeFormated);
		}
		inputS("Enter a license plate number  --> ", plateNumber);
	}
	outputStats(numTicketed, numVehicles, totalTicketPrices);
	return 0;
}

void inputD(string output, double& input)
{
	cout << output;
	cin >> input;
}
void inputI(string output, int& input)
{
	cout << output;
	cin >> input;
}
void inputS(string output, string& input)
{
	cout << output;
	cin >> input;
}

string getTime(int timeMin)
{
	string m = "am";
	if (timeMin > 720)
	{
		timeMin -= 720;
		m = "pm";
	}
	string hours = to_string(timeMin / 60);
	string minutes = to_string(timeMin % 60);
	if (hours == "0")
		hours = "12";
	if (minutes.length() == 1)
		minutes = "0" + minutes;
	return hours + ":" + minutes + m;
}

double getFee(double overLimit)
{
	if (overLimit <= 20)
		return 5;
	else
		return 10;
}

double calcTicketPrice(double speed, double speedLimit, int base)
{
	double overLimit = int(speed - speedLimit);
	double fee = getFee(overLimit);
	return base + fee * overLimit;
}

void outputTicket(int type, string plateNumber, string timeFormated, double ticketPrice)
{
	if (type == 1)
		cout << "A ticket of $1000";
	else if (type == 2)
		cout << "A ticket of $" << ticketPrice;
	else
		cout << "No ticket";
	cout << " is issued to " << plateNumber << " at " << timeFormated << ".\n\n";
}

void outputStats(int numTicketed, int numVehicles, double totalTicketPrices)
{
	cout << fixed << showpoint << setprecision(2);
	cout << "\nTickets were given to " << numTicketed << " out of " << numVehicles << " vehicles.\n";
	cout << "Percent of ticketed vehicles: " << double(numTicketed) * 100 / numVehicles << "%\n";
	cout << "Average ticket amount:       " << totalTicketPrices / numTicketed << endl;
	cout << "Thank you for using our advance AHP program.\n";
}
