#include <stdio.h>

// ingredient requirements for each coffee type
#define expresso_beans 8
#define expresso_water 30
#define expresso_milk 0
#define expresso_syrup 0

#define cappuccino_beans 8
#define cappuccino_water 30
#define cappuccino_milk 70
#define cappuccino_syrup 0

#define mocha_beans 8
#define mocha_water 39
#define mocha_milk 160
#define mocha_syrup 30

// admin password
#define admin_pass 9999

// machine stock levels
int beans = 100;
int water = 100;
int milk = 200;
int syrup = 100;

float total_amount = 0.0; // variable to keep track of total money collected

// prices as variables (modifiable)
float expresso_price = 3.5;
float cappuccino_price = 4.5;
float mocha_price = 5.5;

// function declarations
void dispcoffeetypes(); // displays available coffee types
int userchoice(); // handles users coffee selection 
int confirmchoice(int choice); // confirms the selected coffee before proceeding 
float getprice(int choice); // returns the price of the selected coffee
void preparecoffee(int choice); // deducts ingredients and simulates coffee preparation 
void payment(float price); // handles coin insertion and payment process
void adminmode(); // admin control panel 

int main() { // main function
    int option; // variable to store user's menu choice

    while (1) { // infinite loop to keep the machine running until user exits
        // display main menu options
        printf("\n===== coffee machine options =====\n");
        printf("1) order coffee\n");
        printf("2) admin mode\n");
        printf("3) exit\n");
        printf("enter your choice: ");
        scanf("%d", &option);

        // process user's main menu choice
        if (option == 1) {

            dispcoffeetypes(); // display available coffee types 

            int choice = userchoice(); // let user select coffee

            if (choice == 0) { // if user entered 0, cancel order and return to main menu
                continue;
            }

            if (confirmchoice(choice)) { // confirm selection before preparing
                float price = getprice(choice); // get price for the selected coffee
                payment(price); // process payment
                preparecoffee(choice); // prepare coffee and update stock
            }
        }
        else if (option == 2) {
            adminmode(); // enter admin mode (password protected)
        }
        else if (option == 3) {
            printf("exiting... total sales: %.2f AED\n", total_amount); // exit program and display total sales
            break; // exit the infinite loop
        }
        else {
            printf("invalid option. try again.\n"); // invalid option entered
        }
    }
    return 0; // program end
}

// function definitions

// function to display available coffee types based on ingredient stock
void dispcoffeetypes() {
    printf("\navailable coffee options:\n");

    if (beans >= expresso_beans && water >= expresso_water) // espresso availability check
        printf("1. expresso (%.2f AED)\n", expresso_price);
    else
        printf("expresso: unavailable due to insufficient ingredients.\n");

    if (beans >= cappuccino_beans && water >= cappuccino_water && milk >= cappuccino_milk) // cappuccino availability check
        printf("2. cappuccino (%.2f AED)\n", cappuccino_price);
    else
        printf("cappuccino: unavailable due to insufficient ingredients.\n");

    if (beans >= mocha_beans && water >= mocha_water && milk >= mocha_milk && syrup >= mocha_syrup) // mocha availability check
        printf("3. mocha (%.2f AED)\n", mocha_price);
    else
        printf("mocha: unavailable due to insufficient ingredients.\n");

    printf("0. cancel order\n");
}

// function to get user's coffee choice
int userchoice() {
    int c;
    printf("enter your coffee choice: ");
    scanf("%d", &c);
    return c; // return user's selected option
}

// function to confirm selected coffee before proceeding
int confirmchoice(int choice) {
    int confirm;
    printf("you selected option %d. confirm? (1-Yes, 2-No): ", choice);
    scanf("%d", &confirm);
    return confirm == 1; // return 1 if confirmed, 0 otherwise
}

// function to return price of coffee based on user choice
float getprice(int choice) {
    if (choice == 1)
        return expresso_price;
    else if (choice == 2)
        return cappuccino_price;
    else if (choice == 3)
        return mocha_price;
    else
        return 0;
}

// function to handle coin insertion and payment
void payment(float price) {
    float paid = 0, coin;
    printf("please insert coins (1 or 0.5 AED) to pay %.2f AED:\n", price);

    while (paid < price) { // keep accepting coins until total paid is at least equal to price
        printf("insert coin: ");
        scanf("%f", &coin);

        if (coin == 1.0 || coin == 0.5) { // accept only 1 or 0.5 AED coins
            paid += coin; // add to total paid
            printf("total inserted: %.2f AED\n", paid);
        } else {
            printf("invalid coin. accepts only 1 or 0.5 AED.\n");
        }
    }

    if (paid > price) { // if extra money inserted, give change
        printf("take your change: %.2f AED\n", paid - price);
    }

    total_amount += price; // add coffee price to total sales
}

// function to simulate preparing the selected coffee and update ingredient stock
void preparecoffee(int choice) {
    if (choice == 1) { // espresso
        beans -= expresso_beans;
        water -= expresso_water;
        printf("giving espresso...\n");
    } 
    else if (choice == 2) { // cappuccino
        beans -= cappuccino_beans;
        water -= cappuccino_water;
        milk -= cappuccino_milk;
        printf("giving cappuccino...\n");
    } 
    else if (choice == 3) { // mocha
        beans -= mocha_beans;
        water -= mocha_water;
        milk -= mocha_milk;
        syrup -= mocha_syrup;
        printf("giving mocha...\n");
    } 
    else {
        printf("invalid coffee choice.\n");
    }

    // warning alerts for low stock levels
    if (beans <= 10) printf("ALERT: low coffee beans!\n");
    if (water <= 40) printf("ALERT: low water!\n");
    if (milk <= 160) printf("ALERT: low milk!\n");
    if (syrup <= 40) printf("ALERT: low syrup!\n");
}

// function for admin operations like checking stock, refilling, viewing sales, and updating prices
void adminmode() {
    int pass;
    printf("enter admin password: ");
    scanf("%d", &pass);

    if (pass != admin_pass) { // password check
        printf("incorrect password!\n");
        return; // exit admin mode if password is wrong
    }

    int option = -1;

    while (option != 0) { // repeat until admin chooses to exit
        // admin control menu
        printf("\n--- admin menu ---\n");
        printf("1. view stock\n");
        printf("2. refill stock\n");
        printf("3. view total sales\n");
        printf("4. change coffee prices\n");
        printf("0. exit admin mode\n");
        printf("enter choice: ");
        scanf("%d", &option);

        if (option == 1) { // display current stock levels
            printf("stock levels:\nbeans=%d, water=%d, milk=%d, syrup=%d\n",
                   beans, water, milk, syrup);
        } 
        else if (option == 2) { // refill all stock to full capacity
            beans = 100;
            water = 100;
            milk = 200;
            syrup = 100;
            printf("stock refilled.\n");
        } 
        else if (option == 3) { // show total sales so far
            printf("total sales: %.2f AED\n", total_amount);
        } 
        else if (option == 4) { // modify coffee prices 
            int coffee_choice;
            float new_price;
            printf("\nselect coffee to change price:\n");
            printf("1. expresso (current: %.2f AED)\n", expresso_price);
            printf("2. cappuccino (current: %.2f AED)\n", cappuccino_price);
            printf("3. mocha (current: %.2f AED)\n", mocha_price);
            printf("enter choice: ");
            scanf("%d", &coffee_choice);

            printf("enter new price (AED): ");
            scanf("%f", &new_price);

            if (coffee_choice == 1)
                expresso_price = new_price;
            else if (coffee_choice == 2)
                cappuccino_price = new_price;
            else if (coffee_choice == 3)
                mocha_price = new_price;
            else
                printf("invalid selection.\n");

            printf("price updated successfully!\n");
        } 
        else if (option == 0) { // exit admin mode
            printf("exiting admin mode...\n");
        } 
        else {
            printf("invalid option.\n"); // invalid input
        }
    }
}
