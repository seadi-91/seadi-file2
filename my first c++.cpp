#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_ROOMS = 10;
const float SINGLE_ROOM_PRICE = 2000.0;
const float DOUBLE_ROOM_PRICE = 3500.0;
const float BUNDLE_ROOM_PRICE = 5000.0;
const float JUNIOR_SUITE_PRICE = 7500.0;
const float EXECUTIVE_SUITE_PRICE = 12000.0;
const float PRESIDENTIAL_SUITE_PRICE = 20000.0;
const float VILLA_PRICE = 10000.0;
const float SPA_SERVICE_PRICE = 1500.0;
const float LOCAL_TOUR_PRICE = 1000.0;
const float TAXI_SERVICE_PRICE = 500.0;
const char ADMIN_USERNAME[] = "hotel.cpp";
const char ADMIN_PASSWORD[] = "hotel@123";

struct Booking {
    char name[50];
    int roomNumber;
    char roomType[20];
    int nights;
    float price;
    char phone[15];
    char username[20];
    char password[20];
    bool hasSpa;
    bool hasTour;
    bool hasTaxi;
    bool isPaid;
};

Booking bookings[MAX_ROOMS];
int bookingCount = 0;

void saveBookings() {
    ofstream file("C:/Users/JOSI/Desktop/c++ project/edited/bookings3.txt", ios::out);
    if (!file) return;
    for (int i = 0; i < bookingCount; i++) {
        file << "Name: "<<bookings[i].name << "|" << "Room Number: "<<bookings[i].roomNumber << "|"
             << "Room Type: "<<bookings[i].roomType << "|" <<"Nights: "<<bookings[i].nights << "|"
             << "Price: "<<bookings[i].price << "|" <<"Phone Number: "<<bookings[i].phone << "|"
             << "Username: "<<bookings[i].username << "|" << "Password: "<<bookings[i].password << "|"
             << "Has Spa: "<<bookings[i].hasSpa << "|" <<"Has Tour: "<<bookings[i].hasTour << "|"
             << "Has Taxi: "<<bookings[i].hasTaxi << "|"<<"Paid: " <<bookings[i].isPaid << endl;
    }
    file.close();
}

void loadBookings() {
    ifstream file("C:/Users/JOSI/Desktop/c++ project/edited/bookings3.txt", ios::in);
    if (!file) return;
    string header;
    getline(file, header); // Skip the header line
    bookingCount = 0;
    while (file >> bookings[bookingCount].name >> bookings[bookingCount].roomNumber
                >> bookings[bookingCount].roomType >> bookings[bookingCount].nights
                >> bookings[bookingCount].price >> bookings[bookingCount].phone
                >> bookings[bookingCount].username >> bookings[bookingCount].password
                >> bookings[bookingCount].hasSpa >> bookings[bookingCount].hasTour
                >> bookings[bookingCount].hasTaxi
                >> bookings[bookingCount].isPaid) {
        bookingCount++;
    }
    file.close();
}

void deleteBooking() {
    int roomNumber;
    cout << "Enter room number to delete booking: ";
    cin >> roomNumber;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].roomNumber== roomNumber) {
            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }
            bookingCount--;
            saveBookings();
            cout << "Booking deleted successfully.\n";
            return;
        }
    }
    cout << "Booking not found.\n";
}

void updateBooking() {
    int roomNum;
    cout << "Enter room number to update booking: ";
    cin >> roomNum;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].roomNumber == roomNum) {
            cout << "\nBooking Found! Updating details...\n";

            // Update room number
            cout << "Enter new room number: ";
            cin >> bookings[i].roomNumber;

            // Update room type
            cout << "Enter new room type (single/double/bundle/junior suite/executive suite/presidential suite/villa): ";
            cin >> bookings[i].roomType;

            // Update number of nights
            cout << "Enter new number of nights: ";
            cin >> bookings[i].nights;

            // Update services
            char choice;
            cout << "Do you want to add/update spa service? (y/n): ";
            cin >> choice;
            bookings[i].hasSpa = (choice == 'y' || choice == 'Y');

            cout << "Do you want to add/update local tour? (y/n): ";
            cin >> choice;
            bookings[i].hasTour = (choice == 'y' || choice == 'Y');

            cout << "Do you want to add/update taxi service? (y/n): ";
            cin >> choice;
            bookings[i].hasTaxi = (choice == 'y' || choice == 'Y');

            // Recalculate total price based on new selections
            bookings[i].price = bookings[i].nights *
                                (strcmp(bookings[i].roomType, "single") == 0 ? SINGLE_ROOM_PRICE :
                                 strcmp(bookings[i].roomType, "double") == 0 ? DOUBLE_ROOM_PRICE :
                                 strcmp(bookings[i].roomType, "junior") == 0 ? JUNIOR_SUITE_PRICE :
                                 strcmp(bookings[i].roomType, "executive") == 0 ? EXECUTIVE_SUITE_PRICE:
                                 strcmp(bookings[i].roomType, "presidential") == 0 ? PRESIDENTIAL_SUITE_PRICE :
                                 strcmp(bookings[i].roomType, "villa") == 0 ? VILLA_PRICE:
                                 BUNDLE_ROOM_PRICE);

            if (bookings[i].hasSpa) bookings[i].price += SPA_SERVICE_PRICE;
            if (bookings[i].hasTour) bookings[i].price += LOCAL_TOUR_PRICE;
            if (bookings[i].hasTaxi) bookings[i].price += TAXI_SERVICE_PRICE;

            // Save updated data
            saveBookings();
            cout << "\nBooking updated successfully!\n";

            // Display updated details
            cout << "\n----- Updated Booking Details -----\n";
            cout << "Name: " << bookings[i].name << "\n";
            cout << "Phone Number: "<<bookings[i].phone<<"\n";
            cout << "Room Number: " << bookings[i].roomNumber << "\n";
            cout << "Room Type: " << bookings[i].roomType << "\n";
            cout << "Nights: " << bookings[i].nights << "\n";
            cout << "Spa Service: " << (bookings[i].hasSpa ? "Yes" : "No") << "\n";
            cout << "Local Tour: " << (bookings[i].hasTour ? "Yes" : "No") << "\n";
            cout << "Taxi Service: " << (bookings[i].hasTaxi ? "Yes" : "No") << "\n";
            cout << "Total Price: " << bookings[i].price << "\n";
            cout << "Paid: " << (bookings[i].isPaid ? "Yes" : "No") << "\n";
            return;
        }
    }

    cout << "Booking not found.\n";
}


void searchBooking() {
    int roomNumber;
    cout << "Enter roomNumber to search for booking: ";
    cin >> roomNumber;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].roomNumber==roomNumber) {
            cout << "Booking found:\n";
            cout << "Name: " << bookings[i].name << " | Room: " << bookings[i].roomNumber
                 << " | Type: " << bookings[i].roomType << " | Nights: " << bookings[i].nights
                 << " | Price: " << bookings[i].price << " | Paid: " << (bookings[i].isPaid ? "Yes" : "No") << endl;
            return;
        }
    }
    cout << "Booking not found.\n";
}


void viewAllBookings() {
    if (bookingCount == 0) {
        cout << "No bookings available.\n";
        return;
    }

    cout << "\n----- All Bookings -----\n";
    for (int i = 0; i < bookingCount; i++) {
        cout<< "Name: "<<bookings[i].name << "|" << "Room Number: "<<bookings[i].roomNumber << "|"
             << "Room Type: "<<bookings[i].roomType << "|" <<"Nights: "<<bookings[i].nights << "|"
             << "Price: "<<bookings[i].price << "|" <<"Phone Number: "<<bookings[i].phone << "|"
             << "Username: "<<bookings[i].username << "|" << "Password: "<<bookings[i].password << "|"
             << "Has Spa: "<<bookings[i].hasSpa << "|" <<"Has Tour: "<<bookings[i].hasTour << "|"
             << "Has Taxi: "<<bookings[i].hasTaxi << "|"<<"Paid: " <<bookings[i].isPaid << endl;
    }
    cout << "-----------------------------------------------------------------------------\n";
}

void adminMenu() {
    char username[20], password[20];

    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (strcmp(username, ADMIN_USERNAME) != 0 || strcmp(password, ADMIN_PASSWORD) != 0) {
        cout << "Access Denied!\n";
        return;
    }

    int choice;
    do {
        cout << "\n----- Reception/Admin Panel -----\n";
        cout << "1. View All Bookings\n";
        cout << "2. Search Booking\n";
        cout << "3. Update Booking\n";
        cout << "4. Delete Booking\n";
        cout << "5. Back to Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewAllBookings();
                break;
            case 2:
                searchBooking();
                break;
            case 3:
                updateBooking();
                break;
            case 4:
                deleteBooking();
                break;
            case 5:
                cout << "Exiting admin panel.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

void updateGuestStatus() {
    int roomNumber;
    cout << "Enter your room number to update status: ";
    cin >> roomNumber;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].roomNumber==roomNumber) {
            char choice;
            cout << "Do you want to update the number of nights? (y/n): ";
            cin>>choice;
            if (choice =='y'|| choice =='Y'){
                cout<<"Enter new number of nights: ";
                cin>>bookings[i].nights;
                        }

            cout << "Do you want to add spa service? (y/n): ";
            cin >> choice;
            bookings[i].hasSpa = (choice == 'y' || choice == 'Y');

            cout << "Do you want to add local tour? (y/n): ";
            cin >> choice;
            bookings[i].hasTour = (choice == 'y' || choice == 'Y');

            cout << "Do you want to add taxi service? (y/n): ";
            cin >> choice;
            bookings[i].hasTaxi = (choice == 'y' || choice == 'Y');

            saveBookings();
            cout << "Status updated successfully.\n";
            return;
        }
    }
    cout << "Booking not found.\n";
}



void bookRoom() {
    if (bookingCount >= MAX_ROOMS) {
        cout << "No rooms available!\n";
        return;
    }

    Booking newBooking;
    cout << "Enter your name: ";
    cin.ignore(); // To handle previous input
    cin.getline(newBooking.name, 50);
    cout<<"Enter your phone number: ";
    cin>>newBooking.phone;
    cout << "Enter username: ";
    cin >> newBooking.username;
    cout << "Enter password: ";
    cin >> newBooking.password;
    newBooking.roomNumber = bookingCount + 1;

    cout << "Enter room type (single/double/bundle/junior/executive suite/presidential suite/villa): ";
    cin >> newBooking.roomType;
    cout << "Enter number of nights: ";
    cin >> newBooking.nights;

    // Price Calculation (fixed issue here)
    newBooking.price = newBooking.nights *
                       (strcmp(newBooking.roomType, "single") == 0 ? SINGLE_ROOM_PRICE :
                        strcmp(newBooking.roomType, "double") == 0 ? DOUBLE_ROOM_PRICE :
                        strcmp(newBooking.roomType, "junior") == 0 ? JUNIOR_SUITE_PRICE :
                        strcmp(newBooking.roomType, "executive") == 0 ? EXECUTIVE_SUITE_PRICE:
                        strcmp(newBooking.roomType, "presidential") == 0 ? PRESIDENTIAL_SUITE_PRICE :
                        strcmp(newBooking.roomType, "villa") == 0 ? VILLA_PRICE:
                        BUNDLE_ROOM_PRICE);

    // Adding extra services
    char choice;
    cout << "Do you want to add spa service? (y/n): ";
    cin >> choice;
    newBooking.hasSpa = (choice == 'y' || choice == 'Y');
    if (newBooking.hasSpa) newBooking.price += SPA_SERVICE_PRICE;

    cout << "Do you want to add local tour? (y/n): ";
    cin >> choice;
    newBooking.hasTour = (choice == 'y' || choice == 'Y');
    if (newBooking.hasTour) newBooking.price += LOCAL_TOUR_PRICE;

    cout << "Do you want to add taxi service? (y/n): ";
    cin >> choice;
    newBooking.hasTaxi = (choice == 'y' || choice == 'Y');
    if (newBooking.hasTaxi) newBooking.price += TAXI_SERVICE_PRICE;

    newBooking.isPaid = false; // Default payment status

    // Save the new booking
    bookings[bookingCount++] = newBooking;
    saveBookings();
    cout << "\nRoom booked successfully!\n";

    // Display Booking Information Immediately
    cout << "\n----- Your Booking Details -----\n";
    cout << "Name: " << newBooking.name << "\n";
    cout << "Room Number: " << newBooking.roomNumber << "\n";
    cout << "Room Type: " << newBooking.roomType << "\n";
    cout << "Nights: " << newBooking.nights << "\n";
    cout << "Spa Service: " << (newBooking.hasSpa ? "Yes" : "No") << "\n";
    cout << "Local Tour: " << (newBooking.hasTour ? "Yes" : "No") << "\n";
    cout << "Taxi Service: " << (newBooking.hasTaxi ? "Yes" : "No") << "\n";
    cout << "Total Price: " << newBooking.price << "ETB\n";
    cout << "Paid: " << (newBooking.isPaid ? "Yes" : "No") << "\n";
}

void guestMenu() {
    int choice;
    do {
        cout << "\n----- Guest Interface -----\n";
        cout << "1. Register and Book a Room\n";
        cout << "2. Update Booking Status\n";
        cout << "3. Back to Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;  // Missing input statement

        switch (choice) {  // Missing switch block
            case 1:
                bookRoom();  // Function for guest registration and booking
                break;
            case 2:
                updateGuestStatus();  // Function to update booking status
                break;
            case 3:
                cout << "Exiting guest interface.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);
}


int main() {
    loadBookings();
    int choice;
    do {
        cout << "\n----- Welcome to the Hotel Booking System -----\n";
        cout << "1. Guest Interface\n";
        cout << "2. Reception/Admin Panel\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                guestMenu();
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                cout << "Exiting the system. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);
    return 0;
}
