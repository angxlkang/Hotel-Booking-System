#ifndef PAYMENT_H_INCLUDED
#define PAYMENT_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

class Payment {
public:
    virtual void makePayment(double amount, int checkInMonth, int checkInYear) = 0;
    virtual ~Payment() {}
};

class CreditCardPayment : public Payment {
private:
    string cardHolder;
    string cardNumber;
    string expirationDate;
    string cvv;

public:
    CreditCardPayment(const string& cardNumber, const string& cardHolder,
                      const string& expirationDate, const string& cvv)
        : cardHolder(cardHolder), cardNumber(cardNumber), expirationDate(expirationDate), cvv(cvv) {}

    // Getters
    string getCardHolder() const {
        return cardHolder;
    }

    string getCardNumber() const {
        return cardNumber;
    }

    string getExpirationDate() const {
        return expirationDate;
    }

    string getCVV() const {
        return cvv;
    }

    // Setters
    void setCardHolder(const string& holder) {
        cardHolder = holder;
    }

    void setCardNumber(const string& number) {
        cardNumber = number;
    }

    void setExpirationDate(const string& date) {
        expirationDate = date;
    }

    void setCVV(const string& code) {
        cvv = code;
    }

    // Checks if credit card number is valid (16 digits)
    bool isValidCreditCard(const string& cardNumber) const {
        if (cardNumber.length() != 16) {
            return false;
        }
        for (char c : cardNumber) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    // Checks if expiration date is valid
    bool isValidExpirationDate(int checkInMonth, int checkInYear, const string& expirationDate) const {
        size_t slashPos = expirationDate.find('/');
        if (slashPos == string::npos) {
            return false;
        }

        try {
            int expMonth = stoi(expirationDate.substr(0, slashPos));
            int expYear = stoi(expirationDate.substr(slashPos + 1));

            if (expYear < checkInYear || (expYear == checkInYear && expMonth < checkInMonth)) {
                return false;
            }
            return true;
        } catch (const exception&) {
            return false;
        }
    }

    void makePayment(double amount, int checkInMonth, int checkInYear) override {
        cout << "\nProcessing credit card payment...\n";
        cout << "Card Holder: " << cardHolder << endl;
        cout << "Amount to be paid: $" << fixed << setprecision(2) << amount << endl;
        cout << "Payment successful!" << endl;
    }
};

class EWalletPayment : public Payment {
private:
    string walletID;
    string walletProvider;

public:
    EWalletPayment(const string& walletID, const string& walletProvider)
        : walletID(walletID), walletProvider(walletProvider) {}

    // Getters
    string getWalletID() const {
        return walletID;
    }

    string getWalletProvider() const {
        return walletProvider;
    }

    // Setters
    void setWalletID(const string& id) {
        walletID = id;
    }

    void setWalletProvider(const string& provider) {
        walletProvider = provider;
    }

    bool isValidWalletID(const string& walletID) const {
        if (walletID.length() != 8) {
            return false;
        }
        for (char c : walletID) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

    void makePayment(double amount, int checkInMonth, int checkInYear) override {
        cout << "\nProcessing e-wallet payment...\n";
        cout << "Wallet Provider: " << walletProvider << endl;
        cout << "Amount to be paid: $" << fixed << setprecision(2) << amount << endl;
        cout << "Payment successful!" << endl;
    }
};

class CashOnDeliveryPayment : public Payment {
private:
    string deliveryAddress;

public:
    CashOnDeliveryPayment(const string& deliveryAddress)
        : deliveryAddress(deliveryAddress) {}

    // Getter
    string getDeliveryAddress() const {
        return deliveryAddress;
    }

    // Setter
    void setDeliveryAddress(const string& address) {
        deliveryAddress = address;
    }

    void makePayment(double amount, int checkInMonth, int checkInYear) override {
        cout << "\nCash on delivery payment selected.\n";
        cout << "Delivery Address: " << deliveryAddress << endl;
        cout << "Amount to be paid upon delivery: $" << fixed << setprecision(2) << amount << endl;
        cout << "Payment pending upon delivery.\n";
    }
};

#endif // PAYMENT_H_INCLUDED
