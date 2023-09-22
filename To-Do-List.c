#include <stdio.h>
#include <string.h>
struct data {
	int ID;
	char title[20];
	char description[150];
	int day;
	int month;
	int year;
	char status[20];
};
int AT = 0; /* ALL  TASKS structures */

struct data tasks[50];




void addtask(int HM) {									/* add tasks function */
	for (int i = AT; i < AT + HM; i++) {
		printf("Title : ");
		scanf(" %[^\n]", tasks[i].title);
		printf("Description : ");
		scanf(" %[^\n]", tasks[i].description);
		printf("Deadline like this (DD/MM/YYYY) : ");
		scanf("%d/%d/%d", &tasks[i].day, &tasks[i].month, &tasks[i].year);
		printf("Status: \n");
		printf("enter 1 for (to do) \n");
		printf("enter 2 for (in progress) \n");
		printf("enter 3 for (completed) \n");

		int statusCase;
		scanf("%d", &statusCase);
		switch (statusCase) {
		    	case 1:
		    	strcpy(tasks[i].status, "to do");
		    	break;
		    	case 2:
		    	strcpy(tasks[i].status, "in progress");
		    	break;
		    	case 3:
		    	strcpy(tasks[i].status, "done");
		    	break;
		   	default:
			printf("status not valid !\n");
			break;
    			}
		tasks[i].ID = i + 1;
	}
		AT = AT + HM;
}






void modifytasks (int id) { 							 /* modify function */
	for (int i = 0; i < AT; i++) {
		if (tasks[i].ID == id) {
                printf("Enter a Number to ->\n");
                printf("1: To Edit the description of a task.\n");
                printf("2: To Change the status of a task.\n");
                printf("3: To Change the deadline for a task.\n");
                printf("0: To go Back to the Menu.\n");
		int m;
		scanf("%d", &m);
		switch (m) {
			case 1:
			printf("enter new description: ");
			char  nd[150]; /* new description */
			scanf(" %[^\n]", nd);
			strcpy(tasks[i].description, nd);
			break;

			case 2:
			printf("enter the new status: \n");
        	        printf("1: to do \n");
	                printf("2: in progress \n");
	                printf("3: completed \n");
			int ns; /* new status */
			scanf("%d", &ns);
			switch (ns) {
				case 1:
                     	        strcpy(tasks[i].status, "to do");
                                break;
                                case 2:
                                strcpy(tasks[i].status, "in progress");
                                break;
                                case 3:
                                strcpy(tasks[i].status, "done");
                                break;
                                default:
                                printf("status not valid !\n");
                                break;
			}
			case 3: /* new deadline */
			printf("enter the new deadline (DD/MM/YYY) : ");
			int day, month, year;
			scanf("%d/%d/%d", &day, &month, &year);
	                tasks[i].day = day;
			tasks[i].month = month;
			tasks[i].year = year;
			break;

                	default:
                  	printf("Option not valid!\n");
                   	break;
			}
		}
	}

}






void sorttasks () { 								 /* sort  tasks by title function */
        struct data sort;
        for (int i = 0; i < AT - 1; i++) {
                for (int j = 0; j < AT - i - 1; j++) {
                        if (strcmp(tasks[j].title, tasks[j + 1].title) > 0) {
                                sort = tasks[j];
                                tasks[j] = tasks[j + 1];
                                tasks[j + 1] = sort;
                        }
                }
        }
}




int deletedTasks = 0; /* int that count the deleted tasks */

void deleteTask (int idd) {							/* deleting a task function */
	for (int i = 0; i < AT; i++) {
		if (tasks[i].ID == idd && idd != 1){
			tasks[i].ID = -tasks[i].ID;
                        deletedTasks = deletedTasks + 1;
			if (tasks[i].ID == 1) {
				tasks[i].ID = 0;
			        deletedTasks = deletedTasks + 1;
			}
		}
	}
}




void SearchByID (int id) {							 /* Search for Tasks by ID function */
        for (int i = 0; i < AT; i++) {
                if (tasks[i].ID == id) {
			printf("ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n", tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
		}
	}
}




void SearchByTitle (const char ts[20]) {					/* search for tasks by title function */
        for (int i = 0; i < AT; i++) {
                        if (strcmp(tasks[i].title, ts) == 0) {
                                printf(" ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n", tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
                        }
        }
}




int main() {
while (1) {
	printf("<< ToDo List Menu >>\n");
	printf("Enter a Number To -> \n");
	printf("1: To Add a New Task. \n");
	printf("2: To Add Multiple New Tasks. \n");
	printf("3: To Display the List of All Tasks. \n");
	printf("4: To Modify a Task. \n");
	printf("5: To Delete a Task by ID. \n");
	printf("6: To Search for Tasks. \n");
	printf("7: To Statistics. \n");
	printf("0: To Exit. \n");
	printf("I choose : ");
	int x;
	scanf("%d", &x);
	int exit1 = 0;
	int exit2 = 0;
	int exit3 = 0;
	int a;

	switch (x) {
		/* 1) Add a New Task */
		case 1:
		a = 1;
		addtask(a);
		printf("\n\n");
		break;

		/* 2) To Add Multiple New Tasks */
		case 2:
		printf("How Many Tasks you Want to Add ? : ");
	        scanf("%d", &a);
		addtask(a);
                printf("\n\n");
		break;

		/* 3) Display the List of All Tasks */
		case 3:
                printf("Enter a Number to ->\n");
		printf("1: To Sort tasks alphabetically.\n");
                printf("2: To Sort tasks by deadline.\n");
                printf("3: To Display tasks with a deadline within the next 3 days.\n");
                printf("I choose : ");
		int displayCases;
		scanf("%d", &displayCases);

		switch (displayCases) {
			/*Display 1 -> Sort tasks alphabetically*/
			case 1:
			sorttasks();
			for (int i = 0; i < AT; i++) {
				if (tasks[i].ID > 0) {
					printf("ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n", tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
				}
			}
			break;

			/*Display 2 ->  Sort tasks by deadline */
			case 2:
			break;

			/* Display 3 -> Display tasks with a deadline within the next 3 days */
			case 3:
			break;
		}
                printf("\n\n");
		break;

		/* 4) Modify a Task */
		case 4:
                printf("What task you want to modify ? (enter the task's ID) : ");
                int id;
                scanf("%d", &id);
		modifytasks(id);
                printf("task modified ! \n");
		break;

		/* 5) Delete a Task by ID */
		case 5:
		printf("enter the ID of the task you wanna delete : ");
		int did;
		scanf("%d", &did);
		deleteTask(did);
                printf("task deleted !\n");
		break;

		/* 6) Search for Tasks */
		case 6:
		printf("search for tasks -> \n");
		printf("1: Search for a task by ID \n");
		printf("2: Search for a task by its Title \n");
		printf("I choose : ");
		int searchCases;
		scanf("%d", &searchCases);
		switch (searchCases) {
			/* Search 1 -> Search for a task by ID */
			case 1:
			printf("Enter the ID : ");
			int idSearch;
			scanf("%d", &idSearch);
			SearchByID(idSearch);
                        printf("\n");
			break;

			/* Search 1 -> Search for a task by its Title */
			case 2:
                        printf("Enter the Title : ");
                        char titleSearch[20];
			scanf(" %[^\n]", titleSearch);
                        SearchByTitle(titleSearch);
                        printf("\n\n");
			break;
		}
		break;

		/* 7) Statistics */
		case 7:
                printf("Enter a Number to ->\n");
                printf("1: To Show the total number of tasks.\n");
                printf("2: To Show the number of complete and incomplete tasks.\n");
                printf("3: To Show the number of days remaining until each task's deadline.\n");
                printf("I choose : ");
                int statisticCases;
                scanf("%d", &statisticCases);

                switch (statisticCases) {
                        /* statistic 1 -> total tasks */
                        case 1:
			int numberTasks;
			numberTasks = AT - deletedTasks;
                        break;

                        /* statistic 2 ->  complete and incomplete tasks */
                        case 2:
                        break;

                        /* statistic 3 -> Days left until each task's deadline */
                        case 3:
                        break;
                }
                printf("\n\n");
                break;

		/* 0) Exit */
		case 0:
		exit1 = 1;
		break;

		default:
		printf("nto valid !\n");
		break;
	}

	if (exit1 == 1) {
		break;
	}

  }
}


