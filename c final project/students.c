#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student{
	int id;
	char name[50];
	int age;
	float gpa;
};

struct node {
	struct student data;
	struct node *next;
};

struct node *head = NULL ;  //empty list

// insert node function

void insert_student(const struct student *const ptr){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	struct node *current = head;
	temp->data=*ptr;
	temp->next=NULL;
	if (head == NULL){
		head=temp;
	}
	else{
		while(current->next != NULL){ // to make the current pointer on the last node
			current = current->next;
		}
		current->next = temp;
	}

}

void display_all_students(void){
	struct node *current = head;
	if(current == NULL){
		printf("no students added yet\n");
		return;
	}
	int i = 1;
	while(current != NULL){
		printf("%d. {id: %d, name: %s, age: %d, gpa: %f}\n",
				i,current->data.id,current->data.name,current->data.age,current->data.gpa);
		i++;
		current = current->next;
	}


}

void search_using_id(void){
	if(head==NULL){
		printf("no students added yet\n");
		return;
	}
	int wanted_id;
	printf("enter wanted id:");
	scanf("%d",&wanted_id);
	struct node *current = head;
	int found=0; //works as a boolean variable
	while(current != NULL){
		if(current->data.id == wanted_id){
			printf("%d. {name: %s,id: %d,age: %d, GPA: %f}\n",
					wanted_id,current->data.name,current->data.id,current->data.age,current->data.gpa);
			found=1;
		}
		current = current->next;
	}
	if(!found){
		printf("no student found with this id\n");
	}
}


void update_student_information(void){
	if(head == NULL){
		printf("no students added yet\n");
		return;
	}
	int wanted_id;
	printf("enter student id:\n");
	scanf("%d",&wanted_id);
	struct node *current = head;
	int found=0;//works as flag
	while(current != NULL){
		if(current->data.id == wanted_id){
			printf("Enter new name:\n");
			scanf("%49s",current->data.name);
			printf("Enter age:\n");
			scanf("%d",&current->data.age);
			printf("Enter GPA:\n");
			scanf("%f",&current->data.gpa);
			found = 1;

		}
		current = current->next;
	}
	if(!found){
		printf("no students with this id\n");
	}
	else{
		printf("data updated successfully\n");
	}
}

void delete_a_student(void) {
	if (head == NULL) {
		printf("No students added yet\n");
		return;
	}

	int wanted_id;
	printf("Enter student ID to delete: ");
	scanf("%d", &wanted_id);

	struct node *current = head;
	struct node *prev = NULL;
	while (current != NULL) {
		if (current->data.id == wanted_id) {
			if (current == head){
				head = current->next;
			}
			else{
				prev->next = current->next;
			}
			free(current); // Free the memory of the node
			printf("Student with ID %d deleted successfully\n", wanted_id);
			return;
		}
		prev = current;
		current = current->next;

	}
	printf("No student found with this ID\n");
}


void calculate_average_gpa(void){
	struct node *current = head;
	int number_of_students=0;
	float sum=0.0,average=0.0;
	if(head == NULL){
		printf("no students added yet\n");
		return;
	}
	while(current != NULL){
		sum = sum + current->data.gpa;
		number_of_students++;
		current = current->next;
	}
	average = sum/number_of_students;
	printf("the average gpa= %f\n",average);
}

void highest_gpa(void){
	struct node *current = head->next,*highest=head;
	while(current!=NULL){
		if (current->data.gpa > highest->data.gpa){
			highest = current;
		}
		current = current->next;
	}
	printf("highest gpa -> {name : %s , id : %d , age : %d , gpa : %f\n",
			highest->data.name,highest->data.id,highest->data.age,highest->data.gpa);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void)  {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// to loop untill the user wants to exit the program
	int exit=0;
	while(!exit){
		//print the choices

		printf("----------------------------------------\n");//horizontal for readability
		printf("1.Add a Student\n");
		printf("2.Display All Students\n");
		printf("3.Search for a Student by ID\n");
		printf("4.Update Student Information\n");
		printf("5.Delete a Student\n");
		printf("6.Calculate Average GPA\n");
		printf("7.Find Student with Highest GPA\n");
		printf("8.Exit\n");
		printf("----------------------------------------\n");//horizontal for readability

		//to make the user input his choice
		int choice;
		scanf("%d",&choice);



		switch (choice){
		case 1:{
			struct student s1;

			//take the struct as input from the user

			printf("Enter id:\n");
			scanf("%d",&s1.id);

			//check if id already exist
			struct node *current = head;
			int found=0;
			while(current != NULL){
				if(s1.id == current->data.id){

					printf("this id is already taken please choose another id\n");
					found = 1;
					break;
				}
				current = current->next;
			}
			if(found){
				break;
			}


			printf("Enter name:\n");
			scanf("%49s",s1.name);
			printf("Enter age:\n");
			scanf("%d",&s1.age);
			printf("Enter GPA:\n");
			scanf("%f",&s1.gpa);

			//pass it to the function
			insert_student(&s1);
		}
		break;
		case 2:
			display_all_students();
			break;
		case 3:
			search_using_id();
			break;
		case 4:
			update_student_information();
			break;
		case 5:
			delete_a_student();
			break;
		case 6:
			calculate_average_gpa();
			break;
		case 7:
			highest_gpa();
			break;
		case 8:
			exit = 1;
			break;
		default:
			printf("wrong input please choose a correct operation number ");

		}
	}
}
