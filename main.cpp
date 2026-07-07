/*
 * ============================================================
 *  HOME APPLIANCE POWER USAGE MONITOR AND COST ESTIMATOR
 * ============================================================
 *  Course   : BEE 208 - C++ Programming
 *  Project  : Project Question 25
 *  Purpose  : Record household appliances, calculate their
 *             energy usage, estimate electricity cost, and
 *             warn about appliances that use too much power.
 *
 *  Think of this program like a notebook that:
 *   1) Remembers every appliance you tell it about
 *   2) Does the maths for how much power each one uses
 *   3) Tells you how much money you will pay
 *   4) Saves everything to a file so you don't lose it
 * ============================================================
 */

#include <iostream>   // lets us print to screen and read keyboard input
#include <fstream>    // lets us read/write files
#include <vector>     // lets us keep a growable list of appliances
#include <iomanip>    // lets us format numbers nicely (2 decimal places etc.)
#include <string>     // lets us use text (string) variables
#include <limits>     // helps us clean up bad keyboard input
#include <sstream>    // lets us build text reports and split saved data lines

using namespace std;

// ------------------------------------------------------------
// CLASS: Appliance
// ------------------------------------------------------------
// A "class" is like a blueprint for a toy box. Every appliance
// we add is a new toy box built from this same blueprint. Each
// box holds: an ID tag, a name, how much power it uses, how many
// hours a day it runs, and how many of that appliance we have.
// ------------------------------------------------------------
class Appliance {
private:
    string applianceID;      // e.g. A001
    string applianceName;    // e.g. Refrigerator
    double powerRating;      // watts, e.g. 150
    double hoursPerDay;      // e.g. 24
    int quantity;            // e.g. 1
    double dailyEnergy;      // kWh used per day
    double monthlyEnergy;    // kWh used per month

public:
    // Default constructor - makes an "empty" appliance box
    Appliance() {
        applianceID = "";
        applianceName = "";
        powerRating = 0.0;
        hoursPerDay = 0.0;
        quantity = 0;
        dailyEnergy = 0.0;
        monthlyEnergy = 0.0;
    }

    // ---- setApplianceDetails() ----
    // This asks the user questions and stores the answers.
    // It keeps asking again if the person types something silly
    // (like a negative number), because negative power doesn't
    // make sense in real life.
    void setApplianceDetails() {
        cout << "\nEnter Appliance ID (e.g., A001): ";
        cin >> applianceID;

        cout << "Enter Appliance Name (e.g., Refrigerator): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, applianceName);

        powerRating = readPositiveDouble("Enter Power Rating (Watts): ");
        hoursPerDay = readValidHours("Enter Average Usage Hours per Day (0-24): ");
        quantity    = readPositiveInt("Enter Quantity: ");
    }

    // Helper: keeps asking until the user gives a positive number.
    // "Positive" just means bigger than zero - you can't have a
    // fridge that uses -5 watts, that's not real!
    double readPositiveDouble(string prompt) {
        double value;
        while (true) {
            cout << prompt;
            cin >> value;

            if (cin.fail()) {                 // user typed letters instead of numbers
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Invalid input. Please enter a number.\n";
                continue;
            }
            if (value < 0) {
                cout << "  Value cannot be negative. Try again.\n";
                continue;
            }
            return value;
        }
    }

    // Helper: hours per day must be between 0 and 24, because
    // there are only 24 hours in a day - no appliance can run
    // for 30 hours in one day!
    double readValidHours(string prompt) {
        double value;
        while (true) {
            cout << prompt;
            cin >> value;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Invalid input. Please enter a number.\n";
                continue;
            }
            if (value < 0 || value > 24) {
                cout << "  Hours must be between 0 and 24. Try again.\n";
                continue;
            }
            return value;
        }
    }

    // Helper: quantity must be a whole positive number (you can't
    // own -2 televisions).
    int readPositiveInt(string prompt) {
        int value;
        while (true) {
            cout << prompt;
            cin >> value;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Invalid input. Please enter a whole number.\n";
                continue;
            }
            if (value <= 0) {
                cout << "  Quantity must be greater than zero. Try again.\n";
                continue;
            }
            return value;
        }
    }

    // ---- validateDetails() ----
    // Double-checks that nothing sneaky/negative got stored.
    // This is like a safety guard that checks the toy box before
    // it goes on the shelf.
    bool validateDetails() const {
        if (powerRating < 0 || hoursPerDay < 0 || quantity < 0) {
            return false;
        }
        return true;
    }

    // ---- calculateEnergyUsage() ----
    // This is the maths part. We turn watts into kilowatt-hours
    // (kWh), which is the unit the electricity company uses to
    // charge you.
    //
    //   Daily Energy (kWh)  = (Power Rating x Hours x Quantity) / 1000
    //   Monthly Energy (kWh) = Daily Energy x 30
    void calculateEnergyUsage() {
        dailyEnergy = (powerRating * hoursPerDay * quantity) / 1000.0;
        monthlyEnergy = dailyEnergy * 30.0;
    }

    // ---- displayApplianceReport() ----
    // Prints one neat row of this appliance's info, like one line
    // in a school register.
    void displayApplianceReport() const {
        cout << left << setw(8) << applianceID
             << setw(18) << applianceName
             << setw(11) << powerRating
             << setw(12) << hoursPerDay
             << setw(11) << quantity
             << setw(12) << fixed << setprecision(2) << dailyEnergy
             << setw(12) << fixed << setprecision(2) << monthlyEnergy
             << "\n";
    }

    // ---- saveApplianceRecord() ----
    // Writes this appliance's info into a text file, so it is
    // remembered even after the program closes - like writing in
    // a diary so you remember it tomorrow.
    void saveApplianceRecord(ofstream &file) const {
        file << applianceID << "," << applianceName << "," << powerRating << ","
             << hoursPerDay << "," << quantity << "," << dailyEnergy << ","
             << monthlyEnergy << "\n";
    }

    // ---- Getters ----
    // Small helper functions that let other parts of the program
    // "peek" at private information safely.
    string getID() const { return applianceID; }
    string getName() const { return applianceName; }
    double getPowerRating() const { return powerRating; }
    double getHoursPerDay() const { return hoursPerDay; }
    int getQuantity() const { return quantity; }
    double getDailyEnergy() const { return dailyEnergy; }
    double getMonthlyEnergy() const { return monthlyEnergy; }

    // Allows loading a saved record back from the CSV line.
    void loadFromValues(string id, string name, double power, double hours,
                         int qty, double daily, double monthly) {
        applianceID = id;
        applianceName = name;
        powerRating = power;
        hoursPerDay = hours;
        quantity = qty;
        dailyEnergy = daily;
        monthlyEnergy = monthly;
    }
};

// ------------------------------------------------------------
// GLOBAL DATA
// ------------------------------------------------------------
// A vector is like a magic box that can hold as many appliances
// as we want, and it grows automatically when we add more.
// ------------------------------------------------------------
vector<Appliance> applianceList;
double tariff = 0.0;               // GHS per kWh - the price of electricity
double highConsumptionThreshold = 0.0; // kWh per month - the "too much!" line

const string REPORT_FILE = "home_appliance_report.txt";
const string DATA_FILE = "appliance_data.csv";

// ------------------------------------------------------------
// FUNCTION DECLARATIONS
// ------------------------------------------------------------
void displayTitle();
void inputSetup();
void showMenu();
void addAppliance();
void viewAllAppliances();
void searchAppliance();
void deleteAppliance();
void generateReport(bool saveToFile);
void saveAllRecordsToFile();
void loadRecordsFromFile();
double getPositiveNumber(string prompt);

// ------------------------------------------------------------
// main() - This is where the program starts running, like the
// "Start" button on a game.
// ------------------------------------------------------------
int main() {
    displayTitle();
    loadRecordsFromFile();   // remember appliances from last time
    inputSetup();            // ask for tariff and threshold

    int choice = -1;

    // A loop that keeps showing the menu until the user picks Exit.
    // Think of it like a merry-go-round that keeps spinning until
    // someone says "stop!"
    while (choice != 7) {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid choice. Please enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
            case 1: addAppliance(); break;
            case 2: viewAllAppliances(); break;
            case 3: searchAppliance(); break;
            case 4: deleteAppliance(); break;
            case 5: generateReport(false); break;              // view report on screen
            case 6: generateReport(true); saveAllRecordsToFile(); break; // save report + data
            case 7: cout << "\nSaving data and exiting. Goodbye!\n"; saveAllRecordsToFile(); break;
            default: cout << "\nInvalid choice. Please pick an option from 1 to 7.\n";
        }
    }
    return 0;
}

// ------------------------------------------------------------
// displayTitle() - Shows a nice welcome banner, like the cover
// page of a book.
// ------------------------------------------------------------
void displayTitle() {
    cout << "=========================================================\n";
    cout << "   HOME APPLIANCE POWER USAGE MONITOR AND COST ESTIMATOR\n";
    cout << "=========================================================\n";
    cout << "  BEE 208 - C++ Programming | Project Question 25\n";
    cout << "=========================================================\n\n";
}

// ------------------------------------------------------------
// getPositiveNumber() - A reusable helper to safely ask for a
// number that must not be negative, used for tariff & threshold.
// ------------------------------------------------------------
double getPositiveNumber(string prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please enter a number.\n";
            continue;
        }
        if (value < 0) {
            cout << "  Value cannot be negative. Try again.\n";
            continue;
        }
        return value;
    }
}

// ------------------------------------------------------------
// inputSetup() - Asks the two "settings" the whole program needs:
//   1) tariff: how much 1 kWh of electricity costs, in GHS
//   2) highConsumptionThreshold: the kWh/month line where we say
//      "whoa, that appliance uses a LOT of power!"
// ------------------------------------------------------------
void inputSetup() {
    tariff = getPositiveNumber("Enter electricity tariff (GHS per kWh): ");
    highConsumptionThreshold = getPositiveNumber(
        "Enter high-consumption threshold (kWh per month): ");
}

// ------------------------------------------------------------
// showMenu() - Prints the list of things the user can do, like
// a restaurant menu where you pick a number for what you want.
// ------------------------------------------------------------
void showMenu() {
    cout << "\n---------------------- MAIN MENU -----------------------\n";
    cout << "1. Add Appliance\n";
    cout << "2. View All Appliances\n";
    cout << "3. Search Appliance (by ID or Name)\n";
    cout << "4. Delete Appliance\n";
    cout << "5. View Report (on screen)\n";
    cout << "6. Save Report to File\n";
    cout << "7. Exit\n";
    cout << "-----------------------------------------------------------\n";
}

// ------------------------------------------------------------
// addAppliance() - Creates one new Appliance "toy box", fills it
// in with the user's answers, checks it's valid, does the maths,
// then puts it into our big vector list.
// ------------------------------------------------------------
void addAppliance() {
    Appliance a;
    a.setApplianceDetails();

    if (!a.validateDetails()) {
        cout << "\n  Invalid appliance data. Appliance was NOT added.\n";
        return;
    }

    a.calculateEnergyUsage();
    applianceList.push_back(a);   // push_back = "add to the end of the list"
    cout << "\n  Appliance added successfully!\n";
}

// ------------------------------------------------------------
// viewAllAppliances() - Prints every appliance in our list, one
// row at a time, like reading out every name on a class register.
// ------------------------------------------------------------
void viewAllAppliances() {
    if (applianceList.empty()) {
        cout << "\nNo appliances recorded yet.\n";
        return;
    }

    cout << "\n" << left << setw(8) << "ID" << setw(18) << "Name"
         << setw(11) << "Power(W)" << setw(12) << "Hours/Day"
         << setw(11) << "Quantity" << setw(12) << "Daily kWh"
         << setw(12) << "Monthly kWh" << "\n";
    cout << "----------------------------------------------------------------------\n";

    // A "for each" loop - it visits every appliance in the list,
    // one after another, and prints it.
    for (const auto &appliance : applianceList) {
        appliance.displayApplianceReport();
    }
}

// ------------------------------------------------------------
// searchAppliance() - Lets the user type an ID or a name, and we
// look through the whole list to find a match, like playing
// "Where's Wally?" but for appliances.
// ------------------------------------------------------------
void searchAppliance() {
    if (applianceList.empty()) {
        cout << "\nNo appliances recorded yet.\n";
        return;
    }

    string keyword;
    cout << "\nEnter Appliance ID or Name to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyword);

    bool found = false;
    for (const auto &appliance : applianceList) {
        if (appliance.getID() == keyword || appliance.getName() == keyword) {
            cout << "\nAppliance Found:\n";
            cout << left << setw(8) << "ID" << setw(18) << "Name"
                 << setw(11) << "Power(W)" << setw(12) << "Hours/Day"
                 << setw(11) << "Quantity" << setw(12) << "Daily kWh"
                 << setw(12) << "Monthly kWh" << "\n";
            appliance.displayApplianceReport();
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo appliance matched that ID or Name.\n";
    }
}

// ------------------------------------------------------------
// deleteAppliance() - Removes one appliance from the list by ID,
// like erasing one line from a notebook.
// ------------------------------------------------------------
void deleteAppliance() {
    if (applianceList.empty()) {
        cout << "\nNo appliances recorded yet.\n";
        return;
    }

    string id;
    cout << "\nEnter Appliance ID to delete: ";
    cin >> id;

    // We look through the list to find the matching ID.
    for (size_t i = 0; i < applianceList.size(); i++) {
        if (applianceList[i].getID() == id) {
            applianceList.erase(applianceList.begin() + i); // remove it
            cout << "\n  Appliance " << id << " deleted successfully.\n";
            return;
        }
    }

    cout << "\n  No appliance found with ID " << id << ".\n";
}

// ------------------------------------------------------------
// generateReport() - Adds up all the daily and monthly energy,
// works out the total cost, and lists which appliances use too
// much power. If saveToFile is true, it also writes everything
// into home_appliance_report.txt.
// ------------------------------------------------------------
void generateReport(bool saveToFile) {
    if (applianceList.empty()) {
        cout << "\nNo appliances recorded yet. Nothing to report.\n";
        return;
    }

    double totalDaily = 0.0;
    double totalMonthly = 0.0;

    // Add up every appliance's energy - like counting all your
    // coins to see how much money you have in total.
    for (const auto &appliance : applianceList) {
        totalDaily += appliance.getDailyEnergy();
        totalMonthly += appliance.getMonthlyEnergy();
    }

    double totalCost = totalMonthly * tariff;

    // Build the report as text so we can print it AND save it
    // using the exact same content (no repeated code).
    ostringstream report;
    report << "HOME APPLIANCE POWER USAGE REPORT\n";
    report << "=================================\n";
    report << "Tariff: GHS " << fixed << setprecision(2) << tariff << " per kWh\n";
    report << "High Consumption Threshold: " << highConsumptionThreshold << " kWh/month\n\n";

    report << left << setw(8) << "ID" << setw(18) << "Name"
           << setw(11) << "Power(W)" << setw(12) << "Hours/Day"
           << setw(11) << "Quantity" << setw(12) << "Daily kWh"
           << setw(12) << "Monthly kWh" << "\n";
    report << "----------------------------------------------------------------------\n";

    for (const auto &appliance : applianceList) {
        report << left << setw(8) << appliance.getID()
               << setw(18) << appliance.getName()
               << setw(11) << appliance.getPowerRating()
               << setw(12) << appliance.getHoursPerDay()
               << setw(11) << appliance.getQuantity()
               << setw(12) << fixed << setprecision(2) << appliance.getDailyEnergy()
               << setw(12) << fixed << setprecision(2) << appliance.getMonthlyEnergy()
               << "\n";
    }

    report << "\nTOTAL DAILY ENERGY (kWh): " << fixed << setprecision(2) << totalDaily << "\n";
    report << "TOTAL MONTHLY ENERGY (kWh): " << fixed << setprecision(2) << totalMonthly << "\n";
    report << "ESTIMATED MONTHLY COST (GHS): " << fixed << setprecision(2) << totalCost << "\n";

    // Decision rule: if an appliance's monthly energy is above the
    // threshold, we flag it as "High Consumption".
    report << "\nHIGH CONSUMPTION APPLIANCES:\n";
    bool anyHigh = false;
    for (const auto &appliance : applianceList) {
        if (appliance.getMonthlyEnergy() > highConsumptionThreshold) {
            report << appliance.getID() << " - " << appliance.getName() << " - "
                   << fixed << setprecision(2) << appliance.getMonthlyEnergy()
                   << " kWh/month\n";
            anyHigh = true;
        }
    }
    if (!anyHigh) {
        report << "None. All appliances are within normal consumption range.\n";
    }

    // Print the report to the screen so the user sees it right away.
    cout << "\n" << report.str();

    // If asked, also save it into a text file.
    if (saveToFile) {
        ofstream outFile(REPORT_FILE);
        if (outFile.is_open()) {
            outFile << report.str();
            outFile.close();
            cout << "\nReport saved to " << REPORT_FILE << "\n";
        } else {
            cout << "\nError: Could not open file to save the report.\n";
        }
    }
}

// ------------------------------------------------------------
// saveAllRecordsToFile() - Saves the raw appliance data (not the
// pretty report, just the numbers) so the program can reload it
// next time it starts, like saving your progress in a video game.
// ------------------------------------------------------------
void saveAllRecordsToFile() {
    ofstream dataFile(DATA_FILE);
    if (!dataFile.is_open()) {
        cout << "\nError: Could not save appliance data.\n";
        return;
    }
    for (const auto &appliance : applianceList) {
        appliance.saveApplianceRecord(dataFile);
    }
    dataFile.close();
}

// ------------------------------------------------------------
// loadRecordsFromFile() - Reads the saved data file (if it
// exists) when the program starts, so you don't have to type
// everything again - like continuing a saved game.
// ------------------------------------------------------------
void loadRecordsFromFile() {
    ifstream dataFile(DATA_FILE);
    if (!dataFile.is_open()) {
        return; // no saved file yet - that's OK, just start fresh
    }

    string line;
    while (getline(dataFile, line)) {
        if (line.empty()) continue;

        // Each line looks like: ID,Name,Power,Hours,Quantity,Daily,Monthly
        // We split it apart using commas.
        stringstream ss(line);
        string idStr, nameStr, powerStr, hoursStr, qtyStr, dailyStr, monthlyStr;

        getline(ss, idStr, ',');
        getline(ss, nameStr, ',');
        getline(ss, powerStr, ',');
        getline(ss, hoursStr, ',');
        getline(ss, qtyStr, ',');
        getline(ss, dailyStr, ',');
        getline(ss, monthlyStr, ',');

        Appliance a;
        a.loadFromValues(idStr, nameStr, stod(powerStr), stod(hoursStr),
                          stoi(qtyStr), stod(dailyStr), stod(monthlyStr));
        applianceList.push_back(a);
    }
    dataFile.close();

    if (!applianceList.empty()) {
        cout << "Loaded " << applianceList.size() << " saved appliance record(s).\n";
    }
}
