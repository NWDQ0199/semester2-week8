/**
 * Implementation of a student record management system using structures
 * 
 * This program demonstrates the use of structures in C to manage student data
 * including personal information and module marks.
 */

#include <stdio.h>
#include <string.h>

#include "student_record.h"

/**
 * Calculate the average mark for a student
 * 
 * param student The student whose average mark is to be calculated
 * return float The average mark
 */
float calculate_average(struct student_record student)
{
    // TODO: Implement this function to calculate and return the average
    // of the three module marks
    
    return 0.0; // Placeholder return value
}

/**
 * Display student information including name, ID, marks, and average
 * 
 * student The student whose information is to be displayed
 */
void display_student(struct student_record student)
{
    // TODO: Implement this function to display student information
    // Format: Name, ID, individual marks, and average mark
    printf("%s, %i, ",student.name,student.id);
    for(int i=0;i<NUM_MODULES;i++)
    {
        printf("%i, ");
    }
    float avg=calculate_average(student);
    printf("%f\n",avg);
}

/*
 * main
 */
int main(void)
{
    // TODO: Create and initialise a student variable with sample data
    // Example: name = "John Smith", id = 12345, marks = {75.0, 68.5, 81.0}
    
    struct student_record student;
    student.name="John Smith";
    student.id=12345;
    student.marks={75.0,68.5,81.0};
    
    // TODO: display the student data and average mark
    
    return 0;
}