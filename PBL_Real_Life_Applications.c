
#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student
{
    int id;
    char name[50];
    float fees;
    char course[20];
    char result[20];
};

struct Student students[MAX];
int count = 0;

// Function declarations

void loadData();
void saveData();
void registerStudent();
void payFees();
void allocateCourse();
void enterResult();
void displayStudents();
void searchStudent();
void editStudent();

int main()
{
    char userid[20];
    char password[20];
    int choice;

    printf("\tABC INSTITUTE\n");

    printf("Enter User ID: ");
    scanf("%19s", userid);

    printf("Enter Password: ");
    scanf("%19s", password);

    if (strcmp(userid, "admin") != 0 ||
        strcmp(password, "1234") != 0)
    {
        printf("\nInvalid User ID or Password!\n");
        return 0;
    }

    printf("\nLogin Successful!\n");

    loadData();

    do
    {
        printf("\n\n\tMAIN MENU\n");
        printf("1. Register Student\n");
        printf("2. Pay Fees\n");
        printf("3. Allocate Course\n");
        printf("4. Enter Result\n");
        printf("5. Display All Students\n");
        printf("6. Search Student\n");
        printf("7. Exit\n");
        printf("8. Edit Student Record\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input!\n");
            while (getchar() != '\n')
                ;
            choice = 0;
            continue;
        }

        switch (choice)
        {
        case 1:
            registerStudent();
            break;

        case 2:
            payFees();
            break;

        case 3:
            allocateCourse();
            break;

        case 4:
            enterResult();
            break;

        case 5:
            displayStudents();
            break;

        case 6:
            searchStudent();
            break;

        case 7:
            saveData();
            printf("\nData saved successfully.\n");
            printf("Thank you for using the system!\n");
            break;

        case 8:
            editStudent();
            break;

        default:
            printf("\nInvalid choice!\n");
        }

    } while (choice != 7);

    return 0;
}

// Load data from file

void loadData()
{
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        count = 0;
        return;
    }

    if (fread(&count, sizeof(int), 1, fp) != 1)
    {
        count = 0;
        fclose(fp);
        return;
    }

    if (count < 0 || count > MAX)
    {
        count = 0;
        fclose(fp);
        return;
    }

    if (fread(students, sizeof(struct Student),
              count, fp) != (size_t)count)
    {
        count = 0;
    }

    fclose(fp);
}

// Save data to file

void saveData()
{
    FILE *fp;

    fp = fopen("students.dat", "wb");

    if (fp == NULL)
    {
        printf("Error saving data!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);

    fwrite(students, sizeof(struct Student),
           count, fp);

    fclose(fp);
}

// Register Student

void registerStudent()
{
    int i;

    if (count >= MAX)
    {
        printf("\nStudent limit reached!\n");
        return;
    }

    printf("\nREGISTER STUDENT\n");

    printf("Enter Student ID: ");

    if (scanf("%d", &students[count].id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (students[i].id == students[count].id)
        {
            printf("\nStudent ID already exists!\n");
            return;
        }
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", students[count].name);

    students[count].fees = 0;

    strcpy(students[count].course, "Not Assigned");
    strcpy(students[count].result, "Not Declared");

    count++;

    saveData();

    printf("\nStudent registered successfully!\n");
}

// Pay Fees

void payFees()
{
    int id, i, found = 0;
    float fees;

    printf("\n\tFEE PAYMENT\n");

    printf("Enter Student ID: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            found = 1;

            printf("Student Name: %s\n", students[i].name);
            printf("Enter Fees: ");

            if (scanf("%f", &fees) != 1)
            {
                printf("Invalid fee input!\n");
                while (getchar() != '\n')
                    ;
                return;
            }

            if (fees <= 0)
            {
                printf("\nInvalid fee amount!\n");
                return;
            }

            students[i].fees = fees;

            saveData();

            printf("\nFees paid successfully!\n");
            break;
        }
    }

    if (found == 0)
    {
        printf("\nStudent not found!\n");
    }
}

// Allocate Course

void allocateCourse()
{
    int id, choice, i, found = 0;

    printf("\n\tCOURSE ALLOCATION\n");

    printf("Enter Student ID: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            found = 1;

            if (students[i].fees <= 0)
            {
                printf("\nPlease pay the fees first!\n");
                return;
            }

            printf("\n1. DS\n");
            printf("2. AI\n");
            printf("3. ML\n");
            printf("4. Web\n");

            printf("Select Course: ");

            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input!\n");
                while (getchar() != '\n')
                    ;
                return;
            }

            if (choice == 1)
                strcpy(students[i].course, "DS");

            else if (choice == 2)
                strcpy(students[i].course, "AI");

            else if (choice == 3)
                strcpy(students[i].course, "ML");

            else if (choice == 4)
                strcpy(students[i].course, "Web");

            else
            {
                printf("\nInvalid course!\n");
                return;
            }

            saveData();

            printf("\nCourse allocated successfully!\n");
            break;
        }
    }

    if (found == 0)
    {
        printf("\nStudent not found!\n");
    }
}

// Enter Result

void enterResult()
{
    int id, choice, i, found = 0;

    printf("\n\tRESULT\n");

    printf("Enter Student ID: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            found = 1;

            if (strcmp(students[i].course, "Not Assigned") == 0)
            {
                printf("\nCourse has not been assigned!\n");
                return;
            }

            printf("\nStudent Name: %s\n", students[i].name);
            printf("Course: %s\n", students[i].course);

            printf("\n1. Excellent\n");
            printf("2. Good\n");
            printf("3. Fail\n");

            printf("Enter Result: ");

            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input!\n");
                while (getchar() != '\n')
                    ;
                return;
            }

            if (choice == 1)
                strcpy(students[i].result, "Excellent");

            else if (choice == 2)
                strcpy(students[i].result, "Good");

            else if (choice == 3)
                strcpy(students[i].result, "Fail");

            else
            {
                printf("\nInvalid result!\n");
                return;
            }

            saveData();

            printf("\nResult saved successfully!\n");
            break;
        }
    }

    if (found == 0)
    {
        printf("\nStudent not found!\n");
    }
}

// Display All Students

void displayStudents()
{
    int i;

    printf("\n\tSTUDENT RECORDS\n");

    if (count == 0)
    {
        printf("No student records found!\n");
        return;
    }

    printf("\n%-10s %-20s %-12s %-18s %-18s\n",
           "ID", "Name", "Fees", "Course", "Result");

    printf("-----------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        printf("%-10d %-20s %-12.2f %-18s %-18s\n",
               students[i].id,
               students[i].name,
               students[i].fees,
               students[i].course,
               students[i].result);
    }

    printf("-----------------------------------------------------------------------\n");
}

// Search Student

void searchStudent()
{
    int id, i, found = 0;

    printf("\n\tSEARCH STUDENT\n");

    printf("Enter Student ID: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            found = 1;

            printf("\nStudent Found!\n");

            printf("ID       : %d\n", students[i].id);
            printf("Name     : %s\n", students[i].name);
            printf("Fees     : %.2f\n", students[i].fees);
            printf("Course   : %s\n", students[i].course);
            printf("Result   : %s\n", students[i].result);

            break;
        }
    }

    if (found == 0)
    {
        printf("\nStudent not found!\n");
    }
}

// Edit Student Record

void editStudent()
{
    int id, i, found = 0;
    int choice;
    int c;

    printf("\n\tEDIT STUDENT RECORD\n");

    printf("Enter Student ID: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID!\n");
        while (getchar() != '\n')
            ;
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            found = 1;

            printf("\nStudent Found!\n");

            printf("ID       : %d\n", students[i].id);
            printf("Name     : %s\n", students[i].name);
            printf("Fees     : %.2f\n", students[i].fees);
            printf("Course   : %s\n", students[i].course);
            printf("Result   : %s\n", students[i].result);

            printf("\nWhat do you want to edit?\n");
            printf("1. Name\n");
            printf("2. Fees\n");
            printf("3. Course\n");
            printf("4. Result\n");

            printf("Enter your choice: ");

            if (scanf("%d", &choice) != 1)
            {
                printf("Invalid input!\n");
                while (getchar() != '\n')
                    ;
                return;
            }

            switch (choice)
            {
            case 1:
                printf("Enter New Name: ");
                scanf(" %49[^\n]", students[i].name);
                break;

            case 2:
                printf("Enter New Fees: ");

                if (scanf("%f", &students[i].fees) != 1)
                {
                    printf("Invalid fee input!\n");
                    while (getchar() != '\n')
                        ;
                    return;
                }

                if (students[i].fees < 0)
                {
                    printf("Invalid fee amount!\n");
                    return;
                }
                break;

            case 3:
                printf("\n1. DS\n");
                printf("2. AI\n");
                printf("3. ML\n");
                printf("4. Web\n");

                printf("Select New Course: ");

                if (scanf("%d", &choice) != 1)
                {
                    printf("Invalid input!\n");
                    while (getchar() != '\n')
                        ;
                    return;
                }

                if (choice == 1)
                    strcpy(students[i].course, "DS");

                else if (choice == 2)
                    strcpy(students[i].course, "AI");

                else if (choice == 3)
                    strcpy(students[i].course, "ML");

                else if (choice == 4)
                    strcpy(students[i].course, "Web");

                else
                {
                    printf("Invalid course!\n");
                    return;
                }
                break;

            case 4:
                printf("\n1. Excellent\n");
                printf("2. Good\n");
                printf("3. Fail\n");

                printf("Enter New Result: ");

                if (scanf("%d", &choice) != 1)
                {
                    printf("Invalid input!\n");
                    while (getchar() != '\n')
                        ;
                    return;
                }

                if (choice == 1)
                    strcpy(students[i].result, "Excellent");

                else if (choice == 2)
                    strcpy(students[i].result, "Good");

                else if (choice == 3)
                    strcpy(students[i].result, "Fail");

                else
                {
                    printf("Invalid result!\n");
                    return;
                }
                break;

            default:
                printf("\nInvalid choice!\n");
                return;
            }

            saveData();

            printf("\nStudent record updated successfully!\n");

            break;
        }
    }

    if (found == 0)
    {
        printf("\nStudent not found!\n");
    }
}
