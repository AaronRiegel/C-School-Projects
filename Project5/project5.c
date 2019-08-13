/*
*Assignment: Project 5
*Date: 4/13/2017
*Authors: Aaron Riegel and Ben Conrad
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"


void insert( Student** root, Student* node );
Student* search( Student* root, char* first, char* last );
Student* delete( Student** root, char* first, char* last );
void help();
void load(FILE* file, Student* houses[]);
void createStudent(char* first, char* last, int points, int year, char* house, Student* houses[]);
int getHouseNumber(char* house);
void save(char* file,Student* houses[]);
void clear(Student** root);
int score(Student* root);
void printStudent(Student* node);
void fprintStudent(Student* node, FILE* file);
void inorder(Student* root);
void preorder(Student* root);
void postorder(Student* root);
void fpreorder(Student* root, FILE* file,Student* houses[]);


int main(){

	char command[100] = ""; //initialize command to empty
	char fileName[100];
	
	Student* houses[5] = {NULL,NULL,NULL,NULL,NULL}; //create 5 NULL trees
	

	while(strcmp(command,"quit") != 0){ //while the command isn't quit, process commands
		printf("Enter a command: ");
		scanf("%s", command);
		
		if(strcmp(command, "help") == 0){ //call help function
			help();
		}
		
		else if(strcmp(command, "load") == 0){ //load a file into the trees
			scanf("%s", fileName); //get the name of the file
			FILE* file = fopen(fileName, "r"); //try to open the file
			if(file == NULL)						//if the file is NULL, print fail statment
				printf("Load failed. Invalid file: %s", fileName);
			load(file, houses); //call load function
			fclose(file); //close the file
			printf("Successfully loaded data from file %s.\n", fileName); //indicate successful loading
			
			
		}
		else if(strcmp(command, "save") == 0){ //save the trees into a file of the user's choice
			scanf("%s", fileName);
			save(fileName, houses);
		
		}
		else if(strcmp(command, "clear") == 0){ //clear the tree
			int i = 0;
			printf("\n");
			for(i = 0; i < 5; ++i){
				clear(&houses[i]); //pass address of root of house tree
			
			}
		}
		
		else if(strcmp(command, "inorder") == 0){ //print all trees using inorder traversal
			int i;
			printf("\n");
			for(i = 0; i < 5; ++i){
				switch(i){
					case 0 : printf("Gryffindor House\n\n"); break;
					case 1 : printf("\nRavenclaw House\n\n"); break;
					case 2 : printf("\nHufflepuff House\n\n"); break;
					case 3 : printf("\nSlytherin House\n\n"); break;
					default : printf("\nDeceased\n\n");
				}
					
				inorder(houses[i]);
			}	
			printf("\n");
		
		}
		
		else if(strcmp(command, "preorder") == 0){ //print all trees using preorder traversal
			int i;
			printf("\n");
			for(i = 0; i < 5; ++i){
				switch(i){
					case 0 : printf("Gryffindor House\n\n"); break;
					case 1 : printf("\nRavenclaw House\n\n"); break;
					case 2 : printf("\nHufflepuff House\n\n"); break;
					case 3 : printf("\nSlytherin House\n\n"); break;
					default : printf("\nDeceased\n\n");
				}
					
				preorder(houses[i]);
			}
			printf("\n");
		}
		
		else if(strcmp(command, "postorder") == 0){ //print all trees using postorder traversal
			int i;
			printf("\n");
			for(i = 0; i < 5; ++i){
				switch(i){
					case 0 : printf("Gryffindor House\n\n"); break;
					case 1 : printf("\nRavenclaw House\n\n"); break;
					case 2 : printf("\nHufflepuff House\n\n"); break;
					case 3 : printf("\nSlytherin House\n\n"); break;
					default : printf("\nDeceased\n\n");
				}
					
				postorder(houses[i]);
			}
			printf("\n");
		}
		
		else if(strcmp(command, "add") == 0){ //add user indicated student 
			char firstName[100] = "";
			char lastName[100] = "";
			int points;
			int year;
			char house[100] ="";
			int houseNumber;
			
			
			scanf("%s", firstName); //read in first name, last name, points, year, and house of student to be added
			scanf("%s", lastName);
			scanf("%d", &points);
			scanf("%d", &year);
			scanf("%s", house);
			
			
			houseNumber = getHouseNumber(house); //find the house the student belongs in
			
			
			if(houseNumber == -1){ //if invalid house, indicate the error
				printf("Add Failed. Invalid House: %s\n", house);
			}
			else{ //search to see if student already exists in tree
				Student* student = search(houses[getHouseNumber(house)], firstName, lastName);
			
				if(student) //if the student already exists, indicate the error
					printf("Add failed. Student named %s %s already present in roster.\n", firstName, lastName);
				else{ //create the student in the indicated tree
					createStudent(firstName,lastName,points,year,house,houses);
					printf("Added %s %s to roster.\n", firstName, lastName);
					
				}	
			}	
		}
		
		else if(strcmp(command, "kill") == 0){ //kill student and move them to deceased tree
			char firstName[100];
			char lastName[100];
			char house[100];
			int houseNumber;
			
			scanf("%s", firstName);
			scanf("%s", lastName);
			scanf("%s", house);
			
			houseNumber = getHouseNumber(house);
			
			if(houseNumber == -1){ //kill will fail if house is invalid
				printf("Kill Failed. Invalid House: %s\n", house);
			}
			else{
			
			
				Student* killed = delete(&houses[houseNumber], firstName, lastName);
				if(killed == NULL){ //kill will fail if student is not in indicated house
					printf("Kill failed. %s %s was not found in %s house\n", firstName, lastName, house);
				}
				else{ //if kill does not fail, insert the killed student into the deceased tree
					printf("%s %s moved to list of deceased students\n", firstName, lastName);
					insert(&houses[4],killed);
				}
			}	
		}
		
		else if(strcmp(command, "find") == 0){ //find the student in the indicated tree
			char firstName[100];
			char lastName[100];
			char house[100];
			int houseNumber;
			
			scanf("%s", firstName);
			scanf("%s", lastName);
			scanf("%s", house);
			
			houseNumber = getHouseNumber(house);
			
			if(houseNumber < 0 || houseNumber > 5){ //indicate failure if house is invalid
				printf("Find failed. Invalid house: %s\n", house);
			}
			
			else{
			
				Student* found = search(houses[houseNumber], firstName, lastName); //create a new student with return value of search
			
				if(found) //if student is found, print the student
					printStudent(found);
				else
					printf("Find Failed. %s %s was not found in %s House\n",firstName,lastName,house); 
				
			}
			
		}
		
		else if(strcmp(command, "points") == 0){ //give or take away point values from indicated student
			char firstName[100];
			char lastName[100];
			char house[100];
			int points = 0;
			int houseNumber;
			
			scanf("%s", firstName);
			scanf("%s", lastName);
			scanf("%s", house);
			scanf("%d", &points);
			
			houseNumber = getHouseNumber(house); //find the house number
			
			if(houseNumber < 0 || houseNumber > 5){ //if house is invalid, indicate failure
				printf("Point change Failed. Invalid house: %s\n", house);
			}
			
			else{ //the house number is valid
			
				Student* found = search(houses[houseNumber], firstName, lastName);
			
				if(found){ //if the student is found, increase or decrease their points by the indicated amount
					found->points += points;
					printStudent(found); //print the student with changed results
				}
				else //indicate failure if student is not found in house
					printf("Point change Failed. %s %s was not found in %s House\n",firstName,lastName,house);
			} 
		}
		
		else if(strcmp(command, "score") == 0){ //total the points of all students for their respective houses
			int i;
			printf("Point totals: \n");
			for(i = 0; i < 5; ++i){
				switch(i){
					case 0 : printf("Gryffindor House: %d\n", score(houses[i])); break;
					case 1 : printf("\nRavenclaw House: %d\n", score(houses[i])); break;
					case 2 : printf("\nHufflepuff House: %d\n", score(houses[i])); break;
					case 3 : printf("\nSlytherin House: %d\n", score(houses[i])); break;
					default : printf("\n");
				}
					
			}
			printf("\n");
		}
		
		
		else {
			if(strcmp(command, "quit") != 0){ //if the command is not recognized, indicate it is unknowwn
				printf("Unknown command: %s\n", command);
			}
		}
		
	
	}


}


void help(){ // help function prints explanations of all commands in program

printf("\nhelp\nPrints this display\n\n");

printf("load <filename>\nAdds the contents of a file to the current roster\n\n");

printf("save <filename>\nSaves the current roster to a file\n\n");

printf("clear\nClear the current roster\n\n");

printf("inorder\nPrint out an inorder traversal of the roster for each house\n\n");

printf("preorder\nPrint out a preorder traversal of the roster for each house\n\n");

printf("postorder\nPrint out a postorder traversal of the roster for each house\n\n");

printf("add <firstname> <lastname> <points> <year> <house>\nAdds a student to the roster\n\n");

printf("kill <firstname> <lastname> <house>\nMoves a student to the deceased list\n\n");

printf("find <firstname> <lastname> <house>\nSearches for a student in a house\n\n");

printf("points <firstname> <lastname> <house> <points>\nChanges the points a student has earned by the specified amount\n\n");

printf("score\nLists the point totals for all four houses\n\n");

printf("quit\nQuits the program\n\n");


}


void load(FILE* file, Student* houses[]){
	char firstName[100];
	char lastName[100];
	int points = 0;
	int year = 0;
	char house[100];
	
	
	while(fscanf(file,"%s",firstName) == 1) { //if the file no longer reads first names, stop reading

		fscanf(file,"%s",lastName); //put firstName, lastName, points, year, and house into their respective variables
		fscanf(file,"%d",&points);
		fscanf(file,"%d",&year);
		fscanf(file,"%s",house);
		
		createStudent(firstName, lastName, points, year, house, houses);
			
	}
}

void createStudent( char* first, char* last, int points, int year, char* house, Student* houses[]){
	int houseNumber;
	
	Student* student = malloc(sizeof(Student)); //malloc a student

	student->first = strdup(first); //set the attributes of the student equal to the variables holding their data
	student->last = strdup(last);
	student->points = points;
	student->year = year;
	
	student->left = NULL; //initialize the left and right children of the node to NULL
	student->right = NULL;
	
	houseNumber = getHouseNumber(house); //get the house number
	
	
	if(houseNumber == -1){ //if the house is invalid, do not add the student and indicate the failure
		printf("Add Failed. Invalid House: %s\n", house);
		return;
	}	
	else{ //add the student to their house; indicated by house number
		student->house = houseNumber;
		insert(&houses[houseNumber], student);
	}
		
}

int getHouseNumber(char* house){ //get the house number using the typedef enum house array in Student.h
	int i;
	for(i = 0; i < HOUSES; ++i){
		if(strcmp(house, HOUSE_NAMES[i]) == 0){
			return i;
		
		}
	
	}
	return -1;

}


void save(char* fileName,Student* houses[]) {
	
	FILE* file = fopen(fileName, "w"); //open a file for writing
	
	if(file == NULL) {
		printf("Save failed: Invalid file: %s\n", fileName); //if the file is not capable of being written to, indicate failure
		return;
	}
	else {
		int i = 0;
		for(i = 0; i < HOUSES; i++)
			fpreorder(houses[i],file,houses); //cycle throught the houses and add them to the file using a preorder
		fclose(file);	//close the file
		printf("Successfully saved data to file %s\n", fileName); //indicate success
	}	
	
	
}

void clear(Student** root){
	
	if (*root == NULL) //if the root is NULL, return
		return;
 	
    clear(&(*root)->left); //recursive check the left child
	
    clear(&(*root)->right); //recursive check the right child
   
   
    free(*root); //free the root
    *root = NULL; //set the root equal to NULL
    
    
}

int score(Student* root){
	if(root == NULL) //if the root is NULL, return 0 as the score
		return 0;
	
	return root->points + score(root->left) + score(root->right); //recursively add points of students from indicated house's root
		
}

void printStudent(Student* node){ //print out the information contained in a student node
	char firstLast[100];
	sprintf(firstLast, "%s %s", node->first, node->last); //combine the first and last names with a space between

	printf("%-25s",firstLast); //print the combined first and last names with formatting indicated in directions
	
	printf("Points: %d \t", node->points); //print how many points the person has
	printf("Year: %d ", node->year); //print the year of the person
	
	
	switch(node->house){
		case 0 : printf("House: Gryffindor\n"); break; //if the house is 0, print Gryffindor
		case 1 : printf("House: Ravenclaw\n"); break; //if the house is 1, print Ravenclaw
		case 2 : printf("House: Hufflepuff\n"); break; //if the house is 2, print Hufflepuff
		case 3 : printf("House: Slytherin\n"); break; //if the house is 3, print Slytherin
		default : printf("\tDeceased\n"); //default case is deceased list
		 
	}
	
}

void fprintStudent(Student* node, FILE* file) { //similar to printStudent, prints students to file
	fprintf(file,"%s %s ", node->first, node->last); //prints information of student node to file
	fprintf(file,"%d ", node->points);
	fprintf(file,"%d ", node->year);
	
	
	switch(node->house){
		case 0 : fprintf(file,"Gryffindor\n"); break;
		case 1 : fprintf(file,"Ravenclaw\n"); break;
		case 2 : fprintf(file,"Hufflepuff\n"); break;
		case 3 : fprintf(file,"Slytherin\n"); break;
		default : fprintf(file,"Deceased\n");
		 
	}

}

void inorder(Student* root){ //prints trees using inorder traversal
	if(root == NULL) //if NULL, return
		return;

	inorder(root->left); //recursively inorder left child
	printStudent((root)); //print self
	inorder(root->right); //recursively inorder right child
}


void preorder(Student* root){ //prints trees using preorder traversal
	if(root == NULL) //if NULL, return
		return;

	printStudent((root)); //print self
	preorder(root->left); //recursively preorder left child
	preorder(root->right); //recursively preorder right child
}


void postorder(Student* root){ //prints trees using postorder traversal
	if(root == NULL) //if NULL return
		return;
	
	postorder(root->left); //recusively postorder left child
	postorder(root->right);	//recursively postorder right child
	printStudent(root); //print self
	
}

void fpreorder(Student* root, FILE* file,Student* houses[]) { //similar to preorder, writes student to indicated file
	if(root == NULL)
		return;
	
	fprintStudent(root, file);
	fpreorder(root->left, file,houses);
	fpreorder(root->right, file,houses);	

}


/*
* This section includes tree manipulation functions insert, search, and delete
*/



void insert( Student** root, Student* node ){ //inserts student into tree
	
	

	if(*root == NULL){ //if the root is NULL, add the student as root
		(*root) = node;
	}
	
	else if(strcmp(node->last,(*root)->last) > 0) //if student's last name comes after root's last name, insert to the right
		insert(&(*root)->right, node);
		
	else if(strcmp(node->last,(*root)->last) < 0) //if student's last name comes after root's last name, insert to the left
		insert(&(*root)->left, node);
		
	else { //check the first names if last names are same
	
		if(strcmp(node->first,(*root)->first) > 0) //if first name comes after root's first name, insert to the right
			insert(&(*root)->right, node);
			
		else if(strcmp(node->first,(*root)->first) < 0) //if student's first name comes after root's first name, insert to the left
			insert(&(*root)->left, node);
	}
	
	
}

Student* search( Student* root, char* first, char* last ){ //find a student, returns Student pointer

	if(root == NULL || strcmp(first, root->first) == 0 && strcmp(last, root->last) == 0 ){ //if root is NULL or is equal to first and last name of student, return the root
		return root;
	}

	else if(strcmp(last,root->last) > 0) //if the last name of the one being searched for comes after root's last name, look to the right
		return search(root->right, first, last);
	
	else if(strcmp(last,root->last) < 0)
		return search(root->left, first, last); //if the last name of the one being searched for comes before root's last name, look to the left
	
	else if(strcmp(first,root->first) > 0) //if the first name of the one being searched for comes after root's first name, look to the right
		return search(root->right, first, last);
	
	else 
		return search(root->left, first, last); //if the first name of the one being searched for comes before root's first name, look to the left
	
}


Student* delete( Student** root, char* first, char* last ){ //removes student from tree, returns Student pointer
	Student* current = *root;

	if(*root == NULL) //if the root is NULL, return root
		return *root;
		
	
		
	if(strcmp(last,current->last) > 0) //if last comes after current's last, recursively delete using the right child as root
		return delete(&(*root)->right, first, last); 
		
	else if(strcmp(last,current->last) < 0) //if last come before current's last, recursively delete using the left child as root
		return delete(&(*root)->left, first, last);
		
	else if(strcmp(first,current->first) > 0) //if the first comes after current's first, recursively delete using the right child as root
		return delete(&(*root)->right, first, last);
	
	else if(strcmp(first,current->first) < 0) //if the first comes before current's first, recursively delete using the left child as root
		return delete(&(*root)->left, first, last);
		
	else{
		if((*root)->left == NULL){ //if there is nothing else to the left, check right
			*root = (*root)->right;
			
		}
			
			
		else if((*root)->right == NULL){ //if there is nothing else to the right, check left
			*root = (*root)->left;
			
			
		}
		
		else{
		
			Student* parent = (*root);
			Student* temp = (*root)->right;
		
			while(temp->left != NULL){ //find the smallest leaf in the tree
				parent = temp;
				temp = temp->left;			
			}
		
			if(temp == parent->left){ //if temp is the parent to current's left child, make parent's left child into temp's right child
				parent->left = temp->right;
			}
			else{ //set current's right node to temp's right node
				current->right = temp->right;
			}
		
		
			temp->left = current->left; //set temp's left child to current's left child
			temp->right = current->right; //set temp's right child to current's right child
		
			(*root) = temp; //set root = temp
		
		
		
		}
		current->left = NULL; //NULLify current's left and right nodes, then return current
		current->right = NULL;
		return current;
	}
	
	
		
}





