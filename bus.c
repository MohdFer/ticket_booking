#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TICKETS 6

// Structure to store bus route information
struct BusRoute {
    int id;
    char date[11];
    char origin[20];
    char destination[20];
    char duration[20];
    int availableSeats;
};

// Structure to store passenger information
struct Passenger {
    char name[MAX_NAME_LENGTH];
    int age;
    int seatNo;
    float fare;
};

// Function to display available bus routes
void displayAvailableRoutes(struct BusRoute routes[], int n) {
    printf("----------------------------------------------------------------\n");
    printf("| ID |    DATE    |   ORIGIN   | DESTINATION |  DURATION | SEATS |\n");
    printf("----------------------------------------------------------------\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("| %-2d | %-10s | %-10s | %-11s | %-9s | %-5d |\n",
               routes[i].id, routes[i].date, routes[i].origin, routes[i].destination, 
               routes[i].duration, routes[i].availableSeats);
    }
    printf("----------------------------------------------------------------\n");
}

// Function to book tickets for a bus route
void bookTicket(struct BusRoute *route, struct Passenger passengers[], int *numTickets) {
    int numTicketsToBook,i;
    printf("Enter the number of tickets to book: ");
    scanf("%d", &numTicketsToBook);

    if (numTicketsToBook <= 0 || numTicketsToBook > route->availableSeats) {
        printf("Invalid number of tickets or insufficient seats available.\n");
        return;
    }

    for ( i = 0; i < numTicketsToBook; i++) {
        printf("\nPassenger %d:\n", *numTickets + i + 1);
        printf("Name: ");
        scanf(" %[^\n]s", passengers[*numTickets + i].name);
        printf("Age: ");
        scanf("%d", &passengers[*numTickets + i].age);
        printf("Seat Number: ");
        scanf("%d", &passengers[*numTickets + i].seatNo);

        // Calculate fare (example fares for demonstration purposes)
        passengers[*numTickets + i].fare = 500.0; // Example fare
    }

    *numTickets += numTicketsToBook;

    // Ticket booking confirmation
    printf("\nTickets booked successfully for Route %d from %s to %s.\n", route->id, route->origin, route->destination);
}

// Function to print ticket receipt
void printReceipt(struct BusRoute *route, struct Passenger passengers[], int numTickets) {
    printf("\n--------------------- RECEIPT ---------------------\n");
    printf("BUS ROUTE DETAILS:\n");
    printf("Route ID: %d\n", route->id);
    printf("Date: %s\n", route->date);
    printf("Origin: %s\n", route->origin);
    printf("Destination: %s\n", route->destination);
    printf("Duration: %s\n", route->duration);
    printf("---------------------------------------------------\n");
    printf("PASSENGER DETAILS:\n");
    printf("| %-5s| %-20s| %-4s| %-9s| %-9s|\n", "No.", "Name", "Age", "Seat No.", "Fare");
    printf("---------------------------------------------------\n");
    float totalFare = 0.0;
    int i;
    for (i = 0; i < numTickets; i++) {
        printf("| %-5d| %-20s| %-4d| %-9d| $%-8.2f|\n", i + 1, passengers[i].name, passengers[i].age, passengers[i].seatNo, passengers[i].fare);
        totalFare += passengers[i].fare;
    }
    printf("---------------------------------------------------\n");
    printf("TOTAL FARE: $%.2f\n", totalFare);
}

int main() {
    // Array to store available bus routes
    struct BusRoute routes[] = {
        {1, "01/05/2024", "Vadaseri", "Chennai", "13 hr 11 min", 10},
        {2, "01/05/2024", "Vadaseri", "Madurai", "4 hr 43 min", 20},
        {3, "01/05/2024", "Vadaseri", "Tanjavur", "9 hr 42 min", 15},
        {4, "01/05/2024", "Vadaseri", "Trivandrum", "2 hr 3 min", 30}
    };

    int numRoutes = sizeof(routes) / sizeof(routes[0]);

    // Display available bus routes
    printf("===== Welcome to Bus Booking System =====\n");
    displayAvailableRoutes(routes, numRoutes);

    // Prompt user to select a bus route
    int choice;
    printf("Select a route (1, 2, 3, etc.): ");
    scanf("%d", &choice);

    // Validate user input
    if (choice < 1 || choice > numRoutes) {
        printf("Invalid choice. Please select a valid route.\n");
        return 1;
    }

    struct Passenger passengers[MAX_TICKETS];
    int numTickets = 0;

    // Perform ticket booking
    bookTicket(&routes[choice - 1], passengers, &numTickets);

    // Print ticket receipt
    printReceipt(&routes[choice - 1], passengers, numTickets);

    return 0;
}
