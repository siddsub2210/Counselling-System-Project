#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

struct preference{
    char college[50];
    char branch[50];
    char dept[50];
};

struct student{
    char name[50];
    int id;
    char password[50];
    float mains_percentile;
    float advanced_percentile;
    int n_pref;
    struct preference preferences[11];
    int assigned_seat;
};
typedef struct student student;

typedef struct{
    char college[10];
    char branch[20];
    char dept[10];
    int assigned_to;
}seat;

void randomArr (int n, student arr[n] );
int read_ranklist(char filename[100],int n, student arr_mains[n]);
int assign_seats(int n, student arr_mains[n],student arr_advanced[n], student students[n], int n_seats, seat arr_seats[n_seats]);
int admin_inputs(int *n_seats, char *filename, seat arr_seats[]);
int obtain_int(char*string);
void output_data(int n, student students[n], int n_seats, seat arr_seats[n_seats]);
void preference_add(int *n, student students[]);
void delete_student(int *n, student students[]);


int main(){
    FILE *file_temp;
    file_temp = fopen("C:\\Shyam\\Cprogramming\\project\\ranklists\\MAINS_RANKLIST_FINAL_csvmsdos_text.txt", "r");
    int n=0;
    for (char ch = fgetc(file_temp); ch != EOF; ch = fgetc(file_temp)){
        if (ch == '\n')  n++;
    }n--;
    fclose(file_temp);
    printf("There are %d students\n\n", n);
    int n_seats, response;
    FILE *fptr;
    FILE *file;
    FILE *f1, *f2;
    char line[50], m_filename[200], a_filename[200];
    seat arr_seats[n];
    student arr_mains[250];
    student arr_advanced[250];
    student students[250];
    int FLAG = 0;
    char password[50];
    int id;

    printf("This is a menu driven counselling system\n1. Admin details\n2. Retrieve student result\n3. Add a new student\n4. Update seats results(after adding student)\n5. Delete a student\n0. Terminate the system\n");
    do{
        printf("\nEnter 1(Admin) or 2(student login) or 3(add new student) or 4(update seat allocation results) or 5(Delete a student) or 0(to terminate): ");
        scanf("%d", &response);
    }while (response!=0 && response!=1 && response!=2 && response!= 3 && response!= 4  && response!= 5);


    while (response!=0){
        switch(response){
            case 0:
                break;
            case 1:
                getchar();
                printf("\n\nProceeding to admin drive side...\n");
                strcpy(m_filename, "C:\\Shyam\\Cprogramming\\project\\ranklists\\MAINS_RANKLIST_FINAL_csvmsdos_text.txt");
                strcpy(a_filename, "C:\\Shyam\\Cprogramming\\project\\ranklists\\ADVANCED_RANKLIST_FINAL_csvmsdos_text.txt");
                read_ranklist(a_filename, n, arr_advanced);
                read_ranklist(a_filename, n, arr_mains);
                read_ranklist(m_filename, n, students);
                randomArr(n, students);
                admin_inputs(&n_seats, "C:\\Shyam\\Cprogramming\\project\\admin_details.txt", arr_seats);
                printf("\nAll admin data restored Sucessfully.\n");
                assign_seats(250, arr_mains, arr_advanced, students, n_seats, arr_seats);
                printf("\nAdmin gets to see all seat assignment details.\n");
                output_data(n, students, n_seats, arr_seats);
                printf("\nResults stored in the files visit this file location to view the files: \nC:\\Shyam\\Cprogramming\\project\\assigned_results.txt\nC:\\Shyam\\Cprogramming\\project\\unassigned_results.txt\n");
                do{
                    printf("\nEnter 1(Admin) or 2(student login) or 3(add new student) or 4(update seat allocation results) or 5(Delete a student) or 0(to terminate): ");
                    scanf("%d", &response);
                }while (response!=0 && response!=1 && response!=2 && response!= 3 && response!= 4  && response!= 5);
                break;
            case 2:
                f1 = fopen(m_filename, "r");
                f2 = fopen(a_filename, "r");
                int flag2=0;
                if (f1!=NULL && f2!=NULL){
                    printf("\n\nEnter student ID: ");
                    scanf("%d", &id);
                    printf("Enter password to login: ");
                    scanf("%s", password);
                    for (int i=0; i<250; i++){
                        if (id==students[i].id){
                            if (strcmp(password, students[i].password)==0){
                                printf("______________________________\nLogged in Successfuly\n");
                                printf("Name: %s\n", students[i].name);
                                printf("ID: %d\n", students[i].id);
                                printf("Mains Percentile: %f\n", students[i].mains_percentile);
                                printf("Advanced Percentile: %f\n", students[i].advanced_percentile);
                                if (students[i].assigned_seat==-1) printf("No seat assigned.\n______________________________\n");
                                else printf("Seat details: %s, %s, %s\n______________________________\n", arr_seats[students[i].assigned_seat].college, arr_seats[students[i].assigned_seat].branch, arr_seats[students[i].assigned_seat].dept);
                                flag2=1;
                                break;
                            }
                        }
                    }
                    if (flag2==0) printf("Incorrect login credentials.\n");
                }
                else{
                    printf("\n\nAdmin must give file inputs, then only student can view.\n");
                }
                do{
                    printf("\nEnter 1(Admin) or 2(student login) or 3(add new student) or 4(update seat allocation results) or 5(Delete a student) or 0(to terminate): ");
                    scanf("%d", &response);
                }while (response!=0 && response!=1 && response!=2 && response!= 3 && response!= 4  && response!= 5);
                break;
            case 3:
                f1 = fopen(m_filename, "r");
                f2 = fopen(a_filename, "r");
                if (f1!=NULL && f2!= NULL){
                    preference_add(&n, students);
                }
                else{
                    printf("\n\nAdmin must give file inputs, then only student can be added.\n");
                }
                do{
                    printf("\nEnter 1(Admin) or 2(student login) or 3(add new student) or 4(update seat allocation results) or 5(Delete a student) or 0(to terminate): ");
                    scanf("%d", &response);
                }while (response!=0 && response!=1 && response!=2 && response!= 3 && response!= 4  && response!= 5);
                break;
            case 4:
                f1 = fopen(m_filename, "r");
                f2 = fopen(a_filename, "r");
                if (f1!=NULL && f2!= NULL){
                    assign_seats(n, arr_mains, arr_advanced, students, n_seats, arr_seats);
                    output_data(n, students, n_seats, arr_seats);
                    printf("The seats are successfully allocated!\n");
                    printf("To see all results, you need admin access (1).\n");
                    printf("Otherwise, you can login as a student (2) to see your results\n");
                }
                else{
                    printf("\n\nAdmin must give file inputs, then only student can be added.\n");
                }
                do{
                    printf("\nEnter 1(Admin) or 2(student login) or 3(add new student) or 4(update seat allocation results) or 5(Delete a student) or 0(to terminate): ");
                    scanf("%d", &response);
                }while (response!=0 && response!=1 && response!=2 && response!= 3 && response!= 4  && response!= 5);
                break;
            case 5:
                f1 = fopen(m_filename, "r");
                f2 = fopen(a_filename, "r");
                if (f1!=NULL && f2!= NULL){
                    delete_student(&n, students);
                }
                else{
                    printf("\n\nAdmin must give file inputs, then only student can be added.\n");
                }
                do{
                    printf("\nEnter 1(Admin) or 2(student login) or 3(add new student) or 4(update seat allocation results) or 5(Delete a student) or 0(to terminate): ");
                    scanf("%d", &response);
                }while (response!=0 && response!=1 && response!=2 && response!= 3 && response!= 4  && response!= 5);
                break;
            // case 6:
            //     f1 = fopen(m_filename, "r");
            //     f2 = fopen(a_filename, "r");
            //     if (f1!=NULL && f2!= NULL){
            //         printf("value of n is %d\n", n);
            //         edit_preference(n, students);
            //     }
            //     else{
            //         printf("\n\nAdmin must give file inputs, then only student can be added.\n");
            //     }
            //     do{
            //         printf("\nEnter 1(Admin) or 2(student login) or 3(add new student) or 4(update seat allocation results) or 5(Delete a student) or 6(Update preferences) or 0(to terminate): ");
            //         scanf("%d", &response);
            //     }while (response!=0 && response!=1 && response!=2 && response!= 3 && response!= 4  && response!= 5 && response!= 6);
            //     break;
        }

    }
    printf("\n\nTERMINATING SYSTEM...\n");
    
    return 0;
}


int read_ranklist(char filename[200],int n, struct student arr_mains[n]){
    FILE *file;
    file = fopen(filename, "r");
    int row=0, i=0;
    char pref1[30], pref2[30], pref3[30];
    char buffer[1000];
    char pref_arr[n*10][30];
    char temp[30];
    int index_temp=0;
    while (fgets(buffer, 1000, file)){
        buffer [ strcspn (buffer, "\n")] = 0;
        int field_count =0;
        row++;
        if (row==1) continue;
        char *field = strtok(buffer, ",");
        while(field!= NULL){
            int length =0;
            while(*(field+length)!='\0'){
                temp[length] = *(field+length);
                length++;
            }
            temp[length] = '\0';

            if (field_count==0){
                strcpy(arr_mains[i].name, temp);
            }
            else if (field_count==1){
                arr_mains[i].id =  atoi(temp);
            }
            else if (field_count==2){
                strcpy(arr_mains[i].password, temp);
            }
            else if (field_count==3){
                arr_mains[i].mains_percentile= atof(temp);
            }
            else if (field_count==4){
                arr_mains[i].advanced_percentile = atof(temp);
            }
            else if (field_count==5){
                arr_mains[i].n_pref = atoi(temp);
            }
            else{
                strcpy(pref_arr[index_temp], temp);
                index_temp++;
            }
            field = strtok(NULL, ",");
            field_count++;
        }
        arr_mains[i].assigned_seat = -1;
        i++;

    }    
    int index=0;
    struct preference pref;
    for (int i=0; i<n; i++){
        for (int j=0; j<arr_mains[i].n_pref; j++){
            if (strcmp(arr_mains[i].name, "")==0) continue;
            char *token_temp = strtok(pref_arr[index], "_");
            int length=0;
            while(*(token_temp+length)!='\0'){
                temp[length] = *(token_temp+length);
                length++;
            }
            temp[length] = '\0';
            strcpy(pref.college , temp);
            token_temp = strtok(NULL, "_");
            length=0;
            while(*(token_temp+length)!='\0'){
                temp[length] = *(token_temp+length);
                length++;
            }
            temp[length] = '\0';
            strcpy(pref.branch , temp);
            token_temp = strtok(NULL, "_");
            length=0;
            while(*(token_temp+length)!='\0'){
                temp[length] = *(token_temp+length);
                length++;
            }
            temp[length] = '\0';
            strcpy(pref.dept , temp);
            arr_mains[i].preferences[j] = pref;
            arr_mains[i].assigned_seat = -1;
            index++;
        }
    }
    
    
    fclose(file);
    return 0;
}

int assign_seats(int n, student arr_mains[n], student arr_advanced[n], student students[n], int n_seats, seat arr_seats[n_seats]){
    int freecount =n_seats;  //number of free seats
    int i=0;   //counter for loop
    student stud;
    int breaker=0;
    while (1){
        int OVERALL_FLAG =0;
        for(int x=0;x<n;x++){
            OVERALL_FLAG=0;
            stud = students[i];   //random student
           
            if (stud.assigned_seat==-1/* && strcmp(students[i].name,"")!=0*/){
                //one by one go to all preferences of colleges that the student has
                //iterate through the three preferences
                for (int j=0; j<stud.n_pref && stud.assigned_seat==-1; j++){
                    struct preference pref;
                    strcpy(pref.college, stud.preferences[j].college);
                    strcpy(pref.branch,  stud.preferences[j].branch);
                    strcpy(pref.dept, stud.preferences[j].dept);
                    // if preference is IIT, but student didnt write jee adv, go to next preference
                    if (strcmp(pref.college, "IIT")==0 && stud.advanced_percentile==-1) continue;

                    int flag=0;
                    int index=0;
                    for (int k=0; k<n_seats && flag==0 ; k++){
                        if (arr_seats[k].assigned_to==-1 && strcmp(arr_seats[k].college, pref.college)==0 && strcmp(arr_seats[k].branch, pref.branch)==0 && strcmp(arr_seats[k].dept, pref.dept)==0){
                            index = k;
                            flag = 1;      //an empty seat is found, i.e,  girl to get engaged
                            break;
                        }
                    }
                    if (flag==1){   // case where empty seat in the department is already available
                        //the two are engaged
                        stud.assigned_seat = index;
                        //also assign man to the particular woman
                        arr_seats[index].assigned_to = i;   //ith man in the men's list
                        students[i] = stud;
                        OVERALL_FLAG=1;
                        freecount--;
                    }
                    else{    //case where all seats in that department are filled, so iterate again by checking rank and assign accordingly.
                        //in that preference pref of stud, currently no seats are available.
                        int flag1 = 0;
                        int l=0;
                        while (stud.assigned_seat==-1){
                            if (strcmp(arr_seats[l].college, pref.college)==0 && strcmp(arr_seats[l].branch, pref.branch)==0 && strcmp(arr_seats[l].dept, pref.dept)==0){
                                int index1 = arr_seats[l].assigned_to;  //obtained index for already engaged student
                                student stud1 = students[index1];
                                //we must check if new student is more preferred than current student
                                //for IITs, preferance is through arr_advanced[n] and for NITs, preferance is through arr_mains[n] ranklists respectively
                                if (strcmp(pref.college, "IIT")==0){
                                    //now comparing jee adv ranks for stud and stud1
                                    if (stud.advanced_percentile > stud1.advanced_percentile){
                                        //new student has higher rank
                                        arr_seats[l].assigned_to = i;
                                        stud.assigned_seat = l;
                                        //make previous student free
                                        students[index1].assigned_seat = -1;
                                        students[i] = stud;
                                        OVERALL_FLAG=1;
                                        break;
                                    }
                                    else{
                                        //new student has lower rank than current student
                                        //go to next seat with same department
                                    }
                                }
                                else if (strcmp(pref.college, "NIT")==0){
                                    //preferance is NIT
                                    //now comparing jee mains ranks for stud and stud1
                                    if (stud.mains_percentile > stud1.mains_percentile){
                                        //new student has higher rank
                                        arr_seats[l].assigned_to = i;
                                        stud.assigned_seat = l;
                                        //make previous student free
                                        students[index1].assigned_seat = -1;
                                        students[i] = stud;
                                        OVERALL_FLAG=1;
                                        break;
                                    }
                                    else{
                                        //new student has lower rank than current student
                                        //go to next seat with same department
                                    }
                                }
                            }
                            l++;
                            //arr_seats has only index from 0 to n_seats-1
                            if (l==n_seats) break;
                            //to prevent index error
                        }
                    }
                    if (j==2 && stud.assigned_seat==-1) break;
                }
            }
            else{
                i++;
                if (i==n) i=0;   //wrap around the students array back to index 0.
                continue;
            }
            i++;
        if (i==n) i=0;     //wrap around the students array back to index 0.
    }
    if (OVERALL_FLAG==0){
        breaker++;
        if (breaker == 1000){
            break;
        }
    }
    }
}

void randomArr (int n, student arr[n] ) {           //generate random array element
   srand (time(NULL)); 
   student temp;                //use time to get different seed value to start
   for (int i = n-1; i > 0; i--) {
      int j = rand() % (i+1);           //randomly choose an index from 0 to i
      temp = arr[i];            //swap current element with element placed in jth location
      arr[i] = arr[j];
      arr[j] = temp;
   }
}

int admin_inputs(int *n_seats, char *filename, seat arr_seats[]){
    FILE *file;
    char line[50], temp_branch[10], temp_dept[10];
    int n_IIT, n_NIT, num;
    file = fopen(filename, "r");
    char arr_dept[4][10] = {"CSE", "IT", "ECE", "EEE"};
    if (file==NULL){
        printf("Since the file does not exist, creating a new file\n");
        fclose(file);
        file = fopen(filename, "w");
        printf("Enter the total number of IIT seats: ");
        scanf("%d", &n_IIT);
        printf("Enter the number of IIT branches : ");
        int i_branches;
        scanf("%d", &i_branches);
        printf("Enter the total number of NIT seats: ");
        scanf("%d", &n_NIT);
        printf("Enter the number of NIT branches : ");
        int n_branches;
        scanf("%d", &n_branches);
        fprintf(file ,"Number of IITs: %d\n", (n_IIT));
        fprintf(file ,"Number of NITs: %d\n", (n_NIT));
        *n_seats = n_IIT+n_NIT;
        fprintf(file, "Total number of seats: %d\n", *n_seats);
        fprintf(file, "IIT DETAILS:\n");
        printf("Enter the IIT details: \n\n");
        for (int i=0; i<i_branches; i++){
            printf("Enter the branch:  ");
            scanf("%s", temp_branch);
            fprintf(file, "---------%s---------\n", temp_branch);
            for (int j=0; j<4; j++){
                printf("Enter the number of %s seats: ", arr_dept[j]);
                scanf("%d", &num);
                fprintf(file, "%s:%d\n",arr_dept[j], num);
            }
            printf("\n");
        }
    
        printf("\nEnter the NIT details: \n\n");
        fprintf(file, "NIT DETAILS:\n");
        for (int i=0; i<n_branches; i++){
            printf("Enter the branch:  ");
            scanf("%s", temp_branch);
            fprintf(file, "---------%s---------\n", temp_branch);
            for (int j=0; j<4; j++){
                printf("Enter the number of %s seats: ", arr_dept[j]);
                scanf("%d", &num);
                fprintf(file, "%s:%d\n",arr_dept[j], num);
            }
            printf("\n");
        }
        fclose(file);
        file = fopen(filename, "r");
    }
    fgets(line, sizeof(line), file);
    n_IIT = obtain_int(line);
    fgets(line, sizeof(line), file);
    n_NIT = obtain_int(line);
    fgets(line, sizeof(line), file);
    *n_seats = obtain_int(line);
    int index=0;
    char branch_temp[20];
    while (!feof(file)){
        fgets(line, sizeof(line), file);
        line[ strcspn (line, "\n")] = 0;

        if (line[0]!='-'){
            if ((strncmp(line, "IIT ", 3)==0)||(strncmp(line, "NIT ", 3)==0)) continue;
            num = obtain_int(line);
            char dept_temp[20];
            int m=0;
            for (int p=0; line[p]!=':'; p++){
                dept_temp[m] = line[p];
                m++;
            }dept_temp[m] = '\0';

            for (int k=0; k<num; k++){
                if (index+1>n_IIT) strcpy(arr_seats[index].college, "NIT");
                else strcpy(arr_seats[index].college, "IIT");
                strcpy(arr_seats[index].branch, branch_temp);
                strcpy(arr_seats[index].dept, dept_temp);
                arr_seats[index].assigned_to = -1;
                index++;
                
            }
        }
        else{
            int l=0;
            for (int i=9; line[i]!='-'; i++){
                branch_temp[l] = line[i];
                l++;
            }branch_temp[l] = '\0';
        }
    }
    return 0;
}

int obtain_int(char*string){
    int count=0;
    for (int i=0; i<string[i]!='\0'; i++){
        if (isdigit(string[i])) count++;
    }
    char s2[count];
    int index=0;
    for (int i=0; i<i<string[i]!='\0'; i++){
        if (isdigit(string[i])){
            s2[index] = string[i];
            index++;
        }
    }
    return atoi(s2);
}

void output_data(int n, student students[n], int n_seats, seat arr_seats[n_seats]){
    FILE *file1, *file2;
    file1 = fopen("C:\\Shyam\\Cprogramming\\project\\assigned_results.txt", "w");
    fprintf(file1, "ASSIGNED SEAT DETAILS:\n__________________________________________\n");
    printf("");
    for (int i=0; i<n; i++){
        if (students[i].assigned_seat!=-1&& strcmp(students[i].name,"")!=0){
            fprintf(file1, "Name: %s\n", students[i].name);
            fprintf(file1, "ID: %d\n", students[i].id);
            fprintf(file1, "Mains Percentile: %f\n", students[i].mains_percentile);
            fprintf(file1, "Advanced Percentile: %f\n", students[i].advanced_percentile);
            fprintf(file1, "Assigned seat: %s, %s, %s\n", arr_seats[students[i].assigned_seat].college, arr_seats[students[i].assigned_seat].branch, arr_seats[students[i].assigned_seat].dept);
            fprintf(file1, "__________________________________________\n");
        }
    }
    fclose(file1);
    file2 = fopen("C:\\Shyam\\Cprogramming\\project\\unassigned_results.txt", "w");
    fprintf(file2, "UNASSIGNED SEAT DETAILS:\n__________________________________________\n");
    for (int i=0; i<n; i++){
        if (students[i].assigned_seat==-1 && strcmp(students[i].name,"")!=0){
            fprintf(file2, "Name: %s\n", students[i].name);
            fprintf(file2, "ID: %d\n", students[i].id);
            fprintf(file2, "Mains Percentile: %f\n", students[i].mains_percentile);
            fprintf(file2, "Advanced Percentile: %f\n", students[i].advanced_percentile);
            fprintf(file2, "Assigned seat: NO SEAT ASSIGNED\n");
            fprintf(file2, "__________________________________________\n");
        }
    }   
    fclose(file2);
}

void preference_add(int *n, student students[]){
    FILE *f1,*f2;
    f1=fopen("C:\\Shyam\\Cprogramming\\project\\ranklists\\ADVANCED_RANKLIST_FINAL_csvmsdos_text.txt","a");
    f2=fopen("C:\\Shyam\\Cprogramming\\project\\ranklists\\MAINS_RANKLIST_FINAL_csvmsdos_text.txt","a");
    printf("\n\nEnter student name: ");
    char name[50];
    scanf("%s",name);
    printf("Enter student ID: ");
    int idx;
    scanf("%d",&idx);
    int flag=1;
    for (int i=0; i<*n; i++){
        if (idx==students[i].id) flag=0;
    }
    while (flag==0){
        printf("ID already exists. Enter again : ");
        scanf("%d",&idx);
        flag=1;
        for (int i=0; i<*n; i++){
            if (idx==students[i].id) flag=0;
        }
    }
    getchar();
    printf("Enter the password: ");
    char password[50];
    scanf("%s",password);
    float m_p;
    printf("Enter student's mains percentile: ");
    scanf("%f",&m_p);
    float a_p;
    printf("Enter the student's advanced percentile: ");
    scanf("%f",&a_p);
    int no_pref;
    printf("Enter the no.of preferences: ");
    scanf("%d",&no_pref);
    fprintf(f1,"%s,%d,%s,%f,%f,%d,",name,idx,password,m_p,a_p,no_pref);
    fprintf(f2,"%s,%d,%s,%f,%f,%d,",name,idx,password,m_p,a_p,no_pref);
    (*n )++;
    students[(*n)-1].n_pref = no_pref;
    strcpy(students[ (*n) -1].name, name);
    students[ (*n) -1].id = idx;
    strcpy(students[ (*n) -1].password, password);
    students[ (*n) -1].mains_percentile = m_p;
    students[ (*n) -1].advanced_percentile = a_p;

    for(int i=0;i<no_pref-1;i++){
        printf("Enter %d preference: ",i+1);
        char pref[100];
        scanf("%s",pref);


        int flag=1;       //case when preference is IIT, but student did not write JEE advanced.
        if (students[(*n)-1].advanced_percentile==-1 && strncmp(pref, "IIT ", 3)==0){
            flag=0;
        }
        while (flag==0){
            printf("\nYou did not write JEE advanced, but gave preference as %s. You can only enter NIT preferences.\n", pref);
            printf("Enter preference : ");
            scanf("%s",pref);
            flag=1;
            if (students[(*n)-1].advanced_percentile==-1 && strncmp(pref, "IIT ", 3)==0){
            flag=0;
            }  
        }

        char *token = strtok(pref, ",");
        int index=0;
        char temp[100];
        while (*(token+index)!='\0'){
            temp[index] = *(token+index);
            index++;
        }temp[index] = '\0';
        token = strtok(NULL, ",");
        token = strtok(pref, ",");
        index=0;
        while (token[index]!='\0'){
            temp[index] = *(token+index);
            index++;
        }temp[index] = '\0';
        strcpy(students[ *n -1].preferences[i].branch, temp);
        token = strtok(NULL, ",");
        token = strtok(pref, ",");
        index=0;
        while (*(token+index)!='\0'){
            temp[index] = *(token+index);
            index++;
        }temp[index] = '\0';
        strcpy(students[ *n -1].preferences[i].dept, temp);
        fprintf(f1,"%s,",pref);
        fprintf(f2,"%s,",pref);

    }
    char pref2[100];
    printf("Enter %d preference: ",no_pref);
    scanf("%s",pref2);
    flag=1;       //case when preference is IIT, but student did not write JEE advanced.
    if (students[(*n)-1].advanced_percentile==-1 && strncmp(pref2, "IIT ", 3)==0){
        flag=0;
    }
    while (flag==0){
        printf("\nYou did not write JEE advanced, but gave preference as %s. You can only enter NIT preferences.\n", pref2);
        printf("Enter preference : ");
        scanf("%s",pref2);
        flag=1;
        if (students[(*n)-1].advanced_percentile==-1 && strncmp(pref2, "IIT ", 3)==0){
            flag=0;
        }  
    }
    char *token = strtok(pref2, ",");
    int index=0;
    char temp[100];
    while (*(token+index)!='\0'){
        temp[index] = *(token+index);
        index++;
    }temp[index] = '\0';
    token = strtok(NULL, ",");
    token = strtok(pref2, ",");
    index=0;
    while (*(token+index)!='\0'){
        temp[index] = *(token+index);
        index++;
    }temp[index] = '\0';
    strcpy(students[ (*n) -1].preferences[no_pref-1].branch, temp);
    token = strtok(NULL, ",");
    token = strtok(pref2, ",");
    index=0;
    while (*(token+index)!='\0'){
        temp[index] = *(token+index);
        index++;
    }temp[index] = '\0';
    strcpy(students[ (*n) -1].preferences[no_pref-1].dept, temp);
    fprintf(f1,"%s\n",pref2);
    fprintf(f2,"%s\n",pref2);
    fclose(f1);
    fclose(f2);
    students[ (*n) -1].assigned_seat = -1;
}

void delete_student(int *n, student students[]){
    printf("\nEnter student ID to remove : ");
    int idx, index;
    scanf("%d", &idx);
    int flag=0;
    for (int i=0; i< 250; i++){
        if (idx == students[i].id){
            flag =1;
            index = i;
            break;
        }
    }
    while (flag==0){
        printf("The ID that you entered is not found. Enter again : ");
        scanf("%d", &idx);
        flag=0;
        for (int i=0; i< 250; i++){
            if (idx == students[i].id){
                flag =1;
                index =i;
                break;
            }
        }
    }
    student null_student;
    students[index] = students[(*n)-1];
    students[(*n)-1] = null_student;
    (*n)--;
    FILE *f1, *f2;
    f1=fopen("C:\\Shyam\\Cprogramming\\project\\ranklists\\ADVANCED_RANKLIST_FINAL_csvmsdos_text.txt","w");
    f2=fopen("C:\\Shyam\\Cprogramming\\project\\ranklists\\MAINS_RANKLIST_FINAL_csvmsdos_text.txt","w");
    fprintf(f1,"Name,ID,Password,Mains Percentile,Advanced Percentile,No. Preferences,Pref 1,Pref 2,Pref 3,Pref 4,Pref 5,Pref 6,Pref 7,Pref 8,Pref 9,Pref 10\n");
    fprintf(f2,"Name,ID,Password,Mains Percentile,Advanced Percentile,No. Preferences,Pref 1,Pref 2,Pref 3,Pref 4,Pref 5,Pref 6,Pref 7,Pref 8,Pref 9,Pref 10\n");
    for (int i=0; i< *n; i++){
        fprintf(f1,"%s,%d,%s,%f,%f,%d,",students[i].name,students[i].id,students[i].password,students[i].mains_percentile,students[i].advanced_percentile,students[i].n_pref);
        fprintf(f2,"%s,%d,%s,%f,%f,%d,",students[i].name,students[i].id,students[i].password,students[i].mains_percentile,students[i].advanced_percentile,students[i].n_pref);
        for(int j=0;j<students[i].n_pref-1;j++){
            fprintf(f1, "%s_%s_%s,", students[i].preferences[j].college, students[i].preferences[j].branch, students[i].preferences[j].dept);
            fprintf(f2, "%s_%s_%s,", students[i].preferences[j].college, students[i].preferences[j].branch, students[i].preferences[j].dept);
        }
        fprintf(f1, "%s_%s_%s\n", students[i].preferences[students[i].n_pref-1].college, students[i].preferences[students[i].n_pref-1].branch, students[i].preferences[students[i].n_pref-1].dept);
        fprintf(f2, "%s_%s_%s\n", students[i].preferences[students[i].n_pref-1].college, students[i].preferences[students[i].n_pref-1].branch, students[i].preferences[students[i].n_pref-1].dept);
    }
    fclose(f1);
    fclose(f2);
    printf("Successfully removed.\n");
}
