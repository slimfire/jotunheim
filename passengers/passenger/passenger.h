#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Passenger
{
	public:
		Passenger
		(
			int passengerId, 
			string firstName,
			string lastName
		
		);	

		int getPassengerId();
		string getFirstName();
		string getLastName();
		

		vector<int> getFlightNumber();
		vector<string> getPassengerSeats();

		void setPassengerId(int passengerId);
		void setFirstName(string firstName);
		void setLastName(string lastName);
		

		void addFlightNumber(int flightNumber);
		void addPassengerSeat(string passengerSeat);

		

	private:
		int passengerId;
		string firstName;
		string lastName;	
		vector<int> flightNumbers;
		vector<string>passengerSeats;
		
};