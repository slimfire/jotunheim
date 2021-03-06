#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <typeinfo>
#include <exception>
#include "../../flightSchedule/flight/storageFlight.h"
#include "flightScheduleUtility.h"

using namespace std;

void FlightScheduleUtility::populateReadArray(vector<StorageFlight> &flights, string path) // function to populate the array from storage flights with the path directory
{
	FlightScheduleUtility util;
	string line = "";
	string chunk = "";
	vector< vector<string> > data;
	fstream readStream;
	readStream.open(path.c_str()); //Opens up the file from the subdirectory file location 
	
	//read each line and split by |
	while(getline(readStream, line))
	{
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
			util.stringToInt(chunks[0]), //convert this string to int
			util.stringToInt(chunks[1]), //convert this strong to int 
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
			flight.addPassengerId(util.stringToInt(passsengerInfo[0])); // add passenger id into flight and also convert from string to int
			flight.addPassengerName(passsengerInfo[1] + " " + passsengerInfo[2]);//lastname, firstname
		}
		flights.push_back(flight); //pushes back the flight into the vector
	}
}


void FlightScheduleUtility::writeFile(vector<StorageFlight> &storageFlights,vector<NewFlight> &newFlights, string path)//function to write the flightScheduleUility into file
{
	string pipe = "|";
	ofstream outputStream;
	string outputData = "";
	// write the data from the storageFlights and newFlights to text file
	outputStream.open(path.c_str());
	// extract the data from each method and instert it into the output stream
	for (int i = 0; i < storageFlights.size(); i++)// iterates the storageFlight.size to display all the information
	{
		outputStream << storageFlights[i].getFlightNumber() << " " << storageFlights[i].getPlaneId() << " "; // 
		outputStream << storageFlights[i].getOrigin() << " " << storageFlights[i].getDestination() << " ";
		outputStream << storageFlights[i].getDepartureDate() << " " << storageFlights[i].getDepartureTime() << " ";
		outputStream << storageFlights[i].getReturnDate() << " " << storageFlights[i].getReturnTime();
		vector<int> passengerIds = storageFlights[i].getPassengerIds(); //gets all the newFlights and store them temporarily into the storage flight vector
		vector<string> passengerNames = storageFlights[i].getPassengerNames(); // gets all the passengerName and store them temporarily into the storage flight vector 
		for (int j = 0; j < passengerIds.size(); j++)
		{
			outputStream << " " << pipe << " " << passengerIds[j] << " " << passengerNames[j];
		}
		outputStream << endl;
	}
	// extract the data from each method and instert it into the output stream
	for (int i = 0; i < newFlights.size(); i++) 
	{
		outputStream << newFlights[i].getFlightNumber() << " " << newFlights[i].getPlaneId() << " ";
		outputStream << newFlights[i].getOrigin() << " " << newFlights[i].getDestination() << " ";
		outputStream << newFlights[i].getDepartureDate() << " " << newFlights[i].getDepartureTime() << " ";
		outputStream << newFlights[i].getReturnDate() << " " << newFlights[i].getReturnTime();
		vector<int> passengerIds = newFlights[i].getPassengerIds(); //gets all the newFlights and store them temporarily into the vector 
		vector<string> passengerNames = newFlights[i].getPassengerNames(); //gets all the passengerNames and store them temporarily into the vector 
		// extract the passengerIds from each
		for (int j = 0; j < passengerIds.size(); j++)
		{
			outputStream << " " << pipe << " " << passengerIds[j] << " " << passengerNames[j];
		}
		outputStream << endl;
	}
	outputStream.close();
}
void FlightScheduleUtility::split(string line, vector<string> &words)// function to split the data 
{
	stringstream ss(line);
	string word = "";
	while(ss >> word)
	{
		words.push_back(word);
	}
}

int FlightScheduleUtility::stringToInt(string word)// function to convert the string to int
{
	stringstream ss(word);
	int intVersion;
	ss >> intVersion;
	return intVersion;
}