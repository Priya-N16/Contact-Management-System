#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

class Contact
{
public:
    int id;
    string name;
    string phone;
    string email;
    string address;

    Contact() {}

    Contact(int i, string n, string p, string e, string a)
    {
        id = i;
        name = n;
        phone = p;
        email = e;
        address = a;
    }
};

vector<Contact> contacts;
const string FILE_NAME = "contacts.txt";

// Load contacts from file
void loadContacts()
{
    ifstream file(FILE_NAME);

    if (!file)
        return;

    Contact c;

    while (file >> c.id)
    {
        file.ignore();
        getline(file, c.name);
        getline(file, c.phone);
        getline(file, c.email);
        getline(file, c.address);

        contacts.push_back(c);
    }

    file.close();
}

// Save contacts to file
void saveContacts()
{
    ofstream file(FILE_NAME);

    for (const auto &c : contacts)
    {
        file << c.id << '\n';
        file << c.name << '\n';
        file << c.phone << '\n';
        file << c.email << '\n';
        file << c.address << '\n';
    }

    file.close();
}

// Generate next contact ID
int getNextId()
{
    int id = 1;

    for (const auto &c : contacts)
    {
        if (c.id >= id)
            id = c.id + 1;
    }

    return id;
}

// Add Contact
void addContact()
{
    Contact c;

    c.id = getNextId();

    cin.ignore();

    cout << "\n===== ADD CONTACT =====\n";

    cout << "Name    : ";
    getline(cin, c.name);

    cout << "Phone   : ";
    getline(cin, c.phone);

    cout << "Email   : ";
    getline(cin, c.email);

    cout << "Address : ";
    getline(cin, c.address);

    contacts.push_back(c);

    saveContacts();

    cout << "\nContact Added Successfully!\n";
}

// View Contacts
void viewContacts()
{
    if (contacts.empty())
    {
        cout << "\nNo Contacts Available.\n";
        return;
    }

    cout << "\n================ CONTACT LIST ================\n";

    cout << left
         << setw(5) << "ID"
         << setw(20) << "NAME"
         << setw(15) << "PHONE"
         << setw(28) << "EMAIL"
         << "ADDRESS\n";

    cout << "--------------------------------------------------------------------------\n";

    for (const auto &c : contacts)
    {
        cout << left
             << setw(5) << c.id
             << setw(20) << c.name
             << setw(15) << c.phone
             << setw(28) << c.email
             << c.address << endl;
    }
}

// Search Contact
void searchContact()
{
    string keyword;

    cin.ignore();

    cout << "\nEnter Name or Phone to Search: ";
    getline(cin, keyword);

    bool found = false;

    for (const auto &c : contacts)
    {
        if (c.name.find(keyword) != string::npos ||
            c.phone.find(keyword) != string::npos)
        {
            cout << "\n===== CONTACT FOUND =====\n";
            cout << "ID      : " << c.id << endl;
            cout << "Name    : " << c.name << endl;
            cout << "Phone   : " << c.phone << endl;
            cout << "Email   : " << c.email << endl;
            cout << "Address : " << c.address << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nContact Not Found.\n";
    }
}

// Update Contact
void updateContact()
{
    int id;

    cout << "\nEnter Contact ID to Update: ";
    cin >> id;

    cin.ignore();

    for (auto &c : contacts)
    {
        if (c.id == id)
        {
            cout << "\n===== UPDATE CONTACT =====\n";

            cout << "New Name    : ";
            getline(cin, c.name);

            cout << "New Phone   : ";
            getline(cin, c.phone);

            cout << "New Email   : ";
            getline(cin, c.email);

            cout << "New Address : ";
            getline(cin, c.address);

            saveContacts();

            cout << "\nContact Updated Successfully!\n";
            return;
        }
    }

    cout << "\nContact ID Not Found.\n";
}

// Delete Contact
void deleteContact()
{
    int id;

    cout << "\nEnter Contact ID to Delete: ";
    cin >> id;

    for (auto it = contacts.begin(); it != contacts.end(); ++it)
    {
        if (it->id == id)
        {
            contacts.erase(it);

            saveContacts();

            cout << "\nContact Deleted Successfully!\n";
            return;
        }
    }

    cout << "\nContact ID Not Found.\n";
}

// Main Function
int main()
{
    loadContacts();

    int choice;

    do
    {
        cout << "\n\n========== CONTACT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Exit\n";
        cout << "===============================================\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addContact();
                break;

            case 2:
                viewContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                updateContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                saveContacts();
                cout << "\nData Saved. Thank You!\n";
                break;

            default:
                cout << "\nInvalid Choice. Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}
