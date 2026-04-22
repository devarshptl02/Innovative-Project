#include <stdio.h>
#include <stdlib.h>

#define MAX_LEGS 10

// SECTION 1: Structure Definition
typedef struct {
    char type;      
    float strike;   
    float premium;  
    int isLong;     
    int lotSize;    
} Option;

// Function Prototypes
void displayMenu();
void addOption(Option portfolio[], int *legCount);
void viewPortfolio(Option portfolio[], int legCount);
float calculateLegPnL(Option *opt, float expiryPrice);
void runSimulation(Option portfolio[], int legCount);

// SECTION 4: Interactive UI
int main() {
    Option portfolio[MAX_LEGS]; 
    int legCount = 0;           
    int choice;

    printf("\nWelcome to the Pro F&O Strategy Simulator! \n");

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addOption(portfolio, &legCount);
                break;
            case 2:
                viewPortfolio(portfolio, legCount);
                break;
            case 3:
                runSimulation(portfolio, legCount);
                break;
            case 4:
                printf("\nExiting Simulator. Happy Trading!\n");
                exit(0);
            default:
                printf("\nInvalid choice. Please try again!\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n==================================\n");
    printf("        MAIN MENU        \n");
    printf("==================================\n");
    printf("1. Add Option Leg (Call/Put)\n");
    printf("2. View Current Portfolio\n");
    printf("3. Run Payoff Matrix Simulation\n");
    printf("4. Exit\n");
    printf("==================================\n");
}

void addOption(Option portfolio[], int *legCount) {
    if (*legCount >= MAX_LEGS) {
        printf("\nMaximum legs reached! You can't add more.\n");
        return;
    }

    Option *newOpt = &portfolio[*legCount]; 
    
    printf("\n--- Adding Leg %d ---\n", *legCount + 1);
    
    printf("Type ('C' for Call, 'P' for Put): ");
    scanf(" %c", &newOpt->type);
    
    printf("Strike Price: ");
    scanf("%f", &newOpt->strike);
    
    printf("Premium Price: ");
    scanf("%f", &newOpt->premium);
    
    printf("Position (1 for Buy, 0 for Sell): ");
    scanf("%d", &newOpt->isLong);
    
    printf("Lot Size (e.g., 50 for Nifty): ");
    scanf("%d", &newOpt->lotSize);

    (*legCount)++; 
    printf("Option added successfully!\n");
}

// SECTION 2 & 3: Portfolio View and Math Engine
void viewPortfolio(Option portfolio[], int legCount) {
    if (legCount == 0) {
        printf("\nYour portfolio is empty. Add some trades first!\n");
        return;
    }

    printf("\nCurrent Portfolio:\n");
    printf("--------------------------------------------------\n");
    printf("Leg | Type | Strike  | Premium | Pos  | Lot Size\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < legCount; i++) {
        Option *opt = &portfolio[i];
        printf("%3d |  %c   | %7.2f | %7.2f | %-4s | %d\n", 
               i + 1, opt->type, opt->strike, opt->premium, 
               opt->isLong ? "Buy" : "Sell", opt->lotSize);
    }
    printf("--------------------------------------------------\n");
}

float calculateLegPnL(Option *opt, float expiryPrice) {
    float intrinsic = 0.0;
    
    if (opt->type == 'C' || opt->type == 'c') {
        intrinsic = (expiryPrice > opt->strike) ? (expiryPrice - opt->strike) : 0;
    } else if (opt->type == 'P' || opt->type == 'p') {
        intrinsic = (opt->strike > expiryPrice) ? (opt->strike - expiryPrice) : 0;
    }
    
    if (opt->isLong) {
        return (intrinsic - opt->premium) * opt->lotSize; 
    } else {
        return (opt->premium - intrinsic) * opt->lotSize; 
    }
}

void runSimulation(Option portfolio[], int legCount) {
    if (legCount == 0) {
        printf("\n Cannot run simulation. Portfolio is empty!\n");
        return;
    }

    float lowerBound, upperBound, step;
    printf("\n--- Setup Payoff Simulation ---\n");
    printf("Enter Lower Expiry Price: ");
    scanf("%f", &lowerBound);
    printf("Enter Upper Expiry Price: ");
    scanf("%f", &upperBound);
    printf("Enter Step Size (e.g., 50 or 100): ");
    scanf("%f", &step);

    printf("\nPAYOFF MATRIX\n");
    printf("----------------------------------\n");
    printf("Expiry Price | Total P&L (Net)\n");
    printf("----------------------------------\n");

    for (float price = lowerBound; price <= upperBound; price += step) {
        float totalPnL = 0.0;
        for (int i = 0; i < legCount; i++) {
            totalPnL += calculateLegPnL(&portfolio[i], price);
        }
        
        // Print green for profit, red/default for loss (using basic formatting)
        if (totalPnL > 0) {
            printf("%12.2f | +%.2f \n", price, totalPnL);
        } else if (totalPnL < 0) {
            printf("%12.2f | %.2f \n", price, totalPnL);
        } else {
            printf("%12.2f | %.2f \n", price, totalPnL);
        }
    }
    printf("----------------------------------\n");
}