#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
 {
    int id;
    char name[50];
    int age;
    char grade[10];
};

void addStudent() {
    struct Student s;
    FILE *f = fopen("students.dat", "ab");
    if (!f) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Grade: ");
    scanf(" %s", s.grade);

    fwrite(&s, sizeof(struct Student), 1, f);
    fclose(f);
    printf("Student added successfully!\n");
}

void viewStudents() {
    struct Student s;
    FILE *f = fopen("students.dat", "rb");
    if (!f) {
        printf("No data available.\n");
        return;
    }

    printf("\nAll Students:\n");
    while (fread(&s, sizeof(struct Student), 1, f)) {
        printf("ID: %d, Name: %s, Age: %d, Grade: %s\n", s.id, s.name, s.age, s.grade);
    }

    fclose(f);
}

void searchStudent() {
    struct Student s;
    int id, found = 0;
    FILE *f = fopen("students.dat", "rb");
    if (!f) {
        printf("No data available.\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct Student), 1, f)) {
        if (s.id == id) {
            printf("Student found: ID: %d, Name: %s, Age: %d, Grade: %s\n", s.id, s.name, s.age, s.grade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }

    fclose(f);
}

void deleteStudent() {
    struct Student s;
    int id, found = 0;
    FILE *f = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!f || !temp) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(struct Student), 1, f)) {
        if (s.id != id) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student deleted successfully.\n");
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== School Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
