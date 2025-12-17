#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

// Check if a year is a leap year
bool checkYear(int y) {
    return (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0));
}

// Generate a new date by adding days to an existing date
Date generateDate(int day, int month, int year, int skip) {
    int daysInMonth;
    int newMonth = month;
    int newYear = year;
    int newDay = day + skip;

    if (month == 2)
        daysInMonth = (checkYear(year)) ? 29 : 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        daysInMonth = 30;
    else
        daysInMonth = 31;

    while (newDay > daysInMonth) {
        newDay -= daysInMonth;
        newMonth++;
        if (newMonth > 12) {
            newMonth = 1;
            newYear++;
        }
        if (newMonth == 2)
            daysInMonth = (checkYear(newYear)) ? 29 : 28;
        else if (newMonth == 4 || newMonth == 6 || newMonth == 9 || newMonth == 11)
            daysInMonth = 30;
        else
            daysInMonth = 31;
    }

    return {newDay, newMonth, newYear};
}

// Function to validate country input
string validateCountry() {
    cout << "Enter destination country (China, Korea, Japan, Indonesia, Malaysia, Singapore): ";
    string country;
    getline(cin, country);

    if (country == "China" || country == "Korea" || country == "Japan" ||
        country == "Indonesia" || country == "Malaysia" || country == "Singapore") {
        return country;
    } else {
        throw invalid_argument("Invalid country. Please enter one of the allowed countries.");
    }
}

// Function to validate room type input
string validateRoomType() {
    cout << "Choose room type (Deluxe, Standard, Suite): ";
    string roomType;
    getline(cin, roomType);

    if (roomType == "Deluxe" || roomType == "Standard" || roomType == "Suite") {
        return roomType;
    } else {
        throw invalid_argument("Invalid room type. Please choose from Deluxe, Standard, or Suite.");
    }
}

// Function to validate date inputs
int validateDateInput(const string& prompt, int minValue, int maxValue) {
    cout << prompt;
    int value;
    cin >> value;

    if (value < minValue || value > maxValue) {
        throw out_of_range("Invalid input. Please enter a value within the allowed range.");
    }
    return value;
}

// Check if a date is valid
bool isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12) {
        return false;
    }

    int daysInMonth[] = {31, (checkYear(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }

    return true;
}

// Generate a range of dates in DD/MM/YYYY format
vector<string> generateDateRange(int startDay, int startMonth, int startYear,
                                 int endDay, int endMonth, int endYear) {
    vector<string> dateRange;

    while (startYear < endYear || (startYear == endYear && (startMonth < endMonth
           || (startMonth == endMonth && startDay <= endDay)))) {
        dateRange.push_back(to_string(startDay) + "/" + to_string(startMonth) + "/" + to_string(startYear));

        startDay++;
        int daysInMonth = (startMonth == 2)
                              ? (checkYear(startYear) ? 29 : 28)
                              : (startMonth == 4 || startMonth == 6 ||
                              startMonth == 9 || startMonth == 11 ? 30 : 31);

        if (startDay > daysInMonth) {
            startDay = 1;
            startMonth++;
            if (startMonth > 12) {
                startMonth = 1;
                startYear++;
            }
        }
    }

    return dateRange;
}

#endif // FUNCTIONS_H_INCLUDED
