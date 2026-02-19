#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "student.txt"

struct Student {
    int Rollno;
    char Name[100];
    char Course[50];
    char Contact[20];
    char City[50];
    char State[50];
    char Email[100];
    int Sem;
    int Marks[5];
    char College_name[50];
    int Total;
    float Percentage;
    char Grade[40];
};

// Function Prototypes
int Menu();
void calculate(struct Student *s);
void AddStudent();
void DisplayAllStudents();
void SearchByRollNo();
void DeleteStudent();
void UpdateStudent();
void DisplaySortedStudents();
void EditStudentDetails(struct Student *s);
void PrintMarksheet();

// Comparator functions for sorting
int cmpByRoll(const void *a, const void *b) {
    return ((struct Student*)a)->Rollno - ((struct Student*)b)->Rollno;
}

int cmpByPercentage(const void *a, const void *b) {
    float pa = ((struct Student*)a)->Percentage;
    float pb = ((struct Student*)b)->Percentage;
    return (pa < pb) ? 1 : (pa > pb) ? -1 : 0;
}

int cmpByName(const void *a, const void *b) {
    return strcmp(((struct Student*)a)->Name, ((struct Student*)b)->Name);
}

// Main menu-driven function
int main() {
    int choice;
    do {
        choice = Menu();
        switch (choice) {
            case 1: DisplayAllStudents(); break;
            case 2: SearchByRollNo(); break;
            case 3: AddStudent(); break;
            case 4: UpdateStudent(); break;
            case 5: DeleteStudent(); break;
            case 6: PrintMarksheet(); break;
            case 7: DisplaySortedStudents(); break;
            case 8: exit(0);
            default: printf("\nInvalid Choice! Please try again.\n");
        }
    } while (choice != 8);
    return 0;
}

// Menu display function
int Menu() {
    int ch;
    printf("\n========== Student Record Menu ==========\n");
    printf("1. Display All Students\n");
    printf("2. Search by Roll No\n");
    printf("3. Add Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Print Student Marksheet\n");
    printf("7. Display Sorted Students\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);
    return ch;
}

// Calculation of total, percentage, and grade
void calculate(struct Student *s) {
    s->Total = 0;
    for (int i = 0; i < 5; i++) {
        s->Total += s->Marks[i];
    }
    s->Percentage = s->Total / 5.0f;

    if (s->Percentage >= 80)
        strcpy(s->Grade, "Distinction");
    else if (s->Percentage >= 60)
        strcpy(s->Grade, "First Class");
    else if (s->Percentage >= 50)
        strcpy(s->Grade, "Second Class");
    else if (s->Percentage >= 35)
        strcpy(s->Grade, "Pass");
    else
        strcpy(s->Grade, "Fail");
}

// Centralized input function to fill/edit a student record
void EditStudentDetails(struct Student *s) {
    getchar(); // Clear newline buffer

    printf("Enter Name: ");
    fgets(s->Name, sizeof(s->Name), stdin);
    s->Name[strcspn(s->Name, "\n")] = 0;

    printf("Enter Course: ");
    fgets(s->Course, sizeof(s->Course), stdin);
    s->Course[strcspn(s->Course, "\n")] = 0;

    printf("Enter Contact: ");
    fgets(s->Contact, sizeof(s->Contact), stdin);
    s->Contact[strcspn(s->Contact, "\n")] = 0;

    printf("Enter City: ");
    fgets(s->City, sizeof(s->City), stdin);
    s->City[strcspn(s->City, "\n")] = 0;

    printf("Enter State: ");
    fgets(s->State, sizeof(s->State), stdin);
    s->State[strcspn(s->State, "\n")] = 0;

    printf("Enter Email: ");
    fgets(s->Email, sizeof(s->Email), stdin);
    s->Email[strcspn(s->Email, "\n")] = 0;

    printf("Enter College Name: ");
    fgets(s->College_name, sizeof(s->College_name), stdin);
    s->College_name[strcspn(s->College_name, "\n")] = 0;

    printf("Enter Semester: ");
    scanf("%d", &s->Sem);

    printf("Enter 5 Subject Marks:\n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%d", &s->Marks[i]);
    }

    calculate(s);
}

// Add a new student record
void AddStudent() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "a");
    if (fp == NULL) {
        perror("Unable to open file");
        return;
    }

    printf("Enter Roll No: ");
    scanf("%d", &s.Rollno);

    EditStudentDetails(&s);

    fprintf(fp, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" %d %d %d %d %d %d \"%s\" %d %.2f \"%s\"\n",
            s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
            s.Sem,
            s.Marks[0], s.Marks[1], s.Marks[2], s.Marks[3], s.Marks[4],
            s.College_name, s.Total, s.Percentage, s.Grade);

    fclose(fp);
    printf("\nStudent added successfully.\n");
}

// Display all student records
void DisplayAllStudents() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n==============================================================================================================================\n");
    printf("%-7s %-15s %-10s %-12s %-10s %-10s %-25s %-5s %-6s %-6s %-6s %-6s %-6s %-15s %-7s %-11s %-10s\n",
           "RollNo", "Name", "Course", "Contact", "City", "State", "Email", "Sem", "Mark1", "Mark2", "Mark3", "Mark4", "Mark5", "College", "Total", "Percentage", "Grade");
    printf("==============================================================================================================================\n");

    while (fscanf(fp, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d \"%[^\"]\" %d %f \"%[^\"]\"",
                  &s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
                  &s.Sem,
                  &s.Marks[0], &s.Marks[1], &s.Marks[2], &s.Marks[3], &s.Marks[4],
                  s.College_name, &s.Total, &s.Percentage, s.Grade) != EOF) {
        printf("%-7d %-15s %-10s %-12s %-10s %-10s %-25s %-5d %-6d %-6d %-6d %-6d %-6d %-15s %-7d %-11.2f %-10s\n",
               s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
               s.Sem,
               s.Marks[0], s.Marks[1], s.Marks[2], s.Marks[3], s.Marks[4],
               s.College_name, s.Total, s.Percentage, s.Grade);
    }

    fclose(fp);
}

// Search student by roll number
void SearchByRollNo() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "r");
    int rollno, found = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll No to search: ");
    scanf("%d", &rollno);

    while (fscanf(fp, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d \"%[^\"]\" %d %f \"%[^\"]\"",
                  &s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
                  &s.Sem,
                  &s.Marks[0], &s.Marks[1], &s.Marks[2], &s.Marks[3], &s.Marks[4],
                  s.College_name, &s.Total, &s.Percentage, s.Grade) != EOF) {
        if (s.Rollno == rollno) {
            printf("\nRoll No: %d\n", s.Rollno);
            printf("Name: %s\n", s.Name);
            printf("Course: %s\n", s.Course);
            printf("Contact: %s\n", s.Contact);
            printf("City: %s\n", s.City);
            printf("State: %s\n", s.State);
            printf("Email: %s\n", s.Email);
            printf("College: %s\n", s.College_name);
            printf("Semester: %d\n", s.Sem);
            printf("Marks: %d %d %d %d %d\n", s.Marks[0], s.Marks[1], s.Marks[2], s.Marks[3], s.Marks[4]);
            printf("Total: %d\n", s.Total);
            printf("Percentage: %.2f\n", s.Percentage);
            printf("Grade: %s\n", s.Grade);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student with Roll No %d not found.\n", rollno);

    fclose(fp);
}

// Delete student by roll number
void DeleteStudent() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    int rollno, found = 0;

    if (fp == NULL || temp == NULL) {
        perror("File error");
        return;
    }

    printf("Enter Roll No to delete: ");
    scanf("%d", &rollno);

    while (fscanf(fp, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d \"%[^\"]\" %d %f \"%[^\"]\"",
                  &s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
                  &s.Sem,
                  &s.Marks[0], &s.Marks[1], &s.Marks[2], &s.Marks[3], &s.Marks[4],
                  s.College_name, &s.Total, &s.Percentage, s.Grade) != EOF) {
        if (s.Rollno == rollno) {
            found = 1;
            continue; // skip writing to delete
        }

        fprintf(temp, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" %d %d %d %d %d %d \"%s\" %d %.2f \"%s\"\n",
                s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
                s.Sem,
                s.Marks[0], s.Marks[1], s.Marks[2], s.Marks[3], s.Marks[4],
                s.College_name, s.Total, s.Percentage, s.Grade);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student with Roll No %d not found.\n", rollno);
}

// Update student details by roll number
void UpdateStudent() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("update.txt", "w");
    int rollno, found = 0;

    if (fp == NULL || temp == NULL) {
        perror("File error");
        return;
    }

    printf("Enter Roll No to update: ");
    scanf("%d", &rollno);

    while (fscanf(fp, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d \"%[^\"]\" %d %f \"%[^\"]\"",
                  &s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
                  &s.Sem,
                  &s.Marks[0], &s.Marks[1], &s.Marks[2], &s.Marks[3], &s.Marks[4],
                  s.College_name, &s.Total, &s.Percentage, s.Grade) != EOF) {

        if (s.Rollno == rollno) {
            found = 1;

            int choice;
            do {
                printf("\n--- Current Record ---\n");
                printf("1. Name: %s\n", s.Name);
                printf("2. Course: %s\n", s.Course);
                printf("3. Contact: %s\n", s.Contact);
                printf("4. City: %s\n", s.City);
                printf("5. State: %s\n", s.State);
                printf("6. Email: %s\n", s.Email);
                printf("7. College: %s\n", s.College_name);
                printf("8. Semester: %d\n", s.Sem);
                printf("9. Marks: %d %d %d %d %d\n", s.Marks[0], s.Marks[1], s.Marks[2], s.Marks[3], s.Marks[4]);
                printf("10. Finish Update\n");
                printf("Enter field number to update: ");
                scanf("%d", &choice);

                getchar(); // Clear newline buffer

                switch (choice) {
                    case 1:
                        printf("Enter new Name: ");
                        fgets(s.Name, sizeof(s.Name), stdin);
                        s.Name[strcspn(s.Name, "\n")] = 0;
                        break;
                    case 2:
                        printf("Enter new Course: ");
                        fgets(s.Course, sizeof(s.Course), stdin);
                        s.Course[strcspn(s.Course, "\n")] = 0;
                        break;
                    case 3:
                        printf("Enter new Contact: ");
                        fgets(s.Contact, sizeof(s.Contact), stdin);
                        s.Contact[strcspn(s.Contact, "\n")] = 0;
                        break;
                    case 4:
                        printf("Enter new City: ");
                        fgets(s.City, sizeof(s.City), stdin);
                        s.City[strcspn(s.City, "\n")] = 0;
                        break;
                    case 5:
                        printf("Enter new State: ");
                        fgets(s.State, sizeof(s.State), stdin);
                        s.State[strcspn(s.State, "\n")] = 0;
                        break;
                    case 6:
                        printf("Enter new Email: ");
                        fgets(s.Email, sizeof(s.Email), stdin);
                        s.Email[strcspn(s.Email, "\n")] = 0;
                        break;
                    case 7:
                        printf("Enter new College Name: ");
                        fgets(s.College_name, sizeof(s.College_name), stdin);
                        s.College_name[strcspn(s.College_name, "\n")] = 0;
                        break;
                    case 8:
                        printf("Enter new Semester: ");
                        scanf("%d", &s.Sem);
                        break;
                    case 9:
                        printf("Enter 5 Subject Marks:\n");
                        for (int i = 0; i < 5; i++) {
                            printf("Subject %d: ", i + 1);
                            scanf("%d", &s.Marks[i]);
                        }
                        break;
                    case 10:
                        break;
                    default:
                        printf("Invalid choice! Try again.\n");
                }
            } while (choice != 10);

            calculate(&s);
        }

        fprintf(temp, "%d \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" %d %d %d %d %d %d \"%s\" %d %.2f \"%s\"\n",
                s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
                s.Sem,
                s.Marks[0], s.Marks[1], s.Marks[2], s.Marks[3], s.Marks[4],
                s.College_name, s.Total, s.Percentage, s.Grade);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("update.txt", FILENAME);

    if (found)
        printf("Student updated successfully.\n");
    else
        printf("Student with Roll No %d not found.\n", rollno);
}

// Print marksheet of a student by roll no
void PrintMarksheet() {
    struct Student s;
    FILE *fp = fopen(FILENAME, "r");
    int rollno, found = 0;

    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll No for Marksheet: ");
    scanf("%d", &rollno);

    while (fscanf(fp, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d \"%[^\"]\" %d %f \"%[^\"]\"",
                  &s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email,
                  &s.Sem,
                  &s.Marks[0], &s.Marks[1], &s.Marks[2], &s.Marks[3], &s.Marks[4],
                  s.College_name, &s.Total, &s.Percentage, s.Grade) != EOF) {
        if (s.Rollno == rollno) {
            printf("\n========== Marksheet ==========\n");
            printf("Roll No: %d\nName: %s\nCourse: %s\nContact: %s\nCity: %s\nState: %s\nEmail: %s\nCollege: %s\nSemester: %d\n",
                   s.Rollno, s.Name, s.Course, s.Contact, s.City, s.State, s.Email, s.College_name, s.Sem);
            printf("Marks:\n");
            for (int i = 0; i < 5; i++) {
                printf("Subject %d: %d\n", i + 1, s.Marks[i]);
            }
            printf("Total: %d\n", s.Total);
            printf("Percentage: %.2f\n", s.Percentage);
            printf("Grade: %s\n", s.Grade);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student with Roll No %d not found.\n", rollno);

    fclose(fp);
}

// Display students sorted by roll no, name, or percentage
void DisplaySortedStudents() {
    struct Student *students = NULL;
    int count = 0, capacity = 10;

    students = malloc(sizeof(struct Student) * capacity);
    if (!students) {
        printf("Memory allocation failed.\n");
        return;
    }

    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("No records found.\n");
        free(students);
        return;
    }

    // Read all students into array
    while (1) {
        if (count >= capacity) {
            capacity *= 2;
            students = realloc(students, capacity * sizeof(struct Student));
            if (!students) {
                printf("Memory allocation failed.\n");
                fclose(fp);
                return;
            }
        }
        if (fscanf(fp, "%d \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d %d %d %d %d %d \"%[^\"]\" %d %f \"%[^\"]\"",
                   &students[count].Rollno, students[count].Name, students[count].Course, students[count].Contact, students[count].City,
                   students[count].State, students[count].Email,
                   &students[count].Sem,
                   &students[count].Marks[0], &students[count].Marks[1], &students[count].Marks[2], &students[count].Marks[3], &students[count].Marks[4],
                   students[count].College_name, &students[count].Total, &students[count].Percentage, students[count].Grade) == EOF) {
            break;
        }
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("No records to display.\n");
        free(students);
        return;
    }

    int choice;
    printf("\nSort by:\n1. Roll No\n2. Name\n3. Percentage\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            qsort(students, count, sizeof(struct Student), cmpByRoll);
            break;
        case 2:
            qsort(students, count, sizeof(struct Student), cmpByName);
            break;
        case 3:
            qsort(students, count, sizeof(struct Student), cmpByPercentage);
            break;
        default:
            printf("Invalid choice. Showing unsorted data.\n");
    }

    printf("\n==============================================================================================================================\n");
    printf("%-7s %-15s %-10s %-12s %-10s %-10s %-25s %-5s %-6s %-6s %-6s %-6s %-6s %-15s %-7s %-11s %-10s\n",
           "RollNo", "Name", "Course", "Contact", "City", "State", "Email", "Sem", "Mark1", "Mark2", "Mark3", "Mark4", "Mark5", "College", "Total", "Percentage", "Grade");
    printf("==============================================================================================================================\n");

    for (int i = 0; i < count; i++) {
        printf("%-7d %-15s %-10s %-12s %-10s %-10s %-25s %-5d %-6d %-6d %-6d %-6d %-6d %-15s %-7d %-11.2f %-10s\n",
               students[i].Rollno, students[i].Name, students[i].Course, students[i].Contact, students[i].City, students[i].State,
               students[i].Email, students[i].Sem,
               students[i].Marks[0], students[i].Marks[1], students[i].Marks[2], students[i].Marks[3], students[i].Marks[4],
               students[i].College_name, students[i].Total, students[i].Percentage, students[i].Grade);
    }

    free(students);
}
