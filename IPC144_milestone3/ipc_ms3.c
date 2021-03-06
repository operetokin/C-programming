#include <stdio.h>
#include <stdlib.h>
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0
/* ipc_ms1*/
void welcome(void)
{
	printf("---
	nearch(item,NoOfRecs);
= Grocery Inventory System ===---\n\n");
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
/* ipc_ms2*/
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

struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};

/* ipc_ms3*/
double totalAfterTax(struct Item item)
{
	double AfterTax;
	AfterTax = (item.price + (item.price * 0.13 * item.isTaxed)) * item.quantity;
	return AfterTax;
}

int isLowQty(struct Item item)
{
	int LowQty = 0;
	if (item.minQuantity > item.quantity)
	LowQty = 1;
	return LowQty;
}

struct Item itemEntry(int sku)
{
	struct Item item;
	item.sku = sku;
	printf("        SKU: %d\n",sku);
	printf("       Name: ");
	scanf("%20[^\n]",item.name); // ?
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
		printf("|%3d|%-20s|%8.2lf|   No| %3d | %3d |%12.2lf|",item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));
		
		if (item.isTaxed == 1)
		printf("|%3d|%-20s|%8.2lf|  Yes| %3d | %3d |%12.2lf|",item.sku, item.name, item.price, item.quantity, item.minQuantity, totalAfterTax(item));
		
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
		printf("\n   Is Taxed: Yes");
		if (item.minQuantity > item.quantity)
		printf("\nWARNING: Quantity low, please order ASAP!!!\n");
	}
}

void listItems(const struct Item item[], int NoOfItems)
{
	int i;
	double gTotal = 0;
	prnTitle();
	for(i=0; i<NoOfItems; i++)
	{
		printf("%-4d", i+1);
		dspItem(item[i], LINEAR);
		gTotal += totalAfterTax(item[i]);
	}
	prnFooter(gTotal);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index)
{
	int i=0, n=0;
	for(i=0; i<NoOfRecs; i++)
	{
		if(item[i].sku == sku)
		{
			*index = i;
			n=1;
		}
	}
	return n;
}

/*int main() {
   struct Item I[21] = {
      { 4.4,275,0,10,2,"Royal Apples" },
      { 5.99,386,0,20,4,"Watermelon" },
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
      { 6.69,984,1,30,3,"Coke 24 Pack" },
      { 7.29,350,1,50,5,"Nestea 24 Pack" },
      { 6.49,835,1,20,2,"7up 24 pack" }
   };
   double val;
   int ival;
   int searchIndex;
   val = totalAfterTax(I[0]);
   printf("totalAfterTax:\n"
          "    yours=%lf\n"
          "program's=44.000000\n", val);
   val = totalAfterTax(I[7]);
   printf("totalAfterTax:\n"
          "    yours=%lf\n"
          "program's=101.474000\n", val);
   ival = isLowQty(I[0]);
   printf("isLowQty:\n"
          "    yours=%d\n"
          "program's=0\n",ival);
   ival = isLowQty(I[14]);
   printf("isLowQty:\n"
          "    yours=%d\n"
          "program's=1\n",ival);
   pause();
   
   printf("itemEntry, enter the following values:\n");
   printf("        SKU: 999\n"
      "       Name: Red Apples\n"
      "      Price: 4.54\n"
      "   Quantity: 50\n"
      "Minimum Qty: 5\n"
      "   Is Taxed: n\n");
   printf("Enter the values:\n");
   I[20] = itemEntry(999);
   printf("dspItem, Linear:\nYours: ");
   dspItem(I[20], LINEAR);
   printf(" Prog: |999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|\n");
   printf("dspItem, Form:\nYours:\n");
   dspItem(I[20], FORM);
   printf("Programs: \n");
   printf("        SKU: 999\n"
      "       Name: Red Apples\n"
      "      Price: 4.54\n"
      "   Quantity: 50\n"
      "Minimum Qty: 5\n"
      "   Is Taxed: No\n");
   I[20].quantity = 2;
   I[20].isTaxed = 1;
   pause();
   
   printf("dspItem, Linear with low value and taxed:\nYours: ");
   dspItem(I[20], LINEAR);
   printf(" Prog: |999|Red Apples          |    4.54|  Yes|   2 |   5 |       10.26|***\n");
   printf("dspItem, Form with low value:\nYours:\n");
   dspItem(I[20], FORM);
   printf("Programs: \n");
   printf("        SKU: 999\n"
      "       Name: Red Apples\n"
      "      Price: 4.54\n"
      "   Quantity: 2\n"
      "Minimum Qty: 5\n"
      "   Is Taxed: Yes\n"
      "WARNING: Quantity low, please order ASAP!!!\n");
   pause();
   
   printf("Listing Items: \n");
   listItems(I, 21);
   pause();
   printf("Locate Item, successful search:\n");
   printf("program: Found the item 999 at index: 20\n");
   printf("  Yours: ");
   if (locateItem(I, 21, 999, &searchIndex)) {
      printf("Found the item 999 at index: %d\n", searchIndex);
   }
   else {
      printf("No item with the sku 999 is in the array!\n");
   }

   printf("Locae Item, unsuccessful search:\n");
   printf("Progam: No item with the sku 732 is in the array!\n");
   printf(" Yours: ");
   if (locateItem(I, 21, 732, &searchIndex)) {
      printf("Found the item at index: %d\n", searchIndex);
   }
   else {
      printf("No item with the sku 732 is in the array!\n");
   }
   return 0;
}
*/
