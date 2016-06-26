#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "queuepriv.h"

Queue *Queue_init(void)
{
    Queue *q = calloc(1, sizeof(Queue));
    return q;
}

int Queue_enqueue(Queue *q, const char *id, const char *name)
{
    if (strlen(id) > 6) return 0;
    
    // Get another pointer to the one that would point to the next node
//    struct student** current = &(q->first);
//    while (*current) {
//        current = &((*current)->next);
//    }
    // Make current->next point to the newly allocated memory
//    *current = malloc(sizeof(struct student));
//    struct student* new_student = *current;
    struct student* new_student = malloc(sizeof(struct student));
    if (!new_student)
        return 0;
    strncpy(new_student->id, id, 6);
    new_student->id[6] = '\0';
    
    size_t name_len = strlen(name);
    new_student->name = malloc(name_len + 1);
    if (!new_student->name) {
        free(new_student);
        return 0;
    }
    strncpy(new_student->name, name, name_len);
    new_student->name[name_len] = '\0';
    
    new_student->next = NULL;
    
    // Point first node pointer to new node if empty queue
    if (!q->first)
        q->first = new_student;
    // Add new node to the queue
    if (q->last)
        q->last->next = new_student;
    q->last = new_student;
    return 1;
}

char *Queue_firstID(Queue *q)
{
    if (q && q->first)
        return q->first->id;
    else
        return NULL;
}

char *Queue_firstName(Queue *q)
{
    if (q && q->first)
        return q->first->name;
    else
        return NULL;
}

int Queue_dequeue(Queue *q)
{
    if (!q)
        return 0;
    struct student* first = q->first;
    if (!first)
        return 0;
    q->first = first->next;
    free(first->name);
    free(first);
    // If there is no first node, the list must be empty
    if (!q->first)
        q->last = NULL;
    return 1;
}

int Queue_drop(Queue *q, const char *id)
{
    if (!q)
        return 0;
    struct student* current = q->first;
    if (strncmp(current->id, id, 6) == 0) {
        q->first = current->next;
        free(current->name);
        free(current);
        return 1;
    }
    struct student* prev = current;
    current = current->next;
    while (current) {
        if (strncmp(current->id, id, 6) == 0) {
            prev->next = current->next;
            if (!prev->next)
                // Update the last node if the current node is also the last node
                q->last = prev;
            free(current->name);
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void Queue_delete(Queue *q)
{
    if (q) {
        while(Queue_dequeue(q));
        free(q);
    }
}
