#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <set>
#include <map>

#include "User.h"
#include "Room.h"
#include "Hotel.h"
#include "Destination.h"
#include "DestinationHotel.h"
#include "CSVHandler.h"
#include "Booking.h"
#include "BookingManager.h"
#include "Functions.h"
#include "Payment.h"

using namespace std;

int main() {
    vector<User> users;
    vector<DestinationHotel> destinations;

    try {
        User::loadUsersFromCSV(users, "users.csv");

        string username = User::loginUser(users);
        if (username.empty()) {
            cout << "No user found with the entered credentials. ";
            cout << "Please sign up." << endl;
            User::signUpUser(users);
            username = User::loginUser(users);
        }

        string currentUser = username;
        BookingManager bookingManager;

        while (true) {
            try {
                cout << "\nMenu:" << endl;
                cout << "1. Search for hotels" << endl;
                cout << "2. Book hotel" << endl;
                cout << "3. View booking history" << endl;
                cout << "4. Exit" << endl;
                cout << "Choose an option: ";
                int menuChoice;
                cin >> menuChoice;

                if (menuChoice == 1) {
                    cin.ignore();
                    string country;
                    try {
                        country = validateCountry();
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                        continue;
                    }

                    DestinationHotel destination(country);
                    destination.displayHotelsForCountry();

                } else if (menuChoice == 2) {
                    cin.ignore();
                    string country;
                    try {
                        country = validateCountry();
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                        continue;
                    }

                    cout << "Enter the hotel name: ";
                    string hotelName;
                    getline(cin, hotelName);

                    string roomType;
                    try {
                        roomType = validateRoomType();
                    } catch (const invalid_argument& e) {
                        cout << "Error: " << e.what() << endl;
                        continue;
                    }

                    int day, month, year;
                    do {
                        cout << "Enter check-in month (1-12): ";
                        cin >> month;

                        if (month < 1 || month > 12) {
                            cout << "Invalid month. ";
                            cout << "Please enter a value between 1 and 12." << endl;
                        }
                    } while (month < 1 || month > 12);

                    do {
                        cout << "Enter check-in date: ";
                        cin >> day;

                        if (!isValidDate(day, month, year)) {
                            cout << "Invalid day for the given month and year. ";
                            cout << "Please re-enter." << endl;
                        }
                    } while (!isValidDate(day, month, year));

                    cout << "Enter check-in year: ";
                    cin >> year;
                    string checkInDate = to_string(day) + "/" + to_string(month) + "/" + to_string(year);

                    cout << "Enter the nights stayed: ";
                    int nights;
                    cin >> nights;
                    Date generatedCheckOut = generateDate(day, month, year, nights);
                    string checkOutDate = to_string(generatedCheckOut.day) + "/"
                        + to_string(generatedCheckOut.month) + "/" + to_string(generatedCheckOut.year);

                    cout << "Enter the number of rooms to book: ";
                    int roomsBooked;
                    cin >> roomsBooked;

                    double pricePerNight;
                    int capacity;
                    string amenities;

                    int roomChoice = 1;
                    if (CSVHandler::getRoomDetails(country + ".csv", hotelName, roomChoice,
                                                   roomType, pricePerNight, capacity, amenities)) {
                        if (bookingManager.isDateConflict(checkInDate, checkOutDate, currentUser)) {
                            cout << "Conflict detected: You already have a booking for these dates. ";
                            cout << "Please choose another date." << endl;
                            continue;
                        }

                        double totalPrice = pricePerNight * roomsBooked * nights;

                        cout << "-------------------------------------" << endl;
                        cout << "Booking Summary:" << endl;
                        cout << "Hotel: " << hotelName << endl;
                        cout << "Room Type: " << roomType << endl;
                        cout << "Check-In Date: " << checkInDate << endl;
                        cout << "Check-Out Date: " << checkOutDate << endl;
                        cout << "Amenities: " << amenities << endl;
                        cout << "Capacity: " << capacity << endl;
                        cout << "Price per Night: $" << fixed << setprecision(2) << pricePerNight << endl;
                        cout << "Rooms: " << roomsBooked << endl;
                        cout << "Total Price: $" << totalPrice << endl;
                        cout << "-------------------------------------" << endl;;

                        cout << "Confirm booking? (yes/no): ";
                        string confirmation;
                        cin.ignore();
                        getline(cin, confirmation);

                        if (confirmation == "yes") {
                            Booking booking(currentUser, checkInDate, checkOutDate, hotelName,
                                            roomType, roomsBooked, pricePerNight, nights);
                            bookingManager.addBooking(booking);

                            cout << "Booking confirmed! Thank you." << endl;

                            bool validPayment = false;

                            while (!validPayment) {
                                cout << "\nChoose a payment method:" << endl;
                                cout << "1. Credit Card" << endl;
                                cout << "2. E-Wallet" << endl;
                                cout << "3. Cash on Delivery" << endl;
                                cout << "Choose an option: ";
                                int paymentChoice;
                                cin >> paymentChoice;

                                if (paymentChoice == 1) {
                                    string cardNumber, cardHolder, expirationDate, cvv;
                                    cout << "Enter card number (16 digits): ";
                                    cin >> cardNumber;

                                    cout << "Enter card holder name: ";
                                    cin.ignore();
                                    getline(cin, cardHolder);

                                    cout << "Enter expiration date (MM/YYYY): ";
                                    cin >> expirationDate;

                                    cout << "Enter CVV (3 digits): ";
                                    cin >> cvv;

                                    CreditCardPayment creditCardPayment(cardNumber, cardHolder, expirationDate, cvv);

                                    if (!creditCardPayment.isValidCreditCard(cardNumber)) {
                                        cout << "Error: Invalid credit card number. It must be 16 digits." << endl;
                                    } else if (!creditCardPayment.isValidExpirationDate(month, year, expirationDate)) {
                                        cout << "Error: Expiration date must be later than the check-in date." << endl;
                                    } else {
                                        validPayment = true;
                                        creditCardPayment.makePayment(totalPrice, month, year);
                                    }

                                } else if (paymentChoice == 2) {
                                    string walletID, walletProvider;
                                    cout << "Enter wallet ID (8 digits): ";
                                    cin >> walletID;

                                    cout << "Enter wallet provider: ";
                                    cin.ignore();
                                    getline(cin, walletProvider);

                                    EWalletPayment eWalletPayment(walletID, walletProvider);

                                    if (!eWalletPayment.isValidWalletID(walletID)) {
                                        cout << "Error: Invalid wallet ID. It must be exactly 8 digits." << endl;
                                    } else {
                                        validPayment = true;
                                        eWalletPayment.makePayment(totalPrice, month, year);
                                    }

                                } else if (paymentChoice == 3) {
                                    string deliveryAddress;
                                    cout << "Enter delivery address: ";
                                    cin.ignore();
                                    getline(cin, deliveryAddress);

                                    CashOnDeliveryPayment cashOnDeliveryPayment(deliveryAddress);
                                    validPayment = true;
                                    cashOnDeliveryPayment.makePayment(totalPrice, month, year);

                                } else {
                                    cout << "Invalid choice. Exiting payment process." << endl;
                                    break;
                                }

                                if (!validPayment) {
                                    cout << "Please re-enter your payment details." << endl;
                                }
                            }

                        } else {
                            cout << "Booking cancelled." << endl;
                        }
                    } else {
                        cout << "Error: Room details not found or invalid." << endl;
                    }
                } else if (menuChoice == 3) {
                    bookingManager.viewBookingHistory(currentUser, "bookings.csv");
                } else if (menuChoice == 4) {
                    cout << "Exiting the application. Thank you for using the hotel booking system!" << endl;
                    break;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } catch (const exception& e) {
                cout << "Error: " << e.what() << "\nPlease try again." << endl;
            }
        }

    } catch (const exception& e) {
        cout << "Critical Error: " << e.what() << "\nExiting the application." << endl;
    }

    return 0;
}
