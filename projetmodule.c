#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_FLIGHTS 100
#define MAX_PASSENGERS 50
#define MAX_EMPLOYEES 50
#define MAX_GROUND_VEHICLES 50
#define MAX_SHOPS 50
#define MAX_SERVICES 50
#define MAX_FINANCIAL_RECORDS 50
 
struct Passenger {
    int passengerNumber;
    char name[50];
    char seat[10];
    char status[20];
};
 
struct Flight {
    int flightNumber;
    char destination[50];
    char gate[10];
    char status[20];
    struct Passenger passengers[MAX_PASSENGERS];
    int numPassengers;
};
 
struct Employee {
    int employeeNumber;
    char name[50];
    char role[50];
    char schedule[20];
    char accreditation[50];
};
 
struct GroundVehicle {
    int vehicleNumber;
    char type[50];
    char status[20];
};
 
struct Security {
    int accessControl;
    int cameraSurveillance;
    int securityIncidents;
};
 
struct Shop {
    int shopNumber;
    char name[50];
    char type[50];
    int rented;
};
 
struct Service {
    int serviceNumber;
    char name[50];
    char type[50];
};
 
struct FinancialRecord {
    int transactionNumber;
    char description[100];
    double amount;
};
 
struct Accounting {
    double totalRevenue;
    double totalExpenses;
    struct FinancialRecord financialRecords[MAX_FINANCIAL_RECORDS];
    int numFinancialRecords;
};
 
struct Airport {
    struct Flight flights[MAX_FLIGHTS];
    int numFlights;
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees;
    struct GroundVehicle groundVehicles[MAX_GROUND_VEHICLES];
    int numGroundVehicles;
    struct Security security;
    struct Shop shops[MAX_SHOPS];
    int numShops;
    struct Service services[MAX_SERVICES];
    int numServices;
    struct Accounting accounting;
};
 
// Function prototypes
void addFlight(FILE *fp, struct Airport *airport);
void displayFlights(struct Airport *airport);
void addPassenger(struct Flight *flight, FILE *fp);
void displayPassengers(struct Flight *flight);
void managePassengers(FILE *fp, struct Airport *airport);
void addEmployee(FILE *fp, struct Airport *airport);
void displayEmployees(struct Airport *airport);
void manageEmployees(FILE *fp, struct Airport *airport);
void addGroundVehicle(FILE *fp, struct Airport *airport);
void displayGroundVehicles(struct Airport *airport);
void manageInfrastructure(FILE *fp, struct Airport *airport);
void manageSecurity(struct Airport *airport);
void addShop(struct Airport *airport);
void displayShops(struct Airport *airport);
void rentShop(struct Airport *airport);
void addService(struct Airport *airport);
void displayServices(struct Airport *airport);
void manageShopsAndServices(struct Airport *airport);
void addFinancialRecord(struct Accounting *accounting);
void displayFinancialRecords(struct Accounting *accounting);
void generateFinancialReport(struct Accounting *accounting);
void manageBillingAndAccounting(struct Airport *airport);
 
int main() {
    FILE *fp;
    fp = fopen("aeroport.txt", "a");
    if (fp == NULL) {
        printf("Unable to open the file.\n");
        exit(1);
    }
 
    struct Airport airport;
    airport.numFlights = 0;
    airport.numEmployees = 0;
    airport.numGroundVehicles = 0;
 
    int choice;
 
    do {
        printf("\nAirline Management System\n");
        printf("1. Add a Flight\n");
        printf("2. Display Flights\n");
        printf("3. Manage Passengers\n");
        printf("4. Manage Employees\n");
        printf("5. Manage Infrastructure\n");
        printf("6. Manage Security\n");
        printf("7. Shops and Services Management\n");
        printf("8. Billing and Accounting Management\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                addFlight(fp, &airport);
                break;
            case 2:
                displayFlights(&airport);
                break;
            case 3:
                managePassengers(fp, &airport);
                break;
            case 4:
                manageEmployees(fp, &airport);
                break;
            case 5:
                manageInfrastructure(fp, &airport);
                break;
            case 6:
                manageSecurity(&airport);
                break;
            case 7:
                manageShopsAndServices(&airport);
                break;
            case 8:
                manageBillingAndAccounting(&airport);
                break;
            case 9:
                printf("Exiting the program.\n");
                fclose(fp);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);
 
    fclose(fp);
    return 0;
}
 
void addFlight(FILE *fp, struct Airport *airport) {
    if (airport->numFlights < MAX_FLIGHTS) {
        struct Flight newFlight;
 
        printf("Enter Flight Number: ");
        scanf("%d", &newFlight.flightNumber);
 
        printf("Enter Destination: ");
        scanf("%s", newFlight.destination);
 
        printf("Enter Gate: ");
        scanf("%s", newFlight.gate);
 
        printf("Enter Status: ");
        scanf("%s", newFlight.status);
 
        airport->flights[airport->numFlights++] = newFlight;
 
        fprintf(fp, "%d %s %s %s\n", newFlight.flightNumber, newFlight.destination, newFlight.gate, newFlight.status);
 
        printf("Flight added successfully.\n");
    } else {
        printf("Maximum number of flights reached.\n");
    }
}
 
void displayFlights(struct Airport *airport) {
    printf("\nFlight Details:\n");
    for (int i = 0; i < airport->numFlights; i++) {
        struct Flight flight = airport->flights[i];
        printf("Flight Number: %d, Destination: %s, Gate: %s, Status: %s\n",
               flight.flightNumber, flight.destination, flight.gate, flight.status);
    }
}
 
void addPassenger(struct Flight *flight, FILE *fp) {
    if (flight->numPassengers < MAX_PASSENGERS) {
        struct Passenger newPassenger;
 
        printf("Enter Passenger Number: ");
        scanf("%d", &newPassenger.passengerNumber);
 
        printf("Enter Passenger Name: ");
        scanf("%s", newPassenger.name);
 
        printf("Enter Seat: ");
        scanf("%s", newPassenger.seat);
 
        flight->passengers[flight->numPassengers++] = newPassenger;
 
        fprintf(fp, "P %d %d %s %s %s\n", flight->flightNumber, newPassenger.passengerNumber,
                newPassenger.name, newPassenger.seat, newPassenger.status);
 
        printf("Passenger added successfully.\n");
    } else {
        printf("Maximum number of passengers reached for this flight.\n");
    }
}
 
void displayPassengers(struct Flight *flight) {
    printf("\nPassenger Details for Flight %d:\n", flight->flightNumber);
    for (int i = 0; i < flight->numPassengers; i++) {
        struct Passenger passenger = flight->passengers[i];
        printf("Passenger Number: %d, Name: %s, Seat: %s\n",
               passenger.passengerNumber, passenger.name, passenger.seat);
    }
}
 
void managePassengers(FILE *fp, struct Airport *airport) {
    int flightNumber;
    printf("Enter Flight Number to manage passengers: ");
    scanf("%d", &flightNumber);
 
    struct Flight *flight = NULL;
    for (int i = 0; i < airport->numFlights; i++) {
        if (airport->flights[i].flightNumber == flightNumber) {
            flight = &airport->flights[i];
            break;
        }
    }
 
    if (flight == NULL) {
        printf("Flight not found.\n");
        return;
    }
 
    int choice;
    do {
        printf("\nPassenger Management for Flight %d\n", flightNumber);
        printf("1. Add a Passenger\n");
        printf("2. Display Passengers\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                addPassenger(flight, fp);
                break;
            case 2:
                displayPassengers(flight);
                break;
            case 3:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}
 
void addEmployee(FILE *fp, struct Airport *airport) {
    if (airport->numEmployees < MAX_EMPLOYEES) {
        struct Employee newEmployee;
 
        printf("Enter Employee Number: ");
        scanf("%d", &newEmployee.employeeNumber);
 
        printf("Enter Employee Name: ");
        scanf("%s", newEmployee.name);
 
        printf("Enter Employee Role: ");
        scanf("%s", newEmployee.role);
 
        printf("Enter Employee Schedule: ");
        scanf("%s", newEmployee.schedule);
 
        printf("Enter Employee Accreditation: ");
        scanf("%s", newEmployee.accreditation);
 
        airport->employees[airport->numEmployees++] = newEmployee;
 
        fprintf(fp, "E %d %s %s %s %s\n", newEmployee.employeeNumber, newEmployee.name,
                newEmployee.role, newEmployee.schedule, newEmployee.accreditation);
 
        printf("Employee added successfully.\n");
    } else {
        printf("Maximum number of employees reached.\n");
    }
}
 
void displayEmployees(struct Airport *airport) {
    printf("\nEmployee Details:\n");
    for (int i = 0; i < airport->numEmployees; i++) {
        struct Employee employee = airport->employees[i];
        printf("Employee Number: %d, Name: %s, Role: %s, Schedule: %s, Accreditation: %s\n",
               employee.employeeNumber, employee.name, employee.role, employee.schedule, employee.accreditation);
    }
}
 
void manageEmployees(FILE *fp, struct Airport *airport) {
    int choice;
    do {
        printf("\nEmployee Management\n");
        printf("1. Add an Employee\n");
        printf("2. Display Employees\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                addEmployee(fp, airport);
                break;
            case 2:
                displayEmployees(airport);
                break;
            case 3:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}
 
void addGroundVehicle(FILE *fp, struct Airport *airport) {
    if (airport->numGroundVehicles < MAX_GROUND_VEHICLES) {
        struct GroundVehicle newVehicle;
 
        printf("Enter Vehicle Number: ");
        scanf("%d", &newVehicle.vehicleNumber);
 
        printf("Enter Vehicle Type: ");
        scanf("%s", newVehicle.type);
 
        printf("Enter Vehicle Status: ");
        scanf("%s", newVehicle.status);
 
        airport->groundVehicles[airport->numGroundVehicles++] = newVehicle;
 
        fprintf(fp, "V %d %s %s\n", newVehicle.vehicleNumber, newVehicle.type, newVehicle.status);
 
        printf("Ground vehicle added successfully.\n");
    } else {
        printf("Maximum number of ground vehicles reached.\n");
    }
}
 
void displayGroundVehicles(struct Airport *airport) {
    printf("\nGround Vehicle Details:\n");
    for (int i = 0; i < airport->numGroundVehicles; i++) {
        struct GroundVehicle vehicle = airport->groundVehicles[i];
        printf("Vehicle Number: %d, Type: %s, Status: %s\n",
               vehicle.vehicleNumber, vehicle.type, vehicle.status);
    }
}
 
void manageInfrastructure(FILE *fp, struct Airport *airport) {
    int choice;
    do {
        printf("\nInfrastructure Management\n");
        printf("1. Add a Ground Vehicle\n");
        printf("2. Display Ground Vehicles\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                addGroundVehicle(fp, airport);
                break;
            case 2:
                displayGroundVehicles(airport);
                break;
            case 3:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}
 
void manageSecurity(struct Airport *airport) {
    int choice;
    do {
        printf("\nSecurity Management\n");
        printf("1. Access Control\n");
        printf("2. Camera Surveillance\n");
        printf("3. View Security Incidents\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                printf("CurrentAccess Control Level: %d\n", airport->security.accessControl);
                printf("Enter new Access Control Level (0: No access, 1: Limited access, 2: Full access): ");
                scanf("%d", &airport->security.accessControl);
                break;
            case 2:
                printf("Current Camera Surveillance Status: %d\n", airport->security.cameraSurveillance);
                printf("Turn on (1) or off (0) Camera Surveillance: ");
                scanf("%d", &airport->security.cameraSurveillance);
                break;
            case 3:
                printf("Number of Security Incidents: %d\n", airport->security.securityIncidents);
                break;
            case 4:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}
void addShop(struct Airport *airport) {
    if (airport->numShops < MAX_SHOPS) {
        struct Shop newShop;
 
        printf("Enter Shop Number: ");
        scanf("%d", &newShop.shopNumber);
 
        printf("Enter Shop Name: ");
        scanf("%s", newShop.name);
 
        printf("Enter Shop Type: ");
        scanf("%s", newShop.type);
 
        newShop.rented = 0;  // Initialize as not rented
 
        airport->shops[airport->numShops++] = newShop;
 
        printf("Shop added successfully.\n");
    } else {
        printf("Maximum number of shops reached.\n");
    }
}
 
// Function to display shops
void displayShops(struct Airport *airport) {
    printf("\nShop Details:\n");
    for (int i = 0; i < airport->numShops; i++) {
        struct Shop shop = airport->shops[i];
        printf("Shop Number: %d, Name: %s, Type: %s, Status: %s\n",
               shop.shopNumber, shop.name, shop.type, shop.rented ? "Rented" : "Not Rented");
    }
}
 
// Function to rent a shop
void rentShop(struct Airport *airport) {
    int shopNumber;
    printf("Enter Shop Number to rent: ");
    scanf("%d", &shopNumber);
 
    for (int i = 0; i < airport->numShops; i++) {
        if (airport->shops[i].shopNumber == shopNumber) {
            if (airport->shops[i].rented) {
                printf("Shop is already rented.\n");
            } else {
                airport->shops[i].rented = 1;
                printf("Shop rented successfully.\n");
            }
            return;
        }
    }
 
    printf("Shop not found.\n");
}
 
// Function to add a service
void addService(struct Airport *airport) {
    if (airport->numServices < MAX_SERVICES) {
        struct Service newService;
 
        printf("Enter Service Number: ");
        scanf("%d", &newService.serviceNumber);
 
        printf("Enter Service Name: ");
        scanf("%s", newService.name);
 
        printf("Enter Service Type: ");
        scanf("%s", newService.type);
 
        airport->services[airport->numServices++] = newService;
 
        printf("Service added successfully.\n");
    } else {
        printf("Maximum number of services reached.\n");
    }
}
 
// Function to display services
void displayServices(struct Airport *airport) {
    printf("\nService Details:\n");
    for (int i = 0; i < airport->numServices; i++) {
        struct Service service = airport->services[i];
        printf("Service Number: %d, Name: %s, Type: %s\n",
               service.serviceNumber, service.name, service.type);
    }
}
 
// Function to manage shops, restaurants, and services
void manageShopsAndServices(struct Airport *airport) {
    int choice;
    do {
        printf("\nShops and Services Management\n");
        printf("1. Add a Shop\n");
        printf("2. Display Shops\n");
        printf("3. Rent a Shop\n");
        printf("4. Add a Service\n");
        printf("5. Display Services\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                addShop(airport);
                break;
            case 2:
                displayShops(airport);
                break;
            case 3:
                rentShop(airport);
                break;
            case 4:
                addService(airport);
                break;
            case 5:
                displayServices(airport);
                break;
            case 6:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}
void addFinancialRecord(struct Accounting *accounting) {
    if (accounting->numFinancialRecords < MAX_FINANCIAL_RECORDS) {
        struct FinancialRecord newRecord;
 
        printf("Enter Transaction Number: ");
        scanf("%d", &newRecord.transactionNumber);
 
        printf("Enter Description: ");
        scanf("%s", newRecord.description);
 
        printf("Enter Amount: ");
        scanf("%lf", &newRecord.amount);
 
        accounting->financialRecords[accounting->numFinancialRecords] = newRecord;
 
        if (newRecord.amount > 0) {
            accounting->totalRevenue += newRecord.amount;
        } else {
            accounting->totalExpenses += -newRecord.amount; // consider expenses as negative amounts
        }
 
        (accounting->numFinancialRecords)++;  // Increment the counter
 
        printf("Financial record added successfully.\n");
    } else {
        printf("Maximum number of financial records reached.\n");
    }
}
 
// Function to display financial records
void displayFinancialRecords(struct Accounting *accounting) {
    printf("\nFinancial Records:\n");
    for (int i = 0; i < accounting->numFinancialRecords; i++) {
        struct FinancialRecord record = accounting->financialRecords[i];
        printf("Transaction Number: %d, Description: %s, Amount: %.2f\n",
               record.transactionNumber, record.description, record.amount);
    }
 
    printf("Total Revenue: %.2f\n", accounting->totalRevenue);
    printf("Total Expenses: %.2f\n", accounting->totalExpenses);
    printf("Net Profit/Loss: %.2f\n", accounting->totalRevenue - accounting->totalExpenses);
}
 
// Function to generate a financial report
void generateFinancialReport(struct Accounting *accounting) {
    printf("\nFinancial Report:\n");
    // Add any specific formatting or details you want to include in the report
    displayFinancialRecords(accounting);
}
 
void manageBillingAndAccounting(struct Airport *airport) {
    int choice;
    do {
        printf("\nBilling and Accounting Management\n");
        printf("1. Add a Financial Record\n");
        printf("2. Display Financial Records\n");
        printf("3. Generate Financial Report\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                addFinancialRecord(&airport->accounting);
                break;
            case 2:
                displayFinancialRecords(&airport->accounting);
                break;
            case 3:
                generateFinancialReport(&airport->accounting);
                break;
            case 4:
                printf("Returning to the main menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}
