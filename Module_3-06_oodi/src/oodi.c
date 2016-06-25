#include <stdlib.h>
#include <string.h>
#include "oodi.h"


/* Exercise a: Initialize student record
 * 
 * Parameters:
 * or: Oodi record to be changed (does not need to be allocated)
 * p_student, p_course, p_grade, p_compdate: Values for different structure
 *      fields (must be copied)
 * 
 * Returns: 1 if initialization was succesful, 0 if it failed
 * If student ID is more than 6 characters, initialization fails.
 * 
 * -- Note that structure contains enough space for student ID, but not for
 * course name
 * -- Remember to check that reserved space is not overwritten
 */
int init_record(struct oodi *or, const char *p_student, const char *p_course,
        unsigned char p_grade, struct date p_date)
{
    if (strlen(p_student) > 6) return 0;
    strncpy(or->student, p_student, 6);
    or->student[7] = '\0';
    size_t course_len = strlen(p_course);
    or->course = malloc(course_len + 1);
    if (!or->course) return 0;
    strncpy(or->course, p_course, course_len);
    or->course[course_len] = '\0';
    or->grade = p_grade;
    or->compdate = p_date;
    return 1;
}

/* Exercise b: Add a new record to a dynamic array.
 * (Resize the array as needed). All content of the new structure is copied.
 * 
 * Parameters:
 * array: start of an dynamic array (may be NULL, if array is empty)
 * length: current length of the array (number of entries)
 * newrec: new record to be added, all fields need to be copied.
 * 
 * Returns: pointer to the array after adding the new item
 */
struct oodi *add_record(struct oodi *array, unsigned int length, struct oodi newrec)
{
    struct oodi* newarray = realloc(array, (length + 1) * sizeof(struct oodi));
    if (!newarray) return NULL;
    init_record(&newarray[length], newrec.student, newrec.course, newrec.grade, newrec.compdate);
    return newarray;
}

/* Exercise c: Change grade and date in existing record.
 * 
 * Parameters:
 * array: beginning of array
 * size: size of array
 * student: student ID to be changed
 * course: course to be changed
 * newgrade: new value for grade
 * newdate: new value for date
 * 
 * Returns: number of entries changed, i.e. either 1 or 0
 */
int change_grade(struct oodi *array, unsigned int size, const char *p_student,
        const char *p_course, unsigned char newgrade, struct date newdate)
{
    int changed = 0;
    for (unsigned int i = 0; i < size; i++) {
        if (strncmp(array[i].student, p_student, 6) == 0 && strcmp(array[i].course, p_course) == 0) {
            array[i].grade = newgrade;
            array[i].compdate = newdate;
            changed++;
        }
    }
    return changed;
}

/* Exercise d: Delete array (and all memory allocated for it)
 * 
 * Parameters:
 * array: beginning of the array
 * 
 * Returns: 1 when array is deleted
 */
int delete_array(struct oodi *array, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
        free(array[i].course);
    }
    free(array);
    array = NULL;
    return 1;
}
