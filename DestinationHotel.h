#ifndef DESTINATIONHOTEL_H_INCLUDED
#define DESTINATIONHOTEL_H_INCLUDED


#include <iostream>
#include <string>
#include "Destination.h"
#include "CSVHandler.h"

using namespace std;

class DestinationHotel : public Destination {
public:
    // Constructor
    DestinationHotel(string countryName) : Destination(countryName) {}

    // Method to display hotels for a country
    void displayHotelsForCountry() {
        string hotelsFile;

        if (getName() == "Indonesia") {
            hotelsFile = "Indonesia.csv";
            cout << "1. Verse Luxe Hotel" << endl;
            cout << "2. Miers Kuningan" << endl;
            cout << "3. Anara Airport Hotel" << endl;
            cout << "4. All Seasons Hotel" << endl;
            cout << "5. Merlynn Park Hotel" << endl;
        } else if (getName() == "Japan") {
            hotelsFile = "Japan.csv";
            cout << "1. Sotetsu Fresa Inn" << endl;
            cout << "2. APA Hotel" << endl;
            cout << "3. Hundred Stay" << endl;
            cout << "4. Shinjuku Washington Hotel" << endl;
            cout << "5. KOKO Hotel" << endl;
            cout << "6. Shinagawa Prince Hotel" << endl;
        } else if (getName() == "Korea") {
            hotelsFile = "Korea.csv";
            cout << "1. Roynet Hotel" << endl;
            cout << "2. Migliore Hotel" << endl;
            cout << "3. Seoul Garden Hotel" << endl;
            cout << "4. K-Grand Hotel Seoul" << endl;
            cout << "5. President hotel" << endl;
        } else if (getName() == "China") {
            hotelsFile = "China.csv";
            cout << "1. The St. Regis Beijing" << endl;
            cout << "2. Kerry Hotel" << endl;
            cout << "3. Sunworld Hotel" << endl;
            cout << "4. Novotel Peace" << endl;
            cout << "5. Howard Johnson" << endl;
            cout << "6. Orange Hotel" << endl;
        } else if (getName() == "Singapore") {
            hotelsFile = "Singapore.csv";
            cout << "1. Oasia Hotel" << endl;
            cout << "2. Hotel Boss" << endl;
            cout << "3. Mercure Singapore" << endl;
            cout << "4. Hotel Mi Rochor" << endl;
            cout << "5. M Hotel" << endl;
        } else if (getName() == "Malaysia") {
            hotelsFile = "Malaysia.csv";
            cout << "1. Deface Platinum" << endl;
            cout << "2. Grand Milennium" << endl;
            cout << "3. One World Hotel" << endl;
            cout << "4. The Majestic Hotel" << endl;
            cout << "5. Hilton Garden Inn" << endl;
        } else {
            cout << "Invalid country selected." << endl;
            return;
        }

        string hotelName;
        cout << "Enter the hotel name: ";
        getline(cin, hotelName);

        CSVHandler::searchAndDisplayHotelDetails(hotelName, hotelsFile);
    }
};

#endif // DESTINATIONHOTEL_H_INCLUDED
