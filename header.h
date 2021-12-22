// Programmer: Rueil Manzambi                  Section: 109
// Data: April 2, 2021
// File: header.h
// Purpose: This is the header file for main.cpp of hw6. It contains constants, functions prototypes and structs

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

/* constants initialization */
const int MAX_NUM_COLORS = 7;
const int NUM_PANTS = 100;
const int MAX_WAIST = 40;
const int MIN_WAIST = 20;
const int NUM_WAIST_SIZE = 21;
const int AT_LEAST_ONE_COLOR = 1;
const int TWO_COLORS_AVAILABLE = 2;
const int NO_COLOR_RECORDED = 0;
const int NO_COLOR_CHOICE = -1;
const int BONUS_CHARGE = 40;
const int MIN_INCH_INSEAM = 2;
const float WAIST_MULTIPLIER = 0.9;

// for inventory array
struct Pant
{
  int m_waist;
  int m_inseam;
  int m_color;
  bool m_available;

};

// for index array
struct Pants_of_size
{
  int m_index_waist;
  short m_index_color_array[MAX_NUM_COLORS] = {0};
};

/* Functions prototypes */
string get_color_name(const int color_index, const string color_string[]);
int get_inseam();
bool valid_color_choice(const Pants_of_size index_array[], const int customer_waist, const int customer_color_choice);
bool valid_inseam_choice(const Pant my_array[], const int customer_inseam_choice, const int customer_waist, const int customer_color_choice);
void random_fill_array(Pant my_array[]);
void index_fill_array(Pants_of_size index_array[], Pant my_array[]);
void print_inventory (const Pants_of_size index_array[], const Pant my_array[], const string color_string[]);
void handle_customer_order(const int customer_waist, const string color_string[], Pant my_array[], Pants_of_size index_array[]);
void output_available_inseam(const Pant my_array[], const int customer_waist, const int customer_color_choice, const string color_string[]);
void sell_pant(const int customer_waist, const int customer_inseam_choice);
void update_pant_array(Pant my_array[], const int customer_waist, const int customer_color_choice, const int customer_inseam_choice);
void update_index_array(Pants_of_size index_array[], const int customer_waist, const int customer_color_choice);


#endif
