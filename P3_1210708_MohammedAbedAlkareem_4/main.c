/*
*Name: Mohammed Abed Alkareem
*ID:1210708
*section: 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define nameLength 50
#define cityLength 50
#define intLength 15

typedef struct dateNode Date;
struct dateNode
{
    int day;
    int month;
    int year;
};

typedef struct treeNode stdNode;
struct treeNode
{
    int ID;
    char Name [nameLength];
    char City [cityLength];
    int classID;
    Date* EnrollmentDate ;
    int Height;
    stdNode* Left;
    stdNode* Right;
};

stdNode* DisposeTree( stdNode* );
int Height( stdNode* );
int Max( int, int );

stdNode* RightSingleRotation( stdNode* );
stdNode* LeftSingleRotation( stdNode* );
stdNode* LeftRightDoubleRotation( stdNode*);
stdNode* FindNode(int,stdNode*);
stdNode* FindMin(stdNode*);
stdNode* Delete(int, stdNode*);
stdNode* deleteStudent(stdNode*);
int getBalance(stdNode *);
stdNode* RightLeftDoubleRotation( stdNode* );
stdNode* Insert(int, char*, char*, int, int,int,int, stdNode* );
void ListAllStudents( stdNode*);
/////////////////////////
stdNode* insertStudent(stdNode*); //for case 1
stdNode* updateStudent(stdNode*); //for case 2
////////////////////
void mainMenu();
void SortAll( stdNode*, stdNode** );
void SortByClass( stdNode*, stdNode**, int  );
void SortByCity( stdNode*, stdNode**, char*  );
int checkID ( int, stdNode*);

int ScanInt();

stdNode* InsertByName(int, char*, char*, int, int,int,int, stdNode* );       //for sorting 	in	lexicographic order
void PrintNode(stdNode*);

void CapitalizeEachWord(char*);
int checkValidInt (char*);
///////read
int MaxChar(FILE*);
stdNode* readFile( stdNode*);
/////
void getDate(char*, int*, int*, int*);

void SaveToFile(stdNode *);
void printToFile(FILE*, stdNode*);

int main()
{
    int ID;

    char answer[5]; //for case 2

    stdNode* temp = NULL;

    printf("\nWelcome To The School Database ^_^\n\n");

    printf("\nUploading Students' Info..... \n\n");

    stdNode* stdTree = NULL;
    stdTree=readFile( stdTree);

    if(stdTree !=NULL)
        printf("Students' Info has been Uploaded successfully  ^_^\n\n");
    else
    {
        printf("cannot upload Students' Info  *_*\n\n");
    }

    stdNode* sorted = NULL;//a tree to store the data sorted by name

    while (1) //always ask the user for the choice
    {
        int choice;
        char City [cityLength];

// Display the main menu
        mainMenu();
        printf("What do you want to do: ");
        choice = ScanInt();

        switch (choice)
        {

        case 1://Insert a student

            printf("\nINSERTING NEW STUDENT....\n\n");
            stdTree = insertStudent(stdTree);

            break;

        case 2://Find	a student

            if(stdTree == NULL)
            {
                printf("\nThere is no students to be found \n\n");
                break;
            }

            printf("\nFINDING A STUDENT....\n\n");
            printf("Student's ID: ");
            ID = ScanInt();

            temp = FindNode(ID, stdTree);

            if(temp == NULL)
            {
                printf("invalid id *_* \n");
                break;
            }

            PrintNode(temp);

            do //iterates until the user enters yes / no
            {
                printf("\nDo you want to update %s's info? (Answer with yes / no) \n",temp->Name);
                strcpy(answer, "");
                fgets(answer, sizeof(answer), stdin);// Read the student's name using fgets to allow reading a line with spaces
                answer[strlen(answer)-1] = '\0';
                CapitalizeEachWord(answer);
            }
            while (strcmp(answer, "Yes")!=0 && strcmp(answer, "No")!=0 );//iterates until the user enters his(er) decision


            if(strcmp(answer, "Yes")==0)
            {
                //ask to update
                stdTree = updateStudent(temp);
                break;
            }

            break;

        case 3://List	all students
            if(stdTree == NULL)
            {
                printf("\nThere is no students to be listed \n\n");
                break;
            }

            printf("\nLISTING ALL STUDENTS....\n\n");

            SortAll(stdTree, &sorted);//store all the nodes in a tree that is sorted based on the names

            if(sorted == NULL)
                printf("null");

            ListAllStudents(sorted);

            DisposeTree(sorted);
            sorted=NULL;

            break;

        case 4://List	all students from a specific city
            if(stdTree == NULL)
            {
                printf("\nThere is no students to be listed \n\n");
                break;
            }

            printf("\n which city you want to search for: \n");
            strcpy(City, "");
            fgets(City, sizeof(City), stdin);// Read the student's name using fgets to allow reading a line with spaces
            City[strlen(City)-1] = '\0';
            CapitalizeEachWord(City);

            SortByCity(stdTree, &sorted,City);//store all the nodes where their city was entered by the user in a tree that is sorted based on the names

            if(sorted == NULL)
            {
                printf("There is no students in city %s *_*\n", City);
                break;
            }
            printf("\n==>Students in city %s :\n", City);
            ListAllStudents(sorted);

            DisposeTree(sorted);
            sorted=NULL;

            break;

        case 5://List all students in each class

            if(stdTree == NULL)
            {
                printf("\nThere is no students to be listed \n\n");
                break;
            }

            for(int i = 1 ; i < 13 ; i++)//ITERATES over all class id
            {
                SortByClass(stdTree, &sorted,i);//store all the nodes by their class id in a tree that is sorted based on the names

                if(sorted == NULL)
                {
                    printf("there is no students in class %d *_*\n", i);
                    continue;
                }
                printf("\n==>Students in class %d :\n", i);
                ListAllStudents(sorted);
                DisposeTree(sorted);
                sorted=NULL;
            }
            break;

        case 6: //Delete a student

            if(stdTree == NULL)
            {
                printf("there is no students to be deleted \n\n");
                break;
            }

            stdTree = deleteStudent(stdTree);

            break;

        case 7: //Save	all students in	file
            if(stdTree == NULL)
            {
                printf("\nThere is no students to be saved \n\n");
                break;
            }

            printf("\nSAVING ALL STUDENTS....\n\n");

            SortAll(stdTree, &sorted);

            if(sorted == NULL)
                printf("null");

            SaveToFile(sorted);
            DisposeTree(sorted);
            sorted=NULL;

            break;

        case 8://Exit

            DisposeTree(stdTree);

            printf("Thanks for using School Database ^_^\n");
            exit(0);

        default:
            printf("Enter a choice between 1 and 8\n");
        }
    }
    return 0;
}

stdNode* readFile( stdNode*root)
{
    char filename[] = "students.Data";

    FILE* fin = fopen(filename, "r");

    if (fin == NULL) //make sure that the file is opened correctly
    {
        printf("Failed to open file: %s\n", filename);
        return NULL;
    }

    int maxChar = MaxChar(fin);
    fseek(fin, 0, SEEK_SET); // Reset the file pointer to the beginning of the file

    char* line = malloc(maxChar + 2); // Allocate memory for the line ,size of char is 1bit
    if (line == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(0);
    }

    int state = 0;//state to determine what the token is

    while (fgets(line, maxChar + 2, fin) != NULL)   // Read line by line
    {
        int ID=0, classID=0, day=0, month=0, year=0;
        char *Name=NULL, *City=NULL;

        char* token = strtok(line, "#");

        while (token != NULL) //tokenise the line
        {

            if(state == 0)// ID
            {
                ID = checkValidInt(token);
                if (ID < 0)
                {
                    printf("There is an error in the file. Check it.\n");
                    exit(0);
                }
            }
            else if(state == 1) // Name
                Name = strdup(token);

            else if(state == 2)// city
                City = strdup(token);

            else if(state == 3)// Class ID
            {
                classID = checkValidInt(token);
                if (classID < 0)
                {
                    printf("There is an error in the file. Check it.\n");
                    exit(0);
                }
            }
            else if(state == 4) // Date
            {
                getDate(token, &day, &month, &year);
                if (day < 0 || month < 0 || year < 0 )
                {
                    printf("There is an error in the file. Check it.\n");
                    exit(0);
                }
            }
            state ++;
            token = strtok(NULL, "#");
        }

        state = 0;//after finishing the line reset the state

        CapitalizeEachWord(Name);
        CapitalizeEachWord(City);
        root = Insert(ID,Name,City, classID, day, month, year, root);
        free(Name);
        free(City);
    }

    fclose(fin);
    free(line);

    return root;
}

/*
*returns the max number of char in line
*/
int MaxChar(FILE*fin)
{
    char c;
    int chars=0, maxChars=0;

    while ((c = fgetc(fin)) != EOF)//iterates over all the chars in the file
    {
        if(c!='\n')
            chars ++;

        else
        {
            if(chars>maxChars)
                maxChars=chars;

            chars=0;
        }
    }
    if(chars>maxChars)
        maxChars=chars;

    return maxChars;
}

/*
*iterates over the tree by post order
*the free the nodes
*/
stdNode* DisposeTree( stdNode* root )
{
    if( root != NULL )
    {
        DisposeTree( root->Left );
        DisposeTree( root->Right );
        free(root->EnrollmentDate);
        free( root );
    }
    return NULL;
}

/*
*returns the hight of the node
*if the node is null then returns -1
*/
int Height( stdNode* P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}

/*
*returns the max number between two numbers
*/
int Max( int Lhs, int Rhs )
{
    if(Lhs > Rhs)
        return Lhs;

    return Rhs;
}

/*
*iterates over the BST tree
*if the root is founded return it
*else return null
*/
stdNode* FindNode(int id,stdNode*root)
{
    if(root == NULL)
        return NULL;

    else  if (id >root->ID)
        return  FindNode(id,root->Right);

    else if (id <root->ID)
        return FindNode(id,root->Left);

    else
        return root;
}

/*
*Get the balance factor
*/
int getBalance(stdNode *root)
{
    if (root == NULL)
        return 0;
    return Height(root->Left) - Height(root->Right);
}

/*
*This function can be called only if root has a left child
*Perform a rotate between a node (root) and its left child
* Update heights, then return new root (left child)
*/

stdNode* RightSingleRotation( stdNode* K2 )
{
    stdNode* K1;
    K1 = K2->Left;

    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}

/*
*This function can be called only if root has a right child
*Perform a rotate between a node (root) and its right child
*Update heights, then return new root (right child)
*/
stdNode* LeftSingleRotation( stdNode* K1 )
{
    stdNode* K2;
    K2 = K1->Right;

    K1->Right = K2->Left;
    K2->Left = K1;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K2;  // New root
}

/*
*This function can be called only if root has a left
*child and root's left child has a right child
* Do the left-right double rotation
* Update heights, then return new root
*/
stdNode* LeftRightDoubleRotation( stdNode* K3 )
{
    // Rotate between left child and it's right
    K3->Left = LeftSingleRotation( K3->Left );

    // Rotate between root and right of the left
    return RightSingleRotation( K3 );
}

stdNode* RightLeftDoubleRotation( stdNode* K1 )
{
    // Rotate between right child and it's left
    K1->Right = RightSingleRotation( K1->Right );

    // Rotate between root and left of the right
    return LeftSingleRotation( K1 );
}


stdNode* Insert(int id, char* name, char* city,int classid, int d,int m,int y, stdNode* root )
{
    if(root == NULL)
    {
        root = (stdNode*) malloc(sizeof(stdNode));
        if(root == NULL)
        {
            printf("Out Of Memory *_*\n\n");
            exit(0);
        }
        root->ID=id;
        strcpy(root->Name,name);
        strcpy(root->City,city);
        root->classID =classid;

        Date* date = (Date*) malloc(sizeof(Date));

        date->day =d;
        date->month =m;
        date->year =y;

        root->EnrollmentDate = date;

        root->Height=0;
        root ->Left = root ->Right = NULL;
    }

    else if(id < root->ID)
    {
        root->Left = Insert(id, name, city, classid, d, m,y,root->Left );

        if(getBalance(root) > 1 ) //to correct the balance
        {
            if( id < root->Left->ID )//inserted left of the left
                root = RightSingleRotation( root );

            else//inserted right of the left
                root = LeftRightDoubleRotation( root );
        }
    }

    else if(id > root->ID)
    {
        root->Right=Insert(id, name, city, classid, d, m,y,root->Right );

        if( getBalance(root) < -1 )//to correct the balance
        {
            if( id > root->Right->ID )//inserted right of the right
                root = LeftSingleRotation( root );

            else//inserted left of the right
                root = RightLeftDoubleRotation( root );
        }
    }

    else
    {
        printf("student with ID: %d is already exists!\n",id);
        return root;
    }

    root->Height = Max( Height( root->Left ), Height( root->Right ) ) + 1;
    return root;
}


stdNode* InsertByName(int id, char* name, char* city,int classid, int d,int m,int y, stdNode* root )
{
    if(root == NULL)
    {
        root = (stdNode*) malloc(sizeof(stdNode));
        if(root == NULL)
        {
            printf("Out Of Memory *_*\n\n");
            exit(0);
        }
        root->ID=id;
        strcpy(root->Name,name);
        strcpy(root->City,city);
        root->classID =classid;

        Date* date = (Date*) malloc(sizeof(Date));

        date->day =d;
        date->month =m;
        date->year =y;

        root->EnrollmentDate = date;

        root->Height=0;
        root ->Left = root ->Right = NULL;
    }

    else if(strcmp(name, root->Name)<0)
    {
        root->Left = InsertByName(id, name, city, classid, d, m,y,root->Left );

        if( Height( root->Left ) - Height( root->Right ) == 2 )
        {
            if( strcmp(name, root->Left->Name)<0 )

                root = RightSingleRotation( root );
            else
                root = LeftRightDoubleRotation( root );
        }
    }
    else if(strcmp(name, root->Name)>0)
    {
        root->Right=InsertByName(id, name, city, classid, d, m,y,root->Right );

        if( Height( root->Right ) - Height( root->Left ) == 2 )
        {
            if( strcmp(name, root->Right->Name)>0 )
                root = LeftSingleRotation( root );
            else
                root = RightLeftDoubleRotation( root );
        }
    }

    else //if they have the same name insert them by their id
    {
        root = Insert(id, name, city, classid, d, m,y,root);
    }

    root->Height = Max( Height( root->Left ), Height( root->Right ) ) + 1;

    return root;
}

// Delete a nodes
stdNode* Delete(int ID, stdNode *root )
{
    stdNode * tempCell;

    if(root == NULL)
        return root;

    else if( ID > root->ID )
        root->Right =  Delete(ID, root->Right);

    else if( ID < root->ID )
        root->Left =  Delete(ID, root->Left);


    else//if it is found
    {
        if(root->Left && root->Right)
        {
            tempCell = FindMin(root->Right);

            //swap data
            root->ID = tempCell->ID;
            strcpy(root->Name, tempCell->Name);
            strcpy(root->City, tempCell->City);
            root->classID = tempCell->classID;
            root->EnrollmentDate = tempCell->EnrollmentDate;

            root->Right = Delete(root->ID, root->Right);
        }
        else
        {
            tempCell = root;

            if(root->Left == NULL)
                root=root->Right;

            else if(root->Right == NULL)
                root=root->Left;

            free(tempCell);
        }
    }

    if(getBalance(root)>1 && getBalance(root->Left) >= 0)//right rotation
        return RightSingleRotation(root);

    if (getBalance(root) > 1 && getBalance(root->Left) < 0) //left right rotation
        return LeftRightDoubleRotation(root);

    if (getBalance(root) < -1 && getBalance(root->Right) <= 0)//left rotation
        return LeftSingleRotation(root);

    if (getBalance(root) < -1 && getBalance(root->Right) > 0)//right left rotation
        return RightLeftDoubleRotation(root);

    return root;

}

stdNode* FindMin(stdNode*root)
{
    if(root == NULL)
        return NULL;

    else if(root->Left == NULL)
        return root;

    else
        return FindMin(root ->Left);

}

/*
*print all students in in-order
*/
void ListAllStudents( stdNode* root)
{
    if( root != NULL)
    {
        ListAllStudents( root->Left );
        PrintNode(root);
        ListAllStudents( root->Right );
    }
}

/*
*print the attributes of the node in appropriate way
*/
void PrintNode(stdNode* root)
{
    printf(" _______________________________________________________________________________________________________________________\n");
    printf("|ID: %d\t", root->ID);
    printf("Name: %s\t", root->Name);
    printf("City: %s\t", root->City);
    printf("Class: %02d\t", root->classID);
    printf("Date: %02d/", root->EnrollmentDate->day);
    printf("%02d/", root->EnrollmentDate->month);
    printf("%d\n", root->EnrollmentDate->year);
    printf("|_______________________________________________________________________________________________________________________\n");
}

void mainMenu()
{
    printf("\nChoose from the below operations:\n\n");
    printf("1. Insert a student.\n");
    printf("2. Find	a student.\n");
    printf("3. List	all students.\n");
    printf("4. List	all students from a specific city.\n");
    printf("5. List	all students in each class.\n");
    printf("6. Delete a student.\n");
    printf("7. Save	all students in	file.\n");
    printf("8. Exit\n");
}

/*
*iterates over all nodes and insert them in the sorted tree
*/
void SortAll( stdNode* root, stdNode** sorted )
{
    if( root != NULL)
    {
        SortAll( root->Left, sorted );

        *sorted= InsertByName(root->ID, root->Name, root->City, root->classID, root->EnrollmentDate->day, root->EnrollmentDate->month,root->EnrollmentDate->year,*sorted );

        SortAll( root->Right, sorted );
    }
}

/*
*iterates over all nodes and insert them in the sorted tree
*if their class id as sent to the function
*/
void SortByClass( stdNode* root, stdNode** sorted, int classId )
{
    if( root != NULL)
    {
        SortByClass( root->Left, sorted, classId );

        if(root->classID == classId)
            *sorted= InsertByName(root->ID, root->Name, root->City, root->classID, root->EnrollmentDate->day, root->EnrollmentDate->month,root->EnrollmentDate->year,*sorted );

        SortByClass( root->Right, sorted, classId );
    }
}

/*
*iterates over all nodes and insert them in the sorted tree
*if their city as sent to the function
*/
void SortByCity( stdNode* root, stdNode** sorted, char* city )
{
    if( root != NULL)
    {
        SortByCity( root->Left, sorted, city );

        if(strcmp(root->City, city) == 0)
            *sorted= InsertByName(root->ID, root->Name, root->City, root->classID, root->EnrollmentDate->day, root->EnrollmentDate->month,root->EnrollmentDate->year,*sorted );

        SortByCity( root->Right, sorted, city );
    }
}

/*
*ask the user for the attributes to the student to be added
*with enrollment date as the date of the current day
*/
stdNode* insertStudent(stdNode* root)
{
    int ID, classID,day, month, year;
    char Name[nameLength] = "", City[cityLength]="";

    printf("Enter student information:\n");

    printf("\nStudent's ID: ");

    ID = ScanInt(); //get a real integer value
    ID=checkID(ID, root);  //IF ALREADY EXISTS

    printf("\nStudent's Name: ");
    fgets(Name, sizeof(Name), stdin);// Read the student's name using fgets to allow reading a line with spaces
    Name[strlen(Name)-1] = '\0';
    CapitalizeEachWord(Name);

    printf("\nStudent's City: ");
    fgets(City, sizeof(City), stdin);
    City[strlen(City)-1] = '\0';
    CapitalizeEachWord(City);


    printf("\nStudent's Class id:");
    classID = ScanInt();
    while(classID > 12 || classID < 1 )//iterates until the user enters a valid class id
    {
        printf("Class ID must be between 1 and 12 \n");
        printf("\nEnter another Student's Class id:");

        classID = ScanInt();
    }

//get the current date
    time_t currentTime = time(NULL);
    struct tm *localTime=localtime(&currentTime);

    // Extract the year, month, and day components
    year = localTime->tm_year + 1900;  // Year is offset from 1900
    month = localTime->tm_mon + 1;     // Month is zero-based, so add 1
    day = localTime->tm_mday;

    root  =Insert(ID, Name, City, classID, day, month,year,root );

    PrintNode(FindNode(ID,root));  // print the node after adding it

    return root;
}

/*
*make sure that the string starts with a letter
*capitalize the first letter of each word
*make the other letter in the lowercase
*/
void CapitalizeEachWord(char*String)
{
    while(!isalpha(String[0]))
    {
        printf("Make sure that it is starts with a letter , this starts with %c \n Enter it again: ",String[0]);
        scanf("%s",String);
    }

    char capital [strlen(String)];
    strcpy(capital,"");

    char* token = strtok(String, " ");
    while (token != NULL)
    {
        if (islower(token[0]))
            token[0] -=32 ; //make it in uppercase

        for(int i = 1 ; i < strlen(token) ; i++)
        {
            if (isupper(token[i]))
                token[i] +=32 ;//make it in lowercase
        }

        strcat(capital,token);
        strcat(capital," ");

        token = strtok(NULL, " "); // Get the next token
    }
    capital[strlen(capital)-1] = '\0'; //for the last space
    strcpy(String,"");
    strcat(String, capital);
}

/*
*convert a string to its integer value
*is the string contains any char
*it returns -1 o.w. it returns the value
*/
int checkValidInt (char* num)
{
    int number = 0  ;
    for(int i = 0; i <strlen(num); i++) // Iterate through each character in the string
    {

        if(!((num[i]-48)>=0 && (num[i]-48)<=9))// Check if the character is not a digit
            return -1;

        // Calculate  the number
        number= (number* 10)+(num[i]-48);
    }
    return number;
}

/*
*checks if the entered id is already exists
*/
int checkID ( int ID, stdNode* root  )
{
    stdNode* temp;
    temp =  FindNode(ID, root);
    while(temp != NULL)
    {
        printf("\n ID: %d is already exists!!\n ", ID);
        printf("\nEnter another Student's ID: ");

        ID = ScanInt();

        temp =  FindNode(ID, root);
    }

    return ID;
}

/*
*get from the user the id for a student to delete it
*and then delete it if exists
*/
stdNode* deleteStudent(stdNode*root)
{
    int ID;

    printf("\nEnter Student's ID you want to delete: ");

    ID = ScanInt();

    stdNode* temp;
    temp =  FindNode(ID, root);
    if(temp != NULL)
    {
        PrintNode(temp);
        root =  Delete(ID, root);
        printf("was successfully deleted ^_^\n" );
    }
    else
        printf("student with ID: %d does not exists.\n", ID);


    return root;
}

/*
*reads from the user the string
*and iterates until it is valid value
*/
int ScanInt()
{
    char string [intLength];
    int Integer;

    strcpy(string, "");
    fgets(string, sizeof(string), stdin);// Read the student's name using fgets to allow reading a line with spaces
    string[strlen(string)-1] = '\0';

    Integer = checkValidInt(string);//get the value

    while(Integer<0) //ask the  user to enter the num again if it is not a num
    {
        printf("THIS FIELD must be integers !! Enter it again: ");
        strcpy(string,"");
        fgets(string, sizeof(string), stdin);// Read the student's name using fgets to allow reading a line with spaces
        string[strlen(string)-1] = '\0';//the last char is '\n' so make it '\0'
        Integer =checkValidInt(string);
    }
    return Integer;
}

/*
*save the attributes of the node
*delete the node
*for each attribute ask the user if (s)he wants to update it
*insert it with the updated attributes
*/
stdNode* updateStudent(stdNode* root)
{
    int ID = root->ID, classID = root->classID,day = root->EnrollmentDate->day, month = root->EnrollmentDate->month, year = root->EnrollmentDate->year;
    char *Name = "", *City = "" ;

    Name = strdup(root->Name);
    City = strdup(root->City);

    root= Delete(root->ID, root);

    char answer[5],date[15];

    printf("Enter student new information:\n");

    do //iterates until the user enters his(er) decision

    {
        printf("\nDo you want to update the ID? (Answer with yes / no) \n");
        strcpy(answer, "");
        fgets(answer, sizeof(answer), stdin);// Read the student's name using fgets to allow reading a line with spaces
        answer[strlen(answer)-1] = '\0';
        CapitalizeEachWord(answer);
    }
    while (strcmp(answer, "Yes")!=0 && strcmp(answer, "No")!=0 );


    if(strcmp(answer, "Yes")==0)
    {
        printf("\nNew Student's ID: ");
        ID = ScanInt();
        ID=checkID(ID, root);  //IF ALREADY EXISTS
    }


    do//iterates until the user enters his(er) decision
    {
        printf("\nDo you want to update the Name? (Answer with yes / no) \n");
        strcpy(answer, "");
        fgets(answer, sizeof(answer), stdin);// Read the student's name using fgets to allow reading a line with spaces
        answer[strlen(answer)-1] = '\0';
        CapitalizeEachWord(answer);
    }
    while (strcmp(answer, "Yes")!=0 && strcmp(answer, "No")!=0 );


    if(strcmp(answer, "Yes")==0)
    {
        printf("\nNew Student's Name: ");
        fgets(Name, sizeof(Name), stdin);// Read the student's name using fgets to allow reading a line with spaces
        Name[strlen(Name)-1] = '\0';
        CapitalizeEachWord(Name);
    }

    do//iterates until the user enters his(er) decision
    {
        printf("\nDo you want to update the City? (Answer with yes / no) \n");
        strcpy(answer, "");
        fgets(answer, sizeof(answer), stdin);// Read the student's name using fgets to allow reading a line with spaces
        answer[strlen(answer)-1] = '\0';
        CapitalizeEachWord(answer);
    }
    while (strcmp(answer, "Yes")!=0 && strcmp(answer, "No")!=0 );


    if(strcmp(answer, "Yes")==0)
    {
        printf("\nNew Student's City: ");
        fgets(City, sizeof(City), stdin);
        City[strlen(City)-1] = '\0';
        CapitalizeEachWord(City);
    }

    do//iterates until the user enters his(er) decision
    {
        printf("\nDo you want to update the Class ID? (Answer with yes / no) \n");
        strcpy(answer, "");
        fgets(answer, sizeof(answer), stdin);// Read the student's name using fgets to allow reading a line with spaces
        answer[strlen(answer)-1] = '\0';
        CapitalizeEachWord(answer);
    }
    while (strcmp(answer, "Yes")!=0 && strcmp(answer, "No")!=0 );


    if(strcmp(answer, "Yes")==0)
    {

        printf("\nNew Student's Class id:");

        classID = ScanInt();
        if(classID > 12 || classID < 1 )
        {
            printf("Class ID must be between 1 and 12 \n");
            printf("\nEnter another Student's Class id:");

            classID = ScanInt();
        }
    }

    do//iterates until the user enters his(er) decision
    {
        printf("\nDo you want to update the Date Enrollment? (Answer with yes / no) \n");
        strcpy(answer, "");
        fgets(answer, sizeof(answer), stdin);// Read the student's name using fgets to allow reading a line with spaces
        answer[strlen(answer)-1] = '\0';
        CapitalizeEachWord(answer);
    }
    while (strcmp(answer, "Yes")!=0 && strcmp(answer, "No")!=0 );

    if(strcmp(answer, "Yes")==0)
    {
        do//iterates until the user enters a valid date
        {
            printf("\nNew Student's Enrollment Date (dd/mm/yyyy):");
            strcpy(date, "");
            fgets(date, sizeof(date), stdin);

            getDate(date, &day, &month, &year);
        }
        while(!(day != -1 && month != -1 && year!=-1));
    }

    root=Insert(ID, Name, City, classID, day, month,year,root );

    PrintNode(FindNode(ID, root));
    return root;
}

/*
*convert a string with the format dd/mm/yyyy
*to an integer value of each part
*/
void getDate(char* String, int*d, int*m, int*y)
{
    String[strlen(String)-1] = '\0'; //the last char is \n
    char* token= strtok(String, "/");
    int state = 0 ;

    while(token != NULL) //tokenize the string by '/' and iterates untill the token is null
    {

        switch(state++)//at each state this indicates if the token is day or month or year
        {

        case 0: // day
            *d= checkValidInt(token);

            break;

        case 1: // month
            * m= checkValidInt(token);

            break;

        case 2: // year

            * y= checkValidInt(token);
            break;
        }
        token = strtok(NULL, "/"); // Get the next token
    }
}

/*
*opens the file
*call another function to print in it then close the file
*/
void SaveToFile(stdNode *root)
{
    char filename[]="students.Data";
    FILE *fout = fopen(filename, "w");

    if(fout == NULL)
    {
        printf("Cannot open the file*_* \n\n");
        return;
    }

    printToFile(fout, root);

    fclose(fout);
}


/*
*print in the file each node in the tree in in-order in an appropriate way
*/
void printToFile(FILE*fout, stdNode*root)
{
    if(root!=NULL)
    {
        printToFile(fout, root->Left);

        fprintf(fout," _______________________________________________________________________________________________________________________\n");
        fprintf(fout,"|ID: %d\t", root->ID);
        fprintf(fout,"Name: %s\t", root->Name);
        fprintf(fout,"City: %s\t", root->City);
        fprintf(fout,"Class: %02d\t", root->classID);
        fprintf(fout,"Date: %02d/", root->EnrollmentDate->day);
        fprintf(fout,"%02d/", root->EnrollmentDate->month);
        fprintf(fout,"%d\n", root->EnrollmentDate->year);
        fprintf(fout,"|_______________________________________________________________________________________________________________________\n");

        printToFile(fout, root->Right);
    }
}
