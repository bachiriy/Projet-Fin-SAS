#include <stdio.h>
#include <string.h>
#include <time.h>


struct data {
	int ID;
	char title[20];
	char description[150];
	int day;
	int month;
	int year;
	char status[20];
};

// global structure that stores the tasks
	struct data tasks[50];

// global variable that count the number of tasks
	int NT = 0; // NT = Number of Tasks

// global variable that count the number of deleted tasks
	int deletedTasks = 0; 


// Add Tasks
	void addtask(int HM) { 
		for (int i = NT; i < NT + HM; i++) { // HM = How Many tasks to add
			printf("       Title : ");
			scanf(" %[^\n]", tasks[i].title); // %[^\n] to scan text with spaces
			printf("       Description : ");
			scanf(" %[^\n]", tasks[i].description);
			printf("       Deadline like this (DD/MM/YYYY) : ");
			scanf("%d/%d/%d", &tasks[i].day, &tasks[i].month, &tasks[i].year);
			printf("       Status: \n");
			printf("       1 : 'to do' \n");
			printf("       2 : 'in progress' \n");
			printf("       3 : 'completed' \n");
			printf("       I choose : ");
			int statusCase;
			scanf("%d", &statusCase);
			switch (statusCase) {
				case 1:
					strcpy(tasks[i].status, "to do"); // strcpy = sting copy | to copy the status in the structure
					break;
				case 2:
					strcpy(tasks[i].status, "in progress");
					break;
				case 3:
					strcpy(tasks[i].status, "completed");
					break;
				default:
					printf("       Status not valid !\n");
					break;
		}
		tasks[i].ID = i + 1; // add 1 each time so the ID is unique 
	}

	NT = NT + HM; // to update the nember of tasks by adding how many tasks we just added
}

 // Modify tasks by ID 
	void modifytasks(int id) {
		for (int i = 0; i < NT; i++) {
			if (tasks[i].ID == id) {  // find the task then ask what to modify
				printf("      Enter a Number to ->\n");
				printf("      1 : To Edit the description of a task.\n");
				printf("      2 : To Change the status of a task.\n");
				printf("      3 : To Change the deadline for a task.\n");
				printf("      I choose : ");
				int modifyCases;
				scanf("%d", &modifyCases); // scan a number
				printf("\n\n");
				switch (modifyCases) {
					// 1 : new description case
						case 1:
							printf("     Enter the new Description: ");
							char newDescription[150];
							scanf(" %[^\n]", newDescription);
							strcpy(tasks[i].description, newDescription);
							break;

					// 2 : new status case
						case 2:
							printf("       Enter the new Status: \n");
							printf("       1: 'to do' \n");
							printf("       2: 'in progress' \n");
							printf("       3: 'completed' \n");
							printf("       I choose : ");
							int newStatusCases;
							scanf("%d", &newStatusCases);
							switch (newStatusCases) {
								case 1:
									strcpy(tasks[i].status, "to do");
									break;
								case 2:
									strcpy(tasks[i].status, "in progress");
									break;
								case 3:
									strcpy(tasks[i].status, "completed");
									break;
								default:
									printf("   Status not valid !\n");
									break;
							}
							break;

				// 3 : new deadline case
				case 3:
					printf("       Enter the new deadline (DD/MM/YYY) : ");
					int day, month, year;
					scanf("%d/%d/%d", &day, &month, &year); // scan the new day, month, year
					tasks[i].day = day;
					tasks[i].month = month;
					tasks[i].year = year;
					break;

				// default
				default:
					printf("       Option not valid!\n");
					break;
			}
		}
	}
}


// Sort tasks by title
	void sortByTitle() {
		struct data empty; // empty structure to use in the swapping
		for (int i = 0; i < NT; i++) {
			for (int j = i + 1; j < NT; j++) {
				if (strcmp(tasks[i].title, tasks[j].title) > 0) {
					empty = tasks[i];
					tasks[i] = tasks[j];
					tasks[j] = empty;
				}
			}
		}
	}


// Sort tasks by deadline
	void sortByDeadline() {
		struct data empty; // empty stucture to use to swap tasks
			for (int i = 0; i < NT; i++) {
				for (int j = i + 1; j < NT; j++) {
					if (tasks[i].year > tasks[j].year) {
						empty = tasks[i];
						tasks[i] = tasks[j];
						tasks[j] = empty;
					}
					if (tasks[i].year == tasks[j].year && tasks[i].month > tasks[j].month) {
						empty = tasks[i];
						tasks[i] = tasks[j];
						tasks[j] = empty;
					}
					if (tasks[i].year == tasks[j].year && tasks[i].month == tasks[j].month && tasks[i].day > tasks[j].day) {
						empty = tasks[i];
						tasks[i] = tasks[j];
						tasks[j] = empty;
					}
				}
			}
		}


// Sort tasks with a deadline within the next 3 days
	void sortDealineWithin3Days() {
		for (int i = 0; i < NT; i++) {
			time_t nowSeconds = time(NULL);  // how many seconds from 1970 until now

			int totalDaysUntilNow = (1970*365 + 15) + (nowSeconds/(60*60*24)); // how many days from 0 to 1970 + how many days from 1970 until now
			int deadlineInDays = tasks[i].year*365 + tasks[i].month * 30 + tasks[i].day; // convert deadline to days
			int diffrent = deadlineInDays- totalDaysUntilNow; // diffrence between deadline and now in days


			if (diffrent  <= 3 && tasks[i].ID > 0) {
				printf("ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n", 
							tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
			}
		}
	}


// Delete a task by ID
	void deleteTask(int idd) {
		for (int i = 0; i < NT; i++) {
			if (tasks[i].ID == idd) { // when find the task make its ID negative
				tasks[i].ID = -tasks[i].ID;
				deletedTasks = deletedTasks + 1;
			}
		}
	}


// Search for Tasks by ID
	void SearchByID(int id) {
		for (int i = 0; i < NT; i++) {
			if (tasks[i].ID == id) { // find the tasks by ID and prinf it
			printf("ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n", tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
			}
		}
	}


// Search for Tasks by title
	void SearchByTitle(char searchedTitle[20]) {
		for (int i = 0; i < NT; i++) {
			if ((strcmp(tasks[i].title, searchedTitle) == 0) && tasks[i].ID > 0) { // task title - searchedTitle = 0 means there is no diffrent
				printf(" ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n",
				 tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
			}
		}
	}

 // Sort days left until each task's deadline
	void daysLeft(){
		for (int i = 0; i < NT; i++) {
				time_t nowSeconds = time(NULL);  // how many seconds from 1970 until now

				int totalDaysUntilNow = (1970*365 + 15) + (nowSeconds/(60*60*24)); // how many days from 0 to 1970 + how many days from 1970 until now
				int deadlineInDays = tasks[i].year*365 + tasks[i].month * 30 + tasks[i].day; // convert deadline to days
				int diffrent = deadlineInDays- totalDaysUntilNow; // diffrence between deadline and now in days

				if (tasks[i].ID > 0) // to not print the deleted tasks
					printf("ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s. | %d Day(s) left.\n\n", 
									tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status, diffrent);
		}
	}

// main function
	int main() {
	while (1) {
		printf(" _____________________________________________________________\n\n");
		printf("                   <<  ToDo List Menu  >>                      \n");
		printf(" _____________________________________________________________\n");
		printf("                                                               \n");
		printf("      Enter a Number To ->                                     \n");
		printf("       1: To Add a New Task.                                   \n");
		printf("       2: To Add Multiple New Tasks.                           \n");
		printf("       3: To Display the List of All Tasks.                    \n");
		printf("       4: To Modify a Task.                                    \n");
		printf("       5: To Delete a Task by ID.                              \n");
		printf("       6: To Search for Tasks.                                 \n");
		printf("       7: To Statistics.                                       \n");
		printf("       0: To Exit.                                             \n");
		printf("                                                               \n");
		printf(" _____________________________________________________________ \n");
		printf("\n       I choose : ");
		int menuCases;
		scanf("%d", &menuCases);
		int exit = 0;

		switch (menuCases) {
 			// 1 : Add a New Task
				case 1:
					int addOneTask = 1;
					addtask(addOneTask);
					printf("\n\n");
					break;

			// 2 : Add Multiple New Tasks
				case 2:
					int multipleTasks;
					printf("       How Many Tasks you Want to Add ? : ");
					scanf("%d", &multipleTasks); // scan how many tasks wanted to be added
					addtask(multipleTasks); // put it in the function
					printf("\n\n");
					break;

			// 3 : Display and Sorting Tasks
				case 3:
					printf("      Enter a Number to ->\n");
					printf("      1: To Sort tasks alphabetically.\n");
					printf("      2: To Sort tasks by deadline.\n");
					printf("      3: To Display tasks with a deadline within the next 3 days.\n");
					printf("      I choose : ");
					int displayCases;
					scanf("%d", &displayCases);
					printf("\n\n");
					switch (displayCases) {
						// Sorting tasks alphabetically
							case 1:
								sortByTitle();
								for (int i = 0; i < NT; i++) {
									if (tasks[i].ID > 0) {
										printf("ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n\n",
													 tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
									}
								}
								break;

						//  Sorting tasks by deadline
							case 2:
								sortByDeadline();
								for (int i = 0; i < NT; i++) {
									if (tasks[i].ID > 0) {
										printf("ID: %d, Title: %s, Description: %s, Deadline: %d/%d/%d, Status: %s.\n\n",
													 tasks[i].ID, tasks[i].title, tasks[i].description, tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].status);
							   	}
								}
								break;

						// Display tasks with a deadline within the next 3 days
							case 3:
								sortDealineWithin3Days();
								break;
					}
					printf("\n\n");
					break;

			// 4 : Modify a Task
				case 4:
					printf("\n\n");
					printf("      What task you want to modify ? (enter the task's ID) : ");
					int id;
					scanf("%d", &id);
					modifytasks(id);
					printf("\n   Task modified ! \n");
					printf("\n\n");
					break;

			// 5 : Delete a Task by ID
				case 5:
					printf("\n\n");
					printf("      Enter the ID of the task you want to  Delete : ");
					int did;
					scanf("%d", &did);
					deleteTask(did);
					printf("\n   Task deleted !\n");
					printf("\n\n");
					break;

			// 6 : Search for Tasks
				case 6:
					printf("\n\n");
					printf("       search for tasks -> \n");
					printf("       1: Search for a task by ID \n");
					printf("       2: Search for a task by its Title \n");
					printf("       I choose : ");
					int searchCases;
					scanf("%d", &searchCases);
					printf("\n\n");
					switch (searchCases) {
					// by ID
						case 1:
							printf("     Enter the ID : ");
							int idSearch;
							scanf("%d", &idSearch);
							SearchByID(idSearch);
							printf("\n");
							break;

					// by Title
						case 2:
							printf("     Enter the Title : ");
							char searchTitle[20];
							scanf(" %[^\n]", searchTitle);
							SearchByTitle(searchTitle);
							printf("\n");
							break;
			}
					printf("\n\n");
					break;

			// 7 : Statistics
				case 7:
					printf("\n\n");
					printf("       Enter a Number to ->\n");
					printf("       1: To Show the total number of tasks.\n");
					printf("       2: To Show the number of complete and incomplete tasks.\n");
					printf("       3: To Show the number of days remaining until each task's deadline.\n");
					printf("       I choose : ");
					int statisticCases;
					scanf("%d", &statisticCases);
					printf("\n\n");
					switch (statisticCases) {
					// total tasks
						case 1:
							int numberTasks;
							numberTasks = NT - deletedTasks;
							printf("\n       The total number of tasks is : %d", numberTasks);
							printf("\n\n");
							break;

					// Completed and Incompleted tasks
						case 2:
							int nCompleted = 0; // number of completed tasks
							for (int i = 0; i < NT; i++) {
								if (strcmp(tasks[i].status, "completed") == 0 && tasks[i].ID > 0) {
									nCompleted = nCompleted + 1;
								}
							}
							int nIncompleted = 0; // number of incompleted tasks
							for (int i = 0; i < NT; i++) {
								if (strcmp(tasks[i].status, "in progress") == 0 || strcmp(tasks[i].status, "to do") == 0 && tasks[i].ID > 0) {
									nIncompleted = nIncompleted + 1;
								}
							}
							printf("     Number of completeted tasks : %d \n", nCompleted);
							printf("     Number of incompleted tasks : %d ", nIncompleted);
							printf("\n\n");
							break;

					// Days left until each task's deadline
						case 3:
							daysLeft();
							break;
				}
					printf("\n\n");
					break;

			// 0 : Exit
				case 0:
					exit = 1;
					break;

			// defailt
				default:
					printf("       Option not  valid !\n\n");
					break;
		}
		if (exit == 1) { break;}

	}
}
