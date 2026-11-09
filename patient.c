
#include <stdio.h>
#include <string.h>

#define FILE_NAME "patients.txt"

struct Patient {
    int id;
    char name[50];
    int age;
    char diagnosis[50];
};

void addPatient() {
    struct Patient p;
    struct Patient temp;
    FILE *fp;
    int found = 0;

    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);

    fp = fopen(FILE_NAME, "r");

    if (fp != NULL) {
        while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                      &temp.id, temp.name,
                      &temp.age, temp.diagnosis) == 4) {
            if (temp.id == p.id) {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (found) {
        printf("Patient ID already exists.\n");
        return;
    }

    printf("Enter Patient Name: ");
    scanf(" %49[^\n]", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Diagnosis: ");
    scanf(" %49[^\n]", p.diagnosis);

    if (p.age <= 0 || p.age > 120) {
        printf("Invalid age.\n");
        return;
    }

    fp = fopen(FILE_NAME, "a");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(fp, "%d|%s|%d|%s\n",
            p.id, p.name, p.age, p.diagnosis);

    fclose(fp);

    printf("Patient record added successfully.\n");
}

void displayPatients() {
    struct Patient p;
    FILE *fp = fopen(FILE_NAME, "r");
    int found = 0;

    if (fp == NULL) {
        printf("\nNo patient records found.\n");
        return;
    }

    printf("\n--- PATIENT RECORDS ---\n");

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                  &p.id, p.name,
                  &p.age, p.diagnosis) == 4) {

        printf("\nPatient ID: %d\n", p.id);
        printf("Name: %s\n", p.name);
        printf("Age: %d\n", p.age);
        printf("Diagnosis: %s\n", p.diagnosis);

        found = 1;
    }

    if (!found) {
        printf("No patient records available.\n");
    }

    fclose(fp);
}

void searchPatient() {
    struct Patient p;
    int searchID;
    int found = 0;

    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        printf("No patient records found.\n");
        return;
    }

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &searchID);

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                  &p.id, p.name,
                  &p.age, p.diagnosis) == 4) {

        if (p.id == searchID) {
            printf("\nPatient Found!\n");
            printf("ID: %d\n", p.id);
            printf("Name: %s\n", p.name);
            printf("Age: %d\n", p.age);
            printf("Diagnosis: %s\n", p.diagnosis);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patient not found.\n");
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== HOSPITAL MANAGEMENT =====\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                printf("Hospital system closed.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
