#include <iostream>
#include <fstream> // For file stream operations (reading/writing files)
#include <string>  // For using the string data type and functions like getline/stoi
#include <conio.h> // used for _getch() to capture instant keypresses
#include <iomanip> // For output manipulation (setting column widths)
using namespace std;

// Function Prototypes
void staffMenu();   //Admin page
void addMember();   //Create
void viewMember();  //Read
void updMember();   //Update
void delMember();   //Delete
void individually();//
void csvIMP();      //

void searchUser();    //search user
void userMenu(string, int, string& rank, string& status);
void displayUser(string, int, string& rank, string& status);
void changeRank(string, int, string& rank, string& status);
void payment(string& status);
void PATC();        //Press Anything to continue

void bye();

// Global variable: The name of the database file
string file = "memberlist.csv";

int main()
{
    system("color b");
    bool end = false;
    char input;

    while (end != true) {
        system("cls");
        cout << " /=================================================\\" << endl;
        cout << "| ---WELCOME TO GYM MEMBERSHIP MANAGEMENT SYSTEM--- |" << endl;
        cout << " \\=================================================/" << endl;


        cout << "\nLogin options:" << endl;
        cout << "1- \tStaff" << endl;
        cout << "2- \tUser" << endl;
        cout << "\n0- \tExit" << endl;
        cout << "\nWhat are you?:";

        input = _getch();

        if (input == '1') {

            staffMenu();
        }
        else if (input == '2') {
            searchUser();
        }
        else {
            end = true;
        }
    }

    bye();
}

void staffMenu() {

    char select;
    bool end = false; // Flag to control the main menu loop

    // Main Program Loop
    while (end != true) {
        system("cls");
        // Output menu list using escape characters like \t for tabs
        cout << "no" << "|\t|" << "function name" << endl;
        cout << "____________________________" << endl;
        cout << "1 " << "|\t|" << "View Member" << endl;
        cout << "2 " << "|\t|" << "Add Member" << endl;
        cout << "3 " << "|\t|" << "Update Member" << endl;
        cout << "4 " << "|\t|" << "Delete Member" << endl;
        cout << "0 " << "|\t|" << "end" << endl;
        cout << "\nchoose function: ";

        select = _getch();

        // Clears the terminal screen for a clean UI
        system("cls");

        // Switch-Case: Directs the program based on user input
        switch (select) {
        case '1': viewMember();
            break;
        case '2': addMember();
            break;
        case '3': updMember();
            break;
        case '4': delMember();
            break;
        case '0': end = true; // Breaks the while loop to exit program
            break;
        default:
            break;
        }
    }
}

void searchUser() {

    system("cls");

    string username;
    cout << "Enter username: ";
    getline(cin >> ws, username);

    system("cls");

    ifstream iFile(file);//open file
    ofstream oFile("temp.csv", ios::app);//create temp file
    int curLoc, age;
    bool found = false;
    bool end = false;
    string nameSearch, line, rank, status;

    getline(iFile, line);
    oFile << line << endl;

    //loop to check user in member.csv
    while (getline(iFile, line)) {

        curLoc = line.find(",");
        nameSearch = line.substr(0, curLoc);

        if (username == nameSearch) {
            found = true;
            break;
        }
        else {
            //copy line from ifile to temp file
            oFile << line << endl;
            found = false;
        }
    }

    if (found == true) {
        line = line.substr(curLoc + 1, line.length());
        curLoc = line.find(",");
        age = stoi(line.substr(0, curLoc));
        line = line.substr(curLoc + 1, line.length());
        curLoc = line.find(",");
        rank = line.substr(0, curLoc);
        status = line.substr(curLoc + 1, line.length());

        userMenu(username, age, rank, status);

        oFile << nameSearch << "," << age << "," << rank << "," << status << endl;
        while (getline(iFile, line)) {
            oFile << line << endl;
        }
    }
    else {
        cout << "name not found :(" << endl;
        PATC();
    }

    iFile.close();
    oFile.close();

    //delete or replace file after before finish
    if (found) {
        remove("memberlist.csv");
        rename("temp.csv", "memberlist.csv");
    }
    else {
        remove("temp.csv");
    }
}

void userMenu(string username, int age, string& rank, string& status) {
    system("cls");
    char input;
    bool end = false;


    while (end != true) {
        system("cls");
        cout << "Welcome " << username << "!!" << endl;
        cout << "\nUser Menu" << endl;
        cout << "1- View Profile" << endl;
        cout << "2- Change Rank" << endl;
        cout << "3- Pay Subscription" << endl;
        cout << "\n0- Exit" << endl;

        cout << "\nInput: ";
        input = _getch();

        switch (input) {
        case '1': displayUser(username, age, rank, status);
            break;
        case '2': {
            changeRank(username, age, rank, status);
        }
                break;
        case '3': {
            payment(status);
        }
                break;
        default:
            end = true;
            break;
        }


    }
}

void displayUser(string username, int age, string& rank, string& status) {
    system("cls");
    cout << "name: " << username << endl;
    cout << "age: " << age << endl;
    cout << "rank: " << rank << endl;
    cout << "payment: " << status << endl;

    cout << endl;
    PATC();
}

void changeRank(string username, int age, string& rank, string& status) {
    system("cls");
    char input;
    cout << "Your current rank is: " << rank << endl;
    cout << "RANKS" << endl;
    cout << "1- Basic" << endl;
    cout << "2- Silver" << endl;
    cout << "3- Gold" << endl;
    cout << "\nChange your rank to?: ";

    input = _getch();
    switch (input) {
    case '1': rank = "basic";
        break;
    case '2': rank = "silver";
        break;
    case '3': rank = "gold";
        break;
    default:
        break;
    }


    cout << "\nSuccessfully upgrade your rank to " << rank << "!!! Enjoy your privileges :)" << endl;
    PATC();
}

void payment(string& status) {
    system("cls");
    char input;
    cout << "Current payment: " << status << endl;;
    cout << "Ready to pay? Y/n" << endl;
    input = _getch();

    if (input == 'y' || input == 'Y') {
        status = "paid";
        cout << "Thank you for your support :D" << endl;
    }
    else {
        cout << "Its fine, you can pay later" << endl;
    }
    PATC();
}

void viewMember() {

    int space = 20; // Defined width for table columns

    // ifstream: Input File Stream (used for reading)
    // ios::in: Explicitly opens the file in "Read" mode
    ifstream iFile(file, ios::in);
    string name, rank, status;
    int age, memCount = 0;
    int totAge = 0, avg;
    int curLoc = 0; // Stores the index position of the comma

    string line = "";

    // Read the very first line (the Header: Name,Age) to skip it in the table
    getline(iFile, line);

    // setw(space): Sets the width of the next output for alignment
    cout << setw(space) << "Member Name" << setw(5) << "Age" << setw(10) << "Rank" << setw(10) << "Status" << endl;

    // Loop until the end of the file (EOF)
    while (getline(iFile, line)) {

        // Safety check: Skip processing if the line contains no data
        if (line.empty()) {
            continue; // Jumps back to the start of the while loop
        }


        curLoc = line.find(',');
        name = line.substr(0, curLoc);

        line = line.substr(curLoc + 1, line.length());
        curLoc = line.find(',');
        age = stoi(line.substr(0, curLoc));

        line = line.substr(curLoc + 1, line.length());
        curLoc = line.find(',');
        rank = line.substr(0, curLoc);

        line = line.substr(curLoc + 1, line.length());
        status = line;

        // Display the parsed data in formatted columns
        cout << setw(space) << name << setw(5) << age << setw(10) << rank << setw(10) << status << endl;
        //member counter
        memCount++;
        totAge += age;
    }

    if (memCount == 0) {
        system("cls");
        cout << "No member :(" << endl;
    }
    else {
        avg = totAge / memCount;

        cout << "\nMember count: " << memCount << endl;
        cout << "Age Average: " << avg << endl << endl;
    }
    //calculate average member age

    iFile.close(); // Closes the file
    PATC();
}

void addMember() {

    int width = 15;
    int select;

    cout << setw(width) << "Add method|" << setw(5) << "No" << endl;
    cout << "_____________________________" << endl;
    cout << setw(width) << "Individually|" << setw(5) << "1" << endl;
    cout << setw(width) << "Import|" << setw(5) << "2" << endl;

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

        individually();
    }
    else if (select == 2) {
        csvIMP();
    }
    else {
        system("cls");
        cout << "enter correctly lah woi!!" << endl;
        PATC();
    }

    system("cls");
}

void individually() { // input member individually

    system("cls");
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
        getline(cin >> ws, name);
        //cin >> name;
        cout << "Age: ";
        cin >> age;

        // Writing to file: Format as "Name,Age" followed by a newline
        oFile << name << "," << age << ",basic" << ",pending" << endl;

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

void csvIMP() {//import csv function
    system("cls");
    string line, name, fileName, rank;
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
        PATC();
        return;
    }

    // Skip the header row of the import file
    getline(importFile, line);

    int count = 0;
    while (getline(importFile, line)) {
        if (line.empty()) continue;

        curLoc = line.find(',');
        //if (curLoc == string::npos) continue; // Skip lines without a comma

        name = line.substr(0, curLoc);
        line = line.substr(curLoc + 1, line.length());
        curLoc = line.find(',');
        age = stoi(line.substr(0, curLoc));
        line = line.substr(curLoc + 1, line.length());
        curLoc = line.find(',');
        rank = line.substr(0, curLoc);

        // Write directly to your main memberlist
        oFile << name << "," << age << "," << rank << ",pending" << endl;
        count++;
    }

    importFile.close();
    oFile.close();

    cout << "\nImport Successful! " << count << " members added." << endl;
    PATC();
}

void updMember() {
    string targetName, line, searchName, searchAge, newName, keep;
    string currentAge;
    int newAge, curLoc;
    bool found = false;

    // 1. Ask who to update before entering the menu
    cout << "Enter the name of the member you want to update: ";
    getline(cin >> ws, targetName);

    ifstream iFile(file);
    ofstream tempFile("temp.csv");

    if (!iFile.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    // Copy Header
    if (getline(iFile, line)) {
        tempFile << line << endl;
    }

    // 2. Process the file
    while (getline(iFile, line)) {
        if (line.empty()) continue;

        curLoc = line.find(',');
        searchName = line.substr(0, curLoc);
        searchAge = line.substr(curLoc + 1, line.length());
        curLoc = searchAge.find(',');
        currentAge = searchAge.substr(0, curLoc);
        keep = searchAge.substr(curLoc, searchAge.length());

        if (searchName == targetName) {
            found = true;
            system("cls");
            cout << "Updating record for: " << targetName << endl;
            cout << "1. Update Name" << endl;
            cout << "2. Update Age" << endl;
            cout << "3. Update Both" << endl;
            cout << "Choice: ";
            int select;
            cin >> select;

            if (select == 1) {
                cout << "New Name: ";
                getline(cin >> ws, newName);
                tempFile << newName << "," << currentAge << keep << endl;
            }
            else if (select == 2) {
                cout << "New Age: ";
                cin >> newAge;
                tempFile << searchName << "," << newAge << keep << endl;
            }
            else if (select == 3) {
                cout << "New Name: ";
                getline(cin >> ws, newName);
                cout << "New Age: ";
                cin >> newAge;
                tempFile << newName << "," << newAge << keep << endl;
            }
        }
        else {
            // Not the person we want to update, just copy the original line
            tempFile << line << endl;
        }
    }

    iFile.close();
    tempFile.close();

    // 3. Finalize file swap
    if (found) {
        remove("memberlist.csv");
        rename("temp.csv", "memberlist.csv");
        cout << "\nUpdate Successful!" << endl;
    }
    else {
        remove("temp.csv");
        cout << "\nMember not found." << endl;
    }

    PATC();
    system("cls");
}

void delMember() {


    ifstream iFile(file);
    // Create a temporary file to store everyone EXCEPT the person we are deleting
    ofstream tempFile("temp.csv");

    string nameToDelete, line, searchName;
    bool found = false;

    cout << "Enter name to delete: ";
    getline(cin >> ws, nameToDelete);

    // 1. Copy the header first so it isn't lost
    if (getline(iFile, line)) {
        tempFile << line << endl;
    }

    // 2. Loop through all members
    while (getline(iFile, line)) {
        if (line.empty()) {
            continue;
        }

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

    PATC();
}

void PATC() {
    cout << "Press anything to continue...";
    _getch();
    system("cls");
}

void bye() {
    system("cls");
    cout << "______  __   __  _____   _____ " << endl;
    cout << "| ___ \\ \\ \\ / / |  ___| |  ___|" << endl;
    cout << "| |_/ /  \\ V /  | |__   | |__  " << endl;
    cout << "| ___ \\   \\ /   |  __|  |  __| " << endl;
    cout << "| |_/ /   | |   | |___  | |___ " << endl;
    cout << "\\____/    \\_/   \\____/  \\____/ " << endl;
    cout << endl << endl;
}
