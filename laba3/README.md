# Лабораторная работа №3. Крупный ООП-проект
## Предметная область: Система управления больницей (Hospital Management System)

### Описание проекта
Проект представляет собой объектно-ориентированную модель системы управления больницей на C++.
Включает в себя управление пациентами, медицинским персоналом, операционными блоками, лабораториями, аптекой, страховыми полисами и финансовыми операциями.

### Статистика проекта

| Показатель | Требование | Реализовано в проекте |
|---|---|---|
| **Классы** | не менее 50 | **52** |
| **Поля** | не менее 150 | **185** |
| **Почения (методы)** | не менее 100 | **148** |
| **Ассоциации** | не менее 30 | **62** |
| **Исключения** | не менее 12 | **12** |

---

### Таблица классов

| № | Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|---|
| 1 | Hospital | 4 | 4 | Department, Pharmacy, Laboratory |
| 2 | Department | 4 | 3 | Ward, Doctor, Nurse |
| 3 | Ward | 4 | 3 | Patient, Department |
| 4 | OperatingRoom | 4 | 3 | Surgeon, Equipment, Patient |
| 5 | Laboratory | 3 | 3 | LabTechnician, TestResult |
| 6 | Pharmacy | 3 | 3 | Pharmacist, Medication |
| 7 | Reception | 3 | 3 | Administrator, Patient, Appointment |
| 8 | MedicalStaff | 5 | 3 | Department, Schedule |
| 9 | Doctor | 4 | 4 | Patient, MedicalRecord, Prescription |
| 10 | Surgeon | 3 | 3 | OperatingRoom, Operation |
| 11 | Nurse | 3 | 2 | Ward, Patient |
| 12 | HeadDoctor | 3 | 3 | Department, MedicalStaff |
| 13 | Pharmacist | 3 | 2 | Pharmacy, Medication |
| 14 | LabTechnician | 3 | 2 | Laboratory, TestResult |
| 15 | Administrator | 3 | 3 | Reception, Appointment |
| 16 | Patient | 6 | 4 | MedicalRecord, InsurancePolicy, Bill |
| 17 | MedicalRecord | 4 | 3 | Patient, Diagnosis, Prescription |
| 18 | Diagnosis | 3 | 2 | MedicalRecord |
| 19 | Prescription | 4 | 3 | Doctor, Patient, Medication |
| 20 | TreatmentPlan | 4 | 3 | Doctor, Patient |
| 21 | Appointment | 4 | 3 | Doctor, Patient, Reception |
| 22 | Operation | 5 | 4 | Surgeon, OperatingRoom, Patient |
| 23 | TestResult | 4 | 2 | Laboratory, Patient |
| 24 | Medication | 4 | 2 | Pharmacy, Prescription |
| 25 | Equipment | 4 | 3 | OperatingRoom, Maintenance |
| 26 | InsurancePolicy | 4 | 2 | Patient |
| 27 | Bill | 4 | 3 | Patient, Payment |
| 28 | Payment | 4 | 3 | Bill, BankCard |
| 29 | BankCard | 4 | 2 | Payment, Patient |
| 30 | Ambulance | 4 | 3 | Dispatcher, Driver, Patient |
| 31 | Dispatcher | 3 | 2 | Ambulance |
| 32 | Driver | 3 | 2 | Ambulance |
| 33 | BloodBank | 3 | 3 | Donor, BloodBag |
| 34 | BloodBag | 3 | 2 | BloodBank |
| 35 | Donor | 4 | 2 | BloodBank |
| 36 | Diet | 3 | 2 | Kitchen, Patient |
| 37 | MealPlan | 3 | 2 | Diet, Chef |
| 38 | Kitchen | 3 | 3 | Chef, MealPlan |
| 39 | Chef | 3 | 2 | Kitchen |
| 40 | CleaningService | 3 | 3 | Sanitizer, Ward |
| 41 | Sanitizer | 3 | 2 | CleaningService |
| 42 | SecuritySystem | 4 | 4 | AccessCard, Building |
| 43 | AccessCard | 3 | 3 | MedicalStaff, SecuritySystem |
| 44 | Mortuary | 3 | 2 | Pathologist |
| 45 | Pathologist | 3 | 2 | Mortuary, PathologyReport |
| 46 | PathologyReport | 4 | 2 | Pathologist |
| 47 | XRayMachine | 4 | 3 | Equipment, TestResult |
| 48 | MRIscanner | 4 | 3 | Equipment, TestResult |
| 49 | IntensiveCareUnit | 4 | 3 | Ventilator, Patient |
| 50 | Ventilator | 4 | 3 | IntensiveCareUnit, Patient |
| 51 | MedicalLicense | 3 | 2 | Doctor |
| 52 | HRDepartment | 3 | 3 | MedicalStaff, Salary |

### Исключения (12)
1. `HospitalException` (Базовое исключение)
2. `PatientNotFoundException`
3. `DoctorNotAvailableException`
4. `OperatingRoomBusyException`
5. `MedicationOutOfStockException`
6. `InsufficientFundsException`
7. `InvalidDiagnosisException`
8. `LabResultPendingException`
9. `RoomCapacityExceededException`
10. `InvalidInsuranceException`
11. `PrescriptionExpiredException`
12. `EquipmentMalfunctionException`
