#include <iostream>
#include <fstream>
#include <string>
 
//Base class Medication
class Medication {

    private:

        int days;

        int quantity;

        bool beforeFood;

        std::string id;

        std :: string medicineName;

        std::string timeToTake;
 
    public:

        Medication(const std::string&, const std::string&, int, int, bool, const std::string&);

        //void SetMedicationName(int, const std :: string&, int, int, bool, const std::string&);

        void WriteToCSV(const std :: string&);

        std :: string GetMedicationName() const;

};
 

//Derived class for Tablets
class Tablet : public Medication {

    public:

        Tablet(const std::string&, const std :: string&, int, int, bool, const std::string&);

        void WriteToCSV(const std :: string& );
};
 

//Derived class for Tonic
class Tonic : public Medication {

    public:

        Tonic(const std::string&, const std :: string&, int, int, bool, const std::string& );

        void WriteToCSV(const std :: string&);
};