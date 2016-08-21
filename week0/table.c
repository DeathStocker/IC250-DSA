#include <stdio.h>
#include <string.h>

/*
   Calculates the percentage of marks obtained by the student
 */
double percentage(double num, double den)
{

	double per = num / den * 100.0;

	return per;
}

/*
   Prints dash symbols for formatted output
 */
void dashes()
{
	int i;

	for (i = 1; i <= 60; i++)
		printf("-");
	printf("\n");
}

/*
   Displays the result of the student in a formatted way
 */
void display(char roll[], char name[], char sub1[], int marks1, int mm1, char grade1,
	     char sub2[], int marks2, int mm2, char grade2, char sub3[], int marks3,
	     int mm3, char grade3, char sub4[], int marks4, int mm4, char grade4,
	     char sub5[], int marks5, int mm5, char grade5, double per, int div,
	     int num, int den)
{
	char division[][7] =  { "FAIL", "FIRST", "SECOND", "THIRD" };

	printf("\n\n\t\tIndian Institute of Technology Mandi\n");
	printf("\t\tAcademic Session : (Aug-Dec) 2016\n");
	dashes();
	printf("Name of the Student : %s\n", name);
	printf("Roll number         : %s\n", roll);
	dashes();
	printf("Sr. No. | Subject Code | Maximum | Marks Obtained | Grade\n");
	dashes();
	printf("  [1]        %s         %d           %d           %c\n", sub1, mm1, marks1, grade1);
	printf("  [2]        %s         %d           %d           %c\n", sub2, mm2, marks2, grade2);
	printf("  [3]        %s         %d           %d           %c\n", sub3, mm3, marks3, grade3);
	printf("  [4]        %s         %d           %d           %c\n", sub4, mm4, marks4, grade4);
	printf("  [5]        %s         %d           %d           %c\n", sub5, mm5, marks5, grade5);
	dashes();
	printf("\t\t    Total  %d   Total  %d\n", den, num);
	printf("\tPercentage  %d%c. ", (int)per, '%');
	if (div == 0)
		printf("Student has FAILED\n");
	else
		printf("Student passed with %s division\n", division[div]);
	dashes();
}

int main()
{
	FILE* fp = fopen("master.txt", "r");    //open file in read mode.
	char roll[6], name[25], sub1[5], sub2[5], sub3[5], sub4[5], sub5[5],
	     grade1, grade2, grade3, grade4, grade5;
	int marks1, marks2, marks3, marks4, marks5, mm1, mm2, mm3, mm4, mm5;

	int div = 0;

	int flag = 0;

	printf("Enter the roll number of the student : ");
	char roll_search[6];
	scanf("%s", roll_search);
	char str[512];
	while (fgets(str, 512, fp) != NULL) {
		if (strstr(str, roll_search) == NULL)
			continue;
		char last[13];
		sscanf(str, "%s %s %s %s %d %d %c %s %d %d %c %s %d %d"
		       " %c %s %d %d %c %s %d %d %c",
		       roll, name, last, sub1, &marks1, &mm1, &grade1,
		       sub2, &marks2, &mm2, &grade2, sub3, &marks3, &mm3, &grade3,
		       sub4, &marks4, &mm4, &grade4, sub5, &marks5, &mm5, &grade5);

		if(strcmp(roll, roll_search) != 0)
			break;

		strcat(name, " ");
		strcat(name, last);

		double num = marks1 + marks2 + marks3 + marks4 + marks5;        //Total marks scored
		double den = mm1 + mm2 + mm3 + mm4 + mm5;                       //Total maximum marks

		double per = percentage(num, den);

		/*
		   Finding the division awarded
		 */
		if (per >= 60)
			div = 1;
		else if (per >= 45)
			div = 2;
		else if (per >= 30)
			div = 3;

		display(roll, name, sub1, marks1, mm1, grade1,
			sub2, marks2, mm2, grade2, sub3, marks3, mm3, grade3,
			sub4, marks4, mm4, grade4, sub5, marks5, mm5, grade5, per, div, num, den);
		flag = 1;
		break;
	}

	if (flag == 0)
		printf("Searched roll number was not found in the database.\n");
	fclose(fp);
}
