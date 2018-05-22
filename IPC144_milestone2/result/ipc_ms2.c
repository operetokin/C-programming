#include <stdio.h>
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
                     printf("Invalid integer, please try again: ");					                }
   }	
return value;
}

int yes(void)	//ms2
{
	char CH;
	int RET = 0;
	do {
	scanf("%c",&CH);
	clrKyb();
	if ((CH != 'Y') && (CH != 'N') && (CH != 'y') && (CH !='n'))
		printf ("Only (Y)es or (N)o are acceptable: ");
	}
	while ((CH != 'Y') && (CH != 'N') && (CH != 'y') && (CH !='n'));
	if ((CH == 'Y') || (CH == 'y'))
	RET = 1;
return RET;
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

void welcome(void)
{
	printf("---=== Grocery Inventory System ===---\n\n");
}

void GrocInvSys(void)  // ms2
{
	int DONE = 0;
	welcome();
	while (DONE == 0)
	{
		int SEL;
		SEL = menu();
		if (SEL == 1)
		{
			printf("List Items!\n");
			pause();
		}
		else if (SEL == 2)
		{
			printf("Search Items!\n");
			pause();
		}
		else if (SEL == 3)
		{
			printf("Checkout Item!\n");
			pause();
		}
		else if (SEL == 4)
		{
			printf("Stock Item!\n");
			pause();
		}
		else if (SEL == 5)
		{
			printf("Add/Update Item!\n");
			pause();
		}
		else if (SEL == 6)
		{
			printf("Delete Item!\n");
			pause();
		}
		else if (SEL == 7)
		{
			printf("Search by name!\n");
			pause();
		}
		else if (SEL == 0)
		{
			printf("Exit the program? (Y)es/(N)o : ");
			DONE = yes();
		}
	}
}	
		




int menu(void)  // ms2
{
	int SEL;
	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	printf("6- delete item\n");
	printf("7- Search by name\n");
	printf("0- Exit program\n");
	printf("> ");
	SEL = getIntLimited(0,7);
	return SEL;
}

int main(void)
{
	   GrocInvSys();
	      return 0;
}
