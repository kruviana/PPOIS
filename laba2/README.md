# Лабораторная работа №2. Крупный ООП-проект
## Предметная область: Система управления аэропортом (Airport Management System)

### Описание проекта
Проект представляет собой объектно-ориентированную модель системы управления аэропортом на C++. 
Включает в себя управление рейсами, пассажирами, багажом, инфраструктурой взлётно-посадочных полос, терминалов, службами безопасности и наземного обслуживания.

### Статистика проекта

| Показатель | Требование | Реализовано в проекте |
|---|---|---|
| **Классы** | не менее 50 | **52** |
| **Поля** | не менее 150 | **188** |
| **Поведения (методы)** | не менее 100 | **146** |
| **Ассоциации** | не менее 30 | **64** |
| **Исключения** | не менее 12 | **12** |

---

### Таблица классов

| № | Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|---|
| 1 | Airport | 4 | 4 | Terminal, Runway, ControlTower |
| 2 | Terminal | 4 | 3 | Gate, CheckInDesk, SecurityCheckpoint |
| 3 | Runway | 4 | 3 | ControlTower, Aircraft |
| 4 | ControlTower | 3 | 4 | Runway, Aircraft, Radar |
| 5 | Radar | 3 | 2 | ControlTower, Aircraft |
| 6 | Gate | 4 | 3 | Terminal, BoardingPass, Aircraft |
| 7 | CheckInDesk | 3 | 3 | Passenger, Ticket, Baggage |
| 8 | SecurityCheckpoint | 3 | 3 | Passenger, SecurityScanner |
| 9 | SecurityScanner | 3 | 2 | SecurityCheckpoint |
| 10 | Aircraft | 6 | 5 | Airline, Flight, Crew, Seat |
| 11 | Airline | 3 | 3 | Aircraft, Flight |
| 12 | Flight | 6 | 4 | Aircraft, Route, Crew, Ticket |
| 13 | Route | 4 | 2 | Airport, Flight |
| 14 | Crew | 3 | 3 | Pilot, FlightAttendant, Flight |
| 15 | Pilot | 4 | 3 | Crew, License |
| 16 | FlightAttendant | 3 | 2 | Crew |
| 17 | License | 3 | 2 | Pilot |
| 18 | Passenger | 5 | 4 | Ticket, Passport, Baggage, LoyaltyProgram |
| 19 | Passport | 4 | 2 | Passenger |
| 20 | Ticket | 5 | 3 | Passenger, Flight, Seat, Payment |
| 21 | Seat | 4 | 2 | Aircraft, Ticket |
| 22 | Baggage | 4 | 3 | Passenger, ConveyorBelt, Flight |
| 23 | ConveyorBelt | 3 | 2 | Baggage, Terminal |
| 24 | LoyaltyProgram | 3 | 3 | Passenger, MilesAccount |
| 25 | MilesAccount | 3 | 2 | LoyaltyProgram |
| 26 | Payment | 4 | 3 | Ticket, BankCard |
| 27 | BankCard | 4 | 2 | Payment, Passenger |
| 28 | GroundService | 3 | 3 | Refueler, CateringService, CleaningService |
| 29 | Refueler | 3 | 2 | GroundService, Aircraft |
| 30 | CateringService | 3 | 2 | GroundService, Aircraft |
| 31 | CleaningService | 3 | 2 | GroundService, Aircraft |
| 32 | Hangar | 4 | 3 | Aircraft, MaintenanceEngineer |
| 33 | MaintenanceEngineer | 3 | 3 | Hangar, Aircraft |
| 34 | WeatherStation | 3 | 3 | ControlTower, WeatherReport |
| 35 | WeatherReport | 4 | 2 | WeatherStation |
| 36 | InformationDesk | 3 | 3 | Passenger, ScheduleBoard |
| 37 | ScheduleBoard | 3 | 2 | Flight, InformationDesk |
| 38 | DutyFreeShop | 3 | 3 | Cashier, Product, Passenger |
| 39 | Cashier | 3 | 2 | DutyFreeShop |
| 40 | Product | 4 | 1 | DutyFreeShop |
| 41 | VIPLounge | 4 | 3 | Passenger, Concierge |
| 42 | Concierge | 3 | 2 | VIPLounge |
| 43 | MedicalCenter | 3 | 3 | Doctor, Patient |
| 44 | Doctor | 3 | 2 | MedicalCenter |
| 45 | Patient | 3 | 1 | MedicalCenter |
| 46 | Parking | 4 | 3 | ParkingTicket, Vehicle |
| 47 | ParkingTicket | 3 | 2 | Parking |
| 48 | Vehicle | 4 | 2 | Parking, Driver |
| 49 | Bus | 3 | 2 | Vehicle, Terminal |
| 50 | FireStation | 3 | 3 | FireEngine, Firefighter |
| 51 | FireEngine | 3 | 2 | FireStation |
| 52 | Firefighter | 3 | 2 | FireStation |

### Исключения (12)
1. `AirportException` (Базовое исключение)
2. `FlightNotFoundException`
3. `TicketAlreadySoldException`
4. `SeatNotAvailableException`
5. `BaggageOverweightException`
6. `InvalidPassportDataException`
7. `AccessDeniedException`
8. `RunwayBusyException`
9. `WeatherConditionsUnfavorableException`
10. `InsufficientFundsException`
11. `PilotNotAuthorizedException`
12. `AircraftOverloadException`
