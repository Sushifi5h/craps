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


/*************************************************************
 * Function: run_craps (void) 		                         *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: runs crap games contains all logic 			 *
 * Input parameters: None                                    *
 * Returns: Nothing                                          *
 * Preconditions: calling it.                                *
 * Postconditions: starts game logic                         *
 *************************************************************/
 void run_craps (void)
 {
 	//Variables need to be tracked and init to 0
 	int number_rolls = 0, dice_sum = 0, dice_1 =0, dice_2 = 0, player_score = 0, wager_check = 0;
 	double initial_bank_account = 0.0, current_bank_account = 0.0, wager_amount = 0.0;
 	srand ((unsigned int) time (NULL));

 	//fuctions
 	print_game_rules(); //brief intro

 	initial_bank_account = get_bank_balance(); //set init balance

 	current_bank_account = initial_bank_account; //set the current balance

 	//initialize number rolls / saved dice
 	number_rolls = 1;


 	//may alogriythim of the game
 	do
 	{
 		//random chatter
 		chatter_messages (number_rolls, 1, initial_bank_account, current_bank_account);

 	 	//variables that need to reset
 		player_score = 0;
 		wager_amount = 0.0;
 		wager_check = 0;
 		dice_1 = 0;
 		dice_2 = 0;
 		dice_sum = 0;

 	 	//Ask for wagger
 		wager_amount = get_wager_amount ();

 	 	//check wage to bank 1 is a good 0 is not enough
 		wager_check = check_wager_amount ( wager_amount, current_bank_account);

 	 	//roll dice if but check wager
 		if (1 == wager_check)
 	 	{
 	 		//roll dice since wage is good
 			dice_1 = roll_dice ();
 			dice_2 = roll_dice ();

 			//dice art
 			dice_art (dice_1);
 			dice_art (dice_2);


 	 		//itterate number of roll
 			number_rolls++;

 	 		//sum dice
 			dice_sum = calculate_sum_dice ( dice_1, dice_2);

 

 	 		//Check results for rolls with frist roll
			if ( is_win_loss_or_point (dice_sum) == 1 )
		 	{
		 		// add to bank
				current_bank_account = adjust_bank_balance ( current_bank_account, wager_amount, 1);
		 	}
		 	//player losses
			else if ( is_win_loss_or_point (dice_sum) == 0 )
		 	{
		 		//deduct from bank
				current_bank_account = adjust_bank_balance ( current_bank_account, wager_amount, 0);

		 	}
		 	//handle scoring bit 
			else if ( is_win_loss_or_point (dice_sum) == -1 )
		 	{
		 		//set player score
				player_score = dice_sum;

				

 		 		//Do this until we get conculsion
 				while (1)
 					{
			 			//reset dice
						dice_1 = 0;
	 					dice_2 = 0;
	 					dice_sum = 0;

	 					//reroll
	 					dice_1 = roll_dice ();
	 					dice_2 = roll_dice ();

	 					//dice art
 						dice_art (dice_1);
 						dice_art (dice_2);

	 	 				//itterate rolls
	 					number_rolls++;

	 	 				//sum dice
	 					dice_sum = calculate_sum_dice ( dice_1, dice_2);

	 	 				//player wins
	 					if ( is_point_loss_or_neither ( dice_sum, player_score) == 1 ) 
						{
			 				//update bank for winner
							current_bank_account = adjust_bank_balance ( current_bank_account, wager_amount, 1);
							break;
						}
			 			//player loses
						else if ( (is_point_loss_or_neither ( dice_sum, player_score) == 0) )
						{
			 				//deduct from bank
							current_bank_account = adjust_bank_balance ( current_bank_account, wager_amount, 0);
							break;
						}
 				}

			}
			 

 		} 

 	} while ( player_loses (current_bank_account) );



 }
/*************************************************************
 * Function: print_game_rules (void)                         *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: When call print basic rules  craps to screen *
 * Input parameters: None                                    *
 * Returns: Nothing                                          *
 * Preconditions: calling it.                                *
 * Postconditions: prints to screen                          *
 *************************************************************/
void print_game_rules (void)
{

	//Rules from (http://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA4.htm)
	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf ("Rules from (http://eecs.wsu.edu/~aofallon/cpts121/progassignments/PA4.htm)\n\n");
	printf ("A player rolls two dice. Each die has six faces. These faces contain\n");
	printf ("1, 2, 3, 4, 5, and 6 spots. After the dice have come to rest, the sum\n");
	printf ("of the spots on the two upward faces is calculated. If the sum is 7 or\n");
	printf ("11 on the first throw, the player wins. If the sum is 2, 3, or 12 on\n");
	printf ("the first throw (called \"craps\"), the player loses(i.e. the \"house\" wins).\n");
	printf ("If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes\n");
	printf ("the player's \"point.\" To win, you must continue rolling the dice until you\n");
	printf ("\"make your point.\" The player loses by rolling a 7 before making the point.\n");
	printf ("At any point you may stop the game by pressing Ctrl + C. Have Fun.\n");
	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

/*************************************************************
 * Function: get_bank_balance (void)                         *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: When call ask for bank ammount and display $ *
 * Input parameters: None                                    *
 * Returns: Nothing                                          *
 * Preconditions: game started                               *
 * Postconditions: return bank prints to screen              *
 *************************************************************/
 double get_bank_balance (void)
 {
 	//local var to store bank
 	double total_bank = 0.0; //declare var and inizialize

 	//prompt user for bank balance and assign it to local var
 	do{

 		printf ("[DEALER] Please enter the ammount you would like to deposit in USD.\n(Example for $100.00 enter 100): ");
 		scanf (" %lf", &total_bank);

 	}while (total_bank <= 0);
 	
 	//display user bank
 	printf ("[DEALER] You entered: $%.2lf\n", total_bank);
 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 	//return total bank
 	return total_bank;
 }

/*************************************************************
 * Function: double get_wager_amount (void)                  *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: When call ask for wager ammount and display $*
 * Input parameters: None                                    *
 * Returns: Nothing                                          *
 * Preconditions: bank already exist                         *
 * Postconditions: prints to screen /return wager            *
 *************************************************************/
 double get_wager_amount (void)
 {
 	//local var to store wager
 	double total_wager = 0.0; //declare var and inizialize

 	//prompt user for wager and assign it to local var
 	do{

 		printf ("[DEALER] Please enter the ammount you would like to wager in USD.\n(Example for $100.00 enter 100): ");
 		scanf (" %lf", &total_wager);
 		
 	}while (total_wager <= 0);
 	
 	//display user wager
 	printf ("[DEALER] You entered: $%.2lf\n", total_wager);
 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 	//return total wager
 	return total_wager;
 }

/*************************************************************
 * Function: int check_wager_ammount (double, int)           *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: compare player bank to wager 				 *
 * If the wager exceeds the player's allowable ba k,then 0   *
 * is returned; otherwise 1 is returned.					 *
 * Input parameters: None                                    *
 * Returns: Nothing                                          *
 * Preconditions: bank already exist, wager exist            *
 * Postconditions: prints to screen /return 1 or 0           *
 *************************************************************/
 int check_wager_amount (double wager, double bank)
 {
 	//display entered ammounts
 	printf ("[DEALER] You have $%.2lf in your bank & $%.2lf in your wager.\n", bank, wager);


 	//see if bank as as much or more than wager
 	if (bank >= wager)
 	{
 		// //print a chatter
 		printf ("[DEALER] Shooter is clear! Shot away!\n");
 		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return 1
 		return 1;
 	}
 	//player does not have enough bank to play
 	else{
 		//print chatter
 		printf ("[DEALER] Shooter you are out of bullets!\n");
 		printf ("[DEALER] Try a lower bid.\n");
 		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return 0
 		return 0;
 	}
 }

/*************************************************************
 * Function: int roll_dice (void) 				             *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: Rolls a single dice using rand 				 *
 * returns the rolled ammount at an int inclusive 1-6		 *
 * Input parameters: None                                    *
 * Returns: 1-6 inclusive                                    *
 * Preconditions: None            	 		                 *
 * Postconditions: prints to screen /return dice roll        *
 *************************************************************/
 int roll_dice (void)
 {
 	//local var for dice roll
 	int rolled_dice = 0;

 	//roll dice using rand and assing to rolled dice
 	rolled_dice = (rand() % 6) + 1; //rand is rand() % (6) is exculsive doesn't includes 6 adding 1 will include 1 and 6 and not 0

 	//return dice value
 	return rolled_dice;
}

/*************************************************************
 * Function: int calculate_sum_dice (int , int)              *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: Combines dice rolls         				 *
 * returns the added ammount    							 *
 * Input parameters: 2 dice values                           *
 * Returns: added score                                      *
 * Preconditions: dice roll exist already                    *
 * Postconditions: prints to screen /return sum of dice roll *
 *************************************************************/
int calculate_sum_dice (int dice_1_value, int dice_2_value)
{
	//local var to add sum
	int sum_dice_value;

	//Do math
	sum_dice_value = dice_1_value + dice_2_value;

	//Dealer chatter
	printf ("[DEALER] Shooter you have a score of %d!\n", sum_dice_value);
 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	//return sum of dice
	return sum_dice_value;
}

/*************************************************************
 * Function: int is_win_loss_or_point (int)                  *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: Frist roll of the game          	 		 *
 *:if the sum is 7 or 11 on the roll, the player returns 1   *
 *:if the sum is 2, 3, or 12 on the first throw				 *
 *(called "craps"), the player loses (i.e. the "house" wins) *
 *and 0 is returned											 *
 *:If the sum is 4, 5, 6, 8, 9, or 10 on the first throw,    *
 *then the sum becomes the player's "point" and -1  returned *
 * Input parameters: sum dice values                         *
 * Returns: -1, 0 , 1                                        *
 * Preconditions: sum dice rolls exist already               *
 * Postconditions: game may direction will be affected       *
 *************************************************************/
 int is_win_loss_or_point (int sum_dice)
 {
 	//Player wins
 	if ( (7 == sum_dice) || (11 == sum_dice) )
 	{

 		//Dealer chatter
 		printf ("[DEALER] AIN'T YOU JUST A SHARP SHOTTER YOU WIN PARTNER!\n");
 		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return value to a winner
 		return 1;

 	}
 	//check if players losses / house wins
 	else if ( (2 == sum_dice) || (3 == sum_dice) || (12 == sum_dice) ){

		//Dealer Chatter
		printf ("[DEALER] Looks like I win this time. Try again if you have wager.\n");
 		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return loss 
 		return 0;
	} 
	//since we already checked for all our conditions we can use else and follow through
	else
	{
		//dealer chatter
		// printf ("[DEALER] You Rolled a %d!\n", sum_dice);
		// printf ("[DEALER] Looks like we keep on playing. Show us how it's done Shooter.\n");
 	// 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return game contiune
 		return -1;
	}
 }



/*************************************************************
 * Function: int is_point_loss_or_neither (int, int)         *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: successive rolls of the game          	 	 *
 *:If the sum of the roll is the point_valuethen returns 1   *
 *:If the sum of the roll is a 7, then 0 is returned		 *
 *:Otherwise, -1 is returned                                 *
 * Input parameters: sum dice values                         *
 * Returns: -1, 0 , 1                                        *
 * Preconditions: sum_dice exist,point value exist           *
 * Postconditions: game may direction will be affected       *
 *************************************************************/
 int is_point_loss_or_neither (int sum_dice, int point_value)
  {
 	//Player wins
 	if ( (point_value == sum_dice) )
 	{

 		//Dealer chatter
 		printf ("[DEALER] AIN'T YOU JUST A SHARP SHOTTER YOU WIN PARTNER!\n");
 		printf ("[DEALER] That exactly what you rolled on your first roll %d\n", point_value);
 		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return value to a winner
 		return 1;

 	}
 	//check if players losses / house wins
 	else if ( (7 == sum_dice) ){

		//Dealer Chatter
		printf ("[DEALER] House wins do play again.\n");
 		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return loss 
 		return 0;
	} 
	//since we already checked for all our conditions we can use else and follow through
	else
	{
		//dealer chatter
		printf ("[DEALER] Looks like we keep on playing. Show us how it's done Shooter.\n");
 		printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 		//return game contiune
 		return -1;
	}
 }

/*************************************************************
 * Function: double adjust_bank_balance (double, double, int)*
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: Adjust bank acccount                	 	 *
 *:If add_or_subtract is 1: 								 *
 *		then the wager amount is added to the bank_balance   *
 *:If If add_or_subtract is 0:								 *
 *		then the wager amount is subtracted from bank_balance*
 *:Otherwise:				                                 *
 *    the bank_balance remains the same. 					 *
 * The bank_balance result is returned    				     *
 * Input parameters: bank, wager, outcome                    *
 * Returns: double new bank                                  *
 * Preconditions: input values exist                         *
 * Postconditions: bank updates	if called properly           *
 *************************************************************/
 double adjust_bank_balance (double bank_balance, double wager_amount, int add_or_subtract)
 {
 	//local variables
 	double new_bank = 0.0;

 	//Dealer Chatter
	printf ("[DEALER] Let me look into your account real quick.\n");
	printf ("[DEALER] You have a $%.2lf in your bank!\n", bank_balance);
	printf ("[DEALER] You had waggered $%.2lf!\n", wager_amount);
 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");




 	switch (add_or_subtract)
 	{
 		//handles -1: the bank_balance remains the same.
 		case -1:

 			//Dealer Chatter
 			printf ("[DEALER] Sometimes in life its better to not to do anything, this is one of those times. You have $%.2lf in your bank.\n", bank_balance);
 			printf ("[DEALER] So we are going to leave it there. You still have $%.2lf.\n", bank_balance);
 			printf ("[DEALER] Aw cmon, take a chance!\n");
 			printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 			//no math needed
 			new_bank = bank_balance;
 			
 			//break needed
 			break;
 		case 0:

 			//Dealer Chatter
 			printf ("[DEALER] You and I both know you can't win em'all. You lost your last wager so I am subtracting $%.2lf from your bank.\n", wager_amount);
 			printf ("[DEALER] So your bank now is $%.2lf\n", bank_balance - wager_amount);
 			printf ("[DEALER] Better luck next time bud.\n");
 			printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 			//Math
 			new_bank = bank_balance - wager_amount;

 			
 			//break needed
 			break;
 		case 1:
 			//Dealer Chatter
 			printf ("[DEALER] Shooter you won last wager so I am adding $%.2lf to your bank.\n", wager_amount);
 			printf ("[DEALER] So your bank now is $%.2lf\n", wager_amount + bank_balance);
 			printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 			//Math
 			new_bank = wager_amount + bank_balance;

 			//break is not neede
 	}

 	return new_bank;
 	// //if add_or_subtract is 1 player won
 	// if ( 1 == add_or_subtract )
 	// {
 	// 	//Dealer Chatter
 	// 	printf ("[DEALER] Shooter you won last wager so I am adding $%.2lf to your bank.\n", wager_amount);
 	// 	printf ("[DEALER] So your bank now is $%.2lf\n", wager_amount + bank_balance);
 	// 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 	// 	//Math
 	// 	new_bank = wager_amount + bank_balance;

 	// 	//return new bank
 	// 	return new_bank;
 	// }
 	// //This will check for 0 the player lost  
 	// else if ( !add_or_subtract )
 	// {

 	// 	//Dealer Chatter
 	// 	printf ("[DEALER] You and I both know you can't win em'all. You lost your last wager so I am subtracting $%.2lf from your bank.\n", wager_amount);
 	// 	printf ("[DEALER] So your bank now is $%.2lf\n", bank_balance - wager_amount);
 	// 	printf ("[DEALER] Better luck next time bud.\n");
 	// 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 	// 	//Math
 	// 	new_bank = wager_amount - bank_balance;

 	// 	//return new bank
 	// 	return new_bank;
 	// }
 	// //handles -1
 	// else if ( add_or_subtract == -1 )
 	// {

 	// 	//Dealer Chatter
 	// 	printf ("[DEALER] Sometimes in life its better to not to do anything, this is one of those points. You have $%.2lf in your bank.\n", bank_balance);
 	// 	printf ("[DEALER] So we are going to leave it there $%.2lf\n", bank_balance);
 	// 	printf ("[DEALER] Aw cmon, take a chance!\n");
 	// 	printf ("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

 	// 	//no math needed return value
 	// 	return bank_balance;
 	// }
 }
 	

/*************************************************************
 * Function: void chatter_messages ( 2 x double, 2 x int)    *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: chatter to enterian player                	 *
 * will use percentable to init bank account compared current*
 * win_loss_neither indicates the result previous roll       *
 * Input parameters: rools wins/loss/neither init bank c bank*
 * Returns: nothing                                          *
 * Preconditions: input values exist                         *
 * Postconditions: none                                      *
 *************************************************************/
 void chatter_messages (int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
 {
 	//if .10 of of initial_bank_balance >= current_bank_balance
 	if ( ((0.10 * initial_bank_balance) >= current_bank_balance) )
 	{
 		printf ("[DEALER] I would tell you to stop but at this point well you know. Play on.\n");
 	}
 	//if number of rolls greater than 7
 	else if (number_rolls >= 7)
 	{
 		printf ("[DEALER] You are on a roll! Keep rolling Shooter.\n");
 	}
 	//Won a lot
	else if ((current_bank_balance * 1.6 >= initial_bank_balance))
 	{
 		printf ("[DEALER] This is how it's done you are in the money.\n");
 	}
 }
 /*************************************************************
 * Function: player_loses ( c bank)    						 *
 * Date Created: 10/03/15                                    *
 * Date Last Modified: 10/03/15                              *
 * Description: Tracks player funds                     	 *
 * Input parameters: current bank  							 *
 * Returns: 1 or 0                                           *
 * Preconditions: input values exist                         *
 * Postconditions: may stop game                             *
 *************************************************************/
int player_loses ( double current_bank)
{
	//check to see if bank is positive
	if (current_bank > 0)
	{
		return 1;
	}
	//if less than 0 
	else {
		return 0;
	}
}

void dice_art (int dice_number)
{
	switch (dice_number)
	{
		//dice from (http://codegolf.stackexchange.com/questions/2602/draw-dice-results-in-ascii)
		case 1:
			//drawdice
			printf ("-----\n");
			printf ("|   |\n");
			printf ("| o |\n");
			printf ("|   |\n");
			printf ("-----\n");
			break; //breaks out and stop execution below code
		case 2:
			//draw dice
			printf ("-----\n");
			printf ("|o  |\n");
			printf ("|   |\n");
			printf ("|  o|\n");
			printf ("-----\n");
			break; //breaks out and stop execution below code
		case 3:
			//draw dice
			printf ("-----\n");
			printf ("|o  |\n");
			printf ("| o |\n");
			printf ("|  o|\n");
			printf ("-----\n");
			break;//breaks out and stop execution below code
		case 4:
			//draw dice
			printf ("-----\n");
			printf ("|o o|\n");
			printf ("|   |\n");
			printf ("|o o|\n");
			printf ("-----\n");
			break;//breaks out and stop execution below code
		case 5:
			printf ("-----\n");
			printf ("|o o|\n");
			printf ("| o |\n");
			printf ("|o o|\n");
			printf ("-----\n");
			break; //breaks out and stop execution below code
		case 6:
			printf("-----\n");
			printf("|o o|\n");
			printf("|o o|\n");
			printf("|o o|\n");
			printf("-----\n");
			break; //breaks out and stop execution below code
	}		
}