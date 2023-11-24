#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Global parameters
#define MAX_STRING_LENGTH 100
#define MAX_STUDENTS 100

// ANSI color codes
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"

struct Admin {
    char username[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
};

struct Student {
    char name[MAX_STRING_LENGTH];
    int enrollment_number;
    char batch[MAX_STRING_LENGTH];
    char course[MAX_STRING_LENGTH];
    char address[MAX_STRING_LENGTH];
    char phone_number[MAX_STRING_LENGTH];
    char password[MAX_STRING_LENGTH];
    float marks[5][3];
    int attendance[30];
};

struct Admin adminCredentials = {"admin", "admin"};  // Example admin credentials

struct Student students[MAX_STUDENTS];
int numStudents = 0;  // Track the number of students in the array

int findStudentIndexByEnrollment(int enrollmentNumber);
// Administrative functions
int adminLogin();
void printAdminMenu();
void addStudent();
void deleteStudent();
void editStudent();
void deleteAllStudents();
void showAllStudents();
void findStudent();
void giveMarks();
void markAttendanceBatch(const char *batch);

// Student functions
int studentLogin();
void studentMenu(int enrollmentNumber);
void displayStudentInformation(int enrollmentNumber);
void printStudentMenu();
void performanceReport(int enrollmentNumber);
void calculateCGPA(int enrollmentNumber);
float calculateAttendancePercentage(const int attendance[]);
void displayAttendanceDetails(int enrollmentNumber);

// Designing functions
void art();
void art_2();
void art_3();

// Function to save student data to a file
void saveStudentsToFile() 
{
    FILE *file = fopen("database.txt", "w");
    if (file == NULL) 
    {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the number of students to the file
    fprintf(file, "%d\n", numStudents);

    // Write each student's data to the file
    for (int i = 0; i < numStudents; ++i) 
    {
        fprintf(file, "%d %s %s %s %s %s %s", students[i].enrollment_number, students[i].name, students[i].batch,
                students[i].course, students[i].address, students[i].phone_number, students[i].password);

        // Write marks
        for (int subject = 0; subject < 5; ++subject) 
        {
            for (int examSet = 0; examSet < 3; ++examSet) 
            {
                fprintf(file, " %.2f", students[i].marks[subject][examSet]);
            }
        }

        // Write attendance
        for (int day = 0; day < 30; ++day) 
        {
            fprintf(file, " %d", students[i].attendance[day]);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to load student data from a file
void loadStudentsFromFile() 
{
    FILE *file = fopen("database.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Read the number of students from the file
    fscanf(file, "%d", &numStudents);

    // Read each student's data from the file
    for (int i = 0; i < numStudents; ++i) 
    {
        fscanf(file, "%d %s %s %s %s %s %s", &students[i].enrollment_number, students[i].name, students[i].batch,
               students[i].course, students[i].address, students[i].phone_number, students[i].password);

        // Read marks
        for (int subject = 0; subject < 5; ++subject) 
        {
            for (int examSet = 0; examSet < 3; ++examSet) 
            {
                fscanf(file, " %f", &students[i].marks[subject][examSet]);
            }
        }

        // Read attendance
        for (int day = 0; day < 30; ++day) 
        {
            fscanf(file, " %d", &students[i].attendance[day]);
        }
    }

    fclose(file);
}

int main() 
{
    system("cls");
    loadStudentsFromFile();
    int userType;
    art();
    printf("======================================================================\n");
    printf("                             Login Page                               \n");
    printf("======================================================================\n");
    printf("[1] Admin Login\n");
    printf("[2] Student Login\n");
    printf("======================================================================\n");
    printf(YELLOW"Enter your choice: "RESET);
    scanf("%d", &userType);

    if (userType == 1) 
    {
        if (adminLogin()) 
        {
            int choice;
            do {
                art_2();
                printAdminMenu();
                printf(YELLOW"Enter your choice: "RESET);
                scanf("%d", &choice);

                switch (choice) 
                {
                    case 1:
                        addStudent();
                        break;
                    case 2:
                        deleteStudent();
                        break;
                    case 3:
                        editStudent();
                        break;
                    case 4:
                        deleteAllStudents();
                        break;
                    case 5:
                        showAllStudents();
                        break;
                    case 6:
                        findStudent();
                        break;
                    case 7:
                        giveMarks();
                        break;
                    case 8:
                        printf("Enter the batch name: ");
                        char batchName[MAX_STRING_LENGTH];
                        scanf("%s", batchName);
                        markAttendanceBatch(batchName);
                        break;
                    case 9:
                        printf(RED"Exiting the program."RESET);
                        printf("\n");
                        break;
                    default:
                        printf(RED"Please try again."RESET);
                        printf("\n");
                }
            } 
            // Program termination
            while (choice != 9); // Do statement till while condition is met!!
        } 
        else 
        {
            printf(RED"Incorrect login credentials. Please try again!!"RESET);
            printf("\n");
        }
    } 
    else if (userType == 2) 
    {
        int enrollmentNumber = studentLogin();
        studentMenu(enrollmentNumber);
    }
    saveStudentsToFile();
    return 0;
}

// Function to handle the student menu
void studentMenu(int enrollmentNumber) 
{
    int choice;
    do 
    {
        printStudentMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                displayStudentInformation(enrollmentNumber); //Working
                break;
            case 2:
                performanceReport(enrollmentNumber); //Working 
                break;
            case 3:
                displayAttendanceDetails(enrollmentNumber);
                break;
            case 4:
                printf(RED"Exiting the program\n"RESET);
                break;
            default:
                printf(RED"Invalid choice. Please try again.\n"RESET);
        }
    } 
    while (choice != 4);
}

// Function for printing Admin Menu
void printAdminMenu() 
{
    printf("==========================================\n");
    printf("                Admin Menu                \n");
    printf("==========================================\n");
    printf("[1] Add Student\n");
    printf("[2] Delete Student\n");
    printf("[3] Edit Student\n");
    printf("[4] Delete All Students\n");
    printf("[5] Show All Students\n");
    printf("[6] Find a Student\n");
    printf("[7] Evaluation\n");
    printf("[8] Attendance Marking\n");
    printf("[9] Exit\n");
    printf("==========================================\n");
}

// Function for printing
void printStudentMenu() 
{
    art_3();
    printf("==========================================\n");
    printf("                Student Menu              \n");
    printf("==========================================\n");
    printf("[1] View Profile\n");
    printf("[2] View Performance Report\n");
    printf("[3] View Attendance Percentage\n");
    printf("[4] Exit\n");
    printf("==========================================\n");
}

// Function for admin login
// Checking against constant credentials
int adminLogin() 
{
    system("cls");
    struct Admin adminLogin;
    initial:
    printf("============================================\n");
    printf("               Admin Login Page             \n");
    printf("============================================\n");
    printf("\n");
    printf(YELLOW"Enter Administrative Login Credentials:\n"RESET);
    printf("\n");
    printf("Username: ");
    scanf("%s", adminLogin.username);
    printf("Password: ");
    scanf("%s", adminLogin.password);

    // Check against admin credentials
    if (strcmp(adminLogin.username, adminCredentials.username) == 0 &&
        strcmp(adminLogin.password, adminCredentials.password) == 0) 
    {
        system("cls");
        printf(GREEN "Access Granted!!" RESET);
        printf("\n");
        return 1;
    } 
    else 
    {
        system("cls");
        printf(RED "Invalid username or password. Please try again\n" RESET);
        goto initial;
    }
}

// Function for Student Login
// Checking their passwords against their enrollment number!!
int studentLogin() 
{
    system("cls");
    struct Student studentLogin;
    initial2:
    printf("============================================\n");
    printf("              Student Login Page            \n");
    printf("============================================\n");
    printf("\n");
    printf("Enter Student Login Credentials:\n");
    printf("\n");
    printf("Enrollment Number: ");
    scanf("%d", &studentLogin.enrollment_number);
    printf("Password: ");
    scanf("%s", studentLogin.password);

    // Checking against student records
    for (int i = 0; i < numStudents; ++i) 
    {
        if (studentLogin.enrollment_number == students[i].enrollment_number &&
            strcmp(studentLogin.password, students[i].password) == 0) 
        {
            system("cls");
            printf(GREEN "Access Granted!!\n" RESET);
            return studentLogin.enrollment_number;
        }
    }
    system("cls");
    printf(RED "Invalid username or password. Please try again\n" RESET);
    goto initial2;
}

// Function to find the index of a student based on enrollment number
int findStudentIndexByEnrollment(int enrollmentNumber) 
{
    for (int i = 0; i < numStudents; ++i) 
    {
        if (students[i].enrollment_number == enrollmentNumber) 
        {
            return i;  // Found the student, return the index
        }
    }
    return -1;  // Student not found
}

// Function to add a new student
void addStudent() 
{
    system("cls");
    struct Student newStudent;
    printf("==========================================\n");
    printf("         New Student Registration         \n");
    printf("==========================================\n"); 
    printf("Enter Student Details: \n\n");

    printf("Enrollment Number: ");
    scanf("%d", &newStudent.enrollment_number);

    // Checking if the enrollment number already exists from the file
    for (int i = 0; i < numStudents; ++i) 
    {
        if (newStudent.enrollment_number == students[i].enrollment_number) 
        {
            system("cls");
            printf(YELLOW "Enrollment number already exists.\n" RESET);
            return;
        }
    }

    printf("Name: ");
    scanf("%s", newStudent.name);
    printf("Batch: ");
    scanf("%s", newStudent.batch);
    printf("Course: ");
    scanf("%s", newStudent.course);
    printf("Address: ");
    scanf("%s", newStudent.address);
    printf("Phone Number: ");
    scanf("%s", newStudent.phone_number);
    printf("Password: ");
    scanf("%s", newStudent.password);

    // Initialize marks and attendance to default values
    memset(newStudent.marks, 0, sizeof(newStudent.marks));
    memset(newStudent.attendance, 0, sizeof(newStudent.attendance));

    // Add the new student to the array
    students[numStudents++] = newStudent;
    system("cls");
    printf(GREEN "Registration complete!!\n" RESET);
}

// Function for deleting student based on enrollment number
void deleteStudent() 
{
    system("cls");
    int enrollmentToDelete;
    printf("==========================================\n");
    printf("           Student Record Deletion        \n");
    printf("==========================================\n\n"); 
    printf(YELLOW "Enter the Enrollment Number to delete the student: " RESET);
    scanf("%d", &enrollmentToDelete);

    int foundIndex = -1;

    // Search for the student with the given enrollment number
    for (int i = 0; i < numStudents; ++i) 
    {
        if (students[i].enrollment_number == enrollmentToDelete) 
        {
            foundIndex = i;
            break;
        }
    }

    // If the student is found, delete them
    if (foundIndex != -1) 
    {
        // Move all students after the found student one position up in the array
        for (int i = foundIndex; i < numStudents - 1; ++i) 
        {
            students[i] = students[i + 1];
        }

        // Decrement the number of students
        numStudents--;

        system("cls");
        printf(GREEN "Student with Enrollment Number %d deleted successfully.\n" RESET, enrollmentToDelete);
    } 
    else 
    {
        system("cls");
        printf(RED "Student with Enrollment Number %d not found.\n" RESET, enrollmentToDelete);
    }
}

// Function for editing student infos
void editStudent() 
{
    system("cls");
    int enrollmentToEdit;
    printf("==========================================\n");
    printf("             Editing Student              \n");
    printf("==========================================\n\n"); 
    printf(YELLOW "Enter the Enrollment Number to edit the student: " RESET);
    scanf("%d", &enrollmentToEdit);

    int foundIndex = -1;

    // Search for the student with the given enrollment number
    for (int i = 0; i < numStudents; ++i) 
    {
        if (students[i].enrollment_number == enrollmentToEdit) 
        {
            foundIndex = i;
            break;
        }
    }

    // If the student is found, allow editing
    if (foundIndex != -1) {
        struct Student *studentToEdit = &students[foundIndex];

        printf("Editing information for Student with Enrollment Number %d:\n", enrollmentToEdit);
        printf("[1] Name: %s\n", studentToEdit->name);
        printf("[2] Batch: %s\n", studentToEdit->batch);
        printf("[3] Course: %s\n", studentToEdit->course);
        printf("[4] Address: %s\n", studentToEdit->address);
        printf("[5] Phone Number: %s\n", studentToEdit->phone_number);
        printf("[6] Save Changes: \n");

        // Prompt for new values for selected options
        int fieldChoice,terminate=0;
        while (terminate==0) {
            printf("Option : ");
            scanf("%d", &fieldChoice);

            if (fieldChoice == 6) 
            {
                break;
            } 
            else if (fieldChoice >= 1 && fieldChoice <= 6) {
                // Prompt for new value based on the selected field
                char newValue[MAX_STRING_LENGTH];
                printf("Enter new value: ");
                scanf("%s", newValue);

                // Update the selected field
                switch (fieldChoice) 
                {
                    case 1:
                        strcpy(studentToEdit->name, newValue);
                        break;
                    case 2:
                        strcpy(studentToEdit->batch, newValue);
                        break;
                    case 3:
                        strcpy(studentToEdit->course, newValue);
                        break;
                    case 4:
                        strcpy(studentToEdit->address, newValue);
                        break;
                    case 5:
                        strcpy(studentToEdit->phone_number, newValue);
                        break;
                    case 6:
                        terminate=1;
                        break;
                }
            } 
            else 
            {
                printf(RED "Invalid choice. Please try again!!.\n" RESET);
            }
        }
        system("cls");
        printf(GREEN "Information updated successfully.\n" RESET);
    } 
    else 
    {   
        system("cls");
        printf(RED "Student with Enrollment Number %d not found.\n" RESET, enrollmentToEdit);
    }
}

// Function for deleting all student records
void deleteAllStudents() 
{   
    char confirmation;
    system("cls");
    printf(YELLOW "Are you sure you want to delete all students? (y/n): " RESET);
    scanf(" %c", &confirmation);

    if (confirmation == 'y') 
    {
        // Display a summary of deleted students
        printf(RED "Deleting all students...\n" RESET);
        for (int i = 0; i < numStudents; ++i) 
        {
            printf("Deleted student %s (Enrollment Number: %d)\n", students[i].name, students[i].enrollment_number);
        }
        // Reset the number of students to 0
        numStudents = 0;
        printf(GREEN "All students deleted successfully.\n" RESET);
    }
    else 
    {
        system("cls");
        printf(RED "Operation canceled. No students were deleted.\n" RESET);
    }
}

// Function for showing all students
void showAllStudents() 
{
    system("cls");
    printf("================================================\n");
    printf("              List of All Students:             \n");
    printf("================================================\n");
    for (int i = 0; i < numStudents; ++i) 
    {
        printf("------------------------------------------------\n");
        printf("                   Student %d                   \n", i + 1);
        printf("------------------------------------------------\n");
        printf(GREEN "Enrollment Number: %d\n", students[i].enrollment_number);
        printf("Name: %s\n", students[i].name);
        printf("Batch: %s\n", students[i].batch);
        printf("Course: %s\n", students[i].course);
        printf("Address: %s\n", students[i].address);
        printf("Phone Number: %s\n" RESET, students[i].phone_number);
        printf("\n");
    }
}

// Function for giving marks to a student
void giveMarks() 
{
    system("cls");
    // Search for the student with the given enrollment number
    int enrollmentNumber;
    printf("==========================================\n");
    printf("             Student Evaluation           \n");
    printf("==========================================\n\n");
    printf(YELLOW "Enter the Enrollment Number to evaluate the student: " RESET);
    scanf("%d",&enrollmentNumber);
    int foundIndex = findStudentIndexByEnrollment(enrollmentNumber);

    // If the student is found, enter marks for each subject in the selected exam
    if (foundIndex != -1) 
    {
        struct Student *student = &students[foundIndex];

        int examSet;
        printf(YELLOW "Enter the Exam (1 : T1, 2 : T2(Mid-sem), 3 : T3(End-sem)): " RESET);
        scanf("%d", &examSet);

        // Validation T1 T2 and T3
        if (examSet < 1 || examSet > 3) 
        {
            printf(RED "Invalid exam number.\n" RESET);
            return;
        }

        // Prompt for marks for each subject
        float marks;
        printf("Physics : ");
        scanf("%f", &marks);
        student->marks[0][examSet - 1] = marks;
        printf("Maths : ");
        scanf("%f", &marks);
        student->marks[1][examSet - 1] = marks;
        printf("SDF : ");
        scanf("%f", &marks);
        student->marks[2][examSet - 1] = marks;
        printf("Workshop : ");
        scanf("%f", &marks);
        student->marks[3][examSet - 1] = marks;
        printf("English : ");  
        scanf("%f", &marks);     
        student->marks[4][examSet - 1] = marks;
        system("cls");
        printf(GREEN "Marks entered successfully for T%d exam.\n" RESET, examSet);
    } 
    else 
    {   
        system("cls");
        printf(RED "Student with Enrollment Number %d not found.\n" RESET, enrollmentNumber);
    }
}

// Show every details of the student based on enrollment number
void findStudent() 
{
    system("cls");
    int enrollmentToDisplay;
    printf(YELLOW "Enter the Enrollment Number: " RESET);
    scanf("%d", &enrollmentToDisplay);

    int foundIndex = -1;

    // Search for the student with the given enrollment number
    for (int i = 0; i < numStudents; ++i) 
    {
        if (students[i].enrollment_number == enrollmentToDisplay) 
        {
            foundIndex = i;
            break;
        }
    }

    // If the student is found, display their details
    if (foundIndex != -1) 
    {
        struct Student *studentToDisplay = &students[foundIndex];
        printf("==========================================\n");
        printf("               STUDENT DETAILS            \n");
        printf("==========================================\n");
        printf("Enrollment Number : "GREEN"%d\n"RESET, enrollmentToDisplay);
        printf("Name : "GREEN"%s\n"RESET, studentToDisplay->name);
        printf("Batch : "GREEN"%s\n"RESET, studentToDisplay->batch);
        printf("Course : "GREEN"%s\n"RESET, studentToDisplay->course);
        printf("Address : "GREEN"%s\n"RESET, studentToDisplay->address);
        printf("Phone Number : "GREEN"%s\n"RESET, studentToDisplay->phone_number);
        printf("==========================================\n\n");

        // Displaying marks
        for(int i=0;i<3;i++)
        {
            printf("==========================================\n");
            printf("                 T%d Report               \n",i+1);
            printf("==========================================\n");
            printf("Physics : "GREEN"%.2f\n"RESET,studentToDisplay->marks[0][i]);
            printf("Maths : "GREEN"%.2f\n"RESET,studentToDisplay->marks[1][i]);
            printf("SDF : "GREEN"%.2f\n"RESET,studentToDisplay->marks[2][i]);
            printf("Workshop : "GREEN"%.2f\n"RESET,studentToDisplay->marks[3][i]);
            printf("English : "GREEN"%.2f\n"RESET,studentToDisplay->marks[4][i]);   
        }
        printf("=============================================\n");
    } 
    else 
    {
        system("cls");
        printf(RED "Student with Enrollment Number %d not found.\n" RESET, enrollmentToDisplay);
    }
}

// Function to display student information
void displayStudentInformation(int enrollmentNumber) 
{
    system("cls");
    // Find the index of the student with the given enrollment number
    int studentIndex = findStudentIndexByEnrollment(enrollmentNumber);

    // Check if the student is found
    if (studentIndex != -1) 
    {
        printf("=============================================\n");
        printf(GREEN "Name: %s\n", students[studentIndex].name);
        printf("Batch: %s\n", students[studentIndex].batch);
        printf("Course: %s\n", students[studentIndex].course);
        printf("Phone Number: %s\n", students[studentIndex].phone_number);
        printf("Address: %s\n" RESET, students[studentIndex].address);
        printf("=============================================\n");
    }
}

// Function for displaying Student performance report
void performanceReport(int enrollmentNumber)
{
    system("cls");
    int index = findStudentIndexByEnrollment(enrollmentNumber);
    struct Student *studentToDisplay = &students[index];
    for(int i=0;i<3;i++)
    {
        printf("================================================\n");
        printf("                    T%d Report                  \n",i+1);
        printf("================================================\n");
        printf(GREEN "Physics : %.2f\n",studentToDisplay->marks[0][i]);
        printf("Maths : %.2f\n",studentToDisplay->marks[1][i]);
        printf("SDF : %.2f\n",studentToDisplay->marks[2][i]);
        printf("Workshop : %.2f\n",studentToDisplay->marks[3][i]);
        printf("English : %.2f\n" RESET,studentToDisplay->marks[4][i]);
    }
    printf("================================================\n");
    calculateCGPA(enrollmentNumber);
    printf("================================================\n");
}

// Function for Calculating CGPA
void calculateCGPA(int enrollmentNumber) 
{
    int index = findStudentIndexByEnrollment(enrollmentNumber);
    struct Student *student = &students[index];

    // Grade points for each subject based on obtained marks
    float gradePoints[5];
    for (int subject = 0; subject < 5; ++subject) 
    {
        float totalMarks = 0.0;
        for (int examSet = 0; examSet < 3; ++examSet) 
        {
            totalMarks += student->marks[subject][examSet];
        }

        // Calculate average marks for the subject
        float averageMarks = totalMarks / 3;

        // Convert average marks to grade points
        if (averageMarks >= 90) 
        {
            gradePoints[subject] = 10.0;
        } 
        else if (averageMarks >= 80) 
        {
            gradePoints[subject] = 9.0;
        } 
        else if (averageMarks >= 70) 
        {
            gradePoints[subject] = 8.0;
        } 
        else if (averageMarks >= 60) 
        {
            gradePoints[subject] = 7.0;
        } 
        else if (averageMarks >= 50) 
        {
            gradePoints[subject] = 6.0;
        } 
        else 
        {
            gradePoints[subject] = 0.0;  // Fail condition
        }
    }

    // Calculating CGPA part
    float totalCreditPoints = 0.0;
    float totalCredits = 0.0;
    for (int subject = 0; subject < 5; ++subject) 
    {
        totalCreditPoints += gradePoints[subject] * 4;  // Every subject has credit 4
        totalCredits += 4;
    }

    float cgpa = totalCreditPoints / totalCredits;

    printf(GREEN"CGPA: %.2f\n"RESET, cgpa);
}

void markAttendanceBatch(const char *batch) 
{
    system("cls");
    printf("==========================================\n");
    printf("       Attendance Marking for Batch       \n");
    printf("==========================================\n\n");
    
    //taking time datatype from the time.h library
    time_t t;
    time(&t);
    //setting the current time
    struct tm *currentTime = localtime(&t);

    // setting current DD/MM/YYYY pointing to tm members 
    int currentDay = currentTime->tm_mday;
    int currentMonth = currentTime->tm_mon + 1;  // Month is 0-indexed
    int currentYear = currentTime->tm_year + 1900;  // Years since 1900

    printf("Date: %02d/%02d/%04d\n", currentDay, currentMonth, currentYear);
    printf("Batch: %s\n\n", batch);

    for (int i = 0; i < numStudents; ++i) 
    {
        if (strcmp(students[i].batch, batch) == 0) 
        {
            printf("==========================================\n");
            printf(GREEN"        Student %d - %s               \n"RESET, i + 1, students[i].name);
            printf("==========================================\n");
            printf("(1: Present, 0: Absent): ");

            int isPresent;
            scanf("%d", &isPresent);

            // Validate the input
            if (isPresent == 0 || isPresent == 1) 
            {
                // Mark the attendance
                students[i].attendance[currentDay - 1] = isPresent;
                printf(GREEN"Attendance marked successfully.\n"RESET);
            } 
            else 
            {
                printf(RED"Invalid input. Please enter 1 for present or 0 for absent.\n"RESET);
                --i;  // Repeating the loop for the same student
            }
        }
    }
    system("cls");
    printf(GREEN"Attendance marking for batch %s completed.\n"RESET, batch);
}

// Function for calculating attendance percentage
float calculateAttendancePercentage(const int attendance[]) 
{
    int totalDays = 30;  // Assuming attendance is marked for 30 days
    int presentDays = 0;

    for (int i = 0; i < totalDays; ++i) 
    {
        if (attendance[i] == 1) 
        {
            presentDays++;
        }
    }

    return (float)presentDays / totalDays * 100;
}

// Function for displaying attendance details
void displayAttendanceDetails(int enrollmentNumber) 
{
    system("cls");
    printf("==========================================\n");
    printf("          Attendance Details              \n");
    printf("==========================================\n");

    int index = findStudentIndexByEnrollment(enrollmentNumber);
    struct Student *student = &students[index];

    // Display attendance for each day
    for (int i = 0; i < 30; ++i) 
    {
        printf("Day %d: ", i + 1);
        if (student->attendance[i] == 1) 
        {
            printf(GREEN "Present\n" RESET);
        } 
        else 
        {
            printf(RED "Absent\n" RESET);
        }
    }

    // Calculate and display attendance percentage
    float attendancePercentage = calculateAttendancePercentage(student->attendance);
    printf("\nAttendance Percentage: %.2f%%\n", attendancePercentage);
    printf("==========================================\n");
}

void art()
{
    printf(" ____  _             _            _                           \n");
    printf("/ ___|| |_ _   _  __| | ___ _ __ | |_                         \n");
    printf("\\___ \\| __| | | |/ _` |/ _ \\ '_ \\| __|                        \n");
    printf(" ___) | |_| |_| | (_| |  __/ | | | |_                         \n");
    printf("|____/_\\__|\\__,_|\\__,_|\\___|_| |_|\\__|                    _   \n");
    printf("|  \\/  | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_  \n");
    printf("| |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __| \n");
    printf("| |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_  \n");
    printf("|_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__| \n");
    printf(" ___ _   _ ___| |_ ___ _ _|___/   | |__  _   _                 \n");
    printf("/ __| | | / __| __/ _ \\ '_ ` _ \\  | '_ \\| | | | SAMIK SARDAR \n");
    printf("\\__ \\ |_| \\__ \\ ||  __/ | | | | | | |_) | |_| | VAIBHAV KHANDELWAL \n");
    printf("|___/\\__, |___/\\__\\___|_| |_| |_| |_.__/ \\__, | OJASWI BANSAL \n");
    printf("     |___/                               |___/                \n");
    printf("\n");
}

void art_2()
{
printf("__        __   _                           \n");                      
printf("\\ \\      / /__| | ___ ___  _ __ ___   ___  \n"); 
printf(" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ \n");
printf("  \\ V  V /  __/ | (_| (_) | | | | | |  __/ \n");
printf("   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___| \n");
printf("       / \\   __| |_ __ ___ (_)_ __         \n");
printf("      / _ \\ / _` | '_ ` _ \\| | '_ \\        \n");
printf("     / ___ \\ (_| | | | | | | | | | |       \n");
printf("    /_/   \\_\\__,_|_| |_| |_|_|_| |_|       \n");     
printf("\n");
}

void art_3()
{
    printf("__        __   _                          \n");
    printf("\\ \\      / /__| | ___ ___  _ __ ___   ___ \n"); 
    printf(" \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ \n");
    printf("  \\ V  V /  __/ | (_| (_) | | | | | |  __/\n");
    printf(" __\\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|\n");
    printf("/ ___|| |_ _   _  __| | ___ _ __ | |_     \n");
    printf("\\___ \\| __| | | |/ _` |/ _ \\ '_ \\| __|    \n");
    printf(" ___) | |_| |_| | (_| |  __/ | | | |_     \n");
    printf("|____/ \\__|\\__,_|\\__,_|\\___|_| |_|\\__|    \n");
    printf("\n");
    
}