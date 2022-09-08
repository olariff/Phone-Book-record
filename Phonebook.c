#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//define a person structure with attributes
struct person{
    char name[40];
    char address[50];
    char sex[8];
    char email[40];
    char number[15];
};

int main(){
    system("color 3f"); //set colour of the phonebook's background
    menu();
    return 0;
}

//this function displays the main menu of the phonebook
void menu(){
    system("cls");
    printf("\t\t\tWELCOME TO THE PHONEBOOK\t\t\t\n");
    printf("You can select any of the following options from the menu below:\n\n");
    printf("\t1. Add a person \t2. List the people \t3. Modify\n \t4. Delete a person \t5. Search for a person \t6. Exit\n");
    printf("\nEnter your choice: ");

    // based on the users' input, a particular function is called
    switch(getch()){
        case '1':
            addPerson();
            break;

        case '2':
            list();
            break;

        case '3':
            modify();
            break;

        case '4':
            erase();
            break;

        case '5':
            search();
            break;

        case '6':
            exit(0);
            break;

        default:
            printf("Invalid key entered\n");
            printf("Press any key to return to the menu: ");
            getch();
            menu();

    }
}

// this function adds a person to the phone book with their attributes
void addPerson(){
    system("cls");
    FILE *f;
    struct person p;
    f = fopen("phonebook", "ab+"); //open an external file to store the phonebook

    printf("\nPlease enter a name: ");
    gets(p.name);

    printf("\nPlease enter their address: ");
    gets(p.address);

    printf("\nPlease enter their sex: ");
    gets(p.sex);

    printf("\nPlease enter their email: ");
    gets(p.email);

    printf("\nPlease enter their phone number: ");
    gets(p.number);

    fwrite(&p, sizeof(p), 1, f); //write to the file, the details entered by the user
    fclose(f);
    system("cls");
    menu();
}

//this function lists out all the people and their information from the phone book
void list(){
    FILE *f;
    struct person p;
    f = fopen("phonebook", "rb"); //read the external phone book file

    if(f==NULL){
        printf("\nFile Opening Error");
        printf("\nPress any key to return to the main menu :");
        getch();
        menu();
    }

    // list out the phone book
    while(fread(&p, sizeof(p), 1, f) == 1){
        printf("\nName: %s\nAddress: %s\nSex: %s\nE-mail: %s\nPhone Number: %s\n", p.name, p.address, p.sex, p.email, p.number);

    }
    fclose(f);
    getch();
    menu();
}

// this function enables the user to make modification to a persons information
void modify(){
    FILE *f;
    struct person p;
    f = fopen("phonebook", "rb+");

    if(f==NULL){
        printf("\nFile Opening Error");
        printf("\nPress any key to return to the main menu :");
        getch();
        menu();
    }

    char modify[40];
    printf("\nPlease enter the name of the person you would like to modify: ");
    gets(modify);

    while(fread(&p, sizeof(p), 1, f) == 1){

        if(strcmp(modify, p.name) == 0){    //compare the name entered by the user to the names in the phone book
            printf("\nPlease update name: ");
            gets(p.name);

            printf("\nPlease update their address: ");
            gets(p.address);

            printf("\nPlease update their sex: ");
            gets(p.sex);

            printf("\nPlease update their email: ");
            gets(p.email);

            printf("\nPlease update their phone number: ");
            //scanf("%ld", &p.number);
            gets(p.number);
            fseek(f, -sizeof(p),SEEK_CUR);  // set the cursor of the file pointer to the person to be modified
            fwrite(&p, sizeof(p), 1, f);    //write modified info to the same file, replacing previous content of the person
            break;
        }
    }
    fclose(f);
    menu();

}

// this function deletes a person and their info from the phone book
void erase(){
    FILE *f;
    int flag;
    struct person p;
    f = fopen("phonebook", "rb+");  // open external phone book file

    if(f==NULL){
        printf("\nFile Opening Error");
        printf("\nPress any key to return to the main menu :");
        getch();
        menu();
    }

    FILE *ftemp = fopen("temp", "wb+");     //create a temp file to write the phonebook content to, excluding the person to be deleted

    char modify[40];
    printf("\nPlease enter the name of the person you would like to delete from the records: ");
    gets(modify);

    while(fread(&p, sizeof(p), 1, f) == 1){
        // check that the entered name doesn not match any in the records
        if(strcmp(modify, p.name) != 0){
            //fseek(f, -sizeof(p),SEEK_CUR);
            fwrite(&p, sizeof(p), 1, ftemp);

        }
        //check that the name entered matches a name in the record
        if(strcmp(modify, p.name) == 0){
            flag = 1;

        }
    }
    fclose(f);
    fclose(ftemp);

    if(flag == 1){
        remove("phonebook");    //delete the phonebook file
        rename("temp","phonebook");     //rename the temp file to phonebook

    }

    else{
        remove("temp");

    }

    menu();
}

//this function enables the user to search for a person in the records
//the person and their information is displayed afterwards
void search(){
    FILE *f;
    struct person p;
    f = fopen("phonebook", "rb");

    if(f==NULL){
        printf("\nFile Opening Error");
        printf("\nPress any key to return to the main menu :");
        getch();
        menu();
    }

    char modify[40];
    printf("\nPlease enter the name of the person you would like to search for: ");
    gets(modify);

    while(fread(&p, sizeof(p), 1, f) == 1){

        if(strcmp(modify, p.name) == 0){
            printf("\nName: %s\nAddress: %s\nSex: %s\nE-mail: %s\nPhone Number: %s\n", p.name, p.address, p.sex, p.email, p.number);

        }
    }
    fclose(f);

    printf("\nPress any key to continue");
    getch();
    menu();

}

