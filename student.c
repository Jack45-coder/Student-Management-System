/*
- - - Student Management System - -
System Features
 Add a New Student Add a new student record to the file.
 View All Students Display a list of all students and their details.
  Search a Student Search for a student using their unique ID.
 Update Student Details Modify a studentʼs information.
 Delete Student Delete a student record from the system using their ID.
 Mark Enrollment Status Change a studentʼs enrollment status to "enrolled" or
"withdrawn."
 Menu Options
 5
 File Handling
Add Student Save new student records into the file.
 View Students Display all stored student records.
  Search Student by ID Find a specific student record by their unique ID.
 Update Student Details Modify an existing studentʼs information.
 Update Enrollment Status Mark a student as "enrolled" or "withdrawn."
  Exit Close the program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct students
{
  int id;
  char name[50];
  int age;
  char course[30];
  char enrollmentsts[15];
};

// Student details adding function created:-
void addstudents()
{
  FILE *file = fopen("students.txt", "a");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }
  struct students s;
  int add;
  printf("Enter Your ID: ");
  scanf("%d", &s.id);

  printf("Enter your Name: ");
  getchar();
  fgets(s.name, 50, stdin);
  strtok(s.name, "\n");

  printf("Enter your Age: ");
  scanf("%d", &s.age);

  printf("Enter your course: ");
  getchar();
  fgets(s.course, 30, stdin);
  strtok(s.course, "\n");

  strcpy(s.enrollmentsts, "Enrolled");

  // Save in text format
  fprintf(file, "%d, %s, %d, %s, %s\n", s.id, s.name, s.age, s.course, s.enrollmentsts);
  fclose(file);

  printf("Student added successfully!\n");
  }

// Students details view function created:-
void viewStudents()
{
  FILE *file = fopen("students.txt", "r");
  if (file == NULL)
  {
    printf("No records founds!\n");
    return;
  }
  struct students s;
  printf("\nID\tName\t\tAge\tCourse\t\tstatus\n");
  while (fscanf(file, "%d,%49[^,],%d,%29[^,],%14[^\n]\n", &s.id, s.name, &s.age, s.course, s.enrollmentsts) == 5)
  {
    printf("%d\t%s\t%d\t%s\t%s\n", s.id, s.name, s.age, s.course, s.enrollmentsts);
  }
  fclose(file);
}

// Search Student by ID:-
void findStudents()
{
  FILE *file = fopen("students.txt", "r");
  if (file == NULL)
  {
    printf("NO records Found!\n");
    return;
  }
  struct students s;
  int id, found = 0;
  printf("Enter student ID to search: ");
  scanf("%d", &id);

  while (fscanf(file, "%d,%49[^,],%d,%49[^,],%14[^\n]\n", &s.id, s.name, &s.age, s.course, s.enrollmentsts) == 5)
  {
    if (s.id == id)
    {
      printf("\nID: %d\nName: %s\nAge: %d\nCourse: %s\nEnrollment status: %s\n", s.id, s.name, s.age, s.course, s.enrollmentsts);
      found = 1;
      break;
    }
  }
  if (!found)
  {
    printf("Students not found!\n");
  }
  fclose(file);
}

// Update Student Details:-
void updateStudent()
{
  FILE *file = fopen("students.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (file == NULL || temp == NULL)
  {
    printf("Error opening file!\n");
    return;
  }
  int id, found = 0;
  struct students s;
  printf("Enter Student ID to update: ");
  scanf("%d", &id);
  while (fscanf(file, "%d,%49[^,],%d,%29[^,],%14[^,]", &s.id, s.name, &s.age, s.course, s.enrollmentsts) == 5)
  {
    if (s.id == id)
    {
      found = 1;
      printf("Enter New Name: ");
      getchar();
      fgets(s.name, 50, stdin);
      strtok(s.name, "\n");

      printf("Enter New Age: ");
      scanf("%d", &s.age);

      printf("Enter New Course: ");
      getchar();
      fgets(s.course, 30, stdin);
      strtok(s.name, "\n");
    }
    fprintf(temp, "%d,%s,%d,%s,%s\n", s.id, s.name, s.age, s.course, s.enrollmentsts);
  }
  fclose(file);
  fclose(temp);

  remove("students.txt");
  rename("temp.txt", "students.txt");

  if (found)
  {
    printf("Students updated successfully!\n");
  }
  else
  {
    printf("Students not found!\n");
  }
}

// Deleted function created:
void deleteStudents()
{
  FILE *file = fopen("students.txt", "r");
  FILE *temp = fopen("temp.txt", "w");
  if (file == NULL || temp == NULL)
  {
    printf("Error opening file!\n");
    return;
  }
  int id, found = 0;
  struct students s;
  printf("Enter Student ID to update: ");
  scanf("%d", &id);

  while (fscanf(file, "%d,%49[^,],%d,%49[^,],%14[^\n]\n", &s.id, s.name, &s.age, s.course, s.enrollmentsts) == 5)
  {
    if (s.id != id)
    {
      fprintf(temp, "%d,%s, %d,%s,%s\n", s.id, s.name, s.age, s.course, s.enrollmentsts);
    }
    else
    {
      found = 1;
    }
  }

  fclose(file);
  fclose(temp);

  remove("students.txt");
  rename("temp.txt", "students.txt");

  if (found)
    printf("Student deleted successfully!\n");
  else
    printf("Student not found!\n");
}

int main()
{
  int choice;
  do
  {
    printf("\n1. Add Students\n2. View Students\n3. Search Students\n4. Update Students\n5. Delete Students\n6. Exit\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      addstudents();
      break;

    case 2:
      viewStudents();
      break;

    case 3:
      findStudents();
      break;

    case 4:
      updateStudent();
      break;

    case 5:
      deleteStudents();
      break;

    case 6:
      exit(0);
      break;

    default:
      printf("Invalid Choice! Try again.\n");
    }
  } while (1);
}
