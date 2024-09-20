#include "User.h"

User::User(string u, string p, string name, string phone, string mail, string idT, string idN, int credit, bool v, bool admin)
    : username(u), password(p), fullName(name), phoneNumber(phone), email(mail), idType(idT), idNumber(idN), creditPoints(credit), verified(v), isAdmin(admin) {
    ratings.push_back(-1);
}

void User::addRating(int score, const string& review) {
    if (ratings.size() == 1 && ratings[0] == -1) {
        ratings.clear();
    }
    ratings.push_back(score);
    reviews.push_back(review);
    cout << "Rating added successfully!\n";
}

double User::getAverageRating() const {
    if (ratings.empty()) return -1;
    double sum = 0;
    for (int rating : ratings) {
        sum += rating;
    }
    return sum / ratings.size();
}

void User::viewReviews() const {
    cout << "Reviews for " << username << ":\n";
    for (size_t i = 0; i < reviews.size(); ++i) {
        cout << "Rating: " << ratings[i] << " - Comment: " << reviews[i] << "\n";
    }
}

double User::getRating() const {
    return getAverageRating();
}

bool User::checkAdmin() const {
    return isAdmin;
}

void User::viewProfile() const {
    cout << "Username: " << username << endl;
    cout << "Full Name: " << fullName << endl;
    cout << "Phone: " << phoneNumber << endl;
    cout << "Email: " << email << endl;
    cout << "ID Type: " << idType << " | ID Number: " << idNumber << endl;
    cout << "Credit Points: " << creditPoints << endl;
    cout << "Verification Status: " << (verified ? "Verified" : "Not Verified") << endl;
    cout << "Admin Privileges: " << (isAdmin ? "Yes" : "No") << endl;
    cout << "Average Rating: " << getRating() << endl;
}

bool User::checkPasswordPolicy(const string& pass) const {
    if (pass.length() < 6) {
        cout << "Password must be at least 6 characters long." << endl;
        return false;
    }
    bool hasDigit = false, hasUpper = false;
    for (char ch : pass) {
        if (isdigit(ch)) hasDigit = true;
        if (isupper(ch)) hasUpper = true;
    }
    if (!hasDigit || !hasUpper) {
        cout << "Password must contain at least 1 digit and 1 uppercase letter." << endl;
        return false;
    }
    return true;
}

int User::getCreditPoints() const {
    return creditPoints;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User::getIdNumber() const {
    return idNumber;
}

bool User::isVerified() const {
    return verified;
}

void User::verify() {
    verified = true;
}

void User::topUpCredits(int amount) {
    creditPoints += amount;
    cout << "You have successfully purchased " << amount << " credit points." << endl;
}

void User::deductEntryFee() {
    if (creditPoints >= 10) {
        creditPoints -= 10;
    } else {
        cout << "Insufficient credit points! Please top up your account." << endl;
    }
}

void User::saveToFile(ofstream &out) const {
    out << username << " " << password << " " << fullName << " " << phoneNumber << " " << email << " "
        << idType << " " << idNumber << " " << creditPoints << " " << verified << "\n";
}

User User::loadFromFile(ifstream &in) {
    string u, p, name, phone, mail, idT, idN;
    int credit;
    bool v;
    in >> u >> p >> name >> phone >> mail >> idT >> idN >> credit >> v;
    return User(u, p, name, phone, mail, idT, idN, credit, v);
}