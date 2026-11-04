#ifndef HOSPITAL_INFRASTRUCTURE_HPP
#define HOSPITAL_INFRASTRUCTURE_HPP

#include <string>
#include <vector>
#include <iostream>
#include "../exceptions/HospitalExceptions.hpp"
#include "../entities/MedicalEntities.hpp"

class Equipment {
private:
    std::string eqName;
    bool isFunctional;
public:
    Equipment(std::string name, bool functional = true) : eqName(name), isFunctional(functional) {}
    void checkStatus() const {
        if (!isFunctional) throw EquipmentMalfunctionException(eqName);
    }
};

class OperatingRoom {
private:
    std::string roomId;
    bool isOccupied;
    Equipment equipment;
public:
    OperatingRoom(std::string id, Equipment eq) : roomId(id), isOccupied(false), equipment(eq) {}

    void reserve() {
        equipment.checkStatus();
        if (isOccupied) throw OperatingRoomBusyException(roomId);
        isOccupied = true;
        std::cout << "Operating Room " << roomId << " successfully reserved.\n";
    }
    void release() { isOccupied = false; }
};

class Pharmacy {
private:
    std::string pharmacyName;
    std::vector<Medication> inventory;
public:
    Pharmacy(std::string name) : pharmacyName(name) {}
    void addMedication(const Medication& med) { inventory.push_back(med); }
    
    void issueMedication(const std::string& medName) {
        for (auto& med : inventory) {
            if (med.getName() == medName) {
                med.dispense();
                std::cout << "Medication '" << medName << "' issued from pharmacy.\n";
                return;
            }
        }
        throw MedicationOutOfStockException(medName);
    }
};

class Laboratory {
private:
    std::string labId;
public:
    Laboratory(std::string id) : labId(id) {}
    void analyzeTest(bool isReady) const {
        if (!isReady) throw LabResultPendingException("TEST-999");
        std::cout << "Laboratory analysis completed successfully.\n";
    }
};

class Ward {
private:
    std::string wardNumber;
    int capacity;
    int currentPatients;
public:
    Ward(std::string num, int cap) : wardNumber(num), capacity(cap), currentPatients(0) {}

    void admitPatient() {
        if (currentPatients >= capacity) throw RoomCapacityExceededException(wardNumber);
        currentPatients++;
        std::cout << "Patient admitted to ward " << wardNumber << ".\n";
    }
};

class Department {
private:
    std::string name;
    Ward ward;
public:
    Department(std::string deptName, Ward w) : name(deptName), ward(w) {}
    Ward& getWard() { return ward; }
};

class Hospital {
private:
    std::string hospitalName;
    Pharmacy pharmacy;
    Laboratory laboratory;
public:
    Hospital(std::string name, Pharmacy ph, Laboratory lab) 
        : hospitalName(name), pharmacy(ph), laboratory(lab) {}

    Pharmacy& getPharmacy() { return pharmacy; }
    Laboratory& getLaboratory() { return laboratory; }
    std::string getName() const { return hospitalName; }
};

#endif // HOSPITAL_INFRASTRUCTURE_HPP
