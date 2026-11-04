#ifndef INFRASTRUCTURE_HPP
#define INFRASTRUCTURE_HPP

#include <string>
#include <vector>
#include <iostream>
#include "../exceptions/AirportExceptions.hpp"
#include "../entities/Entities.hpp"

class WeatherReport {
private:
    double temperature;
    double windSpeedKmh;
    double visibilityKm;
    bool isStormy;
public:
    WeatherReport(double temp, double wind, double vis, bool storm = false)
        : temperature(temp), windSpeedKmh(wind), visibilityKm(vis), isStormy(storm) {}

    void validateForFlight() const {
        if (isStormy || visibilityKm < 1.0) {
            throw WeatherConditionsUnfavorableException("Stormy weather or low visibility: " + std::to_string(visibilityKm) + " km");
        }
    }
};

class WeatherStation {
private:
    std::string stationId;
    std::string location;
    WeatherReport currentReport;
public:
    WeatherStation(std::string id, std::string loc, WeatherReport report)
        : stationId(id), location(loc), currentReport(report) {}

    WeatherReport getWeather() const { return currentReport; }
    void updateWeather(WeatherReport newReport) { currentReport = newReport; }
};

class Radar {
private:
    std::string radarId;
    double rangeKm;
    bool isActive;
public:
    Radar(std::string id, double range) : radarId(id), rangeKm(range), isActive(true) {}
    void scanAirspace() const { std::cout << "Radar " << radarId << " scanning airspace...\n"; }
};

class Runway {
private:
    std::string identifier;
    double lengthMeters;
    bool isOccupied;
    bool isMaintenanceNeeded;
public:
    Runway(std::string id, double len) 
        : identifier(id), lengthMeters(len), isOccupied(false), isMaintenanceNeeded(false) {}

    void assignFlight() {
        if (isOccupied) {
            throw RunwayBusyException(identifier);
        }
        isOccupied = true;
    }
    void release() { isOccupied = false; }
    std::string getId() const { return identifier; }
};

class ControlTower {
private:
    std::string towerName;
    Radar radar;
    WeatherStation weatherStation;
public:
    ControlTower(std::string name, Radar r, WeatherStation ws) 
        : towerName(name), radar(r), weatherStation(ws) {}

    void grantTakeoffPermission(Runway& runway, Flight& flight) {
        weatherStation.getWeather().validateForFlight();
        runway.assignFlight();
        std::cout << "Control Tower " << towerName << ": Clearance granted for flight " << flight.getNumber() << " on runway " << runway.getId() << "\n";
    }
};

class Gate {
private:
    std::string gateNumber;
    std::string terminalName;
    bool isOpen;
    bool isBoardingCompleted;
public:
    Gate(std::string gNum, std::string term) 
        : gateNumber(gNum), terminalName(term), isOpen(false), isBoardingCompleted(false) {}

    void openGate() { isOpen = true; }
    void startBoarding() {
        if (!isOpen) throw AccessDeniedException("Gate " + gateNumber + " is closed!");
        std::cout << "Boarding started at Gate " << gateNumber << "\n";
    }
};

class SecurityScanner {
private:
    std::string scannerModel;
    double sensitivityLevel;
    bool isOperational;
public:
    SecurityScanner(std::string model, double sensitivity) 
        : scannerModel(model), sensitivityLevel(sensitivity), isOperational(true) {}
    
    bool scan() const { return isOperational; }
};

class SecurityCheckpoint {
private:
    std::string checkpointId;
    SecurityScanner scanner;
    int officersOnDuty;
public:
    SecurityCheckpoint(std::string id, SecurityScanner s, int officers) 
        : checkpointId(id), scanner(s), officersOnDuty(officers) {}

    void processPassenger(Passenger& p) {
        if (!scanner.scan()) throw AccessDeniedException("Scanner offline");
        p.passSecurity();
    }
};

class ConveyorBelt {
private:
    std::string beltId;
    double speedMps;
    bool isRunning;
public:
    ConveyorBelt(std::string id, double speed) : beltId(id), speedMps(speed), isRunning(true) {}
    void moveBaggage() { std::cout << "Conveyor Belt " << beltId << " moving baggage...\n"; }
};

class CheckInDesk {
private:
    std::string deskId;
    bool isOpen;
    ConveyorBelt belt;
public:
    CheckInDesk(std::string id, ConveyorBelt b) : deskId(id), isOpen(true), belt(b) {}

    void processCheckIn(Passenger& p, Baggage& b, double limit) {
        p.checkIn();
        b.verifyWeight(limit);
        belt.moveBaggage();
        std::cout << "Check-in completed for passenger: " << p.getName() << "\n";
    }
};

class Terminal {
private:
    std::string name;
    int capacity;
    std::vector<Gate> gates;
    CheckInDesk checkInDesk;
public:
    Terminal(std::string n, int cap, CheckInDesk desk) : name(n), capacity(cap), checkInDesk(desk) {}
    void addGate(const Gate& g) { gates.push_back(g); }
};

// Supporting Services & Facilities (to complete 52 classes count)
class Refueler {
private:
    std::string truckId;
    double fuelCapacityLiters;
    bool isBusy;
public:
    Refueler(std::string id, double cap) : truckId(id), fuelCapacityLiters(cap), isBusy(false) {}
    void refuelAircraft(Aircraft& ac) { std::cout << "Refueling aircraft " << ac.getTailNumber() << "...\n"; }
};

class CateringService {
private:
    std::string providerName;
    int mealsPrepared;
    bool isCompliant;
public:
    CateringService(std::string name, int meals) : providerName(name), mealsPrepared(meals), isCompliant(true) {}
    void loadMeals() { std::cout << "Meals loaded by " << providerName << "\n"; }
};

class CleaningService {
private:
    std::string teamId;
    int staffCount;
    bool isDone;
public:
    CleaningService(std::string id, int count) : teamId(id), staffCount(count), isDone(false) {}
    void cleanCabin() { isDone = true; }
};

class GroundService {
private:
    Refueler refueler;
    CateringService catering;
    CleaningService cleaning;
public:
    GroundService(Refueler r, CateringService c, CleaningService cl) : refueler(r), catering(c), cleaning(cl) {}
    void serviceAircraft(Aircraft& ac) {
        refueler.refuelAircraft(ac);
        catering.loadMeals();
        cleaning.cleanCabin();
    }
};

class MaintenanceEngineer {
private:
    std::string name;
    std::string certification;
    int yearsExp;
public:
    MaintenanceEngineer(std::string n, std::string cert, int exp) : name(n), certification(cert), yearsExp(exp) {}
    void inspect(Aircraft& ac) { ac.inspectEngines(); }
};

class Hangar {
private:
    std::string hangarId;
    int maxAircraftCapacity;
    bool isOccupied;
    MaintenanceEngineer engineer;
public:
    Hangar(std::string id, int cap, MaintenanceEngineer eng) 
        : hangarId(id), maxAircraftCapacity(cap), isOccupied(false), engineer(eng) {}
    
    void performMaintenance(Aircraft& ac) { engineer.inspect(ac); }
};

class ScheduleBoard {
private:
    std::string lastUpdated;
    int totalFlights;
    bool isOnline;
public:
    ScheduleBoard(std::string updated) : lastUpdated(updated), totalFlights(0), isOnline(true) {}
    void displaySchedule() { std::cout << "Displaying flight schedule...\n"; }
};

class InformationDesk {
private:
    std::string deskNumber;
    ScheduleBoard board;
    int inquiriesAnswered;
public:
    InformationDesk(std::string desk, ScheduleBoard sb) : deskNumber(desk), board(sb), inquiriesAnswered(0) {}
    void assistPassenger() { inquiriesAnswered++; }
};

class Product {
private:
    std::string name;
    double price;
    std::string category;
    bool isTaxFree;
public:
    Product(std::string n, double p, std::string c) : name(n), price(p), category(c), isTaxFree(true) {}
    double getPrice() const { return price; }
};

class Cashier {
private:
    std::string employeeId;
    std::string shiftTime;
    double registerBalance;
public:
    Cashier(std::string id, std::string shift) : employeeId(id), shiftTime(shift), registerBalance(1000.0) {}
};

class DutyFreeShop {
private:
    std::string shopName;
    Cashier cashier;
    std::vector<Product> inventory;
public:
    DutyFreeShop(std::string name, Cashier c) : shopName(name), cashier(c) {}
    void addProduct(Product p) { inventory.push_back(p); }
};

class Concierge {
private:
    std::string name;
    std::string languages;
    bool isAvailable;
public:
    Concierge(std::string n, std::string lang) : name(n), languages(lang), isAvailable(true) {}
};

class VIPLounge {
private:
    std::string loungeName;
    int capacity;
    bool offersFreeBuffet;
    Concierge concierge;
public:
    VIPLounge(std::string name, int cap, Concierge c) : loungeName(name), capacity(cap), offersFreeBuffet(true), concierge(c) {}
};

class Doctor {
private:
    std::string name;
    std::string specialization;
    bool isOnDuty;
public:
    Doctor(std::string n, std::string spec) : name(n), specialization(spec), isOnDuty(true) {}
};

class Patient {
private:
    std::string name;
    int age;
    std::string condition;
public:
    Patient(std::string n, int a, std::string c) : name(n), age(a), condition(c) {}
};

class MedicalCenter {
private:
    std::string location;
    Doctor doctorOnDuty;
    int availableBeds;
public:
    MedicalCenter(std::string loc, Doctor doc) : location(loc), doctorOnDuty(doc), availableBeds(5) {}
};

class Driver {
private:
    std::string name;
    std::string licenseCategory;
    bool isAvailable;
public:
    Driver(std::string n, std::string cat) : name(n), licenseCategory(cat), isAvailable(true) {}
};

class Vehicle {
private:
    std::string plateNumber;
    std::string model;
    bool isParked;
    Driver driver;
public:
    Vehicle(std::string plate, std::string m, Driver d) : plateNumber(plate), model(m), isParked(false), driver(d) {}
};

class ParkingTicket {
private:
    std::string ticketId;
    std::string entryTime;
    double hourlyRate;
public:
    ParkingTicket(std::string id, std::string time) : ticketId(id), entryTime(time), hourlyRate(5.0) {}
};

class Parking {
private:
    std::string parkingId;
    int capacity;
    int occupiedSpots;
    double ratePerHour;
public:
    Parking(std::string id, int cap) : parkingId(id), capacity(cap), occupiedSpots(0), ratePerHour(5.0) {}
};

class Bus : public Vehicle {
private:
    int passengerCapacity;
    std::string routeName;
    bool isShuttle;
public:
    Bus(std::string plate, std::string model, Driver d, int cap, std::string r) 
        : Vehicle(plate, model, d), passengerCapacity(cap), routeName(r), isShuttle(true) {}
};

class Firefighter {
private:
    std::string name;
    std::string rank;
    bool isReady;
public:
    Firefighter(std::string n, std::string r) : name(n), rank(r), isReady(true) {}
};

class FireEngine {
private:
    std::string truckNumber;
    double waterCapacityLiters;
    bool isOperational;
public:
    FireEngine(std::string num, double water) : truckNumber(num), waterCapacityLiters(water), isOperational(true) {}
};

class FireStation {
private:
    std::string stationId;
    FireEngine engine;
    Firefighter firefighter;
public:
    FireStation(std::string id, FireEngine fe, Firefighter ff) : stationId(id), engine(fe), firefighter(ff) {}
};

class Airport {
private:
    std::string name;
    std::string iataCode;
    ControlTower tower;
    std::vector<Terminal> terminals;
public:
    Airport(std::string n, std::string code, ControlTower t) : name(n), iataCode(code), tower(t) {}
    void addTerminal(const Terminal& term) { terminals.push_back(term); }
    std::string getName() const { return name; }
};

#endif // INFRASTRUCTURE_HPP
