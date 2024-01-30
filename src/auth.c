#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login:");
    scanf("%s", a);

    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tEnter the password to login:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    int id = 0;
    while (fscanf(fp, "%d %s %s", &u.id, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            char *buff = userChecker.password;
            // u.id = id;
            return buff;
        }
    }

    fclose(fp);
    return "no user found";
}

const int getID(char userName[50])
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    int id = 0;
    while (fscanf(fp, "%d %s %s", &id, userChecker.name, userChecker.password) != EOF)
    {
        // printf("%s",userChecker.name);
        if (strcmp(userChecker.name, userName) == 0)
        {
            fclose(fp);
            // printf("found id: %d", id);
            return id;
        }
    }

    fclose(fp);
    return -1;
}

int checkUserExists(char userName[50])
{
    FILE *fp = fopen(USERS, "r");
    struct User userChecker;
    int count = 0;
    while (fscanf(fp, "%d %s %s", &count, userChecker.name, userChecker.password) != EOF)
    {
        if (strcmp(userChecker.name, userName) == 0)
        {
            printf("username already exists");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void registerMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;
    system("clear");
    printf("\n\n\n\t\t\t\tBank Management System\n\t\t\t\tUser Register");
start:
    printf("\n\t\t\t\t\t User Name:");
    scanf("%s", a); // read user name
if (checkUserExists(a) == 0) {
    goto start;
}
    // disabling echo
    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\n\n\n\n\t\t\t\tUser Password:");
    scanf("%s", pass);

    // restore terminal
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};



const int saveUser(struct User *u)
{
    FILE *fp;
    struct User userChecker;

    if ((fp = fopen("./data/users.txt", "a+")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    int count = 0;
    while (fscanf(fp, "%d %s %s", &count, userChecker.name, userChecker.password) != EOF)
    {
        count++;
    }

    fprintf(fp, "\n%d %s %s", count, u->name, u->password);

    fclose(fp);
    return count;
}