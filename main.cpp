#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

const int NUM_JOURNEYS = 4;
const int COACH_CAPACITY = 80;
const double TICKET_PRICE = 50.0; // Updated to reflect the cost for the whole journey

// Data structure to store information about each train journey
struct TrainJourney {
    string trainName;
    string upTrainTime;
    string downTrainTime;
    int availableTickets;
    int passengers;
    double revenue;
};

// Declare the vector globally
vector<TrainJourney> journeys;

// Function to initialize the screen display for the start of the day
void setupScreenDisplay() {
    string upTrainTimes[] = {"9:00", "11:00", "13:00", "15:00"};
    string downTrainTimes[] = {"10:00", "12:00", "14:00", "16:00"};

    for (int i = 0; i < NUM_JOURNEYS; ++i) {
        TrainJourney journey;
        journey.trainName = "Train " + to_string(i + 1);
        journey.upTrainTime = upTrainTimes[i];
        journey.downTrainTime = downTrainTimes[i];
        journey.availableTickets = COACH_CAPACITY;
        journey.passengers = 0;
        journey.revenue = 0.0;
        journeys.push_back(journey);
    }
}

// Function to display the train timings and ticket prices
void displayTrainTimings() {
    cout << "--------------------------------------------------------------" << endl;
    cout << "Train Timings, Ticket Prices, and Available Tickets" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << setw(20) << "Train Name" << setw(20) << "Up Train Time" << setw(20) << "Down Train Time" << setw(20) << "Ticket Price" << setw(20) << "Available Tickets" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < NUM_JOURNEYS; ++i) {
        cout << setw(20) << journeys[i].trainName << setw(20) << journeys[i].upTrainTime << setw(20) << journeys[i].downTrainTime << setw(20) << "$" << TICKET_PRICE << setw(20) << journeys[i].availableTickets << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
}

// Function to purchase tickets for a single passenger or a group
void purchaseTickets() {
    cout << "--------------------------------------------------------------" << endl;
    cout << "Purchase Tickets" << endl;
    cout << "--------------------------------------------------------------" << endl;

    // Get passenger details
    string passengerName, phoneNumber;
    int numPassengers;

    cout << "Enter passenger name: ";
    cin.ignore(); // Clear the newline character from the buffer
    getline(cin, passengerName);

    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    cout << "Enter the number of passengers (1-80): ";
    cin >> numPassengers;

    // Validate the number of passengers
    if (numPassengers < 1 || numPassengers > COACH_CAPACITY) {
        cout << "Invalid number of passengers. Please enter a number between 1 and 80." << endl;
        return;
    }

    // Get user input for the journey
    int journeyIndex;
    cout << "Enter the journey number (1 to 4): ";
    cin >> journeyIndex;

    // Validate user input
    if (journeyIndex < 1 || journeyIndex > NUM_JOURNEYS) {
        cout << "Invalid journey number. Please enter a valid journey number." << endl;
        return;
    }

    // Check if there are enough available tickets
    if (journeys[journeyIndex - 1].availableTickets < numPassengers) {
        cout << "Tickets not available for the selected journey." << endl;
        return;
    }

    // Get user input for the down journey train
    int downJourneyIndex;
    cout << "Enter the down journey train number (1 to 4): ";
    cin >> downJourneyIndex;

    // Validate user input for the down journey train
    if (downJourneyIndex < 1 || downJourneyIndex > NUM_JOURNEYS) {
        cout << "Invalid down journey train number. Please enter a valid number." << endl;
        return;
    }

    // Calculate total price
    double totalPrice = numPassengers * TICKET_PRICE;

    // Update journey information
    journeys[journeyIndex - 1].availableTickets -= numPassengers;
    journeys[journeyIndex - 1].passengers += numPassengers;
    journeys[journeyIndex - 1].revenue += totalPrice;

    // Display purchase summary
    cout << "Purchase Summary:" << endl;
    cout << "Passenger Name: " << passengerName << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Number of Passengers: " << numPassengers << endl;
    cout << "Journey: " << journeys[journeyIndex - 1].trainName << " - " << journeys[journeyIndex - 1].upTrainTime << " to " << journeys[downJourneyIndex - 1].downTrainTime << endl;
    cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;
    cout << "--------------------------------------------------------------" << endl;
}

// Function to display the end-of-day report
void endOfDayReport() {
    cout << "--------------------------------------------------------------" << endl;
    cout << "End-of-Day Report" << endl;
    cout << "--------------------------------------------------------------" << endl;

    // Display table headers
    cout << setw(20) << "Train Name" << setw(20) << "Up Train Time" << setw(20) << "Down Train Time" << setw(20) << "Passengers" << setw(20) << "Revenue" << endl;
    cout << "--------------------------------------------------------------" << endl;

    // Display information for each train journey
    for (const TrainJourney& journey : journeys) {
        cout << setw(20) << journey.trainName << setw(20) << journey.upTrainTime << setw(20) << journey.downTrainTime << setw(20) << journey.passengers << setw(20) << "$" << fixed << setprecision(2) << journey.revenue << endl;
    }

    // Calculate and display total passengers and total revenue
    int totalPassengers = 0;
    double totalRevenue = 0.0;
    for (const TrainJourney& journey : journeys) {
        totalPassengers += journey.passengers;
        totalRevenue += journey.revenue;
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "Total Passengers: " << totalPassengers << endl;
    cout << "Total Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;

    // Find and display the train journey with the most passengers
    int maxPassengersIndex = 0;
    for (int i = 1; i < NUM_JOURNEYS; ++i) {
        if (journeys[i].passengers > journeys[maxPassengersIndex].passengers) {
            maxPassengersIndex = i;
        }
    }

    cout << "Most Popular Journey: " << journeys[maxPassengersIndex].trainName << " - " << journeys[maxPassengersIndex].upTrainTime << " to " << journeys[maxPassengersIndex].downTrainTime << endl;
    cout << "--------------------------------------------------------------" << endl;
}

int main() {
    setupScreenDisplay();

    // Loop to allow multiple transactions
    while (true) {
        // Get user choice
        int choice;
        cout << "Enter 1 to Purchase Tickets, 2 to See End-of-Day Report, 0 to Exit: ";
        cin >> choice;

        if (choice == 1) {
            // Purchase Tickets
            displayTrainTimings();
            purchaseTickets();
        } else if (choice == 2) {
            // End-of-Day Report
            endOfDayReport();
        } else if (choice == 0) {
            // Exit the loop
            break;
        } else {
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}
