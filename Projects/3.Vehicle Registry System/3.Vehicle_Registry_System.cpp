#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
protected:
    int vehicleID;
    char manufacturer[50];
    char model[50];
    int year;

public:
    static int totalVehicles;

    Vehicle() {
        vehicleID = 0;
        strcpy(manufacturer, "");
        strcpy(model, "");
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, const char* man, const char* mod, int yr) {
        vehicleID = id;
        strcpy(manufacturer, man);
        strcpy(model, mod);
        year = yr;
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    void setID(int id) { vehicleID = id; }
    void setManufacturer(const char* m) { strcpy(manufacturer, m); }
    void setModel(const char* m) { strcpy(model, m); }
    void setYear(int y) { year = y; }

    int getID() { return vehicleID; }
    char* getManufacturer() { return manufacturer; }
    char* getModel() { return model; }
    int getYear() { return year; }

    virtual void display() {
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
protected:
    char fuelType[20];

public:
    Car() : Vehicle() { strcpy(fuelType, ""); }

    Car(int id, const char* man, const char* mod, int yr, const char* fuel)
        : Vehicle(id, man, mod, yr) {
        strcpy(fuelType, fuel);
    }

    void setFuelType(const char* f) { strcpy(fuelType, f); }

    virtual void display() {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar() : Car() { batteryCapacity = 0; }

    ElectricCar(int id, const char* man, const char* mod, int yr, const char* fuel, int battery)
        : Car(id, man, mod, yr, fuel) {
        batteryCapacity = battery;
    }

    void display() {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};

class Aircraft {
protected:
    int flightRange;

public:
    Aircraft() { flightRange = 0; }
    Aircraft(int range) { flightRange = range; }

    void displayAircraft() {
        cout << "Flight Range: " << flightRange << " km" << endl;
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() {}

    FlyingCar(int id, const char* man, const char* mod, int yr, const char* fuel, int range)
        : Car(id, man, mod, yr, fuel), Aircraft(range) {}

    void display() {
        Car::display();
        Aircraft::displayAircraft();
    }
};

class SportsCar : public ElectricCar {
private:
    int topSpeed;

public:
    SportsCar() : ElectricCar() { topSpeed = 0; }

    SportsCar(int id, const char* man, const char* mod, int yr,
              const char* fuel, int battery, int speed)
        : ElectricCar(id, man, mod, yr, fuel, battery) {
        topSpeed = speed;
    }

    void display() {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

class Sedan : public Car {
public:
    Sedan() {}
    Sedan(int id, const char* man, const char* mod, int yr, const char* fuel)
        : Car(id, man, mod, yr, fuel) {}

    void display() {
        cout << "-- Sedan --\n";
        Car::display();
    }
};

class SUV : public Car {
public:
    SUV() {}
    SUV(int id, const char* man, const char* mod, int yr, const char* fuel)
        : Car(id, man, mod, yr, fuel) {}

    void display() {
        cout << "-- SUV --\n";
        Car::display();
    }
};

class VehicleRegistry {
private:
    Vehicle* vehicles[100];
    int count;

public:
    VehicleRegistry() { count = 0; }

    void addVehicle(Vehicle* v) {
        vehicles[count++] = v;
        cout << "Vehicle Added Successfully!\n";
    }

    void displayAll() {
        cout << "\n==== All Vehicles ====\n";
        for (int i = 0; i < count; i++) {
            vehicles[i]->display();
            cout << "----------------------\n";
        }
    }

    void searchByID(int id) {
        for (int i = 0; i < count; i++) {
            if (vehicles[i]->getID() == id) {
                cout << "\nVehicle Found:\n";
                vehicles[i]->display();
                return;
            }
        }
        cout << "Vehicle Not Found!\n";
    }
};

int main() {
    VehicleRegistry registry;
    int choice;

    while (true) {
        cout << "\n====== Vehicle Registry Menu ======\n";
        cout << "1. Add Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. Search by ID\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int type;
            cout << "\nChoose Vehicle Type:\n";
            cout << "1. Sedan\n2. SUV\n3. Electric Car\n4. Flying Car\n5. Sports Car\n";
            cout << "Vehicle type:";
            cin >> type;

            int id, yr, battery, speed, range;
            char man[50], mod[50], fuel[20];

            cout << "Enter ID: ";
            cin >> id;
            cout << "Manufacturer: ";
            cin >> man;
            cout << "Model: ";
            cin >> mod;
            cout << "Year: ";
            cin >> yr;

            switch (type) {
                case 1:  // Sedan
                    cout << "Fuel Type: ";
                    cin >> fuel;
                    registry.addVehicle(new Sedan(id, man, mod, yr, fuel));
                    break;

                case 2:  // SUV
                    cout << "Fuel Type: ";
                    cin >> fuel;
                    registry.addVehicle(new SUV(id, man, mod, yr, fuel));
                    break;

                case 3:  // Electric Car
                    cout << "Battery Capacity (kWh): ";
                    cin >> battery;
                    registry.addVehicle(new ElectricCar(id, man, mod, yr, "Electric", battery));
                    break;

                case 4:  // Flying Car
                    cout << "Fuel Type: ";
                    cin >> fuel;
                    cout << "Flight Range (km): ";
                    cin >> range;
                    registry.addVehicle(new FlyingCar(id, man, mod, yr, fuel, range));
                    break;

                case 5: // Sports Car
                    cout << "Battery Capacity (kWh): ";
                    cin >> battery;
                    cout << "Top Speed (km/h): ";
                    cin >> speed;
                    registry.addVehicle(new SportsCar(id, man, mod, yr, "Electric", battery, speed));
                    break;

                default:
                    cout << "Invalid Type!\n";
            }
        }

        else if (choice == 2) {
            registry.displayAll();
        }

        else if (choice == 3) {
            int id;
            cout << "Enter Vehicle ID: ";
            cin >> id;
            registry.searchByID(id);
        }

        else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid Choice!\n";
        }
    }

    return 0;
}
