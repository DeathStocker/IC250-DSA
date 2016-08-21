#include <stdio.h>
#include <string.h>

/*
   Struct containing relevant information about the student
 */
typedef struct students {
	char roll[7];
	char name[25];
	char sub1[6], sub2[6], sub3[6], sub4[6], sub5[6];
	char grade1, grade2, grade3, grade4, grade5;
	int marks1, marks2, marks3, marks4, marks5;
	int mm1, mm2, mm3, mm4, mm5;
} student;

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
void display(student stud, double per, int div,
	     int num, int den)
{
	char division[][7] =  { "FAIL", "FIRST", "SECOND", "THIRD" };

	printf("\n\n\t    Indian Institute of Technology Mandi\n");
	printf("\t      Academic Session : (Aug-Dec) 2016\n");
	dashes();
	printf("Name of the Student : %s\n", stud.name);
	printf("Roll number         : %s\n", stud.roll);
	dashes();
	printf("Sr. No. | Subject Code | Maximum | Marks Obtained | Grade\n");
	dashes();
	printf("  [1]        %s         %d           %d           %c\n",
	       stud.sub1, stud.mm1, stud.marks1, stud.grade1);
	printf("  [2]        %s         %d           %d           %c\n",
	       stud.sub2, stud.mm2, stud.marks2, stud.grade2);
	printf("  [3]        %s         %d           %d           %c\n",
	       stud.sub3, stud.mm3, stud.marks3, stud.grade3);
	printf("  [4]        %s         %d           %d           %c\n",
	       stud.sub4, stud.mm4, stud.marks4, stud.grade4);
	printf("  [5]        %s         %d           %d           %c\n",
	       stud.sub5, stud.mm5, stud.marks5, stud.grade5);
	dashes();
	printf("\t\t    Total  %d   Total  %d\n", den, num);
	printf("\tPercentage  %d%c. ", (int)per, '%');
	if (div == 0)
		printf("Student has FAILED\n");
	else
		printf("Student passed with %s division\n", division[div]);
	dashes();
}

/*
   Adds null terminator to the string variables of the struct.
 */
void nullify(student* stud)
{
	stud->name[24] = '\0';
	stud->roll[6] = '\0';
	stud->sub1[5] = '\0';
	stud->sub2[5] = '\0';
	stud->sub3[5] = '\0';
	stud->sub4[5] = '\0';
	stud->sub5[5] = '\0';
}

int main()
{
	FILE* fp = fopen("master.txt", "r");    //open file in read mode.

	student stud;
	int div = 0;

	printf("Enter the roll number of the student : ");
	char roll_search[6];
	scanf("%s", roll_search);
	char str[512];
	while (fgets(str, 512, fp) != NULL) {
		if (strstr(str, roll_search) == NULL)
			continue;

		char last[13];  // Last name will be obtained separately.

		/*
		   Assigning all the values to the respective fields
		 */
		sscanf(str, "%s %s %s %s %d %d %c %s %d %d %c %s %d %d"
		       " %c %s %d %d %c %s %d %d %c",
		       stud.roll, stud.name, last, stud.sub1, &stud.marks1,
		       &stud.mm1, &stud.grade1, stud.sub2, &stud.marks2,
		       &stud.mm2, &stud.grade2, stud.sub3, &stud.marks3,
		       &stud.mm3, &stud.grade3, stud.sub4, &stud.marks4,
		       &stud.mm4, &stud.grade4, stud.sub5, &stud.marks5,
		       &stud.mm5, &stud.grade5);


		nullify(&stud);

		if (strcmp(stud.roll, roll_search) != 0)
			break;

		/*
		   Merging the first and the last name in a single string.
		 */
		strcat(stud.name, " ");
		strcat(stud.name, last);

		double num = stud.marks1 + stud.marks2 + stud.marks3 +
			     stud.marks4 + stud.marks5;                                 //Total marks scored
		double den = stud.mm1 + stud.mm2 + stud.mm3 + stud.mm4 + stud.mm5;      //Total maximum marks

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

		display(stud, per, div, num, den);
		return 0;
	}

	printf("Searched roll number was not found in the database.\n");
	fclose(fp);
	return 1;
}
