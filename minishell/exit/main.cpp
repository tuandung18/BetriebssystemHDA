#include <iostream>

using namespace std;

int main()
{
   cout<<"Do you want to exit: y/n? ";
   char c;
   cin >> c;
   switch (c) {
   case 'y':
       exit(0);
       break;
   default:break;
   }
}
