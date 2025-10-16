#include<stdio.h>

struct students{
    int roll;
    char name[50];
    float cgpa;
    int dob;
};

void show1(struct students s){
    printf("Roll Number: %d\n", s.roll);
    printf("Name: %s\n", s.name);
    printf("CGPA: %.2f\n", s.cgpa);
    printf("Date of Birth: %d\n", s.dob);
}

void show2(struct students *s){
    printf("Roll Number: %d\n", s->roll);
    printf("Name: %s\n", s->name);
    printf("CGPA: %.2f\n", s->cgpa);
    printf("Date of Birth: %d\n", s->dob);
}

int main(){
    struct students s1;
    printf("Enter roll number: ");
    scanf("%d", &s1.roll);
    printf("Enter name: ");
    scanf("%s", s1.name);
    printf("Enter CGPA: ");
    scanf("%f", &s1.cgpa);
    printf("Enter date of birth (DDMMYYYY): ");
    scanf("%d", &s1.dob);

    show1(s1);
    printf("\n");
    show2(&s1);
    return 0;
}