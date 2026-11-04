#ifndef HOSPITAL_EXCEPTIONS_HPP
#define HOSPITAL_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class HospitalException : public std::runtime_error {
public:
    explicit HospitalException(const std::string& msg) : std::runtime_error(msg) {}
};

class PatientNotFoundException : public HospitalException {
public:
    explicit PatientNotFoundException(const std::string& id) 
        : HospitalException("Patient not found: " + id) {}
};

class DoctorNotAvailableException : public HospitalException {
public:
    explicit DoctorNotAvailableException(const std::string& doc) 
        : HospitalException("Doctor is currently busy or unavailable: " + doc) {}
};

class OperatingRoomBusyException : public HospitalException {
public:
    explicit OperatingRoomBusyException(const std::string& room) 
        : HospitalException("Operating room is occupied: " + room) {}
};

class MedicationOutOfStockException : public HospitalException {
public:
    explicit MedicationOutOfStockException(const std::string& med) 
        : HospitalException("Medication out of stock in pharmacy: " + med) {}
};

class InsufficientFundsException : public HospitalException {
public:
    InsufficientFundsException(double req, double av) 
        : HospitalException("Insufficient funds. Required: $" + std::to_string(req) + ", Available: $" + std::to_string(av)) {}
};

class InvalidDiagnosisException : public HospitalException {
public:
    explicit InvalidDiagnosisException(const std::string& diag) 
        : HospitalException("Invalid or empty diagnosis code: " + diag) {}
};

class LabResultPendingException : public HospitalException {
public:
    explicit LabResultPendingException(const std::string& testId) 
        : HospitalException("Laboratory test results are still pending: " + testId) {}
};

class RoomCapacityExceededException : public HospitalException {
public:
    explicit RoomCapacityExceededException(const std::string& ward) 
        : HospitalException("Ward capacity exceeded: " + ward) {}
};

class InvalidInsuranceException : public HospitalException {
public:
    explicit InvalidInsuranceException(const std::string& policy) 
        : HospitalException("Insurance policy is expired or invalid: " + policy) {}
};

class PrescriptionExpiredException : public HospitalException {
public:
    explicit PrescriptionExpiredException(const std::string& rx) 
        : HospitalException("Prescription has expired: " + rx) {}
};

class EquipmentMalfunctionException : public HospitalException {
public:
    explicit EquipmentMalfunctionException(const std::string& eq) 
        : HospitalException("Critical medical equipment malfunction: " + eq) {}
};

#endif // HOSPITAL_EXCEPTIONS_HPP
