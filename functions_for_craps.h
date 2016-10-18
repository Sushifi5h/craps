/*******************************************************************************************
* Student: Vikram Singh StudentID: 11491025                                                *
* Class: CptS 121, Fall  2015; Lab Section 5                                               *
* Programming Assignment 4: A Game of Chance "Craps"                                       *
* Date: September 19, 2015                                                                 *
* Description: This program will processes numbers, corresponding to student records read  *
in from a file, and writes the required result to a differnet file.						   *
*																						   *
*Relevant Formulas:																		   *
*	x1 + x2                                                                                *
*	x1 - x2                                                                                *
*																						   *
*Other Requirements: 																	   *
*	:2 files (input/outputs)					  										   *
*   :prompting user																		   *
*	:chatter	                														   *	
*	:(if, else if, while, do-while, for)for itterations        							   *	
*	                																	   *	
*******************************************************************************************/
//The next to lines help this header file from being called over and also know as (Including gaurd) //Learned from wikki and youtube (https://en.wikipedia.org/wiki/Include_guard)
#ifndef FUNCTIONS_FOR_CRAPS_H 
#define FUNCTIONS_FOR_CRAPS_H

//Doing this stop annoying errors
#define _CRT_SECURE_NO_WARNINGS //Stop unwanted printf errors

//Including libarises that will be used to write this program
#include <stdio.h> //Fuctions that will be used but not limited to scanf (), printf (), fopen (), fclose (), fscanf (), fprintf ()
#include <stdlib.h> //Functions that will be used but not limited to rand()
//#include <time.h> //for srand

//Prototypes
void run_craps (void); // Runs craps contains all logic
void print_game_rules (void); //shows basic rules of the games
double get_bank_balance (void); //prompt user to enter an intial bank ammount and display what they entered
double get_wager_amount (void); //Prompts the player for a wager on a particular roll. The wager is returned.
int check_wager_amount (double wager, double balance); //Checks to see if the wager is within the limits of the player's available balance.
int roll_dice (void); //Rolls one dice. 
int calculate_sum_dice (int dice_1_value, int dice_2_value); //Sums together the values of the two dice and returns the result. 
int is_win_loss_or_point (int sum_dice); //Determines the result of the first dice roll. If the sum is 7 or 11 on the roll, 
int is_point_loss_or_neither (int sum_dice, int point_value);// Determines the result of any successive roll after the first roll. 
double adjust_bank_balance (double bank_balance, double wager_amount, int add_or_subtract); //If add_or_subtract is 1, then the wager amount is added to the bank_balance. 
void chatter_messages (int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);//Prints an appropriate message dependent on the number of rolls taken so far by the player
int player_loses ( double current_bank); //checks players bank so he/she can play
void dice_art (int dice_number); //dice art with dice number





#endif //This statement ends the gaurd