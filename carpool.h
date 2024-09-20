#ifndef CARPOOL_H
#define CARPOOL_H

#include <string>
#include <fstream>
#include "User.h"

using namespace std;

class Carpool {
private:
    string departureLocation;
    string destination;
    string date;
    string time;
    int availableSeats;
    int contributionPoints;
    bool seatBooked;
    bool bookingAccepted;

public:
    Carpool(string dep, string dest, string d, string t, int seats, int points);
    string getDepartureLocation() const;
    string getDestination() const;
    string getDate() const;
    bool hasSeatBooked() const;
    bool isBookingAccepted() const;
    int getAvailableSeats() const;
    void bookSeat(User& user);
    void cancelBooking();
    void acceptBooking();
    void viewCarpool() const;
    void saveToFile(ofstream &out) const;
    static Carpool loadFromFile(ifstream &in);
};

#endif // CARPOOL_H
