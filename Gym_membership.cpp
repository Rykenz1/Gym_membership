#include <iostream>
#include <fstream> // For file stream operations (reading/writing files)
#include <string>  // For using the string data type and functions like getline/stoi
#include <conio.h> // Windows-specific: used for _getch() to capture instant keypresses
#include <iomanip> // For output manipulation (setting column widths)
using namespace std;

// Function Prototypes: Tells the compiler these functions exist later in the code
void viewMember();
void addMember();
void delMember();
void individually();
void csvIMP();

// Global variable: The name of the database file
string file = "memberlist.csv";

int main()
{
    /*ofstream iFile("memberlist.csv");
    iFile << "name,age" << endl;
    iFile.close();*/

    system("color b");
    int select;
    bool end = false; // Flag to control the main menu loop

    // Main Program Loop
    while (end == false) {

        // Output menu list using escape characters like \t for tabs
        cout << "no" << "|\t|" << "function name" << endl;
        cout << "____________________________" << endl;
        cout << "1 " << "|\t|" << "View Member" << endl;
        cout << "2 " << "|\t|" << "Add Member" << endl;
        cout << "3 " << "|\t|" << "Delete Member" << endl;
        cout << "0 " << "|\t|" << "end" << endl;
        cout << "\nchoose function: ";
        cin >> select;

        // Clears the terminal screen for a clean UI
        system("cls");

        // Switch-Case: Directs the program based on user input
        switch (select) {
        case 1: viewMember();
            break;
        case 2: addMember();
            break;
        case 3: delMember();
            break;
        case 0: end = true; // Breaks the while loop to exit program
            break;
        default:
            break;
        }
    }
}

void viewMember() {

    int space = 20; // Defined width for table columns

    // ifstream: Input File Stream (used for reading)
    // ios::in: Explicitly opens the file in "Read" mode
    ifstream iFile(file, ios::in);
    string name;
    int age,memCount=0;
    int totAge=0,avg;
    int curLoc = 0; // Stores the index position of the comma

    string line = "";

    // Read the very first line (the Header: Name,Age) to skip it in the table
    getline(iFile, line);

    // setw(space): Sets the width of the next output for alignment
    cout << setw(space) << "Member Name" << setw(5) << "Age" << endl;

    // Loop until the end of the file (EOF)
    while (getline(iFile, line)) {

        // Safety check: Skip processing if the line contains no data
        if (line.empty()) {
            continue; // Jumps back to the start of the while loop
        }

        // CSV Parsing Logic:
        // 1. Find the position of the comma
        curLoc = line.find(',');

        // 2. Extract Name: Get characters from index 0 up to the comma
        name = line.substr(0, curLoc);

        // 3. Extract Age String: Get everything after the comma
        line = line.substr(curLoc + 1, line.length());

        // 4. Convert String to Integer: "stoi" (String To Integer) converts the text age to a number
        age = stoi(line);

        // Display the parsed data in formatted columns
        cout << setw(space) << name << setw(5) << age << endl;
        memCount++;
        totAge += age;
    }
    avg = totAge / memCount;

    cout << "\nMember count: " << memCount<<endl;
    cout << "Age Average: " << avg<<endl;
    cout << "\npress anything to continue....";

    // _getch(): Pauses and waits for a single keypress (no Enter required)
    _getch();

    iFile.close(); // Closes the file bridge to free up memory
    system("cls");
}

void addMember() {

    int width = 15;
    char select;

    cout <<setw(width)<< "Add method|"<<setw(5)<<"No" << endl;
    cout << "_____________________________" << endl;
    cout <<setw(width)<< "Individually|"<<setw(5)<<"1" << endl;
    cout <<setw(width)<< "Import|" << setw(5) <<"2" << endl;

    cout << "==============================" << endl;

    cout << "\n(HELP)" << endl;
    cout << "\n-Individually" << endl;
    cout << "\tEnter member name and age manually" << endl;
    
    cout << "\n-Import" << endl;
    cout << "\timport data from csv file by entering csv file's" << endl;
    cout << "\tfull path" << endl;

    cout << "\nMethod: ";
    cin >> select;


    if (select == 1) {
        system("cls");
        individually();
    }
    else if(select==2) {
        csvIMP();
    }
    else {
        cout << "enter correctly lah woi!!";
    }
    
    system("cls");
}

void individually() {
    // ofstream: Output File Stream (used for writing)
    // ios::app: "Append" mode - adds new data to the end without deleting existing text
    ofstream oFile(file, ios::app);

    //members info
    string name;
    int age;

    //system variable
    char input;
    bool end = false;

    while (end == false) {
        cout << "Enter - " << endl;
        cout << "Member name: ";
        cin >> name;
        cout << "Age: ";
        cin >> age;

        // Writing to file: Format as "Name,Age" followed by a newline
        oFile << name << "," << age << endl;

        cout << "\nmember added successfully :)" << endl;
        cout << "\nAdd more member?" << endl;
        cout << "y/n?: ";

        // Capture user choice instantly using _getch()
        input = _getch();

        switch (input) {
        case 'y':
        case 'Y':
            end = false; // Continue the adding loop
            break;
        default:
            end = true; // Exit to main menu
            break;
        }
        system("cls");
    }
    oFile.close(); // Save and close the file
}

void csvIMP() {
    string line, name, fileName;
    int age, curLoc = 0;

    cout << "Enter File's full path (use / or \\\\), ex: C:/data/import.csv" << endl;
    cout << "Path: ";

    // Use getline for the path in case there are spaces in folder names
    cin.ignore(); // Clear any leftover newline from the menu
    getline(cin, fileName);

    ifstream importFile(fileName);
    // Open memberlist in Append mode to add to the bottom
    ofstream oFile(file, ios::app);

    // Safety Check: Did the import file actually open?
    if (!importFile.is_open()) {
        cout << "Error: Could not find or open the import file!" << endl;
        cout << "Check if the path is correct." << endl;
        _getch();
        return;
    }

    // Skip the header row of the import file
    getline(importFile, line);

    int count = 0;
    while (getline(importFile, line)) {
        if (line.empty()) continue;

        curLoc = line.find(',');
        if (curLoc == string::npos) continue; // Skip lines without a comma

        name = line.substr(0, curLoc);
        line = line.substr(curLoc + 1, line.length());
        age = stoi(line);

        // Write directly to your main memberlist
        oFile << name << "," << age << endl;
        count++;
    }

    importFile.close();
    oFile.close();

    cout << "\nImport Successful! " << count << " members added." << endl;
    cout << "Press any key to continue...";
    _getch();
    system("cls");
}

void delMember() {
    ifstream iFile(file);
    // Create a temporary file to store everyone EXCEPT the person we are deleting
    ofstream tempFile("temp.csv");

    string nameToDelete, line, searchName;
    bool found = false;

    cout << "Enter name to delete: ";
    cin >> nameToDelete;

    // 1. Copy the header first so it isn't lost
    if (getline(iFile, line)) {
        tempFile << line << endl;
    }

    // 2. Loop through all members
    while (getline(iFile, line)) {
        if (line.empty()) continue;

        int curLoc = line.find(',');
        searchName = line.substr(0, curLoc);

        // 3. If it's NOT the name we want, save it to the temp file
        if (searchName != nameToDelete) {
            tempFile << line << endl;
        }
        else {
            found = true; // We found the target, so we simply DON'T write it
        }
    }

    iFile.close();
    tempFile.close();

    // 4. Replace the old file with the new one
    if (found) {
        remove("memberlist.csv");             // Delete old file
        rename("temp.csv", "memberlist.csv"); // Rename temp to original
        cout << "\nMember successfully deleted!" << endl;
    }
    else {
        remove("temp.csv"); // Delete the temp file if nothing changed
        cout << "\nMember not found." << endl;
    }

    cout << "Press any key to continue...";
    _getch();
    system("cls");
}