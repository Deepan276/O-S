#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int empId;
    char empName[50];
    double empSalary;
};

void addEmployee(FILE *file) {
    struct Employee employee;

    printf("Enter employee ID: ");
    scanf("%d", &employee.empId);
    getchar(); // Consume the newline character

    printf("Enter employee name: ");
    fgets(employee.empName, sizeof(employee.empName), stdin);
    employee.empName[strlen(employee.empName) - 1] = '\0'; // Remove the newline character

    printf("Enter employee salary: ");
    scanf("%lf", &employee.empSalary);

    fseek(file, (employee.empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&employee, sizeof(struct Employee), 1, file);
}

void displayEmployee(FILE *file, int empId) {
    struct Employee employee;
    
    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&employee, sizeof(struct Employee), 1, file);

    if (employee.empId != 0) {
        printf("Employee ID: %d\n", employee.empId);
        printf("Employee Name: %s\n", employee.empName);
        printf("Employee Salary: %.2lf\n", employee.empSalary);
    } else {
        printf("Employee with ID %d does not exist.\n", empId);
    }
}

void updateEmployee(FILE *file, int empId) {
    struct Employee employee;

    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    fread(&employee, sizeof(struct Employee), 1, file);

    if (employee.empId != 0) {
        printf("Enter new salary for employee %d: ", empId);
        scanf("%lf", &employee.empSalary);

        fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
        fwrite(&employee, sizeof(struct Employee), 1, file);

        printf("Salary updated successfully.\n");
    } else {
        printf("Employee with ID %d does not exist.\n", empId);
    }
}

int main() {
    FILE *employeeFile = fopen("employee.dat", "r+");

    if (employeeFile == NULL) {
        employeeFile = fopen("employee.dat", "w+");
        if (employeeFile == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
    }

    int choice, empId;

    do {
        printf("\nEmployee Database Management\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Update Employee Salary\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employeeFile);
                break;
            case 2:
                printf("Enter employee ID: ");
                scanf("%d", &empId);
                displayEmployee(employeeFile, empId);
                break;
            case 3:
                printf("Enter employee ID: ");
                scanf("%d", &empId);
                updateEmployee(employeeFile, empId);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    fclose(employeeFile);
    return 0;
}
