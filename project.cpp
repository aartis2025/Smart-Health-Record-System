#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Patient {
    string id, name, gender;
    int age;
    float weight;
    string bp, sugar;
    string disease, allergy, medication, treatment, surgery, accident, condition, contact;
};

// Global vector to store all patients
vector<Patient> patients;

// Function to color text (Mac/VSCode friendly)
void color(string code) {
    cout << "\033[" << code << "m";
}

// Function to clear screen (Mac)
void clearScreen() {
    system("clear");
}

// Load patients from file
void loadPatients() {
    ifstream file("patients.txt");
    if (!file) {
        color("1;33");
        cout << "No existing data found. Starting fresh...\n";
        color("0");
        return;
    }
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Patient p;
        string ageStr, weightStr;
        getline(ss, p.id, ',');
        getline(ss, p.name, ',');
        getline(ss, ageStr, ',');
        p.age = stoi(ageStr);
        getline(ss, p.gender, ',');
        getline(ss, weightStr, ',');
        p.weight = stof(weightStr);
        getline(ss, p.bp, ',');
        getline(ss, p.sugar, ',');
        getline(ss, p.disease, ',');
        getline(ss, p.allergy, ',');
        getline(ss, p.medication, ',');
        getline(ss, p.treatment, ',');
        getline(ss, p.surgery, ',');
        getline(ss, p.accident, ',');
        getline(ss, p.condition, ',');
        getline(ss, p.contact, ',');
        patients.push_back(p);
    }
    file.close();
}

// Save patients to file
void savePatients() {
    ofstream file("patients.txt");
    for (auto &p : patients) {
        file << p.id << "," << p.name << "," << p.age << "," << p.gender << ","
             << p.weight << "," << p.bp << "," << p.sugar << "," << p.disease << ","
             << p.allergy << "," << p.medication << "," << p.treatment << ","
             << p.surgery << "," << p.accident << "," << p.condition << "," << p.contact << "\n";
    }
    file.close();
}

// Function to display a single patient
void displayPatient(Patient &p) {
    color("1;36");
    cout << "\n---------------------------------------------\n";
    color("0");
    cout << "ID: " << p.id << "\nName: " << p.name
         << "\nAge: " << p.age << "\nGender: " << p.gender
         << "\nWeight: " << p.weight << " kg"
         << "\nBP: " << p.bp << "\nSugar: " << p.sugar
         << "\nDisease: " << p.disease
         << "\nAllergy: " << p.allergy
         << "\nMedication: " << p.medication
         << "\nTreatment: " << p.treatment
         << "\nSurgery: " << p.surgery
         << "\nAccident: " << p.accident
         << "\nOther Condition: " << p.condition
         << "\nContact: " << p.contact << "\n";
    color("1;31");
    if (p.sugar != "-" && stof(p.sugar) > 130)
        cout << "⚠️  High Sugar Level Alert!\n";
    color("0");
}

// Add new patient
void addPatient() {
    clearScreen();
    Patient p;
    cout << "Enter Patient ID: ";
    cin >> p.id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, p.name);
    cout << "Enter Age: ";
    cin >> p.age;
    cin.ignore();
    cout << "Enter Gender (M/F): ";
    getline(cin, p.gender);
    cout << "Enter Weight (kg): ";
    cin >> p.weight;
    cin.ignore();
    cout << "Enter BP (e.g., 120/80): ";
    getline(cin, p.bp);
    cout << "Enter Sugar Level (mg/dl): ";
    getline(cin, p.sugar);
    cout << "Enter Major Disease: ";
    getline(cin, p.disease);
    cout << "Enter Allergies (if any): ";
    getline(cin, p.allergy);
    cout << "Enter Current Medication: ";
    getline(cin, p.medication);
    cout << "Enter Ongoing Treatment: ";
    getline(cin, p.treatment);
    cout << "Enter Past Surgeries: ";
    getline(cin, p.surgery);
    cout << "Enter Accident History: ";
    getline(cin, p.accident);
    cout << "Enter Other Conditions: ";
    getline(cin, p.condition);
    cout << "Enter Contact Number: ";
    getline(cin, p.contact);
    patients.push_back(p);
    savePatients();
    color("1;32");
    cout << "\nPatient added successfully!\n";
    color("0");
}

// View all patients
void viewAll() {
    clearScreen();
    if (patients.empty()) {
        cout << "No patient records available.\n";
        return;
    }
    for (auto &p : patients)
        displayPatient(p);
}

// Search patient by ID
void searchPatient() {
    clearScreen();
    string id;
    cout << "Enter Patient ID to search: ";
    cin >> id;
    bool found = false;
    for (auto &p : patients) {
        if (p.id == id) {
            displayPatient(p);
            found = true;
        }
    }
    if (!found)
        cout << "No record found with ID " << id << endl;
}

// Delete patient
void deletePatient() {
    clearScreen();
    string id;
    cout << "Enter Patient ID to delete: ";
    cin >> id;
    auto it = remove_if(patients.begin(), patients.end(), [&](Patient &p) {
        return p.id == id;
    });
    if (it != patients.end()) {
        patients.erase(it, patients.end());
        savePatients();
        color("1;31");
        cout << "Record deleted successfully!\n";
        color("0");
    } else
        cout << "Patient not found!\n";
}

// Summary report
void summaryReport() {
    clearScreen();
    int diabetic = 0, thyroid = 0, pcos = 0, allergy = 0;
    for (auto &p : patients) {
        if (p.disease.find("Diabetes") != string::npos)
            diabetic++;
        if (p.disease.find("Thyroid") != string::npos)
            thyroid++;
        if (p.disease.find("PCOS") != string::npos)
            pcos++;
        if (p.allergy != "None" && !p.allergy.empty())
            allergy++;
    }
    cout << "\n===== HEALTH SUMMARY =====\n";
    cout << "Total Patients: " << patients.size() << "\n";
    cout << "Diabetes: " << diabetic << "\nThyroid: " << thyroid
         << "\nPCOS: " << pcos << "\nAllergies: " << allergy << "\n";
}

int main() {
    loadPatients();
    int choice;
    while (true) {
        color("1;34");
        cout << "\n===== SMART HEALTH RECORD SYSTEM =====\n";
        color("0");
        cout << "1. Add New Patient\n2. View All Patients\n3. Search Patient\n";
        cout << "4. Delete Patient\n5. Summary Report\n6. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1: addPatient(); break;
        case 2: viewAll(); break;
        case 3: searchPatient(); break;
        case 4: deletePatient(); break;
        case 5: summaryReport(); break;
        case 6:
            color("1;33");
            cout << "Exiting... Data Saved!\n";
            color("0");
            savePatients();
            return 0;
        default:
            cout << "Invalid choice. Try again!\n";
        }
    }
    return 0;
}