#include <stdio.h>
/***************************************************************
Tester Function prototypes */

void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();
/**************************************************************/
int main() {
   printf("================================\n");
   searchTest();
   printf("================================\n");
   updateTest();
   printf("================================\n");
   addTest();
   printf("================================\n");
   addOrUpdateTest();
   printf("================================\n");
   adjustQtyTest();
   printf("================================\n");
   return 0;
}
