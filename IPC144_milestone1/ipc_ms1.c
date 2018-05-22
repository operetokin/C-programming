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

