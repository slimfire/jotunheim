#include <iostream>
#include <string>
#include "airline.h"

Airline::Airline(){};

void Airline::transferPassengers(int flightNumber, int currentPlaneId, int newPlaneId){
	if((Airline::schedule.flight(flightNumber, currentPlaneId) == true) 
		&& ((Airline::fleet.plane(newPlaneId) == true)))
	{
		if(
			(Airline::fleet.getAvailableFirstClassSeats(currentPlaneId) >= Airline::fleet.getNumberOfFirstClassPassengers(newPlaneId)) &&
			(Airline::fleet.getAvailableEconomyClassSeats(currentPlaneId) >= Airline::fleet.getNumberOfEconomyClassPassengers(newPlaneId)) &&
			(Airline::fleet.getAvailableEconomyPlusClassSeats(currentPlaneId) >= Airline::fleet.getNumberOfEconomyPlusClassPassengers(newPlaneId))
			)
		{
			if(Airline::fleet.allPotentialSeatsAvailable(currentPlaneId, newPlaneId) == true)
			{
				Airline::schedule.changePlane(flightNumber, currentPlaneId, newPlaneId);
				Airline::fleet.transferPassengers(currentPlaneId, newPlaneId);
			}
			else
			{
				cout << "Sorry, the several seats are already taken! " << endl;
			}
		}
		else
		{
			cout << "Sorry, there isn't enough amount of seats on the new plane, #" << newPlaneId << endl;
		}
	}
	else
	{
		cout << "The entered flight number, " << flightNumber << "and plane id, " << currentPlaneId << " doesn't match. Please try again!" << endl;
	}
}

void Airline::addNewFlight(int planeId, string origin, string destination,string departureDate,
		string departureTime, string returnDate, string returnTime){
	Airline::schedule.addFlight(planeId, origin, destination,departureDate,
		departureTime, returnDate, returnTime);
}

void Airline::addNewPassengerToFlight(int flightNumber, int passengerId, string firstName, string lastName){
	Airline::schedule.addPassenger(flightNumber, passengerId, firstName, lastName);
}

void Airline::addNewPlane(int column, int number_of_first_class_rows, int number_of_economy_class_rows, int number_of_economy_plus_rows){
	Airline::fleet.addPlane(column, number_of_first_class_rows, number_of_economy_class_rows, number_of_economy_plus_rows);
}

void Airline::addNewPassengerToList(string firstName, string lastName){
	Airline::passengers.addPassenger(firstName, lastName);
}

void Airline::displayPassengers(int flightNumber){
	Airline::schedule.displayPassengers(flightNumber);
}

void Airline::displayUpcomingFlights(){
	Airline::schedule.displayUpcomingFlights();
}

int Airline::getMaxId(string type){
	if(type == "plane")
	{
		return Airline::fleet.getMaxPlaneId();
	}
	else if(type == "passenger")
	{
		return Airline::passengers.getMaxPassengerId();
	}
	else if(type == "flight")
	{
		return Airline::schedule.getMaxFlightId();
	}
	else
	{
		cout << "Entered type does not exist! Available types are plane, passenger and flight. Please try again!" << endl;
	}
}