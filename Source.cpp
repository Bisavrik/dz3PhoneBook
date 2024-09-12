#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

using namespace std;

const int MAX_CONTACTS = 100;

class Contact
{
private:
    char* name;
    char homePhone[20];
    char workPhone[20];
    char mobilePhone[20];
    char additionalInfo[100];

public:
    Contact(const char* name, const char* homePhone, const char* workPhone, const char* mobilePhone, const char* additionalInfo) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->homePhone, homePhone);
        strcpy(this->workPhone, workPhone);
        strcpy(this->mobilePhone, mobilePhone);
        strcpy(this->additionalInfo, additionalInfo);
    }

    Contact() : name(nullptr) {}

    ~Contact()
    {
        delete[] name;
    }

    void display()
    {
        cout << "Information: " << (name ? name : "Not yet") << endl;
        cout << "Home number: " << homePhone << endl;
        cout << "Work number: " << workPhone << endl;
        cout << "Phone number: " << mobilePhone << endl;
        cout << "Additional information: " << additionalInfo << endl;
    }

    const char* getName()
    {
        return name;
    }

    bool matchesName(const char* searchName)
    {
        return name && strcmp(name, searchName) == 0;
    }

    void saveToFile(FILE* file)
    {
        fprintf(file, "%s\n", name);
        fprintf(file, "%s\n", homePhone);
        fprintf(file, "%s\n", workPhone);
        fprintf(file, "%s\n", mobilePhone);
        fprintf(file, "%s\n", additionalInfo);
    }

    void loadFromFile(FILE* file) 
    {
        char buffer[100];
        fgets(buffer, 100, file); buffer[strlen(buffer) - 1] = '\0'; 
        name = new char[strlen(buffer) + 1];
        strcpy(name, buffer);

        fgets(homePhone, 20, file); homePhone[strlen(homePhone) - 1] = '\0';
        fgets(workPhone, 20, file); workPhone[strlen(workPhone) - 1] = '\0'; 
        fgets(mobilePhone, 20, file); mobilePhone[strlen(mobilePhone) - 1] = '\0'; 
        fgets(additionalInfo, 100, file); additionalInfo[strlen(additionalInfo) - 1] = '\0'; 
    }
};

class PhoneBook
{
private:
    Contact contacts[MAX_CONTACTS];
    int contactCount;

public:
    PhoneBook() : contactCount(0) {}

    void addContact(const char* name, const char* homePhone, const char* workPhone, const char* mobilePhone, const char* additionalInfo)
    {
        if (contactCount < MAX_CONTACTS)
        {
            contacts[contactCount] = Contact(name, homePhone, workPhone, mobilePhone, additionalInfo);
            contactCount++;
        }
        else
        {
            cout << "Phone book full!" << endl;
        }
    }

    void deleteContact(const char* name)
    {
        for (int i = 0; i < contactCount; i++)
        {
            if (contacts[i].matchesName(name))
            {
                for (int j = i; j < contactCount - 1; j++)
                {
                    contacts[j] = contacts[j + 1];
                }
                contactCount--;
                cout << "Contact deleted." << endl;
                return;
            }
        }
        cout << "Contact with same name not found." << endl;
    }

    void searchContact(const char* name)
    {
        for (int i = 0; i < contactCount; i++)
        {
            if (contacts[i].matchesName(name))
            {
                contacts[i].display();
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void displayAllContacts()
    {
        if (contactCount == 0)
        {
            cout << "Phone book empty." << endl;
            return;
        }

        for (int i = 0; i < contactCount; i++)
        {
            cout << "Contact " << (i + 1) << ":" << endl;
            contacts[i].display();
            cout << "-----------------" << endl;
        }
    }

    void saveToFile() 
    {
        const char* PATH_TO_FILE = "phoneBook.txt";
        FILE* file = fopen(PATH_TO_FILE, "w");

        if (file != nullptr) 
        {
            for (int i = 0; i < contactCount; i++) 
            {
                contacts[i].saveToFile(file);
                fprintf(file, "-----------------\n");
            }
            fclose(file);
            cout << "Contacts saved to file." << endl;
        }
        else
        {
            cout << "Error opening file for saving!" << endl;
        }
    }

    void loadFromFile() 
    {
        const char* PATH_TO_FILE = "phoneBook.txt";
        FILE* file = fopen(PATH_TO_FILE, "r");

        if (file != nullptr) 
        {
            contactCount = 0;
            while (!feof(file)) 
            {
                contacts[contactCount].loadFromFile(file);
                char buffer[20];
                fgets(buffer, 20, file);  
                contactCount++;
                if (contactCount >= MAX_CONTACTS) break;
            }
            fclose(file);
            cout << "Contacts loaded from file." << endl;
        }
        else 
        {
            cout << "Error opening file for loading!" << endl;
        }
    }
};

int main()
{
    PhoneBook phoneBook;
    int choice;
    char name[50], homePhone[20], workPhone[20], mobilePhone[20], additionalInfo[100];

    do
    {
        cout << "1. Add contact" << endl;
        cout << "2. Delete contact" << endl;
        cout << "3. Find contact" << endl;
        cout << "4. Show all contacts" << endl;
        cout << "5. Save contacts to file" << endl;
        cout << "6. Load contacts from file" << endl;
        cout << "7. Exit" << endl;
        cout << "Choose option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter home number: ";
            cin >> homePhone;
            cout << "Enter work number: ";
            cin >> workPhone;
            cout << "Enter phone number: ";
            cin >> mobilePhone;
            cout << "Enter additional information: ";
            cin >> additionalInfo;
            phoneBook.addContact(name, homePhone, workPhone, mobilePhone, additionalInfo);
            break;

        case 2:
            cout << "Enter name to delete: ";
            cin >> name;
            phoneBook.deleteContact(name);
            break;

        case 3:
            cout << "Enter name for search: ";
            cin >> name;
            phoneBook.searchContact(name);
            break;

        case 4:
            phoneBook.displayAllContacts();
            break;

        case 5:
            phoneBook.saveToFile();
            break;

        case 6:
            phoneBook.loadFromFile();
            break;

        case 7:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Wrong choice. Try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
