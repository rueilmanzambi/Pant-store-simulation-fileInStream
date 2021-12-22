// Programmer: Rueil Manzambi                  Section: 109
// Data: April 2, 2021
// File: main.cpp
// Purpose: This file contains a program that simulates a pant store. It generates an array of 100 pants of different colors, inseams and waist sizes.
//          The customer is prompt to enter information about the pant he wants to buy, and the program sells it and update the array.


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include "header.h"

//=====================================================================
//
// Don't ask to print the inventory, it should do it automatically
//
// Deductions: -5
//=====================================================================

using namespace std;

int main()
{
  srand(time(NULL));
  
  char more_customer; // check if there's a customer
  int customer_waist;
  string color[] = {"black","blue", "red", "rainbow", "checkered", "electric green","polka dot"};
  Pant pant_array[NUM_PANTS];
  Pants_of_size waist_index_array[NUM_WAIST_SIZE];
  
  cout << "\t\t\tWelcom to the premium pants store" << endl;
  cout << "\t\t\t---------------------------------\n" << endl;

  random_fill_array(pant_array);
  index_fill_array(waist_index_array, pant_array);
  
  print_inventory(waist_index_array, pant_array, color);

  do // looping until there's no customer
  {
    cout << "Would you like to take a look at our premium high-water trousers ? (y/n): ";
    cin >> more_customer;

    if (more_customer == 'y' || more_customer == 'Y') // start processing if there's a customer
    {
      cout << "Please, enter your waist measurement: ";
      cin >> customer_waist;
      if (customer_waist < MIN_WAIST || customer_waist > MAX_WAIST)
        cout << "Sorry, we do not have that waist size. Check with the store on the next block." << endl;
      else
        handle_customer_order(customer_waist, color,pant_array,waist_index_array);
    }
    else if (more_customer == 'n' || more_customer =='N')
      cout << "\nSigning off... bye!" << endl;

  } while (more_customer != 'n' && more_customer != 'N');
  
  return 0;
}
