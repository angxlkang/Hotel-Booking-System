#ifndef DESTINATION_H_INCLUDED
#define DESTINATION_H_INCLUDED

#include <iostream>
#include <vector>
#include <set>
#include "Hotel.h"

using namespace std;

class Destination {
private:
    string name;
    vector<Hotel> hotels;

public:
    // Constructor
    Destination(string n){
        name = n;
    }

    // Getters
    string getName() const {
        return name;
    }

    vector<Hotel> getHotels() const {
        return hotels;
    }

    // Setters
    void setName(const string& n) {
        name = n;
    }

    void setHotels(const vector<Hotel>& h) {
        hotels = h;
    }

    // Display unique hotels in the destination
    void displayHotels() const {
        cout << "\nHotels in " << name << ":\n";

        set<string> displayedHotels;

        int count = 0;
        for (const auto& hotel : hotels) {
            if (displayedHotels.find(hotel.getName()) == displayedHotels.end()) {
                displayedHotels.insert(hotel.getName());
                cout << count + 1 << ". " << hotel.getName() << endl;
                count++;
            }
        }
    }

    // Display rooms of a specific hotel
    void displayHotelRooms(size_t hotelIndex) const {
        if (hotelIndex < 1 || hotelIndex > hotels.size()) {
            cout << "Invalid hotel selection." << endl;
            return;
        }
        hotels[hotelIndex - 1].displayRooms();
    }
};

#endif // DESTINATION_H_INCLUDED
