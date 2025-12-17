#ifndef BOOKINGMANAGER_H_INCLUDED
#define BOOKINGMANAGER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class BookingManager {
public:
    void viewBookingHistory(const string& username, const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open bookings file.\n";
            return;
        }

        string line;
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            // https://stackoverflow.com/questions/30352819/using-getline-and-istringstream-to-read-data-from-csv-file

            string user, checkInDate, checkOutDate, hotelName, roomType,
            roomsBookedStr, pricePerNightStr, nightsStr;

            getline(ss, user, ',');
            getline(ss, checkInDate, ',');
            getline(ss, checkOutDate, ',');
            getline(ss, hotelName, ',');
            getline(ss, roomType, ',');
            getline(ss, roomsBookedStr, ',');
            getline(ss, pricePerNightStr, ',');
            getline(ss, nightsStr, ',');

            if (user == username) {  // Check if the user matches the logged-in username
                found = true;
                int roomsBooked = stoi(roomsBookedStr);
                double pricePerNight = stod(pricePerNightStr);
                int nights = stoi(nightsStr);

                double totalPrice = roomsBooked * pricePerNight * nights;

                cout << "\n-------------------------------------\n";
                cout << "Booking Details:\n";
                cout << "Hotel: " << hotelName
                     << "\nRoom Type: " << roomType
                     << "\nCheck-In: " << checkInDate
                     << "\nCheck-Out: " << checkOutDate
                     << "\nRooms Booked: " << roomsBooked
                     << "\nPrice Per Night: $" << pricePerNight
                     << "\nTotal Price: $" << fixed << setprecision(2) << totalPrice
                     << "\n-------------------------------------\n";
            }
        }

        if (!found) {
            cout << "No bookings found for " << username << endl;
        }

        file.close();
    }

    bool isDateConflict(const string& checkInDate, const string& checkOutDate, const string& username) {
        ifstream file("bookings.csv");
        if (!file.is_open()) {
            cout << "Failed to open bookings file.\n";
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string user, existingCheckIn, existingCheckOut, hotelName,
            roomType, roomsBookedStr, pricePerNightStr, nightsStr;

            getline(ss, user, ',');
            getline(ss, existingCheckIn, ',');
            getline(ss, existingCheckOut, ',');
            getline(ss, hotelName, ',');
            getline(ss, roomType, ',');
            getline(ss, roomsBookedStr, ',');
            getline(ss, pricePerNightStr, ',');
            getline(ss, nightsStr, ',');

            if (user == username) {  // Only check bookings of the logged-in user
                if (isDateOverlap(existingCheckIn, existingCheckOut, checkInDate, checkOutDate)) {
                    file.close();
                    return true;  // Conflict found for the logged-in user
                }
            }
        }

        file.close();
        return false;  // No conflict for the logged-in user
    }

    bool isDateOverlap(const string& start1, const string& end1, const string& start2, const string& end2) {
        // Convert string dates to integer form (YYYYMMDD)
        int start1Int = dateToInt(start1);
        int end1Int = dateToInt(end1);
        int start2Int = dateToInt(start2);
        int end2Int = dateToInt(end2);

        if (!(end1Int < start2Int || start1Int > end2Int)) {
            return true;  // Dates overlap
        }
        return false;
    }

    int dateToInt(const string& date) {
        int day, month, year;
        sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
        return year * 10000 + month * 100 + day;  // Convert to YYYYMMDD format
    }

    void addBooking(const Booking& booking) {
        ofstream file("bookings.csv", ios::app);
        if (file.is_open()) {
            file << booking.getUsername() << ","
                 << booking.getCheckInDate() << ","
                 << booking.getCheckOutDate() << ","
                 << booking.getHotelName() << ","
                 << booking.getRoomType() << ","
                 << booking.getRoomsBooked() << ","
                 << booking.getPricePerNight() << ","
                 << booking.getNights() << endl;
            file.close();
        } else {
            cout << "Failed to open bookings file for writing.\n";
        }
    }
};

#endif // BOOKINGMANAGER_H_INCLUDED
