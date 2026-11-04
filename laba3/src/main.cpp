#include <iostream>
#include "exceptions/HospitalExceptions.hpp"
#include "entities/MedicalEntities.hpp"
#include "infrastructure/HospitalInfrastructure.hpp"

int main() {
    std::cout << "=================================================\n";
    std::cout << "   HOSPITAL MANAGEMENT SYSTEM (OOP C++ PROJECT)  \n";
    std::cout << "=================================================\n\n";

    try {
        // 1. Создание инфраструктуры больницы
        Pharmacy pharmacy("Central Hospital Pharmacy");
        pharmacy.addMedication(Medication("Paracetamol", 10, 5.0));
        pharmacy.addMedication(Medication("Amoxicillin", 0, 15.0)); // Нет в наличии для тестов исключений

        Laboratory lab("Lab-01");
        Hospital hospital("St. Mary Hospital", pharmacy, lab);

        // 2. Создание пациента и доктора
        InsurancePolicy policy("POL-777888", "Full Coverage", true);
        Patient patient("P-001", "Anna Ivanova", 30, policy);

        MedicalLicense license("LIC-555", true);
        Doctor doctor("Dr. House", "Diagnostician", license);

        std::cout << "[Step 1] Patient Verification & Consultation...\n";
        patient.verifyInsurance();
        doctor.consult(patient);
        std::cout << "\n";

        std::cout << "[Step 2] Operating Room Reservation...\n";
        Equipment eq("Surgical Laser", true);
        OperatingRoom opRoom("OR-03", eq);
        opRoom.reserve();
        std::cout << "\n";

        std::cout << "[Step 3] Issuing Medication from Pharmacy...\n";
        hospital.getPharmacy().issueMedication("Paracetamol");
        std::cout << "\n";

        std::cout << "[Step 4] Billing and Payment...\n";
        Bill bill("BILL-100", 150.0);
        BankCard card("4400111122223333", 500.0);
        bill.pay(card);
        std::cout << "Bill successfully paid! Remaining card balance: $" << card.getBalance() << "\n\n";

        // 5. Демонстрация работы исключений
        std::cout << "[Step 5] Testing Exception Handling (Out of Stock Medication)...\n";
        hospital.getPharmacy().issueMedication("Amoxicillin");

    } catch (const HospitalException& e) {
        std::cout << ">>> HOSPITAL SYSTEM EXCEPTION CAUGHT: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << ">>> STD EXCEPTION CAUGHT: " << e.what() << "\n";
    }

    std::cout << "\n=================================================\n";
    std::cout << "             PROJECT DEMO COMPLETED              \n";
    std::cout << "=================================================\n";

    return 0;
}
