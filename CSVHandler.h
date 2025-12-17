#ifndef CSVHANDLER_H_INCLUDED
#define CSVHANDLER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class CSVHandler {
private:
    string filename;
    map<string, vector<string>> hotelDetails;

public:
    // Static function to get room details from CSV file
    static bool getRoomDetails(const string& filename, const string& hotelName, int roomChoice,
                               string& roomType, double& pricePerNight, int& capacity, string& amenities) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            //  https://www.geeksforgeeks.org/cerr-standard-error-stream-object-in-cpp/
            return false;
        }

        string line, country, hotelNameCSV, roomTypeCSV, priceStr, capacityStr, amenitiesStr;
        int count = 0;

        while (getline(inFile, line)) {
            istringstream iss(line);
            // https://stackoverflow.com/questions/30352819/using-getline-and-istringstream-to-read-data-from-csv-file

            if (!getline(iss, country, ',') ||
                !getline(iss, hotelNameCSV, ',') ||
                !getline(iss, roomTypeCSV, ',') ||
                !getline(iss, priceStr, ',') ||
                !getline(iss, capacityStr, ',') ||
                !getline(iss, amenitiesStr, '\n')) {
                cerr << "Malformed CSV line: " << line << endl;
                continue;
            }

            if (hotelName == hotelNameCSV) {
                ++count;
                if (count == roomChoice) {
                    roomType = roomTypeCSV;
                    try {
                        pricePerNight = stod(priceStr);
                        capacity = stoi(capacityStr);
                    } catch (const invalid_argument& e) {
                        cerr << "Invalid number format in CSV: " << line << endl;
                        continue;
                    }
                    amenities = amenitiesStr;
                    inFile.close();
                    return true;
                }
            }
        }

        cerr << "Room choice not found for hotel: " << hotelName << endl;
        //  https://www.geeksforgeeks.org/cerr-standard-error-stream-object-in-cpp/
        inFile.close();
        return false;
    }

    // static function to
    static vector<string> parseAmenities(const string& amenitiesStr) {
        vector<string> amenities;
        istringstream ss(amenitiesStr);
        string amenity;

        while (getline(ss, amenity, ',')) {
            amenities.push_back(amenity);
        }

        return amenities;
    }

    static void searchAndDisplayHotelDetails(const string& hotelName, const string& filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            // https://www.geeksforgeeks.org/cerr-standard-error-stream-object-in-cpp/
            return;
        }

        string line, country, hotelNameCSV, roomType, priceStr, capacityStr, amenitiesStr;
        map<string, vector<Room>> rooms;

        while (getline(inFile, line)) {
            istringstream iss(line);

            if (!getline(iss, country, ',') ||
                !getline(iss, hotelNameCSV, ',') ||
                !getline(iss, roomType, ',') ||
                !getline(iss, priceStr, ',') ||
                !getline(iss, capacityStr, ',') ||
                !getline(iss, amenitiesStr, '\n')) {
                cerr << "Malformed CSV line: " << line << endl;
                // https://www.geeksforgeeks.org/cerr-standard-error-stream-object-in-cpp/
                continue;
            }

            if (hotelName == hotelNameCSV) {
                try {
                    double pricePerNight = stod(priceStr);
                    // https://www.geeksforgeeks.org/stdstod-stdstof-stdstold-c/
                    int capacity = stoi(capacityStr);
                    // https://www.geeksforgeeks.org/stdstoi-function-in-cpp/
                    vector<string> amenities = parseAmenities(amenitiesStr);

                    Room room(roomType, pricePerNight, capacity, amenities);
                    rooms[roomType].push_back(room);
                } catch (const invalid_argument& e) {
                    cerr << "Invalid number format in CSV: " << line << endl;
                    // https://www.geeksforgeeks.org/cerr-standard-error-stream-object-in-cpp/
                    continue;
                }
            }
        }

        inFile.close();

        if (rooms.empty()) {
            cout << "No rooms found for hotel: " << hotelName << endl;
        } else {
            cout << "\nAvailable room types in " << hotelName << ":\n";
            int count = 1;
            for (const auto& entry : rooms) {
                cout << count << ". " << entry.first << endl;
                for (const Room& room : entry.second) {
                    room.displayDetails();
                }
                ++count;
            }
        }
    }
};

#endif // CSVHANDLER_H_INCLUDED
