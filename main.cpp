/*  Program: Automated Highway Patrol V1.0
Author: Daniel Zelfo
Class: CSCI 110
Date: 10/22/2018
Description:
Calculates and Displays the appropriate ticket price for each vehicle given the current speed and the speed limit in the current zone.
Displays calculated statistics for all analyzed vehicles at the end of the program.

I certify that the code below is my own work.
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//prototypes
void inputD(string output, double& input);
void inputS(string output, string& input);
double getFee(double overLimit);
double calcTicketPrice(double speed, double speedLimit, int base);
void outputTicket(int type, string plateNumber, double ticketPrice=0);
void outputStats(int numTicketed, int numVehicles, double totalTicketPrices);
int main()
{
	string plateNumber;
	double speed, speedLimit, ticketPrice, totalTicketPrices = 0;
	const int base = 150;
	int numVehicles = 0, numTicketed = 0;
	cout << "Automated Highway Patrol Program v1.0\nAuthor: Daniel Zelfo\n\n";
	inputS("Enter a license plate number  --> ", plateNumber);
	while (plateNumber != "QUIT")
	{
		inputD("Enter current vehicle's speed --> ", speed);
		inputD("Enter speed limit in the zone --> ", speedLimit);
		numVehicles += 1;
		if (speed - 50 > speedLimit)
		{
			numTicketed += 1;
			totalTicketPrices += 1000;
			outputTicket(1, plateNumber);
		}
		else if (speed - 5 >= speedLimit)
		{
			numTicketed += 1;
			ticketPrice = calcTicketPrice(speed, speedLimit, base);
			totalTicketPrices += ticketPrice;
			outputTicket(2, plateNumber, ticketPrice);
		}
		else
		{
			outputTicket(3, plateNumber);
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
void inputS(string output, string& input)
{
	cout << output;
	cin >> input;
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
	double overLimit = speed - speedLimit;
	double fee = getFee(overLimit);
	return base + fee * overLimit;
}

void outputTicket(int type, string plateNumber, double ticketPrice)
{
	if (type == 1)
		cout << "A ticket of $1000 is issued to " << plateNumber << ".\n\n";
	else if (type == 2)
		cout << "A ticket of $" << ticketPrice << " is issued to " << plateNumber << ".\n\n";
	else
		cout << "No ticket is issued to " << plateNumber << ".\n\n";
}

void outputStats(int numTicketed, int numVehicles, double totalTicketPrices)
{
	cout << fixed << showpoint << setprecision(2);
	cout << "\nTickets were given to " << numTicketed << " out of " << numVehicles << " vehicles.\n";
	cout << "Percent of ticketed vehicles: " << double(numTicketed) * 100 / numVehicles << "%\n";
	cout << "Average ticket amount:       " << totalTicketPrices / numTicketed << endl;
	cout << "Thank you for using our AHP program.\n";
}
