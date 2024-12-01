#include "medication.h"

Medication ::Medication(const std::string &id, const std::string &medicineName, int days, int quantity, bool beforeFood, const std::string &timeToTake) : id(id), medicineName(medicineName), days(days), quantity(quantity), beforeFood(beforeFood), timeToTake(timeToTake) {}

void Medication ::WriteToCSV(const std ::string &fileName = "medication.csv")
{

    std ::ofstream outFile(fileName, std::ios::app);

    // Check if the file was successfully opened
    if (!outFile.is_open())
    {

        std ::cerr << "Failed to open the CSV file." << std::endl;

        return;
    }

    // Write medication details to the CSV file
    // std:: cout << id << "," << medicineName << "," << days << "," << quantity << "," <<timeToTake<< (beforeFood ? "Before" : "After") << " food" << std::endl;
    outFile << id << "," << medicineName << "," << days << "," << quantity << "," << timeToTake << "," << (beforeFood ? "Before" : "After") << " food" << std::endl;

    outFile.close();
}

std ::string Medication ::GetMedicationName() const
{

    return id, medicineName, days, quantity, beforeFood, timeToTake;
}

// void Medication :: SetMedicationName(int id, std :: string& medicineName, int days, int quantity, bool beforeFood,const std::string& timeToTake)Medication(id, medicineName, days, quantity, beforeFood,timeToTake)  { }

// class tablet
Tablet ::Tablet(const std::string &id, const std ::string &medicineName, int days, int quantity, bool beforeFood, const std::string &timeToTake) : Medication(id, medicineName, days, quantity, beforeFood, timeToTake) {}

void Tablet ::WriteToCSV(const std ::string &fileName = "medication.csv")
{

    Medication::WriteToCSV(fileName);
}

// class tonic
Tonic ::Tonic(const std::string &id, const std ::string &medicineName, int days, int quantity, bool beforeFood, const std::string &timeToTake) : Medication(id, medicineName, days, quantity, beforeFood, timeToTake) {}

void Tonic ::WriteToCSV(const std ::string &fileName = "medication.csv")
{

    Medication ::WriteToCSV(fileName);
}
