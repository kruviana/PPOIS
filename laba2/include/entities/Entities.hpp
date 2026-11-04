#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <string>
#include <vector>
#include <iostream>
#include "../exceptions/AirportExceptions.hpp"

// Forward declarations
class Ticket;
class Baggage;
class Aircraft;
class Flight;

class Passport {
private:
    std::string number;
    std::string country;
    std::string expiryDate;
    bool isValid;
public:
    Passport(std::string num, std::string cnt, std::string exp, bool valid = true)
        : number(num), country(cnt), expiryDate(exp), isValid(valid) {}
    
    bool validate() const {
        if (!isValid || number.empty()) {
            throw InvalidPassportDataException(number);
        }
        return true;
    }
    std::string getNumber() const { return number; }
};

class Baggage {
private:
    std::string tagNumber;
    double weight;
    bool isChecked;
    bool isFragile;
public:
    Baggage(std::string tag, double w, bool fragile = false) 
        : tagNumber(tag), weight(w), isChecked(false), isFragile(fragile) {}

    bool verifyWeight(double maxLimit) const {
        if (weight > maxLimit) {
            throw BaggageOverweightException(weight, maxLimit);
        }
        return true;
    }
    void setChecked(bool state) { isChecked = state; }
    double getWeight() const { return weight; }
    std::string getTag() const { return tagNumber; }
};

class MilesAccount {
private:
    std::string accountId;
    int balance;
public:
    MilesAccount(std::string id, int initialBalance = 0) : accountId(id), balance(initialBalance) {}
    void addMiles(int miles) { balance += miles; }
    bool redeemMiles(int miles) {
        if (balance >= miles) { balance -= miles; return true; }
        return false;
    }
    int getBalance() const { return balance; }
};

class LoyaltyProgram {
private:
    std::string programName;
    std::string tierLevel;
    MilesAccount milesAcc;
public:
    LoyaltyProgram(std::string name, std::string tier, std::string accId) 
        : programName(name), tierLevel(tier), milesAcc(accId) {}

    void awardPoints(int amount) { milesAcc.addMiles(amount); }
    void upgradeTier(std::string newTier) { tierLevel = newTier; }
    std::string getTier() const { return tierLevel; }
};

class BankCard {
private:
    std::string cardNumber;
    std::string holderName;
    double balance;
    std::string cvv;
public:
    BankCard(std::string num, std::string holder, double bal, std::string c) 
        : cardNumber(num), holderName(holder), balance(bal), cvv(c) {}

    bool charge(double amount) {
        if (balance < amount) {
            throw InsufficientFundsException(amount, balance);
        }
        balance -= amount;
        return true;
    }
    double getBalance() const { return balance; }
};

class Payment {
private:
    std::string paymentId;
    double amount;
    bool isCompleted;
    BankCard card;
public:
    Payment(std::string id, double amt, BankCard c) 
        : paymentId(id), amount(amt), isCompleted(false), card(c) {}

    bool processTransaction() {
        if (card.charge(amount)) {
            isCompleted = true;
            return true;
        }
        return false;
    }
    bool getStatus() const { return isCompleted; }
};

class Seat {
private:
    std::string seatNumber;
    std::string seatClass; // Economy, Business, First
    bool isOccupied;
    bool isExtraLegroom;
public:
    Seat(std::string num, std::string cls, bool extra = false) 
        : seatNumber(num), seatClass(cls), isOccupied(false), isExtraLegroom(extra) {}

    void reserve() {
        if (isOccupied) {
            throw SeatNotAvailableException(seatNumber);
        }
        isOccupied = true;
    }
    void release() { isOccupied = false; }
    bool getOccupied() const { return isOccupied; }
    std::string getNumber() const { return seatNumber; }
};

class Passenger {
private:
    std::string passportNum;
    std::string fullName;
    int age;
    bool isCheckedIn;
    Passport passport;
public:
    Passenger(std::string passportId, std::string name, int a, Passport p)
        : passportNum(passportId), fullName(name), age(a), isCheckedIn(false), passport(p) {}

    void checkIn() {
        passport.validate();
        isCheckedIn = true;
    }
    void passSecurity() const {
        std::cout << "Passenger " << fullName << " passed security scan.\n";
    }
    std::string getName() const { return fullName; }
    std::string getPassportNumber() const { return passportNum; }
};

class Ticket {
private:
    std::string ticketId;
    std::string flightNumber;
    double price;
    bool isSold;
    Seat seat;
public:
    Ticket(std::string id, std::string flightNum, double p, Seat s)
        : ticketId(id), flightNumber(flightNum), price(p), isSold(false), seat(s) {}

    void purchase(BankCard& card) {
        if (isSold) {
            throw TicketAlreadySoldException(ticketId);
        }
        card.charge(price);
        seat.reserve();
        isSold = true;
    }
    bool getSoldState() const { return isSold; }
    std::string getId() const { return ticketId; }
};

class License {
private:
    std::string licenseId;
    std::string aircraftType;
    bool isExpired;
public:
    License(std::string id, std::string type, bool expired = false) 
        : licenseId(id), aircraftType(type), isExpired(expired) {}

    bool verify() const {
        if (isExpired) return false;
        return true;
    }
};

class Pilot {
private:
    std::string name;
    int flightHours;
    std::string rank;
    License license;
public:
    Pilot(std::string n, int hours, std::string r, License l) 
        : name(n), flightHours(hours), rank(r), license(l) {}

    void authorizeForFlight() const {
        if (!license.verify()) {
            throw PilotNotAuthorizedException(name);
        }
    }
    std::string getName() const { return name; }
};

class FlightAttendant {
private:
    std::string name;
    std::string languageSpoken;
    int yearsExperience;
public:
    FlightAttendant(std::string n, std::string lang, int exp) 
        : name(n), languageSpoken(lang), yearsExperience(exp) {}
    void performSafetyBriefing() const {
        std::cout << "Flight Attendant " << name << " performs safety briefing.\n";
    }
};

class Crew {
private:
    std::string crewId;
    Pilot captain;
    Pilot coPilot;
    std::vector<FlightAttendant> attendants;
public:
    Crew(std::string id, Pilot cap, Pilot co) 
        : crewId(id), captain(cap), coPilot(co) {}

    void addAttendant(const FlightAttendant& fa) { attendants.push_back(fa); }
    void verifyCrew() const {
        captain.authorizeForFlight();
        coPilot.authorizeForFlight();
    }
};

class Aircraft {
private:
    std::string tailNumber;
    std::string model;
    int maxCapacity;
    double maxWeightKg;
    double currentWeightKg;
    bool isEngineOK;
public:
    Aircraft(std::string tail, std::string m, int cap, double maxW)
        : tailNumber(tail), model(m), maxCapacity(cap), maxWeightKg(maxW), currentWeightKg(50000), isEngineOK(true) {}

    void loadCargo(double weight) {
        if (currentWeightKg + weight > maxWeightKg) {
            throw AircraftOverloadException(tailNumber);
        }
        currentWeightKg += weight;
    }
    void inspectEngines() { isEngineOK = true; }
    std::string getTailNumber() const { return tailNumber; }
};

class Route {
private:
    std::string originAirport;
    std::string destinationAirport;
    double distanceKm;
    int estimatedMinutes;
public:
    Route(std::string orig, std::string dest, double dist, int time)
        : originAirport(orig), destinationAirport(dest), distanceKm(dist), estimatedMinutes(time) {}
    
    std::string getRouteInfo() const { return originAirport + " -> " + destinationAirport; }
};

class Airline {
private:
    std::string code;
    std::string name;
    int fleetSize;
public:
    Airline(std::string c, std::string n, int f) : code(c), name(n), fleetSize(f) {}
    std::string getName() const { return name; }
};

class Flight {
private:
    std::string flightNumber;
    Airline airline;
    Aircraft aircraft;
    Route route;
    Crew crew;
    bool isDeparted;
public:
    Flight(std::string fNum, Airline al, Aircraft ac, Route r, Crew c)
        : flightNumber(fNum), airline(al), aircraft(ac), route(r), crew(c), isDeparted(false) {}

    void prepareTakeoff() {
        crew.verifyCrew();
        isDeparted = true;
        std::cout << "Flight " << flightNumber << " successfully departed on route " << route.getRouteInfo() << "\n";
    }
    std::string getNumber() const { return flightNumber; }
};

#endif // ENTITIES_HPP
