/* Coivid 19 patient managenet system
   Author:- P.S.R. Nanayakkara (E/18/233)
   Date:- 10/01/2022
*/
//uses a struct array to holsd patient records
//There is an optional function to save the data to a text file


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

int counter = 0;
typedef struct Patient{ //Parameters that are stored for one patient
    int NIC;
    char fullName[100];
    char gender[2];
    int age;
    char admissionDate[12];
} Patient;

Patient records[250];//This holds the patient reecords.

void gotoxy(short x,short y){
    COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void WelcomeScreen();//Initial welcome screen
int validateAndReturn();//Take input and parse number if valid, if not valid ask for input until a valid one is given
void addRecord();//Adds a record
void viewAll();//view all records
void searchRecord();//search records from NIC
void deleteRecord();//delete record
void saveToTxt();//save content to a .txt file
void quit();//quit the programe

int main(){
    WelcomeScreen();
    int T = 1;//To control the loop;
    while(T){
        system("cls");
        if(counter==250){
            printf("Maximum capacity has reached.");
            break;
        }
        int choice;
        printf("\n\n\n\n\t\t\t\t\t ---------------------------------------------------\n");
        printf("\t\t\t\t\t\t Covid 19 patient management system\n");
        printf("\t\t\t\t\t ---------------------------------------------------\n\n\n");
        printf("\t\tChoose from below\n");
        printf("\t\t\t1.Add patient\n");
        printf("\t\t\t2.View all patients\n");
        printf("\t\t\t3.Search patient details\n");
        printf("\t\t\t4.Delete patient record\n");
        printf("\t\t\t5.Save records to a file\n");
        printf("\t\t\t6.exit\n");
        choice = validateAndReturn();
        
        switch (choice)
        {
        case 1:
            addRecord();
            break;
        case 2:
            viewAll();
            break;
        case 3:
            searchRecord();
            break;
        case 4:
            deleteRecord();
            break;
        case 5:
            saveToTxt();
            break;
        case 6:
            quit();
            T = 0;
            break;
        default:
            printf("Enter a valid input");
        }
    } 
    return 0;
}

void WelcomeScreen(){
    printf("\n\n\n\n\t\t\t\t\t -------------------------------------------------------------\n");
    printf("\t\t\t\t\t\t Welcome to covid 19 patient management system\n");
    printf("\t\t\t\t\t -------------------------------------------------------------\n\n\n");
    printf("Press any key to continue.......\n");
    getch();
    system("cls");

}

int validateAndReturn(){
    int number;
    while(TRUE){
        char *endPtr;
        char str[250];
        fgets(str,250,stdin);
        number = strtol(str,&endPtr,10);
        if(endPtr == str){
            printf("Enter a valid number\n");
            continue;
        }else{
            break;
        }
    }
    return number;
}

void addRecord(){
   
    system("cls");
    fflush(stdout);
    printf("\n\nName:-");
    fgets(records[counter].fullName,100,stdin);

    printf("NIC number:- ");
    records[counter].NIC = validateAndReturn();

    printf("Gender(Male-M,Female-F) M/F:-");
    fgets(records[counter].gender,3,stdin);
    

    printf("Age:- ");
    records[counter].age = validateAndReturn();

    printf("Admission Date (DD/MM/YYYY):- ");
    fgets(records[counter].admissionDate,12,stdin);

    counter++;

}

void viewAll(){
    system("cls");
    printf("\n\n\n\n\t\t\t\t -----------------------------------------\n");
    printf("\t\t\t\t\t List of all patiet records\n");
    printf("\t\t\t\t -----------------------------------------\n\n\n");

    gotoxy(1,10);
    printf("NIC");
    gotoxy(20,10);
    printf("Name");
    gotoxy(60,10);
    printf("Gender");
    gotoxy(70,10);
    printf("Age");
    gotoxy(90,10);
    printf("Admission Date");

    printf("\n================================================================================================================\n");
    int row=12;
    for(int i =0;i<counter;i++){
        gotoxy(1,row);
        printf("%d",records[i].NIC);
        gotoxy(20,row);
        printf("%s",records[i].fullName);
        gotoxy(60,row);
        printf(" %s",records[i].gender);
        gotoxy(70,row);
        printf("%d",records[i].age);
        gotoxy(90,row);
        printf("%s",records[i].admissionDate);
        row++;
    }
    getch();
}

void searchRecord(){
    int nic;
    printf("Enter the NIC number to serarch:-");
    nic = validateAndReturn();

    for(int i =0;i<counter;i++){
        if(records[i].NIC == nic){
            printf("\tName :- %s\n",records[i].fullName);
            printf("\tGender :- %s\n",records[i].gender);
            printf("\tAge :- %d\n",records[i].age);
            printf("\tAdmission Date :- %s\n",records[i].admissionDate);
            getch();
            break;
        }

        if(i == counter-1){
            printf("No record avaliable for this NIC number.\n");
            getch();
        }
    }
}

void deleteRecord(){
    int delNIC;
    char resp[2];
    printf("Enter NIC number to delete:-");
    delNIC = validateAndReturn();

    for(int i =0;i<counter;i++){
        if(records[i].NIC == delNIC){
            printf("\tName :- %s\n",records[i].fullName);
            printf("\tGender :- %s\n",records[i].gender);
            printf("\tAge :- %d\n",records[i].age);
            printf("\tAdmission Date :- %s\n",records[i].admissionDate);
            
            printf("Are you sure you want to delete this record? (Y/N)\n");
            fgets(resp,2,stdin);
            if(strcmp(resp,"Y")==0||strcmp(resp,"y")==0){
                for(int j = i;j<counter;j++){
                    strcpy(records[j].admissionDate,records[j+1].admissionDate);
                    records[j].age = records[j+1].age;
                    strcpy(records[j].fullName,records[j+1].fullName);
                    strcpy(records[j].gender,records[j+1].gender);
                    records[j].NIC = records[j+1].NIC;
                }
                counter--;
                printf("Record was sucsessfully deleted.\n");
                getch();
            }else if(strcmp(resp,"N")==0||strcmp(resp,"n")==0){
                printf("Record was not deleted.\n");
                getch();
            }else{
                printf("Enter a valid input\n");
                getch();
            }
        }

        if(i == counter-1){
            printf("No record avaliable for this NIC number.\n");
            getch();
        }
    }
}

void saveToTxt(){
    FILE* fptr;
    fptr = fopen("PatientRecords.txt","w");
    if(fptr == NULL){
        printf("\nFile cannot be created.\n");
    }
    for(int i =0;i<counter;i++){
        fprintf(fptr,"%d. Name:- %s, NIC:- %d, Gender:- %s, Age:- %d, Admission Date:- %s\n\n",i+1,records[i].fullName,records[i].NIC,records[i].gender,records[i].age,records[i].admissionDate);
    }
    fclose(fptr);
    system("cls");
    printf("Saved sucsessfully");
    getch();

}
void quit(){
    system("cls");
    printf("\n\n\n\n\t\t\t\t\tThank you!\n\n\n\n");
    getch();
}
