#include <stdio.h>
#include <string.h>
#define MAX_ITEM_NO 500
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define STOCK 1
#define LINEAR 1
#define CHECKOUT 0
#define FORM 0
#define DATAFILE "ipc_ms5_long.txt"

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};

/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/


/* ms1 prototypes*/
void clrKyb(void); 
void pause(void); 
int getInt(void); 
int getIntLimited(int lowerLimit, int upperLimit);
void welcome(void); 
void prnTitle(void);
void prnFooter(double gTotal); 
void pause(void); 
double getDbl(void); 
double getDblLimited(double lowerLimit, double upperLimit); 

/* ms2 prototypes*/
int yes(void);  
void GrocInvSys(void);  // ms2
int menu(void);  // ms2

/* ms3 prototypes*/
double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

/* ms4 prototypes */
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);

/*End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);

/*End of milestone 5 prototypes
*********************************************************************/




/**************************************************************************
    TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR                                                      
       TT       EE         SS             TT       EE          RR     RR          
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
       TT       EE               SS       TT       EE          RR  RR
       TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here: 

void prnFile() {
   FILE* tp = fopen("test.txt", "r");
   char ch;
   if (tp) {
      for (; fscanf(tp,"%c", &ch) == 1; putchar(ch));
      fclose(tp);
   }
   else {
      printf("text.txt not found\n");
   }
}

int main(void) {
   int i, n;
   struct Item GI[3] = {
      { 4.4,275,0,10,2,"Royal Gala Apples" },
      { 5.99,386,0,20,4,"Honeydew Melon" },
      { 3.99,240,0,30,5,"Blueberries" },
   };
   struct Item I;
   struct Item IN[3];
   printf("***********Testing saveItem:\n");
   printf("Your saveItem saved the following in test.txt: \n");
   FILE* tp = fopen("test.txt", "w");
   if (tp) {
      for (i = 0; i < 3; i++) saveItem(GI[i], tp);
      fclose(tp);
      prnFile();
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItem!\n\n\n");
   pause();
   printf("***********Testing loadItem:\n");
   printf("Your loadItem loaded the following from test.txt: \n");
   tp = fopen("test.txt", "r");
   if (tp) {
      for (i = 0; i < 3; i++) {
	 loadItem(&I, tp);
	 dspItem(I, LINEAR);
      }
      fclose(tp);
      tp = fopen("test.txt", "w");
      fclose(tp);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItem!\n\n\n");
   pause();
   printf("***********Testing saveItems:\n");
   printf("Your saveItems saved the following in test.txt: \n");
   saveItems(GI, "test.txt", 3);
   prnFile();
   printf("*******************************\nThey have to match the following:\n");
   printf("275,10,2,4.40,0,Royal Gala Apples\n");
   printf("386,20,4,5.99,0,Honeydew Melon\n");
   printf("240,30,5,3.99,0,Blueberries\n");
   printf("***********END Testing saveItems!\n\n\n");
   pause();
   printf("***********Testing loadItems:\n");
   printf("Your loadItems loaded the following from test.txt: \n");
   loadItems(IN, "test.txt", &n);
   for (i = 0; i < n; i++) {
      dspItem(IN[i], LINEAR);
   }
   printf("*******************************\nThey have to match the following:\n");
   printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
   printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
   printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
   printf("***********END Testing loadItems!\n\n\n");
   pause();
   printf("Done!\n");
   return 0;
}

/* End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/********************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here: */
int main(void) {
GrocInvSys();
return 0;
}

/* End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/

void saveItem(struct Item item, FILE *dataFile)
{
	if (dataFile != NULL)
	{
		fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n",item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
	}
	else
	{
		printf("Unable to open\n");
	}
}

int loadItem(struct Item *item, FILE *dataFile)
{
	int scan = 0;
	int sku;
	int quantity;
	int minimum;
	int taxed;
	double price;
	char name[21];
	if(dataFile != NULL)
	{
		scan = fscanf(dataFile,"%d,%d,%d,%lf,%d,%[^\n]%*c", &sku, &quantity, &minimum, &price, &taxed, name);
		
		if (scan == 6)
		{
			item->sku = sku;
			item->quantity = quantity;
			item->minQuantity = minimum;
			item->price = price;
			item->isTaxed = taxed;
			strcpy(item->name, name);
			return 1;
		}
		else
			return 0;
	}
	else
		printf("Unable to open file\n");
		return 0;
}

int saveItems(struct Item *item, char fileName[], int NoOfRecs)
{
	int i = 0;
	FILE *dataFile = NULL;
	dataFile = fopen(fileName, "w");
	if(dataFile != NULL)
	{
		for(i = 0; i < NoOfRecs; i++)
		{
			saveItem(item[i], dataFile);
			//fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n",item[i].sku,item[i].quantity,item[i].minQuantity,item[i].price,item[i].isTaxed,item[i].name);
		}
		fclose(dataFile);
		return 1;
	}
	else
	{
		printf("unable to open file\n");
		return 0;
	}
}

int loadItems(struct Item *item, char fileName[], int *NoOfRecsPtr)
{
	FILE *dataFile = fopen(fileName, "r");
	*NoOfRecsPtr = 0;
	rewind(dataFile);
	if(dataFile != NULL)
	{
		while(loadItem(&item[*NoOfRecsPtr], dataFile) == 1)
			 *NoOfRecsPtr = *NoOfRecsPtr + 1;

		fclose(dataFile);
		return 1;
	}
	else
		return 0;
}

/*End of milestone 5 functions
*********************************************************************/

/********************************************************************
Milestones 1  to 4 functions*/
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
			printf("Invalid value, %d <= value <= %d: ",lowerLimit,upperLimit);
		}
	}
	while (value < lowerLimit || value > upperLimit);
	return value;
}

double getDblLimited(double lowerLimit, double upperLimit)
{
	double value;
	do {
		value = getDbl();
		if (value <= lowerLimit || value >= upperLimit)
		{
			printf("Invalid value, %lf <= value <= %lf: ",lowerLimit,upperLimit);
		}
	}
	while (value <= lowerLimit || value >= upperLimit);
	return value;
}

int yes(void)
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

double totalAfterTax(struct Item item)
{
	double AfterTax;
	AfterTax = (item.price + (item.price * 0.13 * item.isTaxed)) * item.quantity;
	return AfterTax;
}

struct Item itemEntry(int sku)
{
		struct Item item;
		item.sku = sku;
		printf("        SKU: %d\n",sku);
		printf("       Name: ");
		scanf("%s",item.name);
		clrKyb();
		printf("      Price: ");
		item.price = getDblLimited(0.01,1000);
		//scanf("%lf",&item.price);
		//clrKyb();
		printf("   Quantity: ");
		//scanf("%d", &item.quantity);
		item.quantity = getIntLimited(1,MAX_QTY);
		//clrKyb();
		printf("Minimum Qty: ");
		//scanf("%d", &item.minQuantity);
		item.minQuantity = getIntLimited(0,100);
		//clrKyb();
		printf("   Is Taxed: ");
		item.isTaxed = yes();
		return item;
}

int menu(void)  // ms2
{
	int SEL;
	printf("1- List all items\n");
	printf("2- Search by SKU\n");
	printf("3- Checkout an item\n");
	printf("4- Stock an item\n");
	printf("5- Add new item or update item\n");
	//printf("6- delete item\n");
	//printf("7- Search by name\n");
	printf("0- Exit program\n");
	printf("> ");
	SEL = getIntLimited(0,5);
	return SEL;
}

void welcome(void)
{
	printf("---=== Grocery Inventory System ===---\n\n");
}


void GrocInvSys(void)  // ms2
{
	int DONE = 0;
	int n, i;
	struct Item item[MAX_ITEM_NO];
	welcome();
	i = loadItems(item,DATAFILE,&n);
//	if(i==0)
//		printf("Could not read from %s.\n",DATAFILE);
	while (DONE == 0)
	{
		int SEL;
		SEL = menu();
		if (SEL == 1)
		{
			listItems(item,n);
			//printf("List Items!\n");
			pause();
		}
		else if (SEL == 2)
		{
			search(item,n);
			//printf("Search Items!\n");
			pause();
			printf("\n");
		}
		else if (SEL == 3)
		{
			adjustQty(item,n,CHECKOUT);
			i = saveItems(item,DATAFILE,n);
			if(i == 0)
				printf("could not update data file %s\n",DATAFILE);	
			//printf("Checkout Item!\n");
			pause();
		//	printf("\n");
		}
		else if (SEL == 4)
		{
			 adjustQty(item,n,STOCK);
			 i = saveItems(item,DATAFILE,n);
			 if(i == 0)
				 printf("could not update data file %s\n",DATAFILE);
			//rintf("Stock Item!\n");
			pause();
		}
		else if (SEL == 5)
		{
			addOrUpdateItem(item,&n);
			i = saveItems(item,DATAFILE,n);
			if (i == 0)
				printf("could not update data file %s\n",DATAFILE);
			//printf("Add/Update Item!\n");
			pause();
		}
		/*else if (SEL == 6)
		{
			printf("Not implemented!\n");
			//printf("Delete Item!\n");
			pause();
		}
		else if (SEL == 7)
		{
			printf("Not implemented!\n");
			//printf("Search by name!\n");
			pause();
		}*/
		else if (SEL == 0)
		{
			printf("Exit the program? (Y)es/(N)o): ");
			DONE = yes();
		}
	}
}


void dspItem(struct Item item, int linear)
{
	if (linear)
	{
		if (item.isTaxed == 0)
			printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|",item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));								   
		if (item.isTaxed == 1)							     	printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|",item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));
		if (item.minQuantity >= item.quantity)
			printf("***\n");
		else
			printf("\n");
	}
	else
	{
		printf("        SKU: %d",item.sku);
		printf("\n       Name: %s",item.name);
		printf("\n      Price: %.2lf",item.price);
		printf("\n   Quantity: %d",item.quantity);
		printf("\nMinimum Qty: %d",item.minQuantity);
		if(item.isTaxed == 0)
			printf("\n   Is Taxed: No\n");
		if(item.isTaxed == 1)
			printf("\n   Is Taxed: Yes\n");
		if (item.minQuantity >= item.quantity)
			printf("WARNING: Quantity low, please order ASAP!!!\n");
	}
}

void listItems(const struct Item item[], int NoOfItems)
{
	int i;
	double gTotal = 0;
	int linear = 1;
	prnTitle();
	for(i=0; i<NoOfItems; i++)
	{
		printf("%-4d", i+1);
		dspItem(item[i], linear);
		gTotal += totalAfterTax(item[i]);
	}
	prnFooter(gTotal);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int *index)
{
	int i=0, n=0;
	for(i=0; i<NoOfRecs; i++)	//loop for searching sku in array of structs
	{
		if(item[i].sku == sku) 
		{
			*index = i;	//pass the index of fond item to *index
			n=1;		
		}
	}
	return n; 			//return 1 is sku was fond, in other case  0
}

void search(const struct Item item[], int NoOfRecs)
{
	int SKU_num;
	printf("Please enter the SKU: ");
	scanf("%d",&SKU_num);
	int i = 0;
	if (locateItem(item,NoOfRecs,SKU_num,&i))	//call function locateItem, 
	{
		dspItem(item[i],FORM);			//execute this if locateItem returns 1
	}
	else
		printf("Item not found!\n");		//execute this if returns 0
}

void updateItem(struct Item *itemptr)			//using pointer because we gonna change existing element(struct) in array
{
	struct Item I;
	printf("Enter new data:\n");
	I = itemEntry(itemptr->sku);
	printf("Overwrite old data? (Y)es/(N)o: ");
	if (yes()==1)
	{
		*itemptr = I;				//rewrite element of array if yes()==1
		printf("--== Updated! ==--\n");
	}
	else
		printf("--== Aborted! ==--\n");
}		


void addItem(struct Item item[], int *NoOfRecs, int sku)
{
	struct Item I;
	if (*NoOfRecs == MAX_ITEM_NO) 
	{
		printf("Can not add new item; Storage Full!\n");
	}

	else 
	{
		I = itemEntry(sku);			//save new complited struct in I
		printf("Add Item? (Y)es/(N)o: ");
		if (yes()==1)
		{
			item[*NoOfRecs] = I;		//save struct to array (add)
			*NoOfRecs = *NoOfRecs + 1;	//increase number of records by 1
			printf("--== Added! ==--\n");
		}
		else
			printf("--== Aborted ==--\n");		
	}
}

void addOrUpdateItem(struct Item item[], int *NoOfRecs)
{
	int sku, i;
	int searchIndex = 0;
	printf("Please enter the SKU: ");
	sku = getIntLimited(SKU_MIN,SKU_MAX);
	i = locateItem(item, *NoOfRecs, sku, &searchIndex);	//i==0 if sku exists
	if(i==1)
	{
		dspItem(item[searchIndex],FORM);		//display item
		printf("Item already exists, Update? (Y)es/(N)o: ");
		if(yes()==1)
		{
			updateItem(&item[searchIndex]);		//update existing item
		}
		else
			printf("--== Aborted! ==--\n");
	}	
	if(i==0)
	{
		addItem(item, NoOfRecs, sku);			//add item if it doesnt exist
	}
}


void adjustQty(struct Item item[], int NoOfRecs, int stock)
{
	int quan = 0;
	int sku, i;
	int searchIndex = 0;
	printf("Please enter the SKU: ");
	sku = getIntLimited(SKU_MIN,SKU_MAX);
	i = locateItem(item, NoOfRecs, sku, &searchIndex);
	if(i==0)
	{
		printf("SKU not found in storage!\n");
	}

	if(i==1)
	{
		dspItem(item[searchIndex],FORM);
		if(stock == 1)
		{
			char string[100] = "to stock";
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ",string, (MAX_QTY-item[searchIndex].quantity));
			quan = getIntLimited(0,(MAX_QTY-item[searchIndex].quantity));
		}

		else if(stock == 0)
		{
			char string[100] = "to checkout";
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ",string, item[searchIndex].quantity);
			quan = getIntLimited(0,item[searchIndex].quantity);
		}

		if(quan == 0)
			printf("--== Aborted! ==--\n");

		else
		{
			if(stock == 1)
			{
				item[searchIndex].quantity+=quan;
				printf("--== Stocked! ==--\n");
			}
			if(stock == 0)
			{
				item[searchIndex].quantity-=quan;
				printf("--== Checked out! ==--\n");
			}
			if(item[searchIndex].quantity <= item[searchIndex].minQuantity)
				printf("Quantity is low, please reorder ASAP!!!\n");
		}
	}

}

/*End of milestone 1 to 4 functions
*********************************************************************/








/* ms5 Tester output

***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!


Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!


Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!


Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!


Press <ENTER> to continue...
Done!


*/
