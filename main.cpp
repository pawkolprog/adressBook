#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct Contact {
    int id;
    string firstName, lastName, tel, email, adress;
};

struct User {
    int id;
    string login, password;
};

string readLine() {
    string input;
    cin.sync();
    getline(cin, input);
    return input;
}

void outputContact(vector <Contact> contacts, int i) {
    cout << "ID: " << contacts[i].id << ". |Imie: " << contacts[i].firstName << " |Nazwisko: " << contacts[i].lastName << " |Telefon: " << contacts[i].tel << " |Email: " << contacts[i].email << " |Adres: " << contacts[i].adress << endl;
}

char readCharTOrN() {
    string input;
    char znak;
    cin.sync();
    while(true) {
        getline(cin, input);
        if ((input.length() == 1 && input[0] == 't') || (input.length() == 1 && input[0] == 'n')) {
            znak = input[0];
            break;
        } else {
        cout << "Zly znak, wprowadz ponownie: ";
        }
    }
    return znak;
}

Contact breakString (string line) {
    Contact oneContact;
    string singleData;
    size_t position;

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneContact.id = atoi(singleData.c_str());
    line.erase(line.begin(), line.begin() + position + 1);

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneContact.firstName = singleData;
    line.erase(line.begin(), line.begin() + position + 1);

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneContact.lastName = singleData;
    line.erase(line.begin(), line.begin() + position + 1);

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneContact.tel = singleData;
    line.erase(line.begin(), line.begin() + position + 1);

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneContact.email = singleData;
    line.erase(line.begin(), line.begin() + position + 1);

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneContact.adress = singleData;
    line.erase(line.begin(), line.begin() + position + 1);

    return oneContact;

}

void importContacts(vector <Contact> &contacts) {
    fstream file;
    Contact oneContact;
    string line;

    file.open("kontakty.txt", ios::in);
    if(!file.good()) {
        return;
    }

    while(getline(file, line)) {
        oneContact = breakString(line);
        contacts.push_back(oneContact);
    }
    file.close();
}

void addContact(vector <Contact> &contacts) {
    Contact oneContact;

    if (contacts.empty()) {
        oneContact.id = 1;
    } else {
    oneContact.id = contacts[contacts.size()-1].id + 1;
    }
    cout << "Podaj imie: ";
    oneContact.firstName = readLine();
    cout << "Podaj nazwisko: ";
    oneContact.lastName = readLine();
    cout << "Podaj numer telefonu: ";
    oneContact.tel = readLine();
    cout << "Podaj adres email: ";
    oneContact.email = readLine();
    cout << "Podaj adres zamieszkania: ";
    oneContact.adress = readLine();

    contacts.push_back(oneContact);

    fstream file;

    file.open("kontakty.txt", ios::out|ios::app);

    file << oneContact.id << "|";
    file << oneContact.firstName << "|";
    file << oneContact.lastName << "|";
    file << oneContact.tel << "|";
    file << oneContact.email << "|";
    file << oneContact.adress << "|" << endl;

    file.close();

    cout << "Kontakt zostal dodany." << endl;
}

void outputContactsByFirstName(vector <Contact> contacts) {
    int counter = 0;
    string firstName;
    if (contacts.empty()) {
        cout << "Brak zapisanych kontaktow." << endl;
        return;
    }
    cout << "Podaj imie do wyszukania: ";
    cin >> firstName;

    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].firstName == firstName) {
            outputContact(contacts, i);
            counter++;
        }
    }
    cout << "Liczba znalezionych kontaktow: " << counter << endl;
}

void outputContactsByLastName(vector <Contact> contacts) {
    int counter = 0;
    string lastName;
    if (contacts.empty()) {
        cout << "Brak zapisanych kontaktow." << endl;
        return;
    }
    cout << "Podaj nazwisko do wyszukania: ";
    cin >> lastName;

    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].lastName == lastName) {
            outputContact(contacts, i);
            counter++;
        }
    }
    cout << "Liczba znalezionych kontaktow: " << counter << endl;
}

void outputAllContacts(vector <Contact> contacts) {
    if (!contacts.empty()) {
        for (int i = 0; i < contacts.size(); i++) {
            outputContact(contacts, i);
        }
        cout << "Liczba znalezionych kontaktow: " << contacts.size() << endl;
    } else {
        cout << "Brak dodanych kontaktow" << endl;
    }
}

void exportContactsToFile(vector <Contact> contacts) {
    fstream file;
    vector<Contact> :: iterator position;
    file.open("kontakty.txt", ios::out);

    for (vector<Contact> :: iterator position = contacts.begin(); position != contacts.end(); ++position) {
        file << (*position).id << "|";
        file << (*position).firstName << "|";
        file << (*position).lastName << "|";
        file << (*position).tel << "|";
        file << (*position).email << "|";
        file << (*position).adress << "|" << endl;
    }

    file.close();

}

void deleteContact(vector <Contact> &contacts, vector<Contact> :: iterator position) {
    contacts.erase(position);
    exportContactsToFile(contacts);
}

void checkDeleteContact(vector <Contact> &contacts) {
    int id;
    char znak;
    vector <Contact> :: iterator position;

    if (contacts.empty()) {
        cout << "Brak zapisanych kontaktow." << endl;
        return;
    }
    cout << "Podaj ID kontaktu do usuniecia: ";
    cin >> id;
    for (position = contacts.begin(); position != contacts.end(); position++) {
        if ((*position).id == id) {
            break;
        }
    }

    if (position == contacts.end()) {
        cout << "Brak kontaktu o podanym ID." << endl;
    } else {
        cout << "Znaleziono kontakt:" << endl;
        cout << "ID: " << (*position).id << ". |Imie: " << (*position).firstName << " |Nazwisko: " << (*position).lastName << " |Telefon: " << (*position).tel << " |Email: " << (*position).email << " |Adres: " << (*position).adress << endl;
        cout << "Czy usunac ten kontakt? (t/n)";
        znak = readCharTOrN();
        if (znak == 't') {
            deleteContact(contacts, position);
            cout << "Kontakt zostal usuniety." << endl;
        } else if (znak == 'n') {
        cout << "Kontakt nie zostal usuniety." << endl;
        }
    }
}

void editAdressOfContact(vector <Contact> &contacts, vector <Contact> :: iterator position) {
    string adress;
    cout << "Podaj adres do zmiany: ";
    adress = readLine();
    (*position).adress = adress;
    exportContactsToFile(contacts);
    cout << "Adres zmieniony." << endl;
}

void editEmailOfContact(vector <Contact> &contacts, vector <Contact> :: iterator position) {
    string email;
    cout << "Podaj adres email do zmiany: ";
    email = readLine();
    (*position).email = email;
    exportContactsToFile(contacts);
    cout << "Adres email zmieniony." << endl;
}

void editTelOfContact(vector <Contact> &contacts, vector <Contact> :: iterator position) {
    string tel;
    cout << "Podaj numer telefonu do zmiany: ";
    tel = readLine();
    (*position).tel = tel;
    exportContactsToFile(contacts);
    cout << "Numer telefonu zmieniony." << endl;
}

void editLastNameOfContact(vector <Contact> &contacts, vector <Contact> :: iterator position) {
    string lastName;
    cout << "Podaj nazwisko do zmiany: ";
    lastName = readLine();
    (*position).lastName = lastName;
    exportContactsToFile(contacts);
    cout << "Nazwisko zmienione." << endl;
}

void editFirstNameOfContact(vector <Contact> &contacts, vector <Contact> :: iterator position) {
    string firstName;
    cout << "Podaj imie do zmiany: ";
    firstName = readLine();
    (*position).firstName = firstName;
    exportContactsToFile(contacts);
    cout << "Imie zmienione." << endl;
}

void editContact(vector <Contact> &contacts, vector <Contact> :: iterator position) {
    int choice;
    while (1) {
        system("cls");
        cout << "Wybrany kontakt:" << endl;
        cout << "ID: " << (*position).id << ". |Imie: " << (*position).firstName << " |Nazwisko: " << (*position).lastName << " |Telefon: " << (*position).tel << " |Email: " << (*position).email << " |Adres: " << (*position).adress << endl;
        cout << "||Edycja kontaktu||" << endl;
        cout << "1. Imie" << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Numer telefonu" << endl;
        cout << "4. Email" << endl;
        cout << "5. Adres" << endl;
        cout << "6. Powrot do menu" << endl;
        cin.clear(); cin.sync();
        cin >> choice;

        switch (choice) {
        case 1:
            editFirstNameOfContact(contacts, position);
            break;
        case 2:
            editLastNameOfContact(contacts, position);
            break;
        case 3:
            editTelOfContact(contacts, position);
            break;
        case 4:
            editEmailOfContact(contacts, position);
            break;
        case 5:
            editAdressOfContact(contacts, position);
            break;
        case 6:
            return;
            break;
        default:
            cout << "Brak takiej opcji, wybierz ponownie." << endl;
            system("pause");
        }
    }
}


void checkEditContact(vector <Contact> &contacts) {
    int id;
    vector <Contact> :: iterator position;

    if (contacts.empty()) {
        cout << "Brak zapisanych kontaktow." << endl;
        return;
    }
    cout << "Podaj ID kontaktu do edycji: ";
    cin >> id;
    for (position = contacts.begin(); position != contacts.end(); position++) {
        if ((*position).id == id) {
            break;
        }
    }
    //position = findId(contacts);

    if (position == contacts.end()) {
        cout << "Brak kontaktu o podanym ID." << endl;
        system("pause");
    } else {
        editContact(contacts, position);
    }
}

void adressBook (int userId) {
    vector <Contact> contacts;
    int choice;

    //importContacts(contacts);

    while (1) {
        system("cls");
        cout << "||Ksiazka adresowa||" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "--------------------------------" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "8. Wyloguj sie" << endl;
        cout << "--------------------------------" << endl;
        cin.clear(); cin.sync();
        cin >> choice;

        switch (choice) {
        case 1:
            addContact(contacts);
            system("pause");
            break;
        case 2:
            outputContactsByFirstName(contacts);
            system("pause");
            break;
        case 3:
            outputContactsByLastName(contacts);
            system("pause");
            break;
        case 4:
            outputAllContacts(contacts);
            system("pause");
            break;
        case 5:
            checkDeleteContact(contacts);
            system("pause");
            break;
        case 6:
            checkEditContact(contacts);
            system("pause");
            break;
        case 7:
            //changePassword(contacts);
            system("pause");
            break;
        case 8:
            return;
            break;
        default:
            cout << "Brak takiej opcji, wybierz ponownie." << endl;
            system("pause");
        }
    }
}

User breakStringForUser (string line) {
    User oneUser;
    string singleData;
    size_t position;

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneUser.id = atoi(singleData.c_str());
    line.erase(line.begin(), line.begin() + position + 1);

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneUser.login = singleData;
    line.erase(line.begin(), line.begin() + position + 1);

    position = line.find('|');
    singleData.assign(line.begin(), line.begin() + position);
    oneUser.password = singleData;
    line.erase(line.begin(), line.begin() + position + 1);

    return oneUser;

}

void importUsers(vector <User> &users) {
    fstream file;
    User oneUser;
    string line;

    file.open("uzytkownicy.txt", ios::in);
    if(!file.good()) {
        return;
    }

    while(getline(file, line)) {
        oneUser = breakStringForUser(line);
        users.push_back(oneUser);
    }
    file.close();
}

void addUser(vector <User> &users) {
    User oneUser;
    vector <User> :: iterator position;

    if (users.empty()) {
        oneUser.id = 1;
    } else {
    oneUser.id = users[users.size()-1].id + 1;
    }
    cout << "Podaj login: ";
    while (1) {
        oneUser.login = readLine();
        for (position = users.begin(); position != users.end(); position++) {
            if ((*position).login == oneUser.login) break;
        }
        if (position == users.end()) break;
        else cout << "Taki login istnieje, podaj inny login: ";
    }

    cout << "Podaj haslo: ";
    oneUser.password = readLine();

    users.push_back(oneUser);

    fstream file;

    file.open("uzytkownicy.txt", ios::out|ios::app);

    file << oneUser.id << "|";
    file << oneUser.login << "|";
    file << oneUser.password << "|" << endl;

    file.close();

    cout << "Konto zostalo utworzone." << endl;
}

void logIn(vector <User> users) {
    string login, password;
    vector <User> :: iterator position;

    cout << "Podaj login: ";
    while (1) {
        login = readLine();
        for (position = users.begin(); position != users.end(); position++) {
            if ((*position).login == login) break;
        }
        if (position != users.end()) break;
        else cout << "Taki login nie istnieje, podaj inny login: ";
    }
    for (int i = 3; i > 0; i--) {
        cout << "Podaj haslo: ";
        password = readLine();
        if (password == (*position).password) {
            adressBook((*position).id);
            //cout << "zalogowany";
            return;
        }
        else cout << "Haslo nieprawidlowe. Pozostala ilosc prob: " << i-1 << endl;
    }
}

int main() {
    vector <User> users;
    int choice;

    importUsers(users);

    while (1) {
        system("cls");
        cout << "||Menu glowne||" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cin.clear(); cin.sync();
        cin >> choice;

        switch (choice) {
        case 1:
            logIn(users);
            system("pause");
            break;
        case 2:
            addUser(users);
            system("pause");
            break;
        case 3:
            return 0;
            break;
        default:
            cout << "Brak takiej opcji, wybierz ponownie." << endl;
            system("pause");
        }
    }
    return 0;
}
