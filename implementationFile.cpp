// Programmer: Rueil Manzambi                  Section: 109
// Data: April 2, 2021
// File: implementaionFile.cpp
// Purpose: This is the implementation file for main.cpp of hw6. It contains functions definitons to be used in the main program


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include "header.h"

using namespace std;



// Description: Fills up the passed array
// Pre: my_array[] has to be public
// Post: fills the array, returns nothing 
void random_fill_array(Pant my_array[])
{
  for (int i=0; i < NUM_PANTS; i++)
  {
    my_array[i].m_waist = rand()%((MAX_WAIST - MIN_WAIST) + 1) + MIN_WAIST;
    my_array[i].m_color = rand() % MAX_NUM_COLORS;
    my_array[i].m_inseam = get_inseam();
    my_array[i].m_available = true;
  }
  return;
}

// Description: Gets an inseam value from a file
// Pre: The file has to be in the same directory as the file
// Post: gets the inseam value and returns it
int get_inseam()
{
  int num_data = 0;
  int inseam;
  int rand_num;
  int walk_thru_file;
  
  ifstream fin;  
  fin.open("inseams.dat");
  
  while (fin >> walk_thru_file)
    num_data += 1; // get the size of the file
    
  fin.clear();
  fin.seekg(0);
  
  rand_num = rand() % (num_data) + 1;
  
  for (int i = 0; i<rand_num; i++)
    fin >> inseam; 
    
  fin.close();

  return inseam;   
}

// Description: Fills up the indexarray
// Pre: my_array[] has to be full
// Post: Fills up the index_array, returns nothing    
void index_fill_array(Pants_of_size index_array[], Pant my_array[])
{
  int index = 0;

  for (int i = MIN_WAIST; i <= (MIN_WAIST + NUM_WAIST_SIZE); i++)
  {
    index_array[index].m_index_waist = i; 
    index += 1;
  }

  for (int i = 0; i < NUM_PANTS; i++)
  {
    for (int j = 0; j < NUM_WAIST_SIZE; j++)
    {
      if (my_array[i].m_waist == index_array[j].m_index_waist)
        index_array[j].m_index_color_array[my_array[i].m_color] += 1; // filling the member array of index_array
    }
  }
  return;
}

// Description: Outputs the pants that exist in the inventory, with waist size as a reference
// Pre: index_array and my_array should already be filled up
// Post: outputs the inventory of pants by their waist size
void print_inventory (const Pants_of_size index_array[], const Pant my_array[], const string color_string[])
{
  static bool first_pant_not_printed = true;
  static bool waist_not_printed = true;

  for (int i = 0; i < NUM_WAIST_SIZE; i++)
  {
    for (int j = 0; j < NUM_PANTS; j++)
    {
      if (my_array[j].m_waist == index_array[i].m_index_waist)
      {
        if (waist_not_printed) // check if waist size has already be printed
        {
          cout << "waist " << index_array[i].m_index_waist;
          waist_not_printed = false;
        }
        if (first_pant_not_printed) 
        {
          cout <<"   " << "inseam " << my_array[j].m_inseam << "  " << get_color_name(my_array[j].m_color,color_string) << endl;  
          first_pant_not_printed = false;
        }
        else 
        {
          cout << "           inseam " << my_array[j].m_inseam << "  " << get_color_name(my_array[j].m_color,color_string) << endl;
        }
      }
    }
    waist_not_printed = true; // these are updated when we are done with a waist size
    first_pant_not_printed = true;
  }
  return;
}    

// Description: get the string value of the array color_string at the index color_index
// Pre: the array of strings is filled in main
// Post: returns the string value of the array color_string at the index color_index
string get_color_name(const int color_index, const string color_string[])
{
  return color_string[color_index];
}

// Description: handles customer's order. It gets inseam, color values and checks if they are valid. It calls other function to make the sell
//              and update the inventory
// Pre: all the arguments are filled up prior to this function
// Post: check the availability of the waist, checks the validity of inseam and color. calls other functions to sell a pant and update the
//       inventory 
void handle_customer_order(const int customer_waist, const string color_string[], Pant my_array[], Pants_of_size index_array[])
{
  bool waist_available = false;
  int available_colors = 0;
  int num_colors = 1;
  int customer_color_choice;
  int customer_inseam_choice;

  for (int i = 0; i < NUM_PANTS; i++) 
  {
    if (customer_waist == my_array[i].m_waist)
    {                                           // to check if waist size is available
      if (my_array[i].m_available == true)
        waist_available = true;
    }
  }
  if (waist_available)
  {
    cout << "For waist size " << customer_waist << ", we have: ";

    for (int i = 0; i < NUM_WAIST_SIZE; i++)              
    {
      if (index_array[i].m_index_waist == customer_waist)
      {                                                          
        for (int j = 0;j < MAX_NUM_COLORS; j++)
        {
          if (index_array[i].m_index_color_array[j] >= AT_LEAST_ONE_COLOR) // number of available colors in member array of 
            available_colors += 1;                                         // index_array
        }                                                 
        if (available_colors == AT_LEAST_ONE_COLOR) // if there's one available color
        {
          for (int j = 0; j < MAX_NUM_COLORS; j++)
          {
            if (index_array[i].m_index_color_array[j] >= AT_LEAST_ONE_COLOR)
              cout << color_string[j] << "(enter " << j << "). ";
          }
        }
        else if (available_colors == TWO_COLORS_AVAILABLE) // if there are two available colors
        {
          num_colors = available_colors;
          for (int j = 0; j < MAX_NUM_COLORS; j++)
          {
            if (index_array[i].m_index_color_array[j] >= AT_LEAST_ONE_COLOR)
            {
              if (num_colors == AT_LEAST_ONE_COLOR)
              {
                cout << ", and " << color_string[j] << "(enter " << j <<"). "; // prints the last color
              }
              else 
              {
                cout << color_string[j] << "(enter " << j << ")"; // prints the first color
                num_colors -= AT_LEAST_ONE_COLOR;
              } 
            }
          }
        }
        else // if there are more than two available colors
        {
          for (int j = 0; j < MAX_NUM_COLORS; j++)
          {
            if (index_array[i].m_index_color_array[j] >= AT_LEAST_ONE_COLOR)
            {
              if (num_colors == available_colors) // prints the last color
                cout << ", and " << color_string[j] << "(enter " << j << "). ";
              else if (num_colors == available_colors - AT_LEAST_ONE_COLOR)
              {
                cout << color_string[j] << "(enter " << j << ")"; // prints the second to last color
                num_colors += AT_LEAST_ONE_COLOR;
              }
              else
              {
                cout << color_string[j] << "(enter " << j << "), "; 
                num_colors += AT_LEAST_ONE_COLOR;
              }
            }
          }                    
        }
      }
    }
    cout <<"Enter your choice(-1 for none): ";
    cin >> customer_color_choice;

    if (customer_color_choice != -1) // process only if input is not -1
    {
      while (!(valid_color_choice(index_array, customer_waist, customer_color_choice)))
      {
        cout << "Please, enter a valid color number: ";
        cin >> customer_color_choice;
      }
      if (customer_color_choice != -1) // recheck if input is -1
      {
        output_available_inseam(my_array, customer_waist, customer_color_choice, color_string);
        cout << "Please, enter the inseam from the listed inseam(s): ";
        cin >> customer_inseam_choice;
        while (!(valid_inseam_choice(my_array, customer_inseam_choice, customer_waist, customer_color_choice)))
        {
          cout << "Please, enter a valid inseam number: ";
          cin >> customer_inseam_choice;
        }
        sell_pant(customer_waist, customer_inseam_choice);
        update_pant_array(my_array, customer_waist, customer_color_choice, customer_inseam_choice);
        update_index_array(index_array, customer_waist, customer_color_choice);
      }
    }
  }
  else // if waist size is not available
    cout <<"Sorry, we are out of this waist size. Please, check in next week after we get new merchandise." << endl;  
  return;
}

// Description: checks if the customer_color_choice is valid
// Pre: arguments are filled up prior to function call
// Post: returns a bool for the validity of the customer's choice
bool valid_color_choice(const Pants_of_size index_array[], const int customer_waist, const int customer_color_choice) 
{
  bool return_value = false;
  
  if (customer_color_choice < NO_COLOR_CHOICE || (customer_color_choice > (MAX_NUM_COLORS - AT_LEAST_ONE_COLOR)))
    return_value = false;
  else if (customer_color_choice == NO_COLOR_CHOICE)
    return_value = true;
  else
  {
    for (int i = 0; i < NUM_WAIST_SIZE; i++)
    { 
      if (index_array[i].m_index_waist == customer_waist)
      {
        if (index_array[i].m_index_color_array[customer_color_choice] >= AT_LEAST_ONE_COLOR) // checks if there's a pant at the chosen location
          return_value = true;
      }
    }
  }
  return return_value;
}  

// Description: Outputs available inseam values
// Pre: arguments should be filled up prior to the call
// Post: Outputs available inseam values, returns nothing
void output_available_inseam(const Pant my_array[], const int customer_waist, const int customer_color_choice, const string color_string[])
{
  cout << "For waist size " << customer_waist << " and color " << color_string[customer_color_choice] << ", we have the following inseam(s):" << endl;
  for (int i = 0; i < NUM_PANTS; i++)
  {
    if (customer_waist == my_array[i].m_waist)
    {
      if (customer_color_choice == my_array[i].m_color)
      {
        if(my_array[i].m_available == true)
          cout << "Inseam number: " << my_array[i].m_inseam << endl;
      }
    }
  }
  return;
}

// Description: checks if the customer's inseam choice is valid
// Pre: arguments are filled up prior to the function call
// Post: checks if the customer's inseam choice is valid          
bool valid_inseam_choice(const Pant my_array[], const int customer_inseam_choice, const int customer_waist, const int customer_color_choice)
{
  bool return_value = false;

  for (int i = 0; i < NUM_PANTS; i++)
  {
    if (customer_waist == my_array[i].m_waist)
    {
      if (customer_color_choice == my_array[i].m_color)
      {
        if (customer_inseam_choice == my_array[i].m_inseam)
          return_value = true;
      }
    }
  }
  return return_value;
}

// Description: computes the price and sells the pant to the customer
// Pre: arguments have to be valid prior to the function call
// Post: computes the price and sells the pant to the customer
void sell_pant(const int customer_waist, const int customer_inseam_choice)
{
  float price;

  if (((WAIST_MULTIPLIER * customer_waist) - customer_inseam_choice) >= MIN_INCH_INSEAM)
    price = customer_waist + customer_inseam_choice + BONUS_CHARGE;
  else
    price = customer_waist + customer_inseam_choice;

  cout << "The final price for the pant is $" << price << endl;
  cout << "\nProcessing......Thank you for shopping with us, have a good day!" << endl;

  return;
}

// Description: updates my_array[]
// Pre: integer arguments have to be valid, and the pant with integer arguments attributes has to be sold
// Post: updates my_array[] by setting the sold pant availability to false
void update_pant_array(Pant my_array[], const int customer_waist, const int customer_color_choice, const int customer_inseam_choice)
{
  bool found_pant = false;

  for (int i = 0; i < NUM_PANTS; i++)
  {
    if (!found_pant)
    {
      if (customer_waist == my_array[i].m_waist)
      {
        if (customer_color_choice == my_array[i].m_color)
        {
          if (customer_inseam_choice == my_array[i].m_inseam)
          {
            if (my_array[i].m_available == true)
            {
              my_array[i].m_available = false;
              found_pant = true;
            }
          }
        }
      }
    }
  }
  return;
}

// Description: updates index_array[]
// Pre: integer arguements have to be valid, and the pant with integer arguments attributes has to be sold
// Post: updates index_array[] by removing the sold pant
void update_index_array(Pants_of_size index_array[], const int customer_waist, const int customer_color_choice)
{
  bool found_pant = false;

  for (int i = 0; i < NUM_WAIST_SIZE; i++)
  {
    if (!found_pant)
    {
      if (customer_waist == index_array[i].m_index_waist)
      {
        index_array[i].m_index_color_array[customer_color_choice]--;
        found_pant = true;
      }
    }
  }
  return;
}
