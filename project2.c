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
float calculateLegPnL(Option *opt, float expiryPrice);
void saveReportToFile(Option portfolio[], int legCount);

// SECTION 2: Interactive UI (Streamlined)
int main() {
    Option portfolio[MAX_LEGS]; 
    int legCount = 0;           
    int choice;

    printf("\nWelcome to the Pro F&O Strategy Simulator (Engine Edition)!\n");

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                addOption(portfolio, &legCount); 
                break;
            case 2: 
                saveReportToFile(portfolio, legCount); 
                break; 
            case 3: 
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
    printf("2. Full Report (Including \n");
    printf("3. Exit\n");
    printf("==================================\n");
}

void addOption(Option portfolio[], int *legCount) {
    if (*legCount >= MAX_LEGS) { 
        printf("\nMaximum legs reached!\n"); 
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
    printf("Lot Size: "); 
    scanf("%d", &newOpt->lotSize);
    
    (*legCount)++; 
    printf("Option added successfully!\n");
}

// SECTION 3: Math Engine & File Output
float calculateLegPnL(Option *opt, float expiryPrice) {
    float intrinsic = 0;
    if (opt->type == 'C' || opt->type == 'c') {
        intrinsic = (expiryPrice > opt->strike) ? (expiryPrice - opt->strike) : 0;
    } else if (opt->type == 'P' || opt->type == 'p') {
        intrinsic = (opt->strike > expiryPrice) ? (opt->strike - expiryPrice) : 0;
    }
    return opt->isLong ? (intrinsic - opt->premium) * opt->lotSize : (opt->premium - intrinsic) * opt->lotSize;
}

void saveReportToFile(Option portfolio[], int legCount) {
    if (legCount == 0) { 
        printf("\nCannot generate file. Portfolio is empty!\n"); 
        return; 
    }

    float lower, upper, step;
    printf("\n--- Setup File Export ---\n");
    printf("Enter Lower Expiry Price: "); 
    scanf("%f", &lower);
    printf("Enter Upper Expiry Price: "); 
    scanf("%f", &upper);
    printf("Enter Step Size: "); 
    scanf("%f", &step);

    FILE *file = fopen("full_trade_report.txt", "w");
    
    if (file == NULL) {
        printf("\nError: Could not create the file on your system!\n");
        return;
    }
    
    // 1. Print the Portfolio Section to File
    fprintf(file, "==================================================\n");
    fprintf(file, "CURRENT PORTFOLIO DETAILS\n");
    fprintf(file, "==================================================\n");
    fprintf(file, "Leg | Type | Strike  | Premium | Pos  | Lot Size\n");
    fprintf(file, "--------------------------------------------------\n");
    for (int i = 0; i < legCount; i++) {
        fprintf(file, "%3d |  %c   | %7.2f | %7.2f | %-4s | %d\n", 
               i + 1, portfolio[i].type, portfolio[i].strike, portfolio[i].premium, 
               portfolio[i].isLong ? "Buy" : "Sell", portfolio[i].lotSize);
    }
    fprintf(file, "--------------------------------------------------\n\n");

    // 2. Print the Payoff Matrix Section to File
    fprintf(file, "==================================\n");
    fprintf(file, "OPTIONS STRATEGY PAYOFF MATRIX\n");
    fprintf(file, "==================================\n");
    fprintf(file, "Expiry Price | Total Net P&L\n");
    fprintf(file, "----------------------------------\n");
    
    for (float p = lower; p <= upper; p += step) {
        float totalPnL = 0;
        for (int i = 0; i < legCount; i++) {
            totalPnL += calculateLegPnL(&portfolio[i], p);
        }
        
        fprintf(file, "%12.2f | %12.2f\n", p, totalPnL);
    }
    
    fprintf(file, "==================================\n");
    
    fclose(file); 
    printf("\nSuccess! You can now open 'full_trade_report.txt' to view your complete strategy!\n");
}