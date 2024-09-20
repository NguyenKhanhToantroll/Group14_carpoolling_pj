#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include "User.h"
#include "Carpool.h"
#include <vector>

extern std::vector<User> users;
extern std::vector<Carpool> carpools;

// Function declarations
void guestMenu();
void memberMenu(User& user);
void loginAsAdmin();
void adminMenu();
void welcomeScreen();
void saveData();
void loadData();
void viewCarpoolsAsGuest();
void registerUser();
void createCarpool(User& user);
void viewCarpools();
void searchAndBookCarpool(User& user);
void cancelBooking();
void verifyUser(User& user);
void displayDashboard(User& user);
void topUpCredit(User& user);
void ratePassenger(User& passenger);

#endif // UTILITYFUNCTIONS_H