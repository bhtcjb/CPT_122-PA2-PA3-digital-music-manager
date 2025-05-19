/*******************************************************************************
 * Programmer: Blake Turman			                                           *
 * Class: CptS 122; Lab Section 3                                              *
 * Programming Assignment: PA 3	                                               *
 * Date: 1/22/25                                                               *
 *                                                                             *
 * Description: This program is like iTunes but better                         *
 *                                                                             *
 * Relevant Formulas: Refer to each function definition.                       *
 *                                                                             *
 * Format of record in input file (musicPlayList.csv):						   *
 *						"\"Last, First\"" or "name"		(artist name str)	   *
 *                      "title"							(album title str)      *
 *						"title"							(song title str)	   *
 *						"title"							(genre str)			   *
 *						"0:00"							(song length Duration) *
 *						"0"								(times played int)	   *
 *						"1"								(rating int)		   *
 *						"\"filepath.wav\""				(file path str)		   *
 *                                                                             *
 * Format of output file (musicPlayList.csv): Same as input					   *
 ******************************************************************************/
#ifndef TEST_DIGITAL_MUSIC_MANAGER_H
#define TEST_DIGITAL_MUSIC_MANAGER_H

#include "DigitalMusicManager.h"

/*************************************************************
 * Function: testInsertFront()								 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/9/25                                *
 * Description:	Tests if new node is successfully added to	 *
 *				an empty list								 *
 * Input parameters: none									 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h> <assert.h>				 *
 * Postconditions: none										 *
 *************************************************************/
void testInsertFront(void);

/*************************************************************
 * Function: testDeleteSelection()							 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/7/25                                *
 * Description:	Tests if a single node list gets correctly	 *
 *				deleted and memory deallocated				 *
 * Input parameters: none									 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h> <assert.h>				 *
 * Postconditions: none										 *
 *************************************************************/
void testDeleteSelection(void);

/*************************************************************
 * Function: testDeleteSelection()							 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Tests if shuffle will play in correct order	 *
 *				based on given array						 *
 * Input parameters: none									 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h>						 *
 * Postconditions: none										 *
 *************************************************************/
void testShufflePlaySongs(void);

#endif // !TEST_DIGITAL_MUSIC_MANAGER_H
