#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person* create_person(const char *name, int age)
{
    Person *person = malloc(sizeof(Person));

    if (person == NULL) {
        printf("Error in Memory allocation\n");
        return NULL;
    }

    snprintf(person->name, sizeof(person->name), "%s", name);

    person->age = age;
    person->father = NULL;
    person->mother = NULL;
 
    return person;
}
int main ()
{
    return 0;
}