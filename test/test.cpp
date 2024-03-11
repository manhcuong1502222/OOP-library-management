#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Reader {
    int readerID;
    string name;
    string gender;
    string status;

    Reader(int id, string name, string gen, string stat) : readerID(id), name(name), gender(gen), status(stat) {}
};

class Library {
private:
    vector<Reader> readerList;
    int nextReaderID;

public:
    Library() : nextReaderID(1) {}

    // Add reader
    void addReader(string name, string gender, string status) {
        readerList.push_back(Reader(nextReaderID, name, gender, status));
        nextReaderID++;
    }

    // Delete reader
    void deleteReader(int readerID) {
        auto it = find_if(readerList.begin(), readerList.end(), [readerID](const Reader& rd) {
            return rd.readerID == readerID;
            });

        if (it != readerList.end()) {
            readerList.erase(it);
            cout << "Deleted reader with ID " << readerID << "." << endl;
        }
        else {
            cout << "No reader found with ID " << readerID << "." << endl;
        }
    }

    // Display list
    void displayList() {
        for (const Reader& rd : readerList) {
            cout << "Reader ID: " << rd.readerID << ", Name: " << rd.name << ", Gender: " << rd.gender << ", Status: " << rd.status << endl;
        }
    }
};

bool isValidGender(string gender) {
    return gender == "male" || gender == "female";
}

bool isValidStatus(string status) {
    return status == "lock" || status == "active";
}

int main() {
    Library library;

    int choice;
    do {
        cout << "\nMenu: " << endl;
        cout << "1. Add reader" << endl;
        cout << "2. Delete reader" << endl;
        cout << "3. Display list" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, gender, status;
            cout << "Enter reader name: ";
            cin.ignore(); 
            getline(cin, name);

            do {
                cout << "Enter gender (male/female): ";
                cin >> gender;
            } while (!isValidGender(gender));

            do {
                cout << "Enter status (lock/active): ";
                cin >> status;
            } while (!isValidStatus(status));

            library.addReader(name, gender, status);
            break;
        }
        case 2: {
            int readerID;
            cout << "Enter reader ID to delete: ";
            cin >> readerID;
            library.deleteReader(readerID);
            break;
        }
        case 3:
            library.displayList();
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
