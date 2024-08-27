#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 40
#define PASSWORD 2534

int menu();// to choose process
FILE* openTheFile();// opens a file for processes
FILE* updateTheFile(FILE* );// updates from file
FILE* deleteTheFile(FILE* );// deletes from file
FILE* readTheFile(FILE* );// reads from file
FILE* writeTheFile(FILE* );// writes from file
void displayTheLessonNumber(FILE* );// shows everything to us


struct lessonNote// for lessonNote
{
    int midExam;// middle exam note
    int finalExam;// final exam note
};

struct Lessons
{
    int lessonNumber;// lesson number
    char lessonName[STR_SIZE];// lesson name
    struct lessonNote note;// lesson note with mid and final
    char lessonTeacher[STR_SIZE];// lesson teacher
    int discontinuityForLesson;// discontinuity for lesson
};




int main(void)
{
int option;
int passWord;
printf("enter the password:\n");//checks the password true or false
scanf("%d",&passWord);
if( passWord==PASSWORD){
printf("password is true\n");
}else{
printf("this password is not true");
return 1;
}
FILE* fptr= openTheFile();
do{
    option=menu();
   switch(option){
case 1:
    fptr=readTheFile(fptr);
    break;
case 2:
    fptr=writeTheFile(fptr);
    break;
case 3:
    fptr=deleteTheFile(fptr);
    break;
case 4:
    fptr=updateTheFile(fptr);
    break;
case 5:
    displayTheLessonNumber(fptr);
    break;
case 6:
    printf("exit...");
    break;
    default:
				printf("inccorect option...\n");
				break;
    }
    }while(option!=6);
    fclose(fptr);
return 0;
}

int menu()// to choose process
{
    int option;
    printf("\n1-> Read");
    printf("\n2-> Write");
    printf("\n3->Delete");
    printf("\n4->Update");
    printf("\n5->Search");
    printf("\n6->Exit");
    printf("\nEnter your choice: ");
    scanf("%d",&option);
    return option;

}

FILE* openTheFile()// opens a file for processes
{
    FILE* fptr=fopen("cust.txt","rb+");
    if(fptr==NULL)// checks the file null or not null
        {
        printf("!can not open the file!trying to create it now...\n");
        fptr = fopen("cust.txt", "wb+");
       if(fptr==NULL)
       {
        printf("cannot create the file...\n");
        exit(1);
       }else printf("file opened");
    }
    return fptr;
}

void displayTheLessonNumber(FILE* fptr)// shows everything to us
{
struct Lessons les;
int lessonNumber;
fprintf(stdout,"Lesson number to look:");//checks lesson number because if you want to look your lesson detail, you can enter lesson number
scanf("%d",&lessonNumber);

fseek(fptr, sizeof(struct Lessons) * (lessonNumber-1) ,SEEK_SET);
fread(&les,sizeof(struct Lessons),1,fptr);

if(les.lessonNumber!=0)
{

            printf("Lesson Name/Teacher Name/Lesson Number/Midexam/Finalexam\n");// lesson information respectively
            printf("-----------------------------------------------------------\n");
    fprintf(stdout,"%s     |%s         | %d          | %d    | %d        |\n",
            les.lessonName,
            les.lessonTeacher,
            les.lessonNumber,
            les.note.midExam,
            les.note.finalExam);
            printf("-----------------------------------------------------------\n");
}else fprintf(stdout,"!No such a lesson!");

}


FILE* updateTheFile(FILE* fptr )// updates from file
{
struct Lessons les;
int lessonNumber;
fprintf(stdout,"Enter the lesson number:");// checks lesson number because if you want to update from file, you can enter lesson number
scanf("%d",&lessonNumber);
fseek(fptr,sizeof(struct Lessons)*(lessonNumber-1),SEEK_SET);
fread(&les,sizeof(struct Lessons),1,fptr);

if(les.lessonNumber!=0 && lessonNumber==les.lessonNumber)// if your lesson number is true, you can choose to update
{
     int option2;
     printf("choose\n1->lesson name\n2->lesson teacher\n3->discontinuity\n4->exam note\n");
     scanf("%d",&option2);

     if(option2 == 1)// updates for lesson name
     {
     printf("old lesson name is %s , now:\n",les.lessonName);
     scanf("%s",les.lessonName);
     }
     else if(option2 == 2)// updates for lesson teacher
     {
     printf("old lesson teacher name is %s , now:\n",les.lessonTeacher);
     scanf("%s",les.lessonTeacher);
     }
     else if(option2 == 3)// updates for discontinuity
     {
     printf("old discontinuity is %d , now:\n",les.discontinuityForLesson);
     scanf("%d",&les.discontinuityForLesson);
     }
     else if(option2 == 4)// updates for middle or final exam
     {
     int option3;
     printf("choose 1->middle exam\n2->final exam:\n");// choose to update middle or final exam
     scanf("%d",&option3);

     if(option3 == 1)// updates for middle exam note
     {
     printf("old middle exam note is %d , now:\n",les.note.midExam);
     scanf("%d",&les.note.midExam);
     }
     else if(option3 == 2)// updates for final exam note
     {
     printf("old final exam note is %d , now:\n",les.note.finalExam);
     scanf("%d",&les.note.finalExam);
     }
     else {// closes if the number is entered except 1 and 2
                printf("Incorrect option...\n");
                return fptr;
     }
     }
     else {// closes if the number is entered except 1, 2, 3, 4
            printf("Incorrect option...\n");
            return fptr;}

        fseek(fptr,(lessonNumber-1)*sizeof(struct Lessons),SEEK_SET);
        fwrite(&les,sizeof(struct Lessons),1,fptr);
}else printf("!No such a lesson!");

return fptr;
}

FILE* deleteTheFile(FILE* fptr)// deletes from file
{
struct Lessons les;
int lessonNumber;
fprintf(stdout,"Enter the lesson number:");
scanf("%d",&lessonNumber);
fseek(fptr,sizeof(struct Lessons)*(lessonNumber-1),SEEK_SET);
fread(&les,sizeof(struct Lessons),1,fptr);
if(les.lessonNumber!=0 && lessonNumber==les.lessonNumber)
{
    les.lessonName[0]='\0';// it equalizes to null
    les.lessonTeacher[0]='\0';// it equalizes to null
    les.discontinuityForLesson=0;// it equalizes to zero
    les.note.midExam=0;// it equalizes to zero
    les.note.finalExam=0;// it equalizes to zero
    les.lessonNumber=0;// it equalizes to zero

    fseek(fptr,(lessonNumber-1)*sizeof(struct Lessons),SEEK_SET);
    fwrite(&les,sizeof(struct Lessons),1,fptr);
}else fprintf(stdout,"!No such a lesson!");

return fptr;
}

FILE* readTheFile(FILE* fptr)// reads from file
{
struct Lessons les;

rewind(fptr);
// Since the file is already open, ensure you rewind it
fread(&les,sizeof(struct Lessons),1,fptr);

while(!feof(fptr))
{

    if(les.lessonNumber!=0)
    {
        printf("Lesson Name/Teacher Name/Discontinuity/Midexam/Finalexam\n");
        printf("-----------------------------------------------------------\n");
        fprintf(stdout,"%s     |%s         | %d          | %d    | %d     |%d \n",les.lessonName,
                les.lessonTeacher,
                les.discontinuityForLesson,
                les.note.midExam,
                les.note.finalExam,
                les.lessonNumber);
        printf("-----------------------------------------------------------\n");
    }
    fread(&les,sizeof(struct Lessons),1,fptr);
}

return fptr;

}

FILE* writeTheFile(FILE* fptr)// writes from file
{
struct Lessons les;

fprintf(stdout,"Enter the lesson name:");
scanf("%s",les.lessonName);
fprintf(stdout,"Enter the teacher of lesson:");
scanf("%s",les.lessonTeacher);
fprintf(stdout,"Enter the middle exam note:");
scanf("%d",&les.note.midExam);
fprintf(stdout,"Enter the final note:");
scanf("%d",&les.note.finalExam);
fprintf(stdout,"Enter the discontinuity:");
scanf("%d",&les.discontinuityForLesson);
fprintf(stdout,"Enter the lesson number:");
scanf("%d",&les.lessonNumber);

while(!feof(stdin))
{
    if(les.lessonNumber>0)
    {
        fseek(fptr,sizeof(struct Lessons)*(les.lessonNumber-1),SEEK_SET);
        fwrite(&les,sizeof(struct Lessons),1,fptr);
    }
fprintf(stdout,"Enter the lesson name:");
scanf("%s",les.lessonName);
fprintf(stdout,"Enter the teacher of lesson:");
scanf("%s",les.lessonTeacher);
fprintf(stdout,"Enter the middle exam note:");
scanf("%d",les.note.midExam);
fprintf(stdout,"Enter the final note:");
scanf("%d",les.note.finalExam);
fprintf(stdout,"Enter the discontinuity:");
scanf("%d",les.discontinuityForLesson);
}
return fptr;
}



