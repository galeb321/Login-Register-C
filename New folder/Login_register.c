#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void menu();
int check_database();
int id ();
void create_acc();
void restart();




struct registeredUsers{
	int id;
	char username[50];
	char password[50];
	
};

struct registeredUsers newacc;

int check_database(){
	
	FILE *regUsers;
	char check_length[100];
	
	regUsers = fopen("users.csv", "a+");
	
	check_length[0] = getc(regUsers);
	
	if(check_length[0] != 'I')
		fprintf(regUsers, "ID, Username, Password\n");
	
	fclose(regUsers);

}



int id (){
	FILE *regUsers;
	regUsers = fopen("users.csv", "r");
	int count=0;
	char idline;
	
    for (idline = getc(regUsers); idline != EOF; idline = getc(regUsers))
        if (idline == '\n')
            count = count + 1;
                   
	fclose(regUsers);
	
	printf("\nYour ID is %d. Please make sure you remember your id for accessing your acc.", count);
	
	return count;
	
}

void login(){
		
	system("cls");
	FILE *regUsers;
	
	char tmpuser[100], tmppass[100], c;
	int i=0;
	
	printf("Please enter your username: ");
	scanf(" %s", tmpuser);
	printf("Please enter your password: ");
	scanf(" %s", tmppass);
	
//	while( (c=getch()) !=32){
//		tmppass[i] = c;
//		printf("*");
//		i++;
//	}

	regUsers = fopen("users.csv", "r");

    char buffer[1024];
  	
    int row = 0;
    int column = 0;
    int usernameTF=1;
    int passwordTF=1;
    char *value;
    
    const char div[2] = ", ";

  	
    while (fgets(buffer, 1024, regUsers)) {
        column = 0;
        row++;
        
        value = strtok(buffer, div);
  		
        while (value) {
        	
            if(column == 1) {
     	        if(strcmp(tmpuser, value) == 0){
       	        	usernameTF=0;
       	        	printf("%s %s", value, value);
       	        	if(column == 2)
       	        		if(strcmp(tmppass, value) == 0){
       	        			passwordTF=0;
       	        			break;
						   }
					   
   					
                }				               
            }
           
			value = strtok(NULL, div);
            column++;
            
       	    if(usernameTF == 0 ){ 
			          	    
   				break;
            }            
        }
        
       	if(usernameTF == 0){        	
                    
   			break;
        }
    }
    fclose(regUsers);
  	row=0;
  	column=0;
  	printf("%s %s", value, value);
/*  	
  	regUsers = fopen("users.csv", "r");	
  	
  	while (fgets(buffer, 1024, regUsers)) {
        column = 0;
        row++;

        value = strtok(buffer, div);

        while (value) {
        	
            if(column == 2) {
            	passwordTF = strcmp(tmppass, value);
       	        if(passwordTF == 0){
       	        
   					break;
                }               
            }
            if(passwordTF == 0 ){        	    
   				break;
            } 
			value = strtok(NULL, div);
            column++;
            
       	               
        }
       	if(passwordTF == 0){        	
                    
   			break;
        }
    }
*/  
	printf("%s %s", value, value);
    fclose(regUsers);
    
    if(usernameTF == 0 && passwordTF == 0){
    	printf("\n\nWelcome back %s\n", tmpuser);
		restart();
    }
    else {
    	printf("\n\nWrong password or username!!");
    	menu();
	}
}

void create_acc(){
	
	system("cls");
	
	FILE *regUsers;
	
	int idnum = id();
	
	printf("Please enter information of account. \n\n");
	printf("Username: ");
	scanf(" %s", newacc.username);
	printf("\nPassword: ");
	scanf(" %s", newacc.password);
	

	regUsers = fopen("users.csv", "r");

    char buffer[1024];
  
    int row = 0;
    int column = 0;
    int usernameTF=1;
    char *value;
    const char div[2] = ", ";

  	
    while (fgets(buffer, 1024, regUsers)) {
        column = 0;
        row++;

        value = strtok(buffer, div);
  		
        while (value) {
        	
            if(column == 1) {
            	usernameTF = strcmp(newacc.username, value);
       	        if(usernameTF == 0){        	
                    printf("Username already in use!!");
   					break;
                }               
            }
			value = strtok(NULL, div);
            column++;
            
       	    if(usernameTF == 0){        	    
   				break;
            }            
        }
       	if(usernameTF == 0){        	
                    
   			break;
        }
    }
  
    fclose(regUsers);

	if(usernameTF != 0){
			regUsers = fopen("users.csv", "a+");	
		fprintf(regUsers, "%d, %s, %s\n", idnum, newacc.username, newacc.password);
		fclose(regUsers);
	
	
	
		printf("!!!Thank you for registering with us!!!\n\n\n");
	}

	menu();
	
}

void menu(){
	
	int choice;
	
	
	printf("\n\n\n!!!!!!Welcome!!!!!!");
	printf("\n\n\n1.Create new account\n");
	printf("2.Login\n");
	printf("3.Exit\n");
	
	printf("Please chooise one the above: ");
	scanf("%d", &choice);
	
	switch(choice){
		case 1:{
			create_acc();
			break;
		}
		case 2:{
			login();
			break;
		}
		case 3:{
			break;
		}

	}
		
}
void restart(){
	
	char choose;
	
	printf("\n\n\nIf you need something else press Y, or N for exit.");
	scanf(" %c", &choose);
	
	
	if(choose == 'Y'||choose == 'y')
		menu();
	else if (choose == 'n'|| choose == 'N')
		system("cls");
	else
		printf("Wrong choice!!!");
}

void main(){
	
	check_database();
	menu();
	
}
