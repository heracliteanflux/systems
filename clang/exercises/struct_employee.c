/*    struct_employee.c
 *
 *    Define a struct called Employee with members name, age, and salary.
 *    Create an array of Employee objects, and prompt the user to enter the details of each employee.
 *    Then display the details of the employee with the highest salary.
 */

#include <stdio.h>

struct Employee {
  char  name[50];
  int   age;
  float salary;
};

int main () {
  int num_employees;

  printf("Enter the number of employees: ");
  scanf("%d", &num_employees);

  struct Employee employees[num_employees];

  // iterate over each employee to collect their information
  for (int i = 0; i < num_employees; i++) {
    printf("\nEnter the details of employee %d:\n", i + 1);

    printf("Name: ");
    scanf("%s", employees[i].name);

    printf("Age: ");
    scanf("%d", &employees[i].age);

    printf("Salary: ");
    scanf("%f", &employees[i].salary);
  }

  int max_sal_idx = 0;                       // assign max_sal_idx to first employee
  for (int i = 1; i < num_employees; i++) {  // iterate over the remaining employees and compare salaries
    if (employees[i].salary > employees[max_sal_idx].salary)
      max_sal_idx = i;
  }

  printf("\nEmployee with the highest salary:\n");
  printf("name   : %s\n", employees[max_sal_idx].name);
  printf("age    : %d\n", employees[max_sal_idx].age);
  printf("salary : %.2f\n", employees[max_sal_idx].salary);

  return 0;
}