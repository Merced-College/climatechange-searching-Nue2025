// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include "StateClimate.h"

class StateClimate {
    private:
        int fips;
        int year;
        double temp;
        double tempc;
    
    public:
        // Constructor
        StateClimate(int f, int y, double t, double tc);
    
        // Getters
        int getFips() const;
        int getYear() const;
        double getTemp() const;
        double getTempC() const;
    
        // Setters
        void setFips(int f);
        void setYear(int y);
        void setTemp(double t);
        void setTempC(double tc);
    
        // Display function
        void display() const;
};








// Constructor
StateClimate::StateClimate(int f, int y, double t, double tc) : fips(f), year(y), temp(t), tempc(tc) {}

// Getters
int StateClimate::getFips() const { return fips; }
int StateClimate::getYear() const { return year; }
double StateClimate::getTemp() const { return temp; }
double StateClimate::getTempC() const { return tempc; }

//WRITE THE SETTERS
void StateClimate::setFips(int f){
    fips = f;
}

void StateClimate::setYear(int y){
    year = y;
}

void StateClimate::setTemp(double t){
    temp = t;
}

void StateClimate::setTempC(double tc){
    tempc = tc;
}
//END THE SETTERS

// Display function
void StateClimate::display() const {
    std::cout << "FIPS: " << fips << ", Year: " << year 
              << ", Temp (F): " << temp << ", Temp (C): " << tempc << std::endl;
}


/* Notes:
Binary serach here!!!!!!!!!!!!! 
make sure that you do NOT use recursion.
*/
int binarySearch(std::vector<StateClimate> climateDataInBinary, int target){
    int lowIndex = 0;
    int highIndex = climateDataInBinary.size() - 1;
    //use loop here

    while (lowIndex <= highIndex){
        int midIndex = lowIndex + (lowIndex + highIndex)/2;
        if (target == climateDataInBinary[midIndex].getFips()){
            return midIndex;
        }else if(target < climateDataInBinary[midIndex].getFips()){
            lowIndex = midIndex + 1;
        }else if (target > climateDataInBinary[midIndex].getFips()){
            highIndex = midIndex - 1;
        }
    }
    return -1;
}//End binary search class



int main() {
    std::vector<StateClimate> climateData;
    std::ifstream file("climdiv_state_year.csv");
    
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header line
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int fips, year;
        double temp, tempc;
        char comma;

        ss >> fips >> comma >> year >> comma >> temp >> comma >> tempc;
        climateData.emplace_back(fips, year, temp, tempc);
    }

    file.close();

    //getting input for the search process upcoming
    int stateID;
    std::cout << "Enter FIP code for state: ";
    std::cin >> stateID;
    std::cout << std::endl;


//call binary search and then go through the vector and display the data
    int indexOfData = binarySearch(climateData/*VECTOR ABOVE*/, stateID/*TARGET*/);
    while(climateData.at(indexOfData).getFips() == stateID){
        climateData.at(indexOfData).display();
        indexOfData--;

        //Where does this if statement come from?
        if(indexOfData!=0){
            indexOfData++;
        }
    }
    while(climateData.at(indexOfData).getFips() == stateID){
        climateData.at(indexOfData).display();
        indexOfData--;
        if(indexOfData == climateData.size()){
            break;
        }
    }

    /* 
    // Display data
    for (const auto &entry : climateData) {
        entry.display();
    }
    */
    return 0;
}
