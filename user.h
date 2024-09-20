#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class User {
private:
    string username;
    string password;
    string fullName;
    string phoneNumber;
    string email;
    string idType;
    string idNumber;
    int creditPoints;
    bool verified;
    bool isAdmin;
    vector<int> ratings;
    vector<string> reviews;

public:
    User(string u, string p, string name, string phone, string mail, string idT, string idN, int credit, bool v = false, bool admin = false);
    void addRating(int score, const string& review);
    double getAverageRating() const;
    void viewReviews() const;
    double getRating() const;
    bool checkAdmin() const;
    void viewProfile() const;
    bool checkPasswordPolicy(const string& pass) const;
    int getCreditPoints() const;
    string getUsername() const;
    string getPassword() const;
    string getIdNumber() const;
    bool isVerified() const;
    void verify();
    void topUpCredits(int amount);
    void deductEntryFee();
    void saveToFile(ofstream &out) const;
    static User loadFromFile(ifstream &in);
};

#endif // USER_H
