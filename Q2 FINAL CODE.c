#include <stdio.h>
#include <string.h>

// setting up limits for how many subjects and students we can store
#define maxSubjects 5
#define maxStudents 20

// structure to store all info about one student
typedef struct {
    char firstName[20];       // first name of the student
    char lastName[20];        // last name of the student
    int studentID;            // unique student ID
    float subjectMarks[maxSubjects]; // marks for each subject
    float aggregateMarks;     // average of all subjects
    char grade[3];            // grade based on average marks
} Student;

// function prototypes
void enrol(Student students[], int *count);
void searchUpdate(Student students[], int count);
void topStudents(Student students[], int count);
char gradeAssign(float mark);

int main() {
    Student students[maxStudents]; // array to hold student data
    int count = 0;                 // keeps track of how many students are enrolled
    int choice = 0;                // user menu choice

    // menu keeps showing until user chooses to exit
    while (choice != 4) {
        printf("\n==== Student Record System ====\n");
        printf("1. Enrol Students\n");
        printf("2. Search or Update Student\n");
        printf("3. View Top Students\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // checking what user selected
        if (choice == 1) {
            enrol(students, &count);   // calls enrol function
        } 
        else if (choice == 2) {
            searchUpdate(students, count); // calls search and update function
        } 
        else if (choice == 3) {
            topStudents(students, count);  // calls top students function
        } 
        else if (choice == 4) {
            printf("Exiting...\n");        // exits the program
        } 
        else {
            printf("Invalid choice, please try again.\n"); // wrong option
        }
    }

    return 0;
}

// this function adds new students and stores their details
void enrol(Student students[], int *count) {
    int n;
    printf("Enter number of students to enrol: ");
    scanf("%d", &n); // user enters how many students they want to add

    // loop for each student being added
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d\n", *count + 1);

        // asking for basic info
        printf("First name: ");
        scanf("%s", students[*count].firstName);
        printf("Last name: ");
        scanf("%s", students[*count].lastName);
        printf("Student ID: ");
        scanf("%d", &students[*count].studentID);

        // now asking for marks for all subjects
        float total = 0;
        for (int j = 0; j < maxSubjects; j++) {
            printf("Mark for Subject %d: ", j + 1);
            scanf("%f", &students[*count].subjectMarks[j]);
            total += students[*count].subjectMarks[j]; // add to total for average later
        }

        // calculating average marks for this student
        students[*count].aggregateMarks = total / maxSubjects;

        // assigning grade based on the average marks
        strcpy(students[*count].grade,
               (students[*count].aggregateMarks >= 80) ? "A" :
               (students[*count].aggregateMarks >= 70) ? "B" :
               (students[*count].aggregateMarks >= 60) ? "C" :
               (students[*count].aggregateMarks >= 50) ? "D" : "F");

        (*count)++; // increasing total number of students
    }
}

// this function searches for a student and can also update their marks
void searchUpdate(Student students[], int count) {
    if (count == 0) { // if no students are enrolled yet
        printf("No students found.\n");
        return;
    }

    char option[10];
    printf("Search by ID or LastName: ");
    scanf("%s", option);

    int found = -1; // keeps track of found student position (-1 means not found)

    // if user wants to search using student ID
    if (strcasecmp(option, "ID") == 0) {
        int id;
        printf("Enter Student ID: ");
        scanf("%d", &id);
        for (int i = 0; i < count; i++) {
            if (students[i].studentID == id) {
                found = i; // store index where found
                break;
            }
        }
    } 
    // if user searches by last name
    else {
        char lname[20];
        printf("Enter Last Name: ");
        scanf("%s", lname);
        for (int i = 0; i < count; i++) {
            if (strcasecmp(students[i].lastName, lname) == 0) {
                found = i;
                break;
            }
        }
    }

    // if not found
    if (found == -1) {
        printf("Student not found.\n");
        return;
    }

    // display found student details
    printf("\nStudent found:\n");
    printf("%s %s | ID:%d | Agg:%.2f | Grade:%s\n",
           students[found].firstName, students[found].lastName,
           students[found].studentID, students[found].aggregateMarks,
           students[found].grade);

    // ask if user wants to update marks
    char update;
    printf("Update marks? (y/n): ");
    scanf(" %c", &update);

    // if user says yes, we ask for new marks
    if (update == 'y' || update == 'Y') {
        float total = 0;
        for (int j = 0; j < maxSubjects; j++) {
            printf("New mark for Subject %d: ", j + 1);
            scanf("%f", &students[found].subjectMarks[j]);
            total += students[found].subjectMarks[j];
        }

        // recalculate average and grade
        students[found].aggregateMarks = total / maxSubjects;
        strcpy(students[found].grade,
               (students[found].aggregateMarks >= 80) ? "A" :
               (students[found].aggregateMarks >= 70) ? "B" :
               (students[found].aggregateMarks >= 60) ? "C" :
               (students[found].aggregateMarks >= 50) ? "D" : "F");
    }
}

// this function shows students who got the highest average marks
void topStudents(Student students[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }

    // first we find what the highest mark is
    float top = students[0].aggregateMarks;
    for (int i = 1; i < count; i++) {
        if (students[i].aggregateMarks > top)
            top = students[i].aggregateMarks;
    }

    // now we print everyone who got that top average
    printf("\nTop Students:\n");
    for (int i = 0; i < count; i++) {
        if (students[i].aggregateMarks == top)
            printf("%s %s | ID:%d | Agg:%.2f | Grade:%s\n",
                   students[i].firstName, students[i].lastName,
                   students[i].studentID, students[i].aggregateMarks,
                   students[i].grade);
    }
}

// this function returns a grade letter depending on the mark given
char gradeAssign(float mark) {
    if (mark >= 80)
        return 'A';
    else if (mark >= 70)
        return 'B';
    else if (mark >= 60)
        return 'C';
    else if (mark >= 50)
        return 'D';
    else
        return 'F';
}
