#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <typeinfo>
#include "../../flightSchedule/flight/storageFlight.cpp"
#include "flightScheduleUtility.h"

using namespace std;
// FlightScheduleUtility util;

int FlightScheduleUtility::generateId(/*vector<Flight> &flights*/){
	vector<StorageFlight> flights;
	FlightScheduleUtility util;
	util.populateReadArray(flights, "flightSchedule.txt");

	int maximum = 0;
	for(int i = 0; i < flights.size(); i++)
	{
		if(flights[i].getFlightNumber() > maximum)
		{
			maximum = flights[i].getFlightNumber();
		}
	}
	return maximum;
}

void FlightScheduleUtility::populateReadArray(vector<StorageFlight> &flights, string filename)
{
	FlightScheduleUtility util;
	string line = "";
	string chunk = "";
	vector< vector<string> > data;
	fstream readStream;
	readStream.open("../data/flightSchedule.txt");

	//read each line and split by |
	while(getline(readStream, line))
	{
		cout << "** " << line << endl;
		vector<string> row;
		stringstream ss(line);
		while(getline(ss, chunk, '|') )
		{
			row.push_back(chunk);
		}
		data.push_back(row);
	}
	//(Format) data[i][0] : flightID planeID origin destination depDate depTime retDate retTime
	// on each iteration, 
		// breakdown the flight info part of the data ^ by space & put it in a vector
		// breakdown the passegerInfos (['passID fName lName', 'passID fName lName'] ) by space 
		//		 and push each data on passenger vector

	for (int i = 0; i < data.size(); i++)
	{
		vector<string> chunks;
		vector< vector<string> > passsenger;
		util.split(data[i][0], chunks);

		StorageFlight flight(
			util.stringToInt(chunks[0]), 
			util.stringToInt(chunks[1]), 
			chunks[2], 
			chunks[3],
			chunks[4], 
			chunks[5], 
			chunks[6], 
			chunks[7]
		);
		for (int j = 1; j < data[i].size(); j++)
		{
			vector<string> passsengerInfo;
			util.split(data[i][j], passsengerInfo);
			flight.addPassengerId(util.stringToInt(passsengerInfo[0]));
			flight.addPassengerName(passsengerInfo[1] + " " + passsengerInfo[2]);//lastname, firstname
		}
		flights.push_back(flight);
	}
}


void FlightScheduleUtility::writeFile(vector<StorageFlight> &storageFlights,vector<StorageFlight> &newFlights, string filename)
{
	ofstream outputStream;
	outputStream.open("../data/test.txt");
	int iteration = storageFlights.size() + newFlights.size();
	for (int i = 0; i < iteration; i++)
	{
		if(i != storageFlights.size())
		{
			outputStream << storageFlights[i].getFlightNumber() << " " << storageFlights[i].getPlaneId() << " ";
			outputStream << storageFlights[i].getOrigin() << " " << storageFlights[i].getDestination() << " ";
			outputStream << storageFlights[i].getDepartureDate() << " " << storageFlights[i].getDepartureTime() << " ";
			outputStream << storageFlights[i].getReturnDate() << " " << storageFlights[i].getReturnTime();
			vector<int> passengerIds = storageFlights[i].getPassengerIds();
			vector<string> passengerNames = storageFlights[i].getPassengerNames();
			for (int j = 0; j < passengerIds.size(); j++)
			{
				outputStream << " | " << passengerIds[j] << " " << passengerNames[j];
			}
			outputStream << endl;
		}
		else
		{
			outputStream << storageFlights[i].getFlightNumber() << " " << storageFlights[i].getPlaneId() << " ";
			outputStream << storageFlights[i].getOrigin() << " " << storageFlights[i].getDestination() << " ";
			outputStream << storageFlights[i].getDepartureDate() << " " << storageFlights[i].getDepartureTime() << " ";
			outputStream << storageFlights[i].getReturnDate() << " " << storageFlights[i].getReturnTime();
			vector<int> passengerIds = storageFlights[i].getPassengerIds();
			vector<string> passengerNames = storageFlights[i].getPassengerNames();
			for (int j = 0; j < passengerIds.size(); j++)
			{
				outputStream << " | " << passengerIds[j] << " " << passengerNames[j];
			}
			outputStream << endl;
		}
	}
	outputStream.close();
}
void FlightScheduleUtility::split(string line, vector<string> &words)
{
	stringstream ss(line);
	string word = "";
	while(ss >> word)
	{
		words.push_back(word);
	}
}

int FlightScheduleUtility::stringToInt(string word)
{
	stringstream ss(word);
	int intVersion;
	ss >> intVersion;
	return intVersion;
}