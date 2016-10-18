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

//Including Personal library
#include "functions_for_craps.h" //Header files contains prototypes and Libararies

int main (void)
{
	run_craps (); //runs games and contains logic 
	return 0; //the program returns 0 at the end that means everything was executed.
}