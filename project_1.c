/*
 * project_1.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Yahia
 */
#include <stdio.h>
#include <stdlib.h>


//storing each student data in a structure
struct student{
	int id;
	char name[50];
	int age;
	float gpa;
};

//define a bigger structure as a node in linked list
struct node{
	struct student data;
	struct node* next; //points to address of next node in linked list
};

struct node* head=NULL; //initialize head of linked list to be NULL until insertion of nodes
struct node* current=NULL;

void addStudent(const struct student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);


int main(void){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int choice=0;
	struct student s1;
	int id;
	while(choice!=8){
		printf("\n=========================\n");
		printf("1.Add Student.\n");
		printf("2.Display Students.\n");
		printf("3.Search Student by ID.\n");
		printf("4.Update Student Information.\n");
		printf("5.Delete Student.\n");
		printf("6.Calculate Average GPA.\n");
		printf("7.Search for student with the highest GPA.\n");
		printf("8.Exit the program.\n");
		printf("Enter the choice: ");
		scanf("%d",&choice);
		printf("=========================\n");

		switch(choice){
		case 1:

			printf("Enter the student name: ");
			scanf("%s",s1.name);
			printf("\nEnter the student ID: ");
			scanf(" %d",&(s1.id));
			printf("\nEnter the student age: ");
			scanf(" %d",&(s1.age));
			printf("\nEnter the student GPA: ");
			scanf(" %f",&(s1.gpa));
			addStudent(&s1);
			break;

		case 2:
			displayStudents();
			break;

		case 3:

			printf("Enter the ID you would like to search for:\n");
			scanf("%d",&id);
			searchStudentByID(id);
			break;

		case 4:
			printf("Enter the ID you would like to update information for:\n");
			scanf("%d",&id);
			updateStudent(id);
			break;

		case 5:
			printf("Enter the ID you would like to delete:\n");
			scanf("%d",&id);
			deleteStudent(id);
			break;

		case 6:
			printf("The average GPA is %f",calculateAverageGPA());
			break;

		case 7:
			searchHighestGPA();
			break;

		case 8:
			printf("Exiting Program...\n");
		}
	}

	return 0;
}

void addStudent(const struct student *const ptr){
	struct node* myptr=head; //a pointer to struct node that will be used to loop
	while(myptr!=NULL){ //loop until we reach the end of linked list to check if ID already exists
		if(myptr->data.id==ptr->id){
			printf("Error:ID already exists.\n");
			return;
		}
		myptr=myptr->next;
	}
	struct node* link= (struct node*) malloc(sizeof(struct node));
	if(link==NULL){ //check if memory allocation failed
		printf("Error:No space available in heap memory.\n");
		return;
	}
	link->data=*ptr; //if allocation is successful input the student data
	link->next=NULL; //insert the node at last position
	if(head==NULL){
		head=link;  //in case of empty list, head will point to the link node
		return;
	}
	current=head;
	while(current->next!=NULL){
		current=current->next; //loop until we reach the last node of the already available list
	}
	current->next=link;   //let the old last element point to the new inserted at last element
}


void displayStudents(void){
	if(head==NULL){
		printf("No students are present!!.\n");
		return;
	}
	struct node* ptr=head; //pointer will loop from first to last element
	while(ptr!=NULL){
		printf("Student Name: %s\n",ptr->data.name);
		printf("Student ID: %d\n",ptr->data.id);
		printf("Student Age: %d\n",ptr->data.age);
		printf("Student GPA: %f\n",ptr->data.gpa);
		printf("===============================\n");
		ptr=ptr->next;
	}

}


void searchStudentByID(int id){
	struct node* ptr=head;
	while(ptr!=NULL){
		if(ptr->data.id==id){
			printf("Student Name: %s\n",ptr->data.name);
			printf("Student ID: %d\n",ptr->data.id);
			printf("Student Age: %d\n",ptr->data.age);
			printf("Student GPA: %f\n",ptr->data.gpa);
			return;
		}
		ptr=ptr->next;
	}
	printf("Student with ID %d could not be found.\n",id);
}


void updateStudent(int id){
	struct node* ptr=head;
	while(ptr!=NULL){
		if(ptr->data.id==id){
			printf("Enter the updated student name:\n");
			scanf("%s",ptr->data.name);
			printf("Enter the student age:\n");
			scanf("%d",&(ptr->data.age));
			printf("Enter the student GPA:\n");
			scanf("%f",(&ptr->data.gpa));
			printf("Student with ID %d data updated successfully.\n",id);
			return;
		}
		ptr=ptr->next;
	}
	printf("Student with ID %d could not be found.\n",id);
}


float calculateAverageGPA(void){
	float sum=0;
	if(head==NULL){  //if list is empty, return 0.0
		return 0.0;
	}
	float average=0;
	current=head; //this pointer will continue looping till the end of linked list
	float size=0; //this variable will count the number of students
	while(current!=NULL){
		sum+=current->data.gpa;  //add the gpa of the student currently pointed to
		size++;
		current=current->next;
	}
	average=sum/size;
	return average;
}


void searchHighestGPA(void){
	if(head==NULL){
		printf("Error:No students are present.\n");
		return;
	}
	current=head;
	struct node* maxPtr=head; //this pointer will point to the element with the highest gpa
	float max=maxPtr->data.gpa;  //initial max value
	while(current!=NULL){
		if(current->data.gpa >max){ //loop all elements and if a higher gpa is found, update both the variable and the pointer
			max=current->data.gpa;
			maxPtr=current;
		}
		current=current->next;
	}
	printf("Student with the highest GPA:\n"); //print information of student with the highest gpa
	printf("Student Name: %s\n",maxPtr->data.name);
	printf("Student ID: %d\n",maxPtr->data.id);
	printf("Student Age: %d\n",maxPtr->data.age);
	printf("Student GPA: %f\n",maxPtr->data.gpa);
}


void deleteStudent(int id){
	if(head==NULL){
		printf("Error:No students are present.\n");
		return;
	}
	struct node* deleted=NULL;
	if(head->data.id==id){  //this case will check if the student we wish to delete is in the first node
		deleted=head;
		head=head->next;
		free(deleted);
		printf("Student deleted successfully.\n");
		return;
	}

	struct node* prev=head;
	current=head->next;  //the pointer(current) is always one node ahead of (prev)
	while(current!=NULL){
		if(current->data.id==id){
			deleted=current;
			prev->next=current->next;
			free(deleted);
			printf("Student deleted successfully.\n");
			return;
		}
		current=current->next;
		prev=prev->next;
	}
	printf("Student could not be found.\n");
}
