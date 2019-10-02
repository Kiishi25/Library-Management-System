//Name: Kiishi Ifebajo
// C17347676
#define _CRT_SECURE_NO_WARNINGS
#define bool int
#define false 0

#define true (!false)

//Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//amount of books
#define SIZE 10


struct data {
	int borrowedBook; //number of times book is borrowed
	char ID[9];
	char name[15];
	char author[15]; //name of author
	int yearOfPublication;
	char customerName[20];

	bool takenOut; //boolean to check if book is on loan

};

struct LinearNode {
	struct data *element;
	struct LinearNode *next;
};
// Function prototypes
void addBook(); //adding books to end of the list
void viewAllBooks(); //viewing all books
void viewSpecificBook(char);
void deleteBook(char);
void takeOutBook(char);
void saveToFile(FILE *);
void getFromFile(FILE *);
void returnBook(char);
bool isEmpty();

// Global Variables
struct LinearNode *front = NULL;
struct LinearNode *last = NULL;


/**************MAIN FUNCTION*******************/
int main() {
	FILE *fp; //file

	int number; //number option for menu
	char delBook[9]; //parameter passed in for method
	char viewABook[15];//parameter passed in for method
	char borrowedBook[20];//parameter passed in for method
	char returnedBook[21];//parameter passed in for method

						  //File Handling
	if ((fp = fopen("h:book.dat", "rb")) == NULL) {
		printf("There is no data in file \n");



		do {
			printf("1. Add a new book to the library\n");
			printf("2. Allow customer to take out a book \n");
			printf("3. Allow customer to return a book\n");
			printf("4. Delete an old book\n");
			printf("5. View all books\n");
			printf("6. View a specific book\n");
			printf("7. View details of most popular and least popular books\n");
			printf("8. Personal Feature\n");
			printf("9. Exit System\n");


			printf("Enter a number : \n");
			scanf("%d", &number);


			if (number > 9) { //checking if the option is greater than 9

				printf("Option is greater than 9. Try Again! \n");
			}


			if (number == 1) {

				addBook();
			}
			else if (number == 2) {

				takeOutBook(*borrowedBook);
			}
			else if (number == 3) {

				returnBook(*returnedBook);
			}
			else if (number == 4) {

				deleteBook(*delBook);
			}
			else if (number == 5) {

				viewAllBooks();
			}
			else if (number == 6) {

				viewSpecificBook(*viewABook);
			}

			getchar();
		} while (number != 9 || number > 9);

	}
}


void addBook() {

	struct LinearNode *aNode;
	struct data *anElement;
	bool takenOut = true; //boolean to see if book is borrowed
	int yearOfPublication = 0;

	//Create space for data part of book
	anElement = (struct data *)malloc(sizeof(struct data));
	if (anElement == NULL)
		printf("Error - no space for the new book\n");
	else
	{
		//input value into data part
		//do {
		printf("Enter Book Identifier: ");
		scanf("%s", anElement->ID);

		//if (isdigit(anElement->ID)) {
		//}
		//else {
		//printf("Not A digit \n");
		//}
		//} while (!isdigit(anElement->ID));


		printf("Enter name of book: ");
		scanf("%s", anElement->name);
		printf("Enter name of author: ");
		scanf("%s", anElement->author);

		do {
			printf("Enter year of publication: ");
			scanf("%d", &anElement->yearOfPublication);


			if (anElement->yearOfPublication < 2008) { //check if year is older than 2008

				printf("Year cannot be older than 2008\n");
			}
		} while (anElement->yearOfPublication < 2008);


		if (anElement->takenOut = false) { //checking if book is on loan or not

			printf("Loaned out\n");
			//anElement->borrowedBook = 0;
		}
		else {

			printf("Not Loaned out\n");
		}


		aNode = (struct LinearNode *)malloc(sizeof(struct LinearNode));

		if (aNode == NULL)
			printf("Error - no space for the new book\n");
		else { // add data part to the book
			aNode->element = anElement;
			aNode->next = NULL;

			//add book to end of the list
			if (isEmpty())
			{
				front = aNode;
				last = aNode;
			}
			else {
				last->next = aNode;
				last = aNode;

			}
		}
	}
}
//end addBooks

void viewSpecificBook(char viewABook)
{
	struct LinearNode *current, *previous;
	int index = 0;
	bool notFound = true;

	char viewBook[15];
	current = front;

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the list\n");

	else {
		current = front;

		printf("Enter Book ID : ");
		scanf("%s", viewBook);

		while (notFound && current != NULL) {

			if (strcmp(viewBook, current->element->ID) == 0) //comapring the inputed string with list of books
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}

			if (notFound) {


				printf("Book Not Found! \n");

			}

			else {



				printf("Book ID : %s\n ", current->element->ID);
				printf("Book name : %s\n", current->element->name);
				printf("Author : %s\n", current->element->author);
				printf("Year of publication : %d\n", current->element->yearOfPublication);
				if (current->element->takenOut) {
					printf("Book is loaned out \n", current->element->takenOut);
				}
				else {

					printf("Not Borrowed");
				}

				current = current->next;
			}

		}
	}
}




void takeOutBook(char ID) {

	struct LinearNode *current, *previous;
	bool notFound = true;
	char borrowBook[15];

	printf("\n");

	if (isEmpty())
		printf("Error - there are no books in the list\n");
	else {

		printf("What book do you want to take out? \n");
		scanf("%s", borrowBook);

		current = previous = front;
		while (notFound && current != NULL) {

			if (strcmp(borrowBook, current->element->ID) == 0)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}

			if (notFound) {

				printf("This ID cannot be found %s\n", ID);

			}

			else {
				printf("Enter Customer name\n");
				scanf("%s", current->element->customerName);
				current->element->takenOut = true;
				current->element->borrowedBook++; //adding 1 to cuurent when a book is taken out


				printf("Book With ID %s has been taken out\n", current->element->ID);
			}
		}

	}
}


void saveToFile(FILE *fp) {

	fp = fopen("h:books.dat", "wb");

}

void returnBook(char ID) {

	struct LinearNode *current, *previous;
	bool notFound = true;
	char returnBook[15];

	printf("\n");

	if (isEmpty())
		printf("Error - there are no books in the list\n");
	else {

		printf("What book do you want to return?\n");
		scanf("%s", returnBook); //inputed value to return

		current = previous = front;
		while (notFound && current != NULL) {
			if (strcmp(returnBook, current->element->ID) == 0)
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}

			if (notFound) {

				printf("This ID cannot be found %c", ID);

			}

			else {
				printf("Enter Customer name\n");
				scanf("%s", current->element->customerName);
				if (current->element->takenOut = false) {// change back to false if the book is returned
					current->element->borrowedBook;            //check if book has been taken out or not


					printf("Book With ID %s has been returned \n", current->element->ID);
				}

				else {

					printf("This book hasnt been taken out\n");
				}

			}

		}

	}
}


void viewAllBooks() {
	struct LinearNode *current;

	printf("\n");
	if (isEmpty())
		printf("Error - there are no books in the list\n");
	else {
		current = front;
		//iterating through the list while current isnt equal to null
		while (current != NULL) {
			//displaying book details
			printf("Book ID : %s\n ", current->element->ID);
			printf("Book name : %s\n", current->element->name);
			printf("Author : %s\n", current->element->author);
			printf("Year of publication : %d\n", current->element->yearOfPublication);
			if (current->element->takenOut) { //if the book has taken out display if its loaned

				printf("Book is loaned out \n", current->element->takenOut);
			}
			else {

				printf("This book has not been borrowed\n");
			}
			current = current->next;
		} //end while
	}//end else
} //end viewAllBooks



void deleteBook(char aBook) {
	struct LinearNode *current, *previous;
	struct data *anElement;
	bool notFound = true;
	char delBook[9];

	printf("\n");
	printf("Enter Book ID : ");
	scanf("%s", delBook);


	if (isEmpty())
		printf("Error - there are no books in the list\n");


	else {

		current = previous = front;
		//iterating through the list while current and notFound isnt equal to null 
		while (notFound && current != NULL) {
			if (strcmp(delBook, current->element->ID) == 0) //comparing string input with ID in list
				notFound = false;
			else {
				previous = current;
				current = current->next;
			}//end else
		} //end while

		if (notFound)
			printf("Error - there is not such Book with this Book ID %c\n", aBook);
		else
		{
			if (current->element->yearOfPublication < 2010) {  //checking if year is older than 2010
				printf("Year cannot be older than 2010\n");
			}

			else {

				if (current == front) { //delete front book
					front = front->next;
					free(current);
				} //end else
				else if (current == last) {//delete last book
					free(current);
					previous->next = NULL;
					last = previous;
				}
				else {  //delete book in middle of list
					previous->next = current->next;
					free(current);
				} //end else
				printf("Book  %s has been deleted\n", delBook);
			}
		}
	}//end else
}//end else
 // end deleteBook



bool isEmpty() {
	if (front == NULL)
		return true;
	else
		return false;
}

