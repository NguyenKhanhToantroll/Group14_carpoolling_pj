#include "Carpool.h"

Carpool::Carpool(string dep, string dest, string d, string t, int seats, int points)
    : departureLocation(dep), destination(dest), date(d), time(t), availableSeats(seats), contributionPoints(points), seatBooked(false), bookingAccepted(false) {}

string Carpool::getDepartureLocation() const {
    return departureLocation;
}

string Carpool::getDestination() const {
    return destination;
}

string Carpool::getDate() const {
    return date;
}

bool Carpool::hasSeatBooked() const {
    return seatBooked;
}

bool Carpool::isBookingAccepted() const {
    return bookingAccepted;
}

int Carpool::getAvailableSeats() const {
    return availableSeats;
}

void Carpool::bookSeat(User& user) {
    if (availableSeats > 0 && user.getCreditPoints() >= contributionPoints) {
        availableSeats--;
        seatBooked = true;
        user.topUpCredits(-contributionPoints);
        cout << "Seat booked successfully!" << endl;
    } else {
        cout << "Unable to book seat. Either no available seats or insufficient credit points." << endl;
    }
}

void Carpool::cancelBooking() {
    if (!bookingAccepted) {
        seatBooked = false;
        availableSeats++;
        cout << "Booking canceled successfully!" << endl;
    } else {
        cout << "Cannot cancel booking after it has been accepted by the driver." << endl;
    }
}

void Carpool::acceptBooking() {
    if (seatBooked) {
        bookingAccepted = true;
        cout << "Booking accepted by the driver!" << endl;
    } else {
        cout << "No seat has been booked yet." << endl;
    }
}

void Carpool::viewCarpool() const {
    cout << "Date: " << date << " Time: " << time << " Departure: " << departureLocation << " Destination: " << destination << endl;
    cout << "Available Seats: " << availableSeats << " Contribution Points: " << contributionPoints << endl;
}

void Carpool::saveToFile(ofstream &out) const {
    out << departureLocation << " " << destination << " " << date << " " << time << " " << availableSeats << " " << contributionPoints << " "
        << seatBooked << " " << bookingAccepted << "\n";
}

Carpool Carpool::loadFromFile(ifstream &in) {
    string dep, dest, date, time;
    int seats, points;
    bool booked, accepted;
    in >> dep >> dest >> date >> time >> seats >> points >> booked >> accepted;
    Carpool carpool(dep, dest, date, time, seats, points);
    carpool.seatBooked = booked;
    carpool.bookingAccepted = accepted;
    return carpool;
}
