/******************************************************************************
written by: Robert Arentzen @ University of Illinois Springfield
raren3@uis.edu

Date: 12/06/2019

*******************************************************************************/

#include <stdio.h>

//declare required procedures
void man_wants_to_enter();
void woman_wants_to_enter();
void man_leaves();
void woman_leaves();

//declare procedures for queue
void enqueue(char gender);
void dequeue(char gender);

    //queue initialization
    char queue[50];
    int front_of_line_index = 0;
    int line_insertion_index = 0;
    int people_in_line = 0;
    
    //synch variables
    int menPresent = 0;
    int womenPresent = 0;
    int isEmpty = 1;
    
    //people in bathroom counters
    int menInBathroom = 0;
    int womenInBathroom = 0;
    
    //a cycle will be defined as succesful entry into the bathroom or the queue, or when
    //a person exits the bathroom.  A person who is waiting in the queue and enters once
    //the bathroom becomes available will not count against the cycle again.
    int cycle = 0;


//begin main
int main() {  
    int choice;
    
    while(cycle<20) {
        
        //*************************************************************************
        //status display for all the states required (here to line 62)
        
        printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
        printf("Status of Bathroom: \nCycle = %d \n" ,cycle);
        printf("State of bathroom = ");
        if(menPresent == 1) {
            printf("Men are present in bathroom. ");
            printf("# of men in the bathroom = %d \n\n" ,menInBathroom);
        }
        if(womenPresent == 1) {
            printf("Women are present in bathroom. ");
            printf("# of women in the bathroom = %d \n\n" ,womenInBathroom);
        }
        if(isEmpty == 1) {
            printf("Bathroom is empty. \n\n");
        }
        printf("Status of queue: \n");
        
        if(people_in_line>0) {
            printf("The queue is occupied and looks like this (front of line starts at left): \n\n");
            for (int i = front_of_line_index; i<50; i++) {
                if (queue[i] == 'M') {
                    printf(" M ");
                }
                else if (queue[i] == 'F') {
                    printf(" F ");
                }
            }
            printf("\n\n");
        }
        else {
            printf("Queue is empty. \n\n");
        }
        
        //end of status display********************************************************
        
        //choice menu
        printf("************ UIS Bathroom ************\n\nPlease select from the following menu:\n\n");
        printf("1. Man wants to enter\n2. Woman wants to enter\n3. Man leaves\n4. Woman leaves\n");
        printf("Enter your choice (1-4) : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                man_wants_to_enter();
                break;
            case 2:
                woman_wants_to_enter();
                break;
            case 3:
                man_leaves();
                break;
            case 4:
                woman_leaves();
                break;
            default:
                printf("Please select a number between 1 & 4\n");
                break;
        }//end switch
        //end choice menu
        
    }//end while loop
    printf("20 cycles have executed... Program terminated \n");
    
    return 0;
}//end main




/***********************************************************
 *             REQUIRED PROCEDURES                         *
 * ********************************************************/
 
void man_wants_to_enter() {
    //if the bathroom is empty and no one is in line, man can enter
    if (isEmpty == 1 && people_in_line == 0) {
        isEmpty = 0;
        menPresent = 1;
        menInBathroom++;
    }
    //if men are already in the bathroom and no one is in line, man can enter
    else if (menPresent == 1 && people_in_line == 0) {
        menInBathroom++;
    }
    //if men are in bathroom and there are people in line, logically there must be 
    //a woman waiting so man enters queue
    else if (menPresent == 1 && people_in_line > 0) {
        enqueue('M');
    }
    //if women are in the bathroom, man enters queue
    else if (womenPresent == 1) {
        enqueue('M');
    }
    //successful entry into line or into queue so cycle is incremented
    cycle++;
}



void woman_wants_to_enter() {
    //if bathroom is empty and no one is in line, woman can enter
    if (isEmpty == 1 && people_in_line == 0) {
        isEmpty = 0;
        womenPresent = 1;
        womenInBathroom++;
    }
    //if women are in bathroom and no one is in line, woman can enter
    else if (womenPresent == 1 && people_in_line == 0) {
        womenInBathroom++;
    }
    //if women are in the bathroom but people are in line, logically a man must be waiting in line, so woman
    //enter the queue
    else if (womenPresent == 1 && people_in_line > 0) {
        enqueue('F');
    }
    //if men are in the bathroom, woman enters queue
    else if (menPresent == 1) {
        enqueue('F');
    }
    cycle++;
}




void man_leaves() {
    //error catch, --cycle counters the ++cycle at the end of the procedure to avoid
    //counting an invalid exit
    if (menInBathroom <= 0) {
        --cycle;
        printf("\n\n**ERROR**  There aren't any men in the bathroom right now.  **ERROR**  \n\n");
    }
    //if 1 man is in bathroom and leaves, set states to correct value to represent empty bathroom
    else if (menInBathroom == 1) {
        menPresent = 0;
        isEmpty = 1;
        menInBathroom--;
        printf("\n\nMan leaves.\n\n");
    }
    //if more than 1 man is in bathroom and 1 leaves, simply decrement # in bathroom
    else if (menInBathroom > 1) {
        menInBathroom--;
        printf("\n\nMan leaves.\n\n");
    }
    //this code checks the queue once the bathroom is emptied.  It allows the next gender into the bathroom
    //depending on position in line. If multiple people of same gender are next, they will all be allowed in
    if (isEmpty == 1 && people_in_line > 0) {
        while (queue[front_of_line_index] == 'F') {
            womenPresent = 1;
            womenInBathroom++;
            people_in_line--;
            front_of_line_index++;
            isEmpty = 0;
            printf ("\n\n**The bathroom was either empty or had a woman inside, and\n the next person in line was a woman, so she entered**\n\n");
        }
    }
    cycle++;
}




void woman_leaves() {
    //error catch, --cycle counters the ++cycle at the end of the procedure to avoid
    //counting an invalid exit
    if (womenInBathroom <= 0) {
        --cycle;
        printf("\n\n**ERROR**  There aren't any women in the bathroom right now.  **ERROR**  \n\n");
    }
    //if 1 woman is in bathroom and leaves, set states to correct value to represent empty bathroom
    else if (womenInBathroom == 1) {
        womenPresent = 0;
        isEmpty = 1;
        womenInBathroom--;
        printf("\n\nWoman leaves.\n\n");
    }
    //if more than 1 woman is in bathroom and 1 leaves, simply decrement # in bathroom
    else if (womenInBathroom > 1) {
        womenInBathroom--;
        printf("\n\nWoman leaves.\n\n");
    }
    //this code checks the queue once the bathroom is emptied.  It allows the next gender into the bathroom
    //depending on position in line. If multiple people of same gender are next, they will all be allowed in
    if (isEmpty == 1 && people_in_line > 0) {
        while (queue[front_of_line_index] == 'M') {
            menPresent = 1;
            menInBathroom++;
            people_in_line--;
            front_of_line_index++;
            isEmpty = 0;
            printf ("\n\n**The bathroom was either empty or had a man inside, and\n the next person in line was a man, so he entered**\n\n");
        }
    }
    cycle++;
}

/****************************************************************
 *                 QUEUE PROCEDURES                             *
 * *************************************************************/
void enqueue(char gender) {
    queue[line_insertion_index] = gender;
    line_insertion_index++;
    people_in_line++;
}

void dequeue(char gender) {
    front_of_line_index++;
    people_in_line--;
}

//END PROGRAM
