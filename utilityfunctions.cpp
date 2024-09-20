#include "UtilityFunctions.h"
#include <iostream>
#include <fstream>

using namespace std;

vector<User> users;
vector<Carpool> carpools;

void loadData() {
    ifstream file("data.txt");

    if (!file.is_open()) {
        cerr << "Error opening file for loading." << endl;
        return;
    }

    string line;
    bool loadingUsers = false;
    bool loadingCarpools = false;

    while (getline(file, line)) {
        if (line == "#USERS") {
            loadingUsers = true;
            loadingCarpools = false;
        } else if (line == "#CARPOOLS") {
            loadingUsers = false;
            loadingCarpools = true;
        } else if (loadingUsers) {
            users.push_back(User::loadFromFile(file));  // Load user data
        } else if (loadingCarpools) {
            carpools.push_back(Carpool::loadFromFile(file));  // Load carpool data
        }
    }

    file.close();
}

void saveData() {
    ofstream file("data.txt");

    if (!file.is_open()) {
        cerr << "Error opening file for saving." << endl;
        return;
    }

    // Write users
    file << "#USERS\n";
    for (const auto& user : users) {
        user.saveToFile(file);
    }

    // Write carpools
    file << "#CARPOOLS\n";
    for (const auto& carpool : carpools) {
        carpool.saveToFile(file);
    }

    file.close();
}

void viewCarpoolsAsGuest() {
    cout << "List of available carpools with passenger-rating <= 3:\n";
    for (const auto& carpool : carpools) {
        bool displayCarpool = true;
        for (const auto& user : users) {
            if (user.getRating() > 3) {
                displayCarpool = false;
                break;
            }
        }

        if (displayCarpool) {
            carpool.viewCarpool();
            cout << "------------------------" << endl;
        }
    }
}

void registerUser() {
    string username, password, fullName, phoneNumber, email, idType, idNumber;
    int creditPoints = 10;  // Default credit points for a new user
    bool verified = false; // New users are not verified by default

    cout << "Enter username: ";
    cin >> username;

    User tempUser("", "", "", "", "", "", "", 0);  // Temporary user for password check
    do {
        cout << "Enter password: ";
        cin >> password;
    } while (!tempUser.checkPasswordPolicy(password));

    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, fullName);
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter ID type (Citizen ID/Passport): ";
    cin >> idType;
    cout << "Enter ID number: ";
    cin >> idNumber;

    User newUser(username, password, fullName, phoneNumber, email, idType, idNumber, creditPoints, verified);
    users.push_back(newUser);

    cout << "Registration successful!" << endl;
}

void welcomeScreen() {
    cout << "\nUse the app as:" << endl;
    cout << "1. Guest" << endl;
    cout << "2. Member" << endl;
    cout << "3. Admin" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            guestMenu();  // Guests can view carpools and register as a member
            break;
        case 2:
            memberMenu(users[0]);  // Login as a member or register as a member
            break;
        case 3:
            loginAsAdmin();  // Login as an admin
            break;
        case 4:
            saveData();
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
}

void guestMenu() {
    int choice;
    std::cout << "\nGuest Menu:\n";
    std::cout << "1. View Carpools (with passenger-rating <= 3)\n";
    std::cout << "2. Register as a Member\n";
    std::cout << "3. Go Back to Main Menu\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            viewCarpoolsAsGuest();
            break;
        case 2:
            registerUser();
            break;
        case 3:
            return;
        case 4:
            saveData();
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
    }
}

void memberMenu(User& user) {
    int choice;
    std::cout << "\nMember Menu:\n";
    std::cout << "1. Create Carpool\n";
    std::cout << "2. View Carpools\n";
    std::cout << "3. Search and Book Carpool\n";
    std::cout << "4. Rate a Passenger\n";
    std::cout << "5. Cancel Booking\n";
    std::cout << "6. Verify Account\n";
    std::cout << "7. View Dashboard\n";
    std::cout << "8. Top Up Credits\n";
    std::cout << "9. Exit\n";
    std::cin >> choice;

    switch (choice) {
        case 1:
            createCarpool(user);
            break;
        case 2:
            viewCarpools();
            break;
        case 3:
            searchAndBookCarpool(user);
            break;
        case 4: {
            std::string passengerUsername;
            std::cout << "Enter the passenger's username to rate: ";
            std::cin >> passengerUsername;
            bool found = false;
            for (auto& passenger : users) {
                if (passenger.getUsername() == passengerUsername) {
                    ratePassenger(passenger);
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << "Passenger not found!\n";
            }
            break;
        }
        case 5:
            cancelBooking();
            break;
        case 6:
            verifyUser(user);
            break;
        case 7:
            displayDashboard(user);
            break;
        case 8:
            topUpCredit(user);
            break;
        case 9:
            std::cout << "Exiting Member Menu.\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
    }
}

void loginAsAdmin() {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;

    if (username == "admin" && password == "adminpass") {
        std::cout << "Admin login successful!\n";
        adminMenu();  // Call the admin menu
    } else {
        std::cout << "Invalid admin credentials!\n";
    }
}

void adminMenu() {
    int choice;
    std::cout << "Admin Menu\n";
    std::cout << "1. View All Users\n";
    std::cout << "2. View All Carpools\n";
    std::cout << "3. Exit\n";
    std::cin >> choice;

    switch (choice) {
        case 1:
            for (const auto& user : users) {
                user.viewProfile();
                std::cout << std::endl;
            }
            break;
        case 2:
            viewCarpools();
            break;
        case 3:
            std::cout << "Exiting Admin Menu.\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
    }
}

void createCarpool(User& user) {
    std::string depLocation, dest, date, time;
    int seats, points;
    std::cout << "Enter departure location: ";
    std::cin.ignore();
    std::getline(std::cin, depLocation);
    std::cout << "Enter destination: ";
    std::getline(std::cin, dest);
    std::cout << "Enter date (e.g., 2023-09-20): ";
    std::cin >> date;
    std::cout << "Enter time (e.g., 10:00): ";
    std::cin >> time;
    std::cout << "Enter available seats: ";
    std::cin >> seats;
    std::cout << "Enter contribution points per passenger: ";
    std::cin >> points;

    Carpool newCarpool(depLocation, dest, date, time, seats, points);
    carpools.push_back(newCarpool);
    std::cout << "Carpool created successfully!\n";
}

void viewCarpools() {
    if (carpools.empty()) {
        std::cout << "No carpools available at the moment.\n";
        return;
    }

    std::cout << "List of available carpools:\n";
    for (const auto& carpool : carpools) {
        carpool.viewCarpool();
        std::cout << "------------------------\n";
    }
}

void ratePassenger(User& passenger) {
    int score;
    std::string comment;

    std::cout << "Enter a rating for " << passenger.getUsername() << " (1-5): ";
    std::cin >> score;
    if (score < 1 || score > 5) {
        std::cout << "Invalid rating. Please enter a value between 1 and 5.\n";
        return;
    }

    std::cin.ignore();
    std::cout << "Leave a comment: ";
    std::getline(std::cin, comment);

    passenger.addRating(score, comment);
    std::cout << "Rating added successfully!\n";
}

void cancelBooking() {
    std::string depLocation;
    std::cout << "Enter the departure location of the carpool to cancel booking: ";
    std::cin.ignore();
    std::getline(std::cin, depLocation);

    for (auto& carpool : carpools) {
        if (carpool.getDepartureLocation() == depLocation) {
            carpool.cancelBooking();
            return;
        }
    }
    std::cout << "No carpool found with the specified departure location.\n";
}

void verifyUser(User& user) {
    if (user.isVerified()) {
        std::cout << "User " << user.getUsername() << " is already verified.\n";
        return;
    }

    std::string idNumber;
    std::cout << "Enter your ID number for verification: ";
    std::cin >> idNumber;

    if (idNumber == user.getIdNumber()) {
        user.verify();
        std::cout << "Verification successful. User " << user.getUsername() << " is now verified.\n";
    } else {
        std::cout << "Verification failed. ID number does not match.\n";
    }
}

void displayDashboard(User& user) {
    std::cout << "\n===== Activity Dashboard =====\n";

    // Display active carpool listings created by the member
    std::cout << "Active Carpool Listings\n";
    std::cout << "------------------------\n";
    bool hasListings = false;
    for (const auto& carpool : carpools) {
        if (carpool.getDepartureLocation() == user.getUsername()) {
            std::cout << "Listing: " << carpool.getDepartureLocation()
                      << " -> " << carpool.getDestination()
                      << " | Seats Available: " << carpool.getAvailableSeats() << "\n";
            hasListings = true;
        }
    }
    if (!hasListings) {
        std::cout << "No active carpool listings.\n";
    }

    // Display active bookings made by the member
    std::cout << "\nActive Bookings\n";
    std::cout << "---------------\n";
    bool hasBookings = false;
    for (const auto& carpool : carpools) {
        if (carpool.hasSeatBooked() && carpool.isBookingAccepted()) {
            std::cout << "Booking: " << carpool.getDepartureLocation()
                      << " -> " << carpool.getDestination()
                      << " | Status: " << (carpool.isBookingAccepted() ? "Accepted" : "Pending") << "\n";
            hasBookings = true;
        }
    }
    if (!hasBookings) {
        std::cout << "No active bookings.\n";
    }

    std::cout << "=============================\n";
}

void topUpCredit(User& user) {
    std::string password;
    std::cout << "Enter your password to authorize the transaction: ";
    std::cin >> password;

    if (password != user.getPassword()) {
        std::cout << "Incorrect password. Transaction failed.\n";
        return;
    }

    int amount;
    std::cout << "Enter the amount of credit points you wish to purchase: ";
    std::cin >> amount;
    user.topUpCredits(amount);
}

void searchAndBookCarpool(User& user) {
    std::string depLocation, dest, date;
    std::cout << "Enter departure location: ";
    std::cin.ignore();
    std::getline(std::cin, depLocation);
    std::cout << "Enter destination: ";
    std::getline(std::cin, dest);
    std::cout << "Enter date (e.g., 2023-09-20): ";
    std::cin >> date;

    bool found = false;
    for (auto& carpool : carpools) {
        if (carpool.getDepartureLocation() == depLocation && carpool.getDestination() == dest && carpool.getDate() == date) {
            carpool.viewCarpool();
            found = true;
            std::cout << "Attempting to book a seat...\n";
            carpool.bookSeat(user);
            break;
        }
    }
    if (!found) {
        std::cout << "No carpools found matching your criteria.\n";
    }
}