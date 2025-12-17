#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

class User {
private:
    string username;
    string password;
    string firstName;
    string lastName;
    string icNumber;
    string email;
    string phoneNumber;
    string country;
    string fullName;

    bool isValidEmail(string e) {
        return e.find('@') != string::npos && e.find('.') != string::npos;
        // https://www.geeksforgeeks.org/stringnpos-in-c-with-examples/
    }

    void generateFullName() {
        fullName = firstName + " " + lastName;
    }

public:
    User(string u, string p, string fName, string lName,
         string ic, string mail, string phone, string ctry) {
        username = u;
        password = p;
        firstName = fName;
        lastName = lName;
        icNumber = ic;
        email = mail;
        phoneNumber = phone;
        country = ctry;
        generateFullName();
    }

    // Getters
    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    string getName() const {
        return fullName;
    }

    string getEmail() const {
        return email;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getCountry() const {
        return country;
    }

    string getICNumber() const {
        return icNumber;
    }

    // Setters
    void setUsername(const string& u) {
        username = u;
    }

    void setPassword(const string& p) {
        password = p;
    }

    void setFirstName(const string& fName) {
        firstName = fName;
        generateFullName();
    }

    void setLastName(const string& lName) {
        lastName = lName;
        generateFullName();
    }

    void setICNumber(const string& ic) {
        icNumber = ic;
    }

    void setEmail(const string& e) {
        if (isValidEmail(e)) {
            email = e;
        } else {
            throw invalid_argument("Invalid email address.");
        }
    }

    void setPhoneNumber(const string& phone) {
        phoneNumber = phone;
    }

    void setCountry(const string& ctry) {
        country = ctry;
    }

    // Other member functions
    bool validatePassword(string inputPassword) const {
        return password == inputPassword;
    }

    void display() const {
        cout << "Username: " << username << endl;
        cout << "Name: " << fullName << endl;
        cout << "IC Number: " << icNumber << endl;
        cout << "Email: " << email << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Country: " << country << endl;
    }

    static void loadUsersFromCSV(vector<User>& users, const string& filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            // https://stackoverflow.com/questions/30352819/using-getline-and-istringstream-to-read-data-from-csv-file
            string username, password, firstName, lastName, icNumber, email, phoneNumber, country;

            if (!getline(iss, username, ',') || !getline(iss, password, ',') || !getline(iss, firstName, ',') ||
                !getline(iss, lastName, ',') || !getline(iss, icNumber, ',') || !getline(iss, email, ',') ||
                !getline(iss, phoneNumber, ',') || !getline(iss, country, ',')) {
                cerr << "Malformed CSV line: " << line << endl;
                // https://www.geeksforgeeks.org/cerr-standard-error-stream-object-in-cpp/
                continue;
            }

            users.emplace_back(username, password, firstName, lastName, icNumber, email, phoneNumber, country);
        }
    }

    static void saveUsersToCSV(const vector<User>& users, const string& filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        for (const auto& user : users) {
            outFile << user.username << "," << user.password << ","
            << user.firstName << "," << user.lastName << ","
            << user.icNumber << "," << user.email << ","
            << user.phoneNumber << "," << user.country << endl;
        }
    }

    static string loginUser(const vector<User>& users) {
        string username, password;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        for (const auto& user : users) {
            if (user.getUsername() == username && user.validatePassword(password)) {
                cout << "Login successful!" << endl;
                return username;
            }
        }
        cout << "Invalid username or password." << endl;
        return "";
    }

    static void signUpUser(vector<User>& users) {
        string username, password, firstName, lastName, icNumber, email, phoneNumber, country;

        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter First Name: ";
        cin >> firstName;
        cout << "Enter Last Name: ";
        cin >> lastName;
        cout << "Enter IC Number: ";
        cin >> icNumber;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Phone Number: ";
        cin >> phoneNumber;
        cout << "Enter Country: ";
        cin >> country;

        users.emplace_back(username, password, firstName, lastName, icNumber, email, phoneNumber, country);
        saveUsersToCSV(users, "users.csv");

        cout << "Sign-up successful! You can now log in." << endl;
    }
};

#endif // USER_H_INCLUDED
