#include <iostream>
#include <vector>
#include "exceptions/AirportExceptions.hpp"
#include "entities/Entities.hpp"
#include "infrastructure/Infrastructure.hpp"

int main() {
    std::cout << "=================================================\n";
    std::cout << "   AIRPORT MANAGEMENT SYSTEM (OOP C++ PROJECT)   \n";
    std::cout << "=================================================\n\n";

    try {
        // 1. Setup Weather & Control Tower
        WeatherReport weather(22.5, 12.0, 10.0, false);
        WeatherStation weatherStation("WS-01", "Zone A", weather);
        Radar radar("RADAR-01", 150.0);
        ControlTower tower("Main Tower", radar, weatherStation);

        Airport airport("Sheremetyevo International", "SVO", tower);

        // 2. Setup Aircraft & Crew
        Aircraft aircraft("RA-89001", "Sukhoi Superjet 100", 100, 45000.0);
        License pilotLicense("LIC-9988", "SSJ-100", false);
        Pilot captain("Captain Ivan Petrov", 4500, "Senior Captain", pilotLicense);
        Pilot coPilot("Co-Pilot Alexey Smirnov", 1200, "First Officer", pilotLicense);
        Crew flightCrew("CREW-101", captain, coPilot);

        Airline airline("SU", "Aeroflot", 150);
        Route route("SVO", "AER", 1400.0, 140);
        Flight flight("SU-1122", airline, aircraft, route, flightCrew);

        // 3. Passenger Check-in & Security
        Passport passport("751234567", "RU", "2030-10-10", true);
        Passenger passenger("751234567", "Dmitry Ivanov", 28, passport);

        Seat seat("12A", "Economy");
        BankCard card("4532111122223333", "Dmitry Ivanov", 500.0, "123");
        Ticket ticket("TCK-9900", "SU-1122", 150.0, seat);

        std::cout << "[Step 1] Ticket Purchasing...\n";
        ticket.purchase(card);
        std::cout << "Ticket successfully purchased! Remaining balance: $" << card.getBalance() << "\n\n";

        std::cout << "[Step 2] Passenger Check-In...\n";
        ConveyorBelt belt("BELT-01", 1.5);
        CheckInDesk checkInDesk("DESK-05", belt);
        Baggage baggage("BAG-5511", 18.5); // Weight limit: 23.0 kg
        checkInDesk.processCheckIn(passenger, baggage, 23.0);
        std::cout << "\n";

        std::cout << "[Step 3] Security Clearance...\n";
        SecurityScanner scanner("SCAN-X200", 0.95);
        SecurityCheckpoint security("SEC-01", scanner, 4);
        security.processPassenger(passenger);
        std::cout << "\n";

        std::cout << "[Step 4] Runway & Takeoff Clearance...\n";
        Runway runway("13L/31R", 3000.0);
        tower.grantTakeoffPermission(runway, flight);
        flight.prepareTakeoff();
        std::cout << "\n";

        // 4. Test Exception Handling
        std::cout << "[Step 5] Testing Exception Handling (Overweight Baggage)...\n";
        Baggage heavyBaggage("BAG-9999", 35.0); // Exceeds 23.0 kg
        heavyBaggage.verifyWeight(23.0);

    } catch (const AirportException& e) {
        std::cout << ">>> AIRPORT SYSTEM EXCEPTION CAUGHT: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << ">>> STD EXCEPTION CAUGHT: " << e.what() << "\n";
    }

    std::cout << "\n=================================================\n";
    std::cout << "             PROJECT DEMO COMPLETED              \n";
    std::cout << "=================================================\n";

    return 0;
}
