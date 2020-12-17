#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct Node {
    int contactkey;
    char firstname[50];
    char lastname[50];
    char phone[50];
    char email[50];
    struct Node * next;
} node;

//note: key generator will be max_key(list) + 1

int checksize(node* head);
void printitem(node* head, int index);
int add_contact(node * head, char * firstname, char * lastname, char * phone, char * email);
int search_contacts(node* head);
node* delete_contact(node* head);
int importcontacts(node * head, char* fname);
int updatecontact(node* T);
void printListA(node * head);
void savecontacts(node * head, char fname[]);
void exportcontacts(node * head);
void exitprogramme(node * head);



int checksize(node* head){     //returns the size of the current linked list(number of nodes)
    int count = 1;
    node* tmp = head;
    while(tmp->next != NULL){
        tmp = tmp->next;
        count ++;
    }
    return count;

}

void printitem(node* head, int index){
                                           //prints a node of the linked list with the desired index 
    int count = 0;
    node* tmp = head;
    while(count < index){
        tmp = tmp->next;
        count++;
    }
    printf("%10d %20s %20s %20s %30s \n", tmp->contactkey, tmp->firstname, tmp->lastname, tmp->phone, tmp->email);
}

// ------------------------------------------------------------------------------------------------------------------------

int add_contact(node * head, char * firstname, char * lastname, char * phone, char * email) {
    // VALIDATE INPUT
    
    // check lengths of all inputs
    if(strlen(firstname) > 50){
        printf("first name is too long");
        return 0;
    }

    if(strlen(lastname) > 50) {
        printf("last name is too long");
        return 0;
    }

    if(strlen(phone) > 8) {
        printf("phone number is too long");
        return 0;
    }

    if(strlen(email) > 50) {
        printf("email is too long");
        return 0;
    }


    // validate firstname (loop through string to check if all chars are letters via ASCII)
    for (int i = 0; i < strlen(firstname); i++){
        int temp = (int)firstname[i];
        if(temp < 65 || (temp > 90 && temp < 97) || temp > 122) {
            printf("First name includes a non-letter character");
            return 0;
        }
    }


    // validate lastname (loop through string to check if all chars are letters via ASCII)
    for (int i = 0; i < strlen(lastname); i++){
        int temp = (int)lastname[i];
        if(temp < 65 || (temp > 90 && temp < 97) || temp > 122) {
            printf("First name includes a non-letter character");
            return 0;
        }
    }

    // check if phone numbers are 8 digits
    if(strlen(phone) < 8) {
        printf("\n phone number is too short");
        return 0;
    }

    if(strlen(phone) > 8) {
        printf("\n phone number is too long");
        return 0;
    }

    // check if email contains @
    int emailflag = 0;
    for (int i = 0; i < strlen(email); i++){
        if(email[i] == '@') {
            emailflag = 1;
        }
    }

    if(emailflag != 1){
        printf("email does not contain @");
        return 0;
    }

    // ADD CONTACT TO LINKEDLIST
    if(head == NULL){
        head->contactkey = 1;
        strcpy(head->firstname, firstname);
        strcpy(head->lastname, lastname);
        strcpy(head->phone, phone);
        strcpy(head->email, email);
        head->next = NULL;
    }
    else {
        int listsize = 0;
        int curr_largest_contactkey = 0;

        node * prev = head;
        while (head != NULL) {
            if(head->contactkey > curr_largest_contactkey){
                curr_largest_contactkey = head->contactkey;
            }

            prev = head;
            head = head->next;
            listsize++;
        }
        if(listsize >= 500){
            printf("Contact list is full");
            return 0;
        }
        
        node * newnode = (struct Node*)malloc(sizeof(struct Node)); 
        prev->next = newnode;

        newnode->contactkey = curr_largest_contactkey + 1;
        strcpy(newnode->firstname, firstname);
        strcpy(newnode->lastname, lastname);
        strcpy(newnode->phone, phone);
        strcpy(newnode->email, email);
        newnode->next = NULL;
    }

    
    return 1;
}


node* delete_contact(node * head){
    if (head == NULL){
        printf("Contact list is empty");
        return head;
    }
    else {
        int delete_key;
        printf("Enter key to delete in contact list: ");
        scanf("%d", &delete_key);

        // in case node to be deleted is actually head
        if(head->contactkey == delete_key){
            head = head->next;
            printf("Success to delete. \n");
            return head;
        }
        else{
            node * cur = head;
            node * prev = cur;
            while(cur != NULL){
                if(cur->contactkey == delete_key){
                    prev->next = cur->next; // skip head
                    printf("Success to delete. \n");
                    return head;
                }
                prev = cur;
                cur = cur->next;
            }
            // traversed through the linked list, no match for delete_key.
            printf("No such contact \n");
            return head;
        }
    }
}


int importcontacts(node * head, char* fname){  

    FILE *f1;
    f1 = fopen(fname, "r");
    
    if (f1 == NULL){
        fclose(f1);
        return 0;
    }
    
    int ck;
    char fn[50], ln[50], phn[50], em[50];
    fscanf(f1, "%d %s %s %s %s", &ck, fn, ln, phn, em);
    head->contactkey = ck;
    strcpy(head->firstname, fn);
    strcpy(head->lastname, ln);
    strcpy(head->phone, phn);
    strcpy(head->email, em);
    head->next = NULL;
    node* cur = head;
    node* newnode;
    
    while(fscanf(f1, "%d %s %s %s %s", &ck, fn, ln, phn, em)!=EOF){
        newnode = (node*)malloc(sizeof(node));
        newnode->contactkey = ck;
        strcpy(newnode->firstname, fn);
        strcpy(newnode->lastname, ln);
        strcpy(newnode->phone, phn);
        strcpy(newnode->email, em);
        newnode->next = NULL;
        cur->next = newnode;
        cur = cur->next;    
    }
    return 1;

}


void printListA(node * head) {                              //prints the existing linked list in alphabetical order
       int n = checksize(head);
       printf("size = %d \n", n);
       char firstnames[n][50];
       node* tmp = head;
       
       for (int i = 0; i < n; i ++){
           strcpy(firstnames[i], tmp->firstname);
           tmp = tmp->next;
       }
       
       char word[50];
       
        for (int i = 0; i<n; i++){
            strcpy(word, firstnames[i]);
            for(int j=0; j<strlen(word); j++){          //convert string to lowercase for sort algorithm                                  
                if (word[j] < 97){                     //allows names to contain upper and lowercase letters and still be sorted
                    word[j] += 32;
                }                  
            }
            strcpy(firstnames[i], word);
        }
    int indices[500];
    for(int i=0; i<n; i++){                           //these indices will be rearranged based on existing order of linked list
        indices[i]= i;
    }

    int tmp0;
    char tmp1[50];
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n-i-1;j++){         
            if (strcmp(firstnames[j], firstnames[j+1]) >0){
                tmp0 = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = tmp0;
                strcpy(tmp1,firstnames[j]);
                strcpy(firstnames[j], firstnames[j+1]);
                strcpy(firstnames[j+1], tmp1);
            }
        } 
    }
    printf("        ID            FirstName            LastName               Number                          Email \n");

    for(int i=0; i<n; i++){                            //print elements from linked list based on order of indices
        printitem(head, indices[i]);
    }
    
}
void savecontacts(node * head, char fname[]){
    FILE * f1;
    f1 = fopen(fname, "w");
    while (!feof(f1)){
        if(f1 == NULL){
            printf("Sorry, that file name is unavailable, please try again.");
            exportcontacts(head);
        }
        else{
            while(head != NULL)
            {
                fprintf(f1, "%d %s %s %s %s\n", head->contactkey, head->firstname, head->lastname, head->phone, head->email);
                head = head->next;
            }
            break;
        }
    }
    fclose(f1);
}

void exportcontacts(node * head){
    char fname[300];
    int i;
    printf("Enter a name for your file of your choice:\n");
    scanf("%s", fname);
    for(i = 0; i < 100; i++)
        fname[i] = tolower(fname[i]); // might want to add a feature that appends ".txt" in case the user forgot to include it in his input
    savecontacts(head, fname);
}

void exitprogramme(node * head){
    savecontacts(head, "latest.txt");
    exit(1);
}

// ------------------------------------------------------------------------------------------------------------------------

int search_contacts(node * head){
    int globalflag = 0; // used to check whether even 1 search hit is detected
    char search_str[50];
    // get search_str from user
    printf("Please enter string to search within contact list: ");
    scanf("%s", search_str);   
    node * res_head = (struct Node*)malloc(sizeof(struct Node)); 
    while (head != NULL){
        int flag = 0;
        // convert head->contactkey to str
        char contactkey_str[10001];
        sprintf(contactkey_str, "%d", head->contactkey);
        // search fields inside each contact
        if(strstr(contactkey_str, search_str)){
            flag = 1;
        }
        if(strstr(head->firstname, search_str)){
            flag = 1;
        }
        if(strstr(head->lastname, search_str)){
            flag = 1;
        }
        if(strstr(head->phone, search_str)){
            flag = 1;
        }
        if(strstr(head->email, search_str)){
            flag = 1;
        }

        // if flag == 1, print this node
        if(flag == 1){
            globalflag = 1;
            printf("%10d %20s %20s %20s %30s \n", head->contactkey, head->firstname, head->lastname, head->phone, head->email);
        }

        head = head->next;
    }
    return globalflag;
} 

int updatecontact(node * head){
    int update_key;
    char update_firstname[50];
    char update_lastname[50];
    char update_phone[50];
    char update_email[50];
    int flag;
    node * originalhead = head;
    node * prev = head;

    printf("Enter contact key to update: ");
    scanf("%d", &update_key);

    // ask for input, then validate
    do {

        printf("\n Enter updated firstname: ");
        scanf("%s", update_firstname);

        if(strlen(update_firstname) > 50){
            printf("\n updated first name is too long");
            flag = 0;
            continue;
        }

        printf("\n Enter updated lastname: ");
        scanf("%s", update_lastname);
        if(strlen(update_lastname) > 50) {
            printf("\n last name is too long");
            flag = 0;
            continue;
        }

        printf("\n Enter phone: ");
        scanf("%s", update_phone);
        if(strlen(update_phone) < 8) {
            printf("\n updated phone number is too short");
            flag = 0;
            continue;
        }

        if(strlen(update_phone) > 8) {
            printf("\n updated phone number is too long");
            flag = 0;
            continue;
        }

        printf("\n Enter email: ");
        scanf("%s", update_email);
        if(strlen(update_email) > 50) {
            printf("\n updated email is too long");
            flag = 0;
            continue;
        }
        // check if email contains @
        int emailflag = 0;
        for (int i = 0; i < strlen(update_email); i++){
            if(update_email[i] == '@') {
                emailflag = 1;
            }
        }
        if (emailflag != 1){
            printf("\n updated email has no @");
            flag = 0;
            continue;
        }
            
        flag = 1;
    } while (flag != 1);


    while(head != NULL){
        if(head->contactkey == update_key){
            strcpy(head->firstname, update_firstname);
            strcpy(head->lastname, update_lastname);
            strcpy(head->phone, update_phone);
            strcpy(head->email, update_email);
            printf("Updated successfully. \n");
            return 1;
        }

        head = head->next;
    }
    printf("No such contact. \n");
    return 0;
}


int main() {
    // initialize local contacts database (basically linked list)
    node * head = NULL;
    
    //Initialize 5 dummy linked list nodes for the sake of easier testing
    head = (struct Node*)malloc(sizeof(struct Node)); 
    node * second = (struct Node*)malloc(sizeof(struct Node)); 
    node * third = (struct Node*)malloc(sizeof(struct Node)); 
    node * fourth = (struct Node*)malloc(sizeof(struct Node));
  
    head->contactkey = 1;
    strcpy(head->firstname, "kevin");
    strcpy(head->lastname, "boi");
    strcpy(head->phone, "55351696");
    strcpy(head->email, "kevinboi@gmail.com");
    head->next = second; 
  
    second->contactkey = 2; 
    strcpy(second->firstname, "gautham");
    strcpy(second->lastname, "boi");
    strcpy(second->phone, "23498786");
    strcpy(second->email, "gauthamboi@gmail.com");
    second->next = third;
	  
    third->contactkey = 3; 
    strcpy(third->firstname, "rick");
    strcpy(third->lastname, "boi");
    strcpy(third->phone, "23413456");
    strcpy(third->email, "rickboi@gmail.com");
    third->next = fourth;

    fourth->contactkey = 4; 
    strcpy(fourth->firstname, "leslie");
    strcpy(fourth->lastname, "boi");
    strcpy(fourth->phone, "77413456");
    strcpy(fourth->email, "leslieboi@gmail.com");
    fourth->next = NULL;

    importcontacts(head, "contacts.txt");
    printf("%d Contacts loaded from contacts.txt \n", checksize(head));
    while(1){

        int option;
        printf("\n \n \n \n ==========Menu========== \n");
        printf("1 - Add a contact \n");
        printf("2 - Delete a contact \n");
        printf("3 - Update a contact \n");
        printf("4 - Search contacts \n");
        printf("5 - Import from file\n");
        printf("6 - Export to file \n");
        printf("7 - View all contacts \n");
        printf("0 -  Exit \n");
        printf("Please enter your option:");

        scanf("%d", &option);
        
        switch(option){

            case 1:
                printf("ADD CONTACT SELECTED. \n");
                char firstname[50];
                char lastname[50];
                char phone[50];
                char email[50];
                int flag;

                do {

                    printf("\n Enter firstname: ");
                    scanf("%s", firstname);

                    if(strlen(firstname) > 50){
                        printf("\n first name is too long");
                        flag = 0;
                        continue;
                    }

                    printf("\n Enter lastname: ");
                    scanf("%s", lastname);
                    if(strlen(lastname) > 50) {
                        printf("\n last name is too long");
                        flag = 0;
                        continue;
                    }

                    printf("\n Enter phone: ");
                    scanf("%s", phone);
                    if(strlen(phone) < 8) {
                        printf("\n phone number is too short");
                        flag = 0;
                        continue;
                    }

                    if(strlen(phone) > 8) {
                        printf("\n phone number is too long");
                        flag = 0;
                        continue;
                    }

                    printf("\n Enter email: ");
                    scanf("%s", email);
                    if(strlen(email) > 50) {
                        printf("\n email is too long");
                        flag = 0;
                        continue;
                    }

                    flag = add_contact(head, firstname, lastname, phone, email);
                } while (flag != 1);
            break;

            case 2:
            head = delete_contact(head);
            break;

            case 3:
            updatecontact(head);
            break;

            case 4:
            search_contacts(head);
            break;

             case 5:
             printf("Please enter name of file to be imported:");      //imports contacts from a file and replaces the existing linked list
             char filename[50];
            scanf("%s", filename);
            int a = importcontacts(head, filename);
            if(a){
                 printf("Load successful! \n");
            }
             break;

             case 6:
             exportcontacts(head);
             break;

             case 7:
             printListA(head);
             break;

            case 0:
            exitprogramme(head);
            break;

            default:
            printf("Error! Invalid input. Press ENTER to return to main menu. \n");
            getchar();
            getchar();
        }
    }
    
    printf("\n");
    printListA(head);
    return 0;
}	
