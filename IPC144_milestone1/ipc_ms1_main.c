#include <stdio.h>
void welcome(void)
{
	printf("---=== Grocery Inventory System ===---\n\n"); 
}

void prnTitle(void)
{
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
	printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void prnFooter(double gTotal)
{
	printf("--------------------------------------------------------+----------------\n");
	if(gTotal > 0)
		printf("                                           Grand Total: |%12.2lf\n",gTotal);
}

void clrKyb(void)
{
	char character;
	do {
	scanf("%c",&character);
	}
	while(character != '\n');
}

void pause(void)
{
	printf("Press <ENTER> to continue...");
	clrKyb();
}

int getInt(void)
{
	char NL = 'x';
	int value;
	while (NL != '\n')
	{
		scanf("%d%c",&value,&NL);
		if (NL != '\n')
		{
			clrKyb();
			printf("Invalid integer, please try again: ");
		}
	}
	return value;
}	

double getDbl(void)
{
        char NL = 'x';
        double value;
	while (NL != '\n')
        {					
		scanf("%lf%c",&value,&NL);
	        if (NL != '\n')
	        {
	                 clrKyb();
		         printf("Invalid number, please try again: ");
                }
        }
 	return value;
}

int getIntLimited(int lowerLimit, int upperLimit)
{
	int value;
	do {
	value = getInt();
	if (value < lowerLimit || value > upperLimit)
		{
		printf("Invalid value, %d < value < %d: ",lowerLimit,upperLimit);
		}
	}
	while (value < lowerLimit || value >upperLimit);
	return value;
	}	

double getDblLimited(double lowerLimit, double upperLimit)
{
	double value;
        do {
         value = getDbl();
         if (value < lowerLimit || value > upperLimit)
         {
               printf("Invalid value, %lf< value < %lf: ",lowerLimit,upperLimit);
	 }
	 }
 	        while (value < lowerLimit || value > upperLimit);
		return value;
}

int main(void) {
   int iVal;
   double dVal;
   welcome(); //welcome message

   printf("listing header and footer with grand total:\n");
   prnTitle(); //print title

   prnFooter(1234.5678); //print footer
   printf("listing header and footer without grand total:\n");
   prnTitle(); //print title
   prnFooter(-1); //print footer

   pause(); //waiting for <Enter>

   printf("Enter an integer: ");
   iVal = getInt(); //get Integer
   printf("You entered: %d\n", iVal);

   printf("Enter an integer between 10 and 20: ");
   iVal = getIntLimited(10, 20); //get integer from range
   printf("Your entered %d\n", iVal);

   printf("Enter a floating point number: ");
   dVal = getDbl(); //get floating point number 
   printf("You entered: %0.2lf\n", dVal);

   printf("Enter a floating point number between 10.00 and 20.00: ");
   dVal = getDblLimited(10.0, 20.0); //get floating point number from range
   printf("You entered: %0.2lf\n", dVal);

   printf("End of tester program for milestone one!\n");
   return 0;
}
