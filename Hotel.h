#ifndef HOTEL_H_INCLUDED
#define HOTEL_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "Room.h"

using namespace std;

class Hotel {
private:
    string name;
    string country;
    vector<Room> rooms;

public:
    // Constructor
    Hotel(string n, string c){
        name = n;
        country = c;
    }

    // Getters
    string getName() const {
        return name;
    }

    string getCountry() const {
        return country;
    }

    vector<Room> getRooms() const {
        return rooms;
    }

    // Setters
    void setName(const string& n) {
        name = n;
    }

    void setCountry(const string& c) {
        country = c;
    }

    void setRooms(const vector<Room>& r) {
        rooms = r;
    }

    // Add room to the hotel
    void addRoom(const Room& room) {
        rooms.push_back(room);
    }

    // Display rooms
    void displayRooms() const {
        cout << "\nAvailable rooms in " << name << ":\n";
        for (const auto& room : rooms) {
            room.displayDetails();
        }
    }
};

#endif // HOTEL_H_INCLUDED
