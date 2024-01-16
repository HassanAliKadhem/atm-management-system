#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                  &r->id,
                  &r->userId,
                  name,
                  &r->accountNbr,
                  &r->deposit.month,
                  &r->deposit.day,
                  &r->deposit.year,
                  r->country,
                  &r->phone,
                  &r->amount,
                  r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void fail(struct User u)
{
    int option;
    printf("\n✖ Fail!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");

    system("clear");
    printf("\t\t\t===== New record =====\n");

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
noAccount:
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);
    r.id = 0;
    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
        r.id = cr.id + 1;
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    success(u);
}

void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void checkAccount(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\n\n\t\tEnter account id that you want to check\n  Account ID:");

    int id;
    scanf("%d", &id);
    
    int found = 0;
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.id == id)
        {
            found = 1;
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);

            if (strcmp(r.accountType, "saving") == 0)
            {
                printf("savings: interest rate 7%%\n");
                printf("You will get $%.2f as interest on day %d of every month", r.amount * 0.07/12, r.deposit.day);
            }
            else if (strcmp(r.accountType, "fixed01") == 0)
            {
                printf("fixed01(1 year account): interest rate 4%%\n");
                printf("You will get $%.2f as interest on %d/%d/%d", r.amount * 0.04, r.deposit.month,r.deposit.day,r.deposit.year+1);
            }
            else if (strcmp(r.accountType, "fixed02") == 0)
            {
                printf("fixed01(1 year account): interest rate 5%%\n");
                printf("You will get $%.2f as interest on %d/%d/%d", r.amount * 0.05*2, r.deposit.month,r.deposit.day,r.deposit.year+2);
            }
            else if (strcmp(r.accountType, "fixed03") == 0)
            {
                printf("fixed01(1 year account): interest rate 8%%\n");
                printf("You will get $%.2f as interest on %d/%d/%d", r.amount * 0.08*3, r.deposit.month,r.deposit.day,r.deposit.year+3);
            }
            else if (strcmp(r.accountType, "current") == 0)
            {
                printf("You will not get interests because the account is of type current");
            }
        }
    }
    fclose(pf);
    if (found ==1 ) {
        success(u);
    } else {
        printf("no account matching %d found",id);
        fail(u);
    }
}

void updateAccount(struct User u)
{
    char userName[100];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");
    FILE *newPf = fopen("./data/newRecords.txt", "w");

    system("clear");
    printf("\n\n\t\tEnter account id that you want to update\n  Account ID:");

    int id;
    scanf("%d", &id);

    int found = 0;

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.id == id)
        {
            system("clear");
            printf("\n\n\t\tChoose field you want to change");
            printf("\n\t\t[1] Country");
            printf("\n\t\t[2] Phone number");
            printf("\n\t\t[3] Cancel\n");

            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice)
            {
            case 1: // country
                printf("\n\n\t\tPlease enter new country: \nCountry: ");
                scanf("%s", r.country);
                found = 1;
                break;
            case 2: // phone
                printf("\n\n\t\tPlease enter new phone number: \nPhone: ");
                scanf("%d", &r.phone);
                found = 1;
                break;
            default: // wrong choice
                found = 2;
                break;
            }
        }
        fprintf(newPf, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                r.id,
                r.userId,
                userName,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
    }

    fclose(pf);
    fclose(newPf);
    remove("./data/records.txt");
    rename("./data/newRecords.txt", "./data/records.txt");
    if (found == 1)
    {
        success(u);
    }
    else
    {
        if (found == 2)
        {
            printf("Operation Canceled");
        }
        else
        {
            printf("Account not found");
        }
        fail(u);
    }
}

void transactAccount(struct User u)
{
    char userName[100];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");
    FILE *newPf = fopen("./data/newRecords.txt", "w");

    system("clear");
    printf("\n\n\t\tEnter account id that you want to make a transaction to\n  Account ID:");

    int id;
    scanf("%d", &id);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.id == id)
        {
            system("clear");
            if (strcmp(r.accountType, "fixed01") == 0 || strcmp(r.accountType, "fixed02") == 0 || strcmp(r.accountType, "fixed03") == 0)
            {
                printf("\n\nthe account type is %s and you are not allowed to make transactions to it", r.accountType);
            }
            else
            {
                printf("\n\n\t\tChoose transaction type");
                printf("\n\t\t[1] Transaction");
                printf("\n\t\t[2] Withdraw");
                printf("\n\t\t[3] Deposit\n");

                int userChoice;
                scanf("%d", &userChoice);

                float amount = 0.0;
                switch (userChoice)
                {
                case 1:
                    printf("\n\n\t\tHow much do you want to pay \nAmount: ");
                    scanf("%f", &amount);
                    if (amount > r.amount)
                    {
                        printf("\n\nYou don't have enough money in your account.");
                    }
                    else
                    {
                        r.amount = r.amount - amount;
                    }
                    break;
                case 2:
                    printf("\n\n\t\tHow much do you want to withdraw \nAmount: ");
                    scanf("%f", &amount);
                    if (amount > r.amount)
                    {
                        printf("\n\nYou don't have enough money in your account.");
                    }
                    else
                    {
                        r.amount = r.amount - amount;
                        printf("\n\nDon't forget to take your cash from the machine.");
                    }
                    break;
                case 3:
                    printf("\n\n\t\tHow much do you want to deposit \nAmount: ");
                    scanf("%f", &amount);
                    r.amount = r.amount + amount;
                    printf("\n\n%f Deposited to your account.", amount);
                    break;
                default: // wrong choice
                    break;
                }
            }
        }
        fprintf(newPf, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                r.id,
                r.userId,
                userName,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
    }

    fclose(pf);
    fclose(newPf);
    remove("./data/records.txt");
    rename("./data/newRecords.txt", "./data/records.txt");
    success(u);
}

void deleteAccount(struct User u)
{
    char userName[100];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");
    FILE *newPf = fopen("./data/newRecords.txt", "w");

    system("clear");
    printf("\n\n\t\tEnter account id that you want to delete\n  Account ID:");

    int id;
    scanf("%d", &id);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) != 0 || r.id != id)
        {
            fprintf(newPf, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    r.id,
                    r.userId,
                    userName,
                    r.accountNbr,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);
        }
    }

    fclose(pf);
    fclose(newPf);
    remove("./data/records.txt");
    rename("./data/newRecords.txt", "./data/records.txt");
    success(u);
}

void transferAccount(struct User u)
{
    char userName[100];
    struct Record r;
    FILE *pf = fopen(RECORDS, "r");
    FILE *newPf = fopen("./data/newRecords.txt", "w");

    system("clear");
    printf("\n\n\t\tEnter account id that you want to transfer\n  Account ID:");

    int id;
    scanf("%d", &id);

    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.id == id)
        {
            system("clear");

            printf("\n\n\t\tEnter new user ID:\nid:");

            int userChoice;
            scanf("%d", &userChoice);

            FILE *fp;
            struct User userChecker;
            if ((fp = fopen("./data/users.txt", "a+")) == NULL)
            {
                printf("Error! opening file");
                exit(1);
            }
            int changed = 0;
            while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) != EOF)
            {
                if (userChecker.id == userChoice)
                {
                    changed = 1;
                    fprintf(newPf, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                            r.id,
                            userChecker.id,
                            userChecker.name,
                            r.accountNbr,
                            r.deposit.month,
                            r.deposit.day,
                            r.deposit.year,
                            r.country,
                            r.phone,
                            r.amount,
                            r.accountType);
                }
            }
            if (changed == 0)
            {
                printf("User doesn't exist.\naccount not transferred.\n");
                fprintf(newPf, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                        r.id,
                        r.userId,
                        userName,
                        r.accountNbr,
                        r.deposit.month,
                        r.deposit.day,
                        r.deposit.year,
                        r.country,
                        r.phone,
                        r.amount,
                        r.accountType);
            }
        }
        else
        {

            fprintf(newPf, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    r.id,
                    r.userId,
                    userName,
                    r.accountNbr,
                    r.deposit.month,
                    r.deposit.day,
                    r.deposit.year,
                    r.country,
                    r.phone,
                    r.amount,
                    r.accountType);
        }
    }

    fclose(pf);
    fclose(newPf);
    remove("./data/records.txt");
    rename("./data/newRecords.txt", "./data/records.txt");
    success(u);
}