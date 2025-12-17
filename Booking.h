#ifndef BOOKING_H_INCLUDED
#define BOOKING_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Booking {
private:
    string username;
    string checkInDate;
    string checkOutDate;
    string hotelName;
    string roomType;
    int roomsBooked;
    double pricePerNight;
    int nights;

public:
    // Constructor
    Booking(const string& u, const string& checkin, const string& checkout,
            const string& hotel, const string& room, int rooms, double price, int nightsBooked){
        username = u;
        checkInDate = checkin;
        checkOutDate = checkout;
        hotelName = hotel;
        roomType = room;
        roomsBooked = rooms;
        pricePerNight = price;
        nights = nightsBooked;
    }

    // Setters
    void setUsername(const string& u) {
        username = u;
    }

    void setCheckInDate(const string& checkin) {
        checkInDate = checkin;
    }

    void setCheckOutDate(const string& checkout) {
        checkOutDate = checkout;
    }

    void setHotelName(const string& hotel) {
        hotelName = hotel;
    }

    void setRoomType(const string& room) {
        roomType = room;
    }

    void setRoomsBooked(int rooms) {
        roomsBooked = rooms;
    }

    void setPricePerNight(double price) {
        pricePerNight = price;
    }

    void setNights(int nightsBooked) {
        nights = nightsBooked;
    }

    // Getters
    string getUsername() const {
        return username;
    }

    string getCheckInDate() const {
        return checkInDate;
    }

    string getCheckOutDate() const {
        return checkOutDate;
    }

    string getHotelName() const {
        return hotelName;
    }

    string getRoomType() const {
        return roomType;
    }

    int getRoomsBooked() const {
        return roomsBooked;
    }

    double getPricePerNight() const {
        return pricePerNight;
    }

    int getNights() const {
        return nights;
    }

    // Display booking details
    void display() const {
        cout << "Username: " << username << endl;
        cout << "Check-In Date: " << checkInDate << endl;
        cout << "Check-Out Date: " << checkOutDate << endl;
        cout << "Hotel: " << hotelName << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Rooms Booked: " << roomsBooked << endl;
        cout << "Price Per Night: $" << fixed << setprecision(2) << pricePerNight << endl;
        cout << "Total Price: $" << fixed << setprecision(2) << (roomsBooked * pricePerNight * nights) << endl;
    }

    // Save booking details to a CSV file
    static void saveBookingToCSV(const string& filename, const Booking& booking) {
        ofstream outFile(filename, ios::app);
        if (!outFile.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            // https://www.geeksforgeeks.org/cerr-standard-error-stream-object-in-cpp/
            return;
        }

        outFile << booking.username << ","
                << booking.checkInDate << ","
                << booking.checkOutDate << ","
                << booking.hotelName << ","
                << booking.roomType << ","
                << booking.roomsBooked << ","
                << booking.pricePerNight << ","
                << booking.nights << endl;

        outFile.close();
    }
};

#endif // BOOKING_H_INCLUDED
