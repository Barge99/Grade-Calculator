#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Component {
    char title[20];
    float weight;
    float maxpoints;
    float earnedpoints;
    struct Component* next;
} Component;

typedef struct student {
    char name[20];
    float grade;
    struct student* next;
    struct Component* corresponding;
} student;

Component* copyComponentList(Component* master) {
    if (!master) return NULL;

    Component* newHead = NULL;
    Component* tail = NULL;

    while (master) {
        Component* newNode = malloc(sizeof(Component));
        strcpy(newNode->title, master->title);
        newNode->weight = master->weight;
        newNode->maxpoints = master->maxpoints;
        newNode->earnedpoints = 0;
        newNode->next = NULL;

        if (!newHead) {
            newHead = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        master = master->next;
    }

    return newHead;
}

int displaymenu() {
    int menuchoice;
do {
    puts("===================================");
    puts("Grade Calculation Program");
    puts("===================================");
    puts("1. Single Student Grades");
    puts("2. multiple Students grades");
    puts("3. Sort students by Grade");
    puts("4. Search for a student");
    puts("5. Exit\n");
    puts("Enter your choice (1/2/3/4/5):");
    scanf(" %d", &menuchoice);

    if(menuchoice < 1 || menuchoice > 5){
        puts("Invalid Input");
    }

    if(menuchoice == 5) {
        puts("The program will now exit");
        exit(0);
    }

}while(menuchoice < 1 || menuchoice > 5);
    
    return menuchoice;
}

Component* createcomplist(int menuchoice) {
    int stop = 1;
    int count = 0;
    int valid = 1;
    int totalweight = 0;

    Component* Previous;
    struct Component* llhead = (Component*)malloc(sizeof(Component));
    llhead->next = NULL;

    while(stop == 1 && totalweight<100 ) {
        
        if(count == 0) {
            puts("Please enter the title of the first course component:");
            scanf("%s",llhead->title);

            while(valid == 1) {
            puts("Please enter the weight of the first course component(1-100):");
            scanf("%f",&llhead->weight);
            
            if(llhead->weight >= 1 && llhead->weight <= 100) {
                valid = 0;
                totalweight = totalweight + llhead->weight;
            } else {
                puts("Invalid input must be between 0 and 100");
            }
            }
            valid = 1;
            
            while(valid == 1) {
            puts("Please enter the max points of the first course component:");
            scanf("%f",&llhead->maxpoints);
            
             if(llhead->maxpoints > 1) {
                valid = 0;
            } else {
                puts("Invalid input must be greater than 0");
            }
            }
            valid = 1;
            Previous = llhead;
            count = 1;
                
                
                puts("\nWould you like to create another component?\nYes = 1\nNo = 0");
                scanf("%d",&stop);
        }
        
        if(count > 0 && stop == 1 && totalweight<100) {
        struct Component* newNode = (Component*)malloc(sizeof(Component));
        newNode->next = NULL;

        puts("\n\n--------------------------------------------------------------");
        puts("Please enter the title of the next course component:");
        scanf("%s",newNode->title);

        while(valid == 1) {
        puts("Please enter the weight of the next course component:");
        scanf("%f",&newNode->weight);
        if(newNode->weight >= 1 && newNode->weight <= 100) {
            valid = 0;
            totalweight = totalweight + newNode->weight;
        } else {
            puts("Invalid input must be between 0 and 100");
        }
        }
        valid = 1;

        while(valid == 1) {
        puts("Please enter the max points of the next course component:");
        scanf("%f",&newNode->maxpoints);

        if(newNode->maxpoints > 1) {
            
            valid = 0;
        } else {
            puts("Invalid input must be greater than 0");
        }
        }
        valid = 1;
        
        Previous->next = newNode;
        Previous = newNode;
        
        count+=1;

        puts("\nWould you like to create another component?\nYes = 1\nNo = 0");
                scanf("%d",&stop);
        
    }
    if(totalweight < 100) {
        
        Component* cleanup = llhead;
    while (cleanup != NULL) {
        Component* temp = cleanup;
        cleanup = cleanup->next;
        free(temp);
    }

    return createcomplist(menuchoice);
        
    }
    return llhead;
}
}

student* createstudlist(int menuchoice,Component* master) {
    int stop = 1;
    int count = 0;
    int valid = 1;
    Component *current;
    student* Previous;

    struct student* llhead = (student*)malloc(sizeof(student));
    llhead->next = NULL;

    while(stop == 1) {
        
        if(count == 0) {
            puts("Please enter the name of the first student:");
            scanf("%s",llhead->name);

            current = copyComponentList(master);
            
            llhead->corresponding = current;
            Component* comp = current;

            while(comp != NULL) {

                while(valid == 1) {
                printf("Enter score for %s:", comp->title);
                scanf("%f", &comp->earnedpoints);
                
                if(comp->earnedpoints >= 0 && comp->earnedpoints <= comp->maxpoints) {
                    valid = 0;
                } else {
                    puts("Invalid input must be at least zero");
                }
                }
                valid = 1;
                comp = comp->next;
            }
            count += 1;
                Previous = llhead;
                if(menuchoice == 1) {
                    stop = 0;
                }
                
        }
        if(count > 0 && menuchoice == 2 || menuchoice == 3 || menuchoice == 4) {
            struct student* newNode = (student*)malloc(sizeof(student));
            newNode->next = NULL;
            
            puts("\nPlease enter the name of the next student:");
            scanf("%s",newNode->name);
            
            current = copyComponentList(master);
            
            Previous->next = newNode;
            newNode->corresponding = current;
            Component* comp = current;

            while(comp != NULL) {

                while(valid == 1) {
                printf("Enter score for %s:", comp->title);
                scanf("%f", &comp->earnedpoints);
                
                if(comp->earnedpoints >= 0 && comp->earnedpoints <= comp->maxpoints) {
                    valid = 0;
                } else {
                    puts("Invalid input must be at least zero");
                }
                }
                valid = 1;
                comp = comp->next;

            }

            count+=1;
        
        if(count>1) {
            Previous = newNode;
        }

        puts("Would you like to create another student?\nYes = 1\nNo = 0");
        scanf("%d",&stop);
        }
    }

    return llhead;
}

const char *lettergrade(float final) {

    final = round(final);
    
    if(final <= 49) {
        return "F";
    }
    else if(final <=59 && final >=50) {
        return "D";
    }
    else if(final <=64 && final >=60) {
        return "C";
    }
    else if(final <=69 && final >=65) {
        return "C+";
    }
    else if(final <=74 && final >=70) {
        return "B";
    }
    else if(final <=79 && final >=75) {
        return "B+";
    }
    else if(final <=84 && final >=80) {
        return "A-";
    }
    else if(final <=89 && final >=85) {
        return "A";
    }
    else if(final <=100 && final >=90) {
        return "A+";
    }
    else {
        return "Invalid Grade";
    }

}

void calculategrade(Component *comphead, student *stuhead) {
    student* currentstud = stuhead;
    
    int count = 0;
    
    while(currentstud != NULL) {
        
        float earnedscore = 0;
        float maxpoints = 0;
        float weight = 0;
        Component* currentcomp = currentstud->corresponding;
        
        while(currentcomp != NULL) {

                earnedscore = earnedscore + currentcomp->earnedpoints;
                maxpoints = maxpoints + currentcomp->maxpoints;
                weight = weight + currentcomp->weight;
                
                currentcomp = currentcomp->next;
                
        }
        currentstud->grade = ((earnedscore / maxpoints) * (weight / 100))*100;
        count = 1;

        currentstud = currentstud->next;
        
    }
}

void sortgrades(student *head) {
        
    int swapped;
    student* ptr1;
    student* lptr = NULL;

    if (head == NULL) return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->grade < ptr1->next->grade) {
                
                float tempGrade = ptr1->grade;
                ptr1->grade = ptr1->next->grade;
                ptr1->next->grade = tempGrade;

                char tempName[50];
                strcpy(tempName, ptr1->name);
                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->next->name, tempName);

                
                Component* tempList = ptr1->corresponding;
                ptr1->corresponding = ptr1->next->corresponding;
                ptr1->next->corresponding = tempList;

                swapped = 1;
            }

            ptr1 = ptr1->next;
        }

        lptr = ptr1;
    } while (swapped);
}

void studentsearch(student *stuhead) {
    char name[20];
    student* current = stuhead;
    int count = 0;

        puts("Please enter the name of the student you're looking for");
        scanf("%s",name);

        while(current != NULL) {
            if(strcmp(current->name, name) == 0) {
                printf("%s was found in list\n",name);
                printf("Grade: %.2f\n",current->grade);
                printf("Letter grade: %s",lettergrade(current->grade));
                count +=1;
                return;
            }
            current = current->next;
        }
        if(count = 0) {
            puts("Student no found");
}
}

int compareFloats(const void* a, const void* b) {
    float fa = *(const float*)a;
    float fb = *(const float*)b;
    return (fa > fb) - (fa < fb);
}

void printlist(student* head, const char* letter, int menuchoice) {
    struct student* current = head;
    int place = 1;

    if (menuchoice == 1 || menuchoice == 2) {
        while (current != NULL) {
            printf("\n%s:\nGrade:%.2f\nLetter Grade:%s", current->name, current->grade, lettergrade(current->grade));
            current = current->next;
        }

        if (menuchoice == 2) {
            int count = 0;
            float total = 0;
            float max = 0;
            char maxName[50];

            current = head;
            while (current != NULL) {
                if (count == 0 || current->grade > max) {
                    max = current->grade;
                    strcpy(maxName, current->name);
                }
                total += current->grade;
                count++;
                current = current->next;
            }

            if (count > 0) {
                float* grades = malloc(count * sizeof(float));
                current = head;
                for (int i = 0; i < count; i++) {
                    grades[i] = current->grade;
                    current = current->next;
                }

                qsort(grades, count, sizeof(float), compareFloats);

                float median;
                if (count % 2 == 1) {
                    median = grades[count / 2];
                } else {
                    median = (grades[count / 2 - 1] + grades[count / 2]) / 2.0f;
                }

                float average = total / count;

                printf("\n\n Grade Statistics:\n");
                printf("- Maximum: %.2f (%s)\n", max, maxName);
                printf("- Average: %.2f\n", average);
                printf("- Median : %.2f\n", median);

                free(grades);
            }
        }

    } else if (menuchoice == 3) {
        while (current != NULL) {
            printf("%d.%s\nGrade:%.2f\n", place, current->name, current->grade);
            current = current->next;
            place += 1;
        }
    }
}

void freeComponentList(Component* head) {
    Component* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freeStudentList(student* head) {
    student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;

        freeComponentList(temp->corresponding);

        free(temp);
    }
}

int main() {
    int menuchoice;

    menuchoice = displaymenu();

    Component* masterlisthead = createcomplist(menuchoice);
    student* stuhead = NULL;
    Component* comphead = NULL;

    switch(menuchoice) {

        case 1:
        comphead = masterlisthead;
        stuhead = createstudlist(menuchoice, comphead);
        calculategrade(comphead,stuhead);
        const char* letter = lettergrade(stuhead->grade);
        
        printlist(stuhead,letter,menuchoice); 

        freeComponentList(comphead);
        freeStudentList(stuhead);
        break;

        case 2:
        comphead = masterlisthead;
        stuhead = createstudlist(menuchoice, comphead);
        letter = lettergrade(stuhead->grade);
        calculategrade(comphead,stuhead); 
        
        printlist(stuhead,letter,menuchoice);

        break;

        case 3:
        comphead = masterlisthead;
        stuhead = createstudlist(menuchoice, comphead);
        
        calculategrade(comphead,stuhead);
        
        sortgrades(stuhead);
        
        printlist(stuhead,letter,menuchoice);
        
        break;

        case 4:
        comphead = masterlisthead;
        stuhead = createstudlist(menuchoice, comphead);
        calculategrade(comphead,stuhead);

        studentsearch(stuhead);

        break;
    }
}