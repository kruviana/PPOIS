#ifndef AIRPORT_EXCEPTIONS_HPP
#define AIRPORT_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

// 1. Base Exception
class AirportException : public std::runtime_error {
public:
    explicit AirportException(const std::string& msg) : std::runtime_error(msg) {}
};

// 2. Flight Exceptions
class FlightNotFoundException : public AirportException {
public:
    explicit FlightNotFoundException(const std::string& flightNum) 
        : AirportException("Flight non-existent or not found: " + flightNum) {}
};

// 3. Ticket Exceptions
class TicketAlreadySoldException : public AirportException {
public:
    explicit TicketAlreadySoldException(const std::string& ticketId) 
        : AirportException("Ticket has already been sold: " + ticketId) {}
};

// 4. Seat Exceptions
class SeatNotAvailableException : public AirportException {
public:
    explicit SeatNotAvailableException(const std::string& seatNum) 
        : AirportException("Seat is not available or occupied: " + seatNum) {}
};

// 5. Baggage Exceptions
class BaggageOverweightException : public AirportException {
public:
    BaggageOverweightException(double weight, double limit)
        : AirportException("Baggage overweight! Weight: " + std::to_string(weight) + " kg (Limit: " + std::to_string(limit) + " kg)") {}
};

// 6. Passport Exceptions
class InvalidPassportDataException : public AirportException {
public:
    explicit InvalidPassportDataException(const std::string& passportNum) 
        : AirportException("Invalid passport data format: " + passportNum) {}
};

// 7. Security Exceptions
class AccessDeniedException : public AirportException {
public:
    explicit AccessDeniedException(const std::string& zone) 
        : AirportException("Access denied to secure zone: " + zone) {}
};

// 8. Runway Exceptions
class RunwayBusyException : public AirportException {
public:
    explicit RunwayBusyException(const std::string& runwayName) 
        : AirportException("Runway is occupied and unavailable: " + runwayName) {}
};

// 9. Weather Exceptions
class WeatherConditionsUnfavorableException : public AirportException {
public:
    explicit WeatherConditionsUnfavorableException(const std::string& condition) 
        : AirportException("Unfavorable weather conditions for flight operations: " + condition) {}
};

// 10. Financial Exceptions
class InsufficientFundsException : public AirportException {
public:
    InsufficientFundsException(double required, double available)
        : AirportException("Insufficient funds! Required: $" + std::to_string(required) + ", Available: $" + std::to_string(available)) {}
};

// 11. Crew Exceptions
class PilotNotAuthorizedException : public AirportException {
public:
    explicit PilotNotAuthorizedException(const std::string& pilotName) 
        : AirportException("Pilot is not authorized or license expired: " + pilotName) {}
};

// 12. Aircraft Exceptions
class AircraftOverloadException : public AirportException {
public:
    explicit AircraftOverloadException(const std::string& tailNumber) 
        : AirportException("Aircraft maximum takeoff weight exceeded: " + tailNumber) {}
};

#endif // AIRPORT_EXCEPTIONS_HPP
