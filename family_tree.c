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


void read_person_info(const char *role, char *name_out, int *age_out)
{
    printf("Enter name of %s: ", role);
    fgets(name_out, 50, stdin);


    name_out[strcspn(name_out, "\n")] = '\0';


    printf("Enter age of %s: ", role);
    scanf("%d", age_out);


    getchar();
}




int main(void)
{
    char name[50];
    int age;


    Person *paternal_grandfather;
    Person *paternal_grandmother;
    Person *maternal_grandfather;
    Person *maternal_grandmother;
    Person *father;
    Person *mother;
    Person *me;


    read_person_info("Paternal Grandfather", name, &age);
    paternal_grandfather = create_person(name, age);


    read_person_info("Paternal Grandmother", name, &age);
    paternal_grandmother = create_person(name, age);


    read_person_info("Maternal Grandfather", name, &age);
    maternal_grandfather = create_person(name, age);


    read_person_info("Maternal Grandmother", name, &age);
    maternal_grandmother = create_person(name, age);


    read_person_info("Father", name, &age);
    father = create_person(name, age);


    read_person_info("Mother", name, &age);
    mother = create_person(name, age);


    read_person_info("Yourself", name, &age);
    me = create_person(name, age);


    printf("\nAll 7 family members have been entered!\n");


    return 0;
}

