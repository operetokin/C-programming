#include <stdio.h>
#define MAX_ITEM_NO 21
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100
#define STOCK 1
#define LINEAR 1
#define CHECKOUT 0
#define FORM 0

void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();

struct Item {
	double price;
	int sku;
   	int isTaxed;
   	int quantity;
   	int minQuantity;
   	char name[21];
};

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
int yes(void);
void GrocInvSys(void);
int menu(void);
double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);


struct Item GI[21] = {
	{ 4.4,275,0,10,2,"Royal Gala Apples" },	
   { 5.99,386,0,20,4,"Honeydew Melon" },
   { 3.99,240,0,30,5,"Blueberries" },
   { 10.56,916,0,20,3,"Seedless Grapes" },
   { 2.5,385,0,5,2,"Pomegranate" },
   { 0.44,495,0,100,30,"Banana" },
   { 0.5,316,0,123,10,"Kiwifruit" },
   { 4.49,355,1,20,5,"Chicken Alfredo" },
   { 5.49,846,1,3,5,"Veal Parmigiana" },
   { 5.29,359,1,40,5,"Beffsteak Pie" },
   { 4.79,127,1,30,3,"Curry Checken" },
   { 16.99,238,1,10,2,"Tide Detergent" },
   { 10.49,324,1,40,5,"Tide Liq. Pods" },
   { 10.99,491,1,50,5,"Tide Powder Det." },
   { 3.69,538,1,1,5,"Lays Chips S&V" },
   { 3.29,649,1,15,5,"Joe Org Chips" },
   { 1.79,731,1,100,10,"Allen's Apple Juice" },
   { 6.69,984,1,30,3,"Coke 12 Pack" },
   { 7.29,350,1,50,5,"Nestea 12 Pack" },
   { 6.49,835,1,20,2,"7up 12 pack" }
};
int GNoOfRecs = 20;

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
		if (value <= lowerLimit || value >= upperLimit)
		{
			printf("Invalid value, %d <= value <= %d: ",lowerLimit,upperLimit);
		}
	}
	while (value <= lowerLimit || value >= upperLimit);
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
	scanf("%lf",&item.price);
	clrKyb();
	printf("   Quantity: ");
	scanf("%d", &item.quantity);
	clrKyb();
	printf("Minimum Qty: ");
	scanf("%d", &item.minQuantity);
	clrKyb();
	printf("   Is Taxed: ");
	item.isTaxed = yes();
	return item;
}

void dspItem(struct Item item, int linear)
{
	if (linear)
	{
		if (item.isTaxed == 0)
			printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|",item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));								                	if (item.isTaxed == 1)							     	printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|",item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));

		if (item.minQuantity > item.quantity)
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
		if (item.minQuantity > item.quantity)
			printf("\nWARNING: Quantity low, please order ASAP!!!\n");
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
		printf("Add item? (Y)es/(N)o: ");
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
		printf("Item already exist, Upgrade? (Y)es/(N)o: ");
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
			scanf("%d",&quan);
		}

		else if(stock == 0)
		{
			char string[100] = "to checkout";
			printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ",string, item[searchIndex].quantity);
			scanf("%d",&quan);
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
		}
	}

}	

/* int main() {
	searchTest();
	updateTest();
	addTest();
	addOrUpdateTest();
	adjustQtyTest();
	return 0;  
}

void searchTest() {
	printf("================Search Test:\n");
	printf("Enter 731: \n");
	search(GI, GNoOfRecs);
	printf("Enter 222: \n");
	search(GI, GNoOfRecs);
	}


void updateTest() {
		   struct Item I = { 11.11,111,1,11,1,"Ones!" };
		   printf("================Update Test:\n");
		   printf("Enter the follwoing: \n");
		   printf(
	   "         SKU: 111\n"
	   "        Name: Grape\n"
 	   "      Price : 22.22\n"	
	   "   Quantity : 22\n"
	   "Minimum Qty : 2\n"
	   "   Is Taxed : y\n"
	   "Overwrite old data? (Y)es/(N)o: n\n");
		   updateItem(&I);
		   printf("Unchanged Item Data:\n");
		   dspItem(I, FORM);
		   printf("Enter the follwoing: \n");
		   printf(
  		"         SKU: 111\n"					    
	      	"        Name: Grape\n"
		"      Price : 22.22\n"
		"   Quantity : 22\n"
		"Minimum Qty : 2\n"
		"   Is Taxed : y\n"
		"Overwrite old data? (Y)es/(N)o: y\n");
		   updateItem(&I);
		   printf("Updated Item: \n");
		   dspItem(I, FORM);
	}
void addTest() {
	printf("================Add Test:\n");
	printf("Total items in Storage: %d, Max no: %d\n", GNoOfRecs, MAX_ITEM_NO);
	printf("Enter the follwoing: \n");
	printf(
			"         SKU: 222\n"
			"        Name: Grape\n"
			"      Price : 22.22\n"
			"   Quantity : 22\n"
			"Minimum Qty : 2\n"
			"   Is Taxed : y\n"
			"Add Item? (Y)es/(N)o: n\n");
	addItem(GI, &GNoOfRecs, 222); //n
	printf("Garbage here! Nothing is added, No of items in storage: %d\n", GNoOfRecs);
	dspItem(GI[GNoOfRecs], FORM);
	printf("Enter the follwoing: \n");
	printf(
			"         SKU: 222\n"
			"        Name: Grape\n"
			"      Price : 22.22\n"
			"   Quantity : 22\n"
			"Minimum Qty : 2\n"
			"   Is Taxed : y\n"
			"Add Item? (Y)es/(N)o: y\n");
	addItem(GI, &GNoOfRecs, 222); //y
	printf("New item is added, No of itemsinstorage: %d\n", GNoOfRecs);
	dspItem(GI[GNoOfRecs - 1], FORM);
	printf("Adding 333: \n");
	addItem(GI, &GNoOfRecs, 333);
	}

void addOrUpdateTest() {
	GNoOfRecs = MAX_ITEM_NO;
	printf("================AddOrUpdate Test:\n");
	printf("Enter 731 and then \'n\':\n");
	addOrUpdateItem(GI, &GNoOfRecs); // n
	printf("Enter 731, \'y\' and then:\n"
			"       Name: Apple\n"
			"      Price: 1.80\n"
			"   Quantity: 101\n"
			"Minimum Qty: 11\n"
			"   Is Taxed: n\n"
			"Overwrite old data? (Y)es/(N)o: y\n");
		addOrUpdateItem(GI, &GNoOfRecs); // yes new data Yes
		printf("Updated Item: \n");
		dspItem(GI[16], FORM);
		printf("Enter 444: \n");
		addOrUpdateItem(GI, &GNoOfRecs); //n
}

void adjustQtyTest() {
	printf("================AdjustQty Test:\n");
	printf("Invalid SKU Test; Enter 444:\n");
	adjustQty(GI, GNoOfRecs, STOCK);
	printf("Aborting Entry test; Enter 731 and then 0:\n");
	adjustQty(GI, GNoOfRecs, CHECKOUT);
	printf("Checking out with low quantity warning; Enter 731 and then 90:\n");
	adjustQty(GI, GNoOfRecs, CHECKOUT);
	printf("Stocking; Enter 731 and then 50:\n");
	adjustQty(GI, GNoOfRecs, STOCK);
	dspItem(GI[16], FORM);
}

*/











