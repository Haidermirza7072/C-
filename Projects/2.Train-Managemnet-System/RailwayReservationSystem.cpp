#include <iostream>
#include <cstring>
using namespace std;

class Train {
private:
    int trainNumber;
    char trainName[50];
    char source[50];
    char destination[50];
    char trainTime[10];
    static int trainCount;

public:
    // Default Constructor
    Train() {
        trainNumber = 0;
        strcpy(trainName, "");
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(trainTime, "");
    }

    // Parameterized Constructor
    Train(int number, const char* name, const char* src, const char* dest, const char* time) {
        trainNumber = number;
        strcpy(trainName, name);
        strcpy(source, src);
        strcpy(destination, dest);
        strcpy(trainTime, time);
        trainCount++;
    }

    // Destructor
    ~Train() {
        trainCount--;
    }

    // Getters
    int getTrainNumber() const { return trainNumber; }
    const char* getTrainName() const { return trainName; }
    const char* getSource() const { return source; }
    const char* getDestination() const { return destination; }
    const char* getTrainTime() const { return trainTime; }

    // Setters
    void setTrainNumber(int number) { trainNumber = number; }
    void setTrainName(const char* name) { strcpy(trainName, name); }
    void setSource(const char* src) { strcpy(source, src); }
    void setDestination(const char* dest) { strcpy(destination, dest); }
    void setTrainTime(const char* time) { strcpy(trainTime, time); }

    // Input train details
    void inputTrainDetails() {
        cout << "\nEnter Train Number: ";
        cin >> trainNumber;
        cin.ignore(); // clear buffer

        cout << "Enter Train Name: ";
        cin.getline(trainName, 50);

        cout << "Enter Source: ";
        cin.getline(source, 50);

        cout << "Enter Destination: ";
        cin.getline(destination, 50);

        cout << "Enter Train Time: ";
        cin.getline(trainTime, 10);

        trainCount++;
    }

    // Display train details
    void displayTrainDetails() const {
        cout << "\nTrain Number: " << trainNumber;
        cout << "\nTrain Name: " << trainName;
        cout << "\nSource: " << source;
        cout << "\nDestination: " << destination;
        cout << "\nTrain Time: " << trainTime << endl;
    }

    // Static method
    static int getTrainCount() {
        return trainCount;
    }
};

// Static variable initialization
int Train::trainCount = 0;

// ------------------------------------------------------------

class RailwaySystem {
private:
    Train trains[100];
    int totalTrains;

public:
    RailwaySystem() {
        totalTrains = 0;
    }

    void addTrain() {
        if (totalTrains >= 100) {
            cout << "\nCannot add more trains! Limit reached.\n";
            return;
        }
        trains[totalTrains].inputTrainDetails();
        totalTrains++;
        cout << "\nTrain added successfully!\n";
    }

    void displayAllTrains() const {
        if (totalTrains == 0) {
            cout << "\nNo train records found!\n";
            return;
        }
        for (int i = 0; i < totalTrains; i++) {
            cout << "\nTrain " << i + 1 << " details:";
            trains[i].displayTrainDetails();
        }
    }

    void searchTrainByNumber(int number) const {
        bool found = false;
        for (int i = 0; i < totalTrains; i++) {
            if (trains[i].getTrainNumber() == number) {
                cout << "\nTrain found!\n";
                trains[i].displayTrainDetails();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "\nTrain with number " << number << " not found!\n";
        }
    }
};

// ------------------------------------------------------------

int main() {
    RailwaySystem system;
    int choice;

    cout << "\n--- Railway Reservation System ---\n";

    do {
        cout << "\n--- Railway Reservation System Menu ---";
        cout << "\n1. Add New Train Record";
        cout << "\n2. Display All Train Records";
        cout << "\n3. Search Train by Number";
        cout << "\n4. Exit";
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.addTrain();
                break;
            case 2:
                system.displayAllTrains();
                break;
            case 3: {
                int num;
                cout << "\nEnter Train Number to search: ";
                cin >> num;
                system.searchTrainByNumber(num);
                break;
            }
            case 4:
                cout << "\nExiting the system. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
