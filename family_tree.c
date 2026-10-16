#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

void link_parents(Person *child, Person *father, Person *mother);
void print_family_relationships(const Person *me);
void free_family_tree(Person *people[], int count);
void print_tree_visual(const Person *root, int level);

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

void link_parents(Person *child, Person *father, Person *mother)
{
    child->father = father;
    child->mother = mother;
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

if (paternal_grandfather == NULL ||
    paternal_grandmother == NULL ||
    maternal_grandfather == NULL ||
    maternal_grandmother == NULL ||
    father == NULL ||
    mother == NULL ||
    me == NULL) {

    printf("Error: Unable to create the complete family tree.\n");

    free(paternal_grandfather);
    free(paternal_grandmother);
    free(maternal_grandfather);
    free(maternal_grandmother);
    free(father);
    free(mother);
    free(me);

    return 1;
}

    printf("\nAll 7 family members have been entered!\n");

    link_parents(me, father, mother);
    link_parents(father, paternal_grandfather, paternal_grandmother);
    link_parents(mother, maternal_grandfather, maternal_grandmother);

    print_family_relationships(me);

     printf("\n=== VISUAL FAMILY TREE ===\n");
    print_tree_visual(me, 0);

    
    Person *all_people[] = {
        paternal_grandfather, paternal_grandmother,
        maternal_grandfather, maternal_grandmother,
        father, mother, me
    };
    free_family_tree(all_people, 7);


    return 0;
}

void print_family_relationships(const Person *me)
{
    printf("\n=== FAMILY TREE ===\n");

    printf("\nYourself: %s (Age: %d)\n", me->name, me->age);

    printf("\nParents:\n");
    printf("Father: %s (Age: %d)\n",
           me->father->name, me->father->age);
    printf("Mother: %s (Age: %d)\n",
           me->mother->name, me->mother->age);

    printf("\nPaternal Grandparents:\n");
    printf("Grandfather: %s (Age: %d)\n",
           me->father->father->name, me->father->father->age);
    printf("Grandmother: %s (Age: %d)\n",
           me->father->mother->name, me->father->mother->age);

    printf("\nMaternal Grandparents:\n");
    printf("Grandfather: %s (Age: %d)\n",
           me->mother->father->name, me->mother->father->age);
    printf("Grandmother: %s (Age: %d)\n",
           me->mother->mother->name, me->mother->mother->age);
}

void print_tree_visual(const Person *root, int level)
{
    if (root == NULL) {
        return;
    }

    if (level == 0) {
        printf("%s (Age: %d)\n", root->name, root->age);
    } else {
        if (level == 1) {
            if (root == root->mother) {
                printf("└── ");
            } 
        } else if (level == 2) {
            printf("│   ├── ");
        }
    }

    if (level == 0) {
        printf("├── Father: ");
        print_tree_visual(root->father, 1);
        printf("└── Mother: ");
        print_tree_visual(root->mother, 1);
    } 
    else if (level == 1) {
        printf("%s (Age: %d)\n", root->name, root->age);
        
        if (root->father != NULL) {
            printf("│   ├── Grandfather: %s (Age: %d)\n", root->father->name, root->father->age);
        }
        if (root->mother != NULL) {
            printf("│   └── Grandmother: %s (Age: %d)\n", root->mother->name, root->mother->age);
        }
    }
}
void free_family_tree(Person *people[], int count)
{
    for (int i = 0; i < count; i++) {
        free(people[i]);
    }

    printf("\nMemory cleanup completed successfully!\n");
}