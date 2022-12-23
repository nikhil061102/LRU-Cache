//LRU cache implementation using HashTable and Queue(implemented using Double Linked List)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size_of_queue = 0;
int max_cache_size; //will be read from first line of input.txt

struct HashNode{
    char str[1000];
    struct HashNode *next, *prev;
};

struct QNode{
    char str[1000];
    struct QNode *next, *prev;
};

//initializing front and rear node for the queue which will be used as LRU cache
struct QNode *front = NULL;
struct QNode *rear = NULL;

//Hash Function to give unique keys for strings to be stored in hash table
int hashFunc(char string[]){
    int sl = strlen(string);
    
    int sum = 0;
    for(int i = 0 ; i <= sl ; i++){
        sum += (int)((string[i])%7);
    }

    int hashval = sum % max_cache_size;

    return hashval;
}

//Function to insert strings in the Hash Table
void InsertInHashTable(char string[], struct HashNode*table[]){
    int index = hashFunc(string);
    struct HashNode *temp = (struct HashNode *)malloc(sizeof(struct HashNode));

    if(table[index] == NULL){
        strcpy(temp->str,string);
        temp->prev = NULL;                     
        temp->next = NULL;

        table[index]=temp;
    }
    else{
        strcpy(temp->str,string); 
        temp->prev = NULL;
        temp->next = table[index];
        table[index]->prev = temp;
        table[index] = temp;    
    }
}

//Function to search a particular string in Hash Table and if present returns 1, else returns 0 
int SearchInHashTable(char string[],struct HashNode*table[]){    
    int index = hashFunc(string);
    
    struct HashNode* ptr = table[index];
    int flag = 0;
   
    while(ptr != NULL){
        if(strcmp(ptr->str,string) == 0){                                
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }

    return flag;
}

//Function to delete a particular string from Hash Table
void DeleteFromHashTable(char string[],struct HashNode*table[]){           
    int index = hashFunc(string);
    
    struct HashNode *temp = table[index];
    
    while (temp){
        if (strcmp(temp->str, string) == 0){
            break;
        }
        temp = temp->next;
    }

    if (temp == table[index]){
        table[index] = table[index]->next;
        free(temp);
    }

    else if (temp->next == NULL){
        temp = temp->prev;
        temp->next = NULL;
    }

    else{
        struct HashNode *tempaft = temp->next;
        struct HashNode *tempbef = temp->prev;
        tempaft->prev = tempbef;
        tempbef->next = tempaft;
        free(temp);
    }
}

//Function that displays the strings stored in Queue in order from least recently enqueued to most recently enqueued elements
void DisplayQueue(){
    struct QNode *move = front;
    while (move != NULL){
        printf("%s\n", move->str);
         move = move->next;
    }
    printf("\n");
}

//Function to display the contents of Hash Table
//This function was basically made to check if the code is working properly or not
//THIS FUNCTION IS NOT USED ANYWHERE IN THE FUNCTIONING SECTION OF CODE
void DisplayHashTable(struct HashNode* table[]){             
    for(int i = 0 ; i < max_cache_size ; i++){
        printf("Index %d: ",i);
        struct HashNode *ptr = table[i];
        if(ptr != NULL){                      
            printf("%s ",ptr->str);
            while(ptr->next != NULL){
                ptr = ptr->next;
                printf("&& %s ",ptr->str);
            }
        }
        else{
            printf(" - ");            
        }
        printf("\n");
    }
}

//Function that intakes a char string and enqueues it in the queue (which is made from Double Linked List) 
void Enqueue(char string[]){
    struct QNode *temp = (struct QNode *)malloc(sizeof(struct QNode));
    temp->next = NULL;
    temp->prev = NULL;

    strcpy(temp->str,string);
    if (front == NULL){
        front = rear = temp;
    }
    else{
        rear->next = temp;
        temp->prev = rear;
        rear = temp;
    }

    size_of_queue++;
}

//Function that returns char string while dequeuing it from the queue (which is made from Double Linked List)
char *Dequeue(){
    struct QNode *ptr = front;

    if (front != NULL){
        front = front->next;
    }
    front->prev = NULL;

    size_of_queue--; 
    return ptr->str;
}

//This is a specialized function used in specific cases when the element is already present in queue
//This function finds the particular string which is already present in queue and bring it in rear of queue
void BringInRear(char string[]){
    struct QNode *ptr = rear;
    
    while(strcmp(ptr->str,string) != 0){
        ptr = ptr->prev;
    }

    if(ptr != rear){
        struct QNode *befptr = ptr->prev;
        struct QNode *aftptr = ptr->next;
    
        befptr->next = aftptr;
        aftptr->prev = befptr;

        ptr->prev = rear;
        ptr->next = NULL;
        rear->next = ptr;

        rear = ptr;
    }
}

/*
This is the most important function of the code
It takes String and Hash Table as input 
then it checks if the string has already been added or not
If the string is already added then it uses the 'BringInRear' function to put the string at the front of queue
If string is not added then it inserts it into the Hash Table
Now again 2 cases form - either no. of elements in queue has reached max or not
If no. of elements in queue is less than max size of queue then it simply enqueues the string
Else it dequeues the least recently added string and deletes it from Hash Table and enqueues the new string
*/

int CentralFunc(char string[],struct HashNode* table[]){
    if (SearchInHashTable(string,table) == 1){
        BringInRear(string);
    }
    else{
        InsertInHashTable(string,table);
        if (size_of_queue < max_cache_size){
            Enqueue(string);
        }
        else{           
            DeleteFromHashTable(Dequeue(),table);
            Enqueue(string);
        }
    }
}

int main(){
    FILE *in;
    FILE *out;
    
    in = freopen("input.txt", "r",stdin);
    out = freopen("output.txt","w",stdout);
    
    scanf("%d", &max_cache_size);

    if (in == NULL){
        printf("Can not access the file !\n");
        printf("Error opening the file !");
    }
    else
    {
        struct HashNode *HashTable[max_cache_size];
        for (int i = 0; i < max_cache_size; i++){
            HashTable[i] = NULL;
        }
        
        char str[100] = "0";
        int count = 0;
        printf("Note - During the display of queue, the order is least recent to most recent from top to bottom.\n");
    
        while (1){
            scanf("%s", str);
            if (!(str[0] == '-' && str[1] == '1' && str[2] == '\0')){
                count++;
                CentralFunc(str,HashTable);
                printf("-------------------------------------------------------------------------------------------------\n");
                printf("After reading line no. %d\n",count);
                printf("The link is = %s\n",str);
                printf("--------------------------------------------Queue------------------------------------------------\n");
                DisplayQueue();
                //printf("--------------------------------------------HashTable------------------------------------------------\n");
                //DisplayHashTable(HashTable);
            }
            else{
                break;
            }
        }
    }
        printf("-------------------------------------------------------------------------------------------------\n");        
        printf("\n");
        printf("Finally, the Least recently accessed element in cache is: ");
        printf("\n");
        printf("%s", front->str);
        printf("\n");
        printf("Finally, the most recently accessed element in cache is: ");
        printf("\n");
        printf("%s", rear->str);
        
        fclose(in);
        fclose(out);
}