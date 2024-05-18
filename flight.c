#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_TICKETS 5

// ANSI color escape codes
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"

// Structure to store flight information
struct Flight {
    int sl_no;
    char date[11];
    char origin[4];
    char destination[4];
    char flight_name[50];
    int flight_no;
    char departure_time[6];
    char arrival_time[6];
    int gate_no;
    int available_seats;
};

// Structure to store passenger information
struct Passenger {
    char name[MAX_NAME_LENGTH];
    int age;
    int seat_no;
    float fare;
};

// Function to display available flights
void displayAvailableFlights(struct Flight flights[], int n) {
    printf("+------+----------+---------+-------------+------------------------------+------------+----------------+--------------+----------+-----------------+\n");
    printf("|SL.NO.| DATE     | ORIGIN  | DESTINATION | FLIGHT NAME                  | FLIGHT NO. | DEPARTURE TIME | ARRIVAL TIME | GATE NO. | AVAILABLE SEATS |\n");
    printf("+------+----------+---------+-------------+------------------------------+------------+----------------+--------------+----------+-----------------+\n");
    int i;
	for ( i = 0; i < n; i++) {
        printf("|%-5d| %-10s| %-8s| %-12s|%-30s| %-11d| %-15s| %-13s| %-9d| %-16d|\n",
               flights[i].sl_no, flights[i].date, flights[i].origin, flights[i].destination, 
               flights[i].flight_name, flights[i].flight_no, flights[i].departure_time, 
               flights[i].arrival_time, flights[i].gate_no, flights[i].available_seats);
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------+\n");
}

// Function to book tickets
void bookTicket(struct Flight *flight, struct Passenger passengers[], int *num_tickets) {
    int num_tickets_to_book;
    printf("Enter the number of tickets to book: ");
    scanf("%d", &num_tickets_to_book);

    if (num_tickets_to_book <= 0 || num_tickets_to_book > flight->available_seats) {
        printf("Invalid number of tickets or insufficient seats available.\n");
        return;
    }

    int i;
	for ( i = 0; i < num_tickets_to_book; i++) {
        printf("\nPassenger %d:\n", *num_tickets + i + 1);
        printf("Name: ");
        scanf(" %[^\n]s", passengers[*num_tickets + i].name);
        printf("Age: ");
        scanf("%d", &passengers[*num_tickets + i].age);
        printf("Seat Number: ");
        scanf("%d", &passengers[*num_tickets + i].seat_no);

        // Calculate fare (example fares for demonstration purposes)
        passengers[*num_tickets + i].fare = 1000.0; // Example fare
    }

    *num_tickets += num_tickets_to_book;

    // Ticket booking confirmation
    printf("\nTickets booked successfully for Flight %d (%s) from %s to %s.\n", flight->flight_no, flight->flight_name, flight->origin, flight->destination);
}

// Function to print receipt
void printReceipt(struct Flight *flight, struct Passenger passengers[], int num_tickets) {
    printf("\n--------------------- RECEIPT ---------------------\n");
    printf("FLIGHT DETAILS:\n");
    printf("Flight Name: %s\n", flight->flight_name);
    printf("Flight No.: %d\n", flight->flight_no);
    printf("Date: %s\n", flight->date);
    printf("Origin: %s\n", flight->origin);
    printf("Destination: %s\n", flight->destination);
    printf("Departure Time: %s\n", flight->departure_time);
    printf("Arrival Time: %s\n", flight->arrival_time);
    printf("Gate No.: %d\n", flight->gate_no);
    printf("+--------------------------------------------------------+\n");
    printf("|               PASSENGER DETAILS                        |\n");   
    printf("+--------------------------------------------------------+\n");
    printf("| %-5s| %-20s| %-4s| %-9s| %-9s|\n", "No.", "Name", "Age", "Seat No.", "Fare");
    printf("+------+---------------------+-----+----------+----------+\n");
    float total_fare = 0.0;
    int i;
    for ( i = 0; i < num_tickets; i++) {
        printf("| %-5d| %-20s| %-4d| %-9d| " GREEN "$%-8.2f" RESET "|\n", i + 1, passengers[i].name, passengers[i].age, passengers[i].seat_no, passengers[i].fare);
        total_fare += passengers[i].fare;
    }
    printf("+------+---------------------+-----+----------+----------+\n");
    printf("|                                  |TOTAL FARE| " GREEN "$%.2f" RESET " |\n", total_fare);
    printf("+--------------------------------------------------------+\n");
}

int main() {
    // Array to store available flights
    struct Flight flights[] = {
        {1, "08/05/2024", "TRV", "LHR", "Trivandrum to London", 101, "10:00", "15:00", 20, 150},
        {2, "08/05/2024", "TRV", "JFK", "Trivandrum to New York", 202, "11:00", "19:00", 15, 180},
        {3, "09/05/2024", "TRV", "DXB", "Trivandrum to Dubai", 303, "12:00", "16:00", 12, 200},
        {4, "09/05/2024", "TRV", "NRT", "Trivandrum to Tokyo", 404, "13:00", "21:00", 18, 160},
        {5, "08/05/2024", "TRV", "SFO", "Trivandrum to San Francisco", 505, "14:00", "23:00", 25, 170},
        {6, "09/05/2024", "TRV", "LAX", "Trivandrum to Los Angeles", 606, "15:00", "23:00", 22, 190},
        {7, "10/05/2024", "TRV", "ORD", "Trivandrum to Chicago", 707, "16:00", "02:00", 17, 140},
        {8, "10/05/2024", "TRV", "YYZ", "Trivandrum to Toronto", 808, "17:00", "04:00", 19, 160}
    };

    int num_flights = sizeof(flights) / sizeof(flights[0]);

    // Display available flights
    printf(BLUE "====== Welcome to Trivandrum International Airport ======\n" RESET);
    printf(YELLOW "Attractions: Enjoy your flight experience!\n" RESET);
    displayAvailableFlights(flights, num_flights);

    // Prompt user to select a flight
    int choice;
    printf("Select a flight (1, 2, 3 etc.): ");
    scanf("%d", &choice);

    // Validate user input
    if (choice < 1 || choice > num_flights) {
        printf("Invalid choice. Please select a valid flight.\n");
        return 1;
    }

    struct Passenger passengers[MAX_TICKETS];
    int num_tickets = 0;

    // Perform booking
    bookTicket(&flights[choice - 1], passengers, &num_tickets);

    // Print receipt
    printReceipt(&flights[choice - 1], passengers, num_tickets);

    return 0;
}
