#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Room {
private:
    string type;
    double price;
    int capacity;
    vector<string> amenities;

public:
    // Constructor
    Room(string t, double p, int c, vector<string> a){
        type = t;
        price = p;
        capacity = c;
        amenities = a;
    }

    // Getters
    string getType() const {
        return type;
    }

    double getPrice() const {
        return price;
    }

    int getCapacity() const {
        return capacity;
    }

    vector<string> getAmenities() const {
        return amenities;
    }

    // Setters
    void setType(const string& t) {
        type = t;
    }

    void setPrice(double p) {
        if (p >= 0) { // Validate that price is positive
            price = p;
        } else {
            cerr << "Price cannot be negative." << endl;
        }
    }

    void setCapacity(int c) {
        if (c > 0) { // Validate that capacity is positive
            capacity = c;
        } else {
            cerr << "Capacity must be greater than zero." << endl;
        }
    }

    void setAmenities(const vector<string>& a) {
        amenities = a;
    }

    // Display room details
    void displayDetails() const {
        cout << "Room Type: " << type << endl;
        cout << "Price per night: $" << fixed << setprecision(2) << price << endl;
        cout << "Capacity: " << capacity << " guests" << endl;
        cout << "Amenities: ";
        for (size_t i = 0; i < amenities.size(); ++i) {
            cout << amenities[i];
            if (i != amenities.size() - 1) cout << ", ";
        }
        cout << endl;
    }
};

#endif // ROOM_H_INCLUDED
