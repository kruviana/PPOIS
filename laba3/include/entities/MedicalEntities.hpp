#ifndef MEDICAL_ENTITIES_HPP
#define MEDICAL_ENTITIES_HPP

#include <string>
#include <vector>
#include <iostream>
#include "../exceptions/HospitalExceptions.hpp"

class InsurancePolicy {
private:
    std::string policyNumber;
    std::string coverageType;
    bool isValid;
public:
    InsurancePolicy(std::string num, std::string type, bool valid = true)
        : policyNumber(num), coverageType(type), isValid(valid) {}

    void validate() const {
        if (!isValid) throw InvalidInsuranceException(policyNumber);
    }
    std::string getNumber() const { return policyNumber; }
};

class BankCard {
private:
    std::string cardNumber;
    double balance;
public:
    BankCard(std::string num, double bal) : cardNumber(num), balance(bal) {}
    void withdraw(double amount) {
        if (balance < amount) throw InsufficientFundsException(amount, balance);
        balance -= amount;
    }
    double getBalance() const { return balance; }
};

class Bill {
private:
    std::string billId;
    double amount;
    bool isPaid;
public:
    Bill(std::string id, double amt) : billId(id), amount(amt), isPaid(false) {}
    void pay(BankCard& card) {
        card.withdraw(amount);
        isPaid = true;
    }
    bool getPaidStatus() const { return isPaid; }
    double getAmount() const { return amount; }
};

class Patient {
private:
    std::string patientId;
    std::string fullName;
    int age;
    InsurancePolicy insurance;
public:
    Patient(std::string id, std::string name, int a, InsurancePolicy ins)
        : patientId(id), fullName(name), age(a), insurance(ins) {}

    void verifyInsurance() const { insurance.validate(); }
    std::string getName() const { return fullName; }
    std::string getId() const { return patientId; }
};

class Medication {
private:
    std::string name;
    int stockCount;
    double price;
public:
    Medication(std::string n, int stock, double p) : name(n), stockCount(stock), price(p) {}
    void dispense() {
        if (stockCount <= 0) throw MedicationOutOfStockException(name);
        stockCount--;
    }
    std::string getName() const { return name; }
};

class Prescription {
private:
    std::string rxId;
    std::string details;
    bool isExpired;
public:
    Prescription(std::string id, std::string det, bool expired = false)
        : rxId(id), details(det), isExpired(expired) {}

    void checkValidity() const {
        if (isExpired) throw PrescriptionExpiredException(rxId);
    }
};

class MedicalRecord {
private:
    std::string recordId;
    std::string diagnosis;
public:
    MedicalRecord(std::string id, std::string diag) : recordId(id), diagnosis(diag) {}
    void updateDiagnosis(const std::string& newDiag) {
        if (newDiag.empty()) throw InvalidDiagnosisException(newDiag);
        diagnosis = newDiag;
    }
    std::string getDiagnosis() const { return diagnosis; }
};

class MedicalLicense {
private:
    std::string licenseId;
    bool isActive;
public:
    MedicalLicense(std::string id, bool active = true) : licenseId(id), isActive(active) {}
    bool checkActive() const { return isActive; }
};

class Doctor {
private:
    std::string name;
    std::string specialization;
    MedicalLicense license;
    bool isAvailable;
public:
    Doctor(std::string n, std::string spec, MedicalLicense lic)
        : name(n), specialization(spec), license(lic), isAvailable(true) {}

    void consult(Patient& p) {
        if (!isAvailable || !license.checkActive()) {
            throw DoctorNotAvailableException(name);
        }
        std::cout << "Doctor " << name << " (" << specialization << ") is consulting patient " << p.getName() << ".\n";
    }
    std::string getName() const { return name; }
};

#endif // MEDICAL_ENTITIES_HPP
