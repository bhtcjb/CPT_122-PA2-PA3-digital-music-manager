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
#include "TestDigitalMusicManager.h"
#include "DigitalMusicManager.h"

#include <assert.h>

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
void testInsertFront(void)
{
	Node* pHead = NULL;
	Record testData = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop",
		{4, 36}, -1, 6, "Katy Perry - Chained To The Rhythm.wav"};
	int returnValue = 0,
		success = 1;

	returnValue = insertFront(&pHead, testData);

	if (returnValue == 1)
		printf("[testInsertFront] return value correct!\n");
	else
	{
		printf("[testInsertFront] return value bad!\n");
		success = 0;
	}

	assert(success);

	if (pHead != NULL)
		printf("[testInsertFront] successfully updated pHead!\n");
	else
	{
		printf("[testInsertFront] failed to update pHead!\n");
		success = 0;
	}

	assert(success);

	if (pHead->pNext == pHead)
		printf("[testInsertFront] pNext is correct!\n");
	else
		printf("[testInsertFront] pNext is bad!\n");

	if (pHead->pPrev == pHead)
		printf("[testInsertFront] pPrev is correct!\n");
	else
		printf("[testInsertFront] pPrev is bad!\n");
		
	if (strcmp(pHead->data.artist, testData.artist) == 0)
		printf("[testInsertFront] artist is correct!\n");
	else
		printf("[testInsertFront] artist is wrong!\n");

	if (strcmp(pHead->data.albumTitle, testData.albumTitle) == 0)
		printf("[testInsertFront] album is correct!\n");
	else
		printf("[testInsertFront] album is wrong!\n");

	if (strcmp(pHead->data.songTitle, testData.songTitle) == 0)
		printf("[testInsertFront] song is correct!\n");
	else
		printf("[testInsertFront] song is wrong!\n");

	if (strcmp(pHead->data.genre, testData.genre) == 0)
		printf("[testInsertFront] genre is correct!\n");
	else
		printf("[testInsertFront] genre is wrong!\n");

	if (pHead->data.songLength.minutes == testData.songLength.minutes)
		printf("[testInsertFront] duration minutes is correct!\n");
	else
		printf("[testInsertFront] duration minutes is wrong!\n");

	if (pHead->data.songLength.seconds == testData.songLength.seconds)
		printf("[testInsertFront] duration seconds is correct!\n");
	else
		printf("[testInsertFront] duration seconds is wrong!\n");

	if (pHead->data.timesPlayed == 0)
		printf("[testInsertFront] times played was successfully corrected!\n");
	else
		printf("[testInsertFront] times played failed to be corrected!\n");

	if (pHead->data.rating == 5)
		printf("[testInsertFront] rating was successfully corrected!\n");
	else
		printf("[testInsertFront] rating failed to be corrected!\n");

	if (strcmp(pHead->data.filePath, testData.filePath) == 0)
		printf("[testInsertFront] file path is correct!\n");
	else
		printf("[testInsertFront] file path is wrong!\n");
}

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
void testDeleteSelection(void)
{
	Node* pDelete = malloc(sizeof(Node)),
		* pHead = pDelete;
	Record testData = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop",
		{4, 36}, 3, 5, "Katy Perry - Chained To The Rhythm.wav" },
		* selection = NULL;
	char* searchSong = "Chained to the Rhythm";
	int success = 1;
	
	pDelete->data = testData;
	pDelete->pNext = pDelete;
	pDelete->pPrev = pDelete;

	findRecordBySong(pHead, searchSong, &selection);

	if (selection == &(pDelete->data))
		printf("[testDeleteSelection] successfully found record from song!\n");
	else
	{
		printf("[testDeleteSelection] failed to find record from song!\n");
		success = 0;
	}

	assert(success);

	deleteSelection(&pHead, selection);

	if (pDelete->pNext != pDelete && pDelete->pPrev != pDelete)
		printf("[testDeleteSelection] successfully deallocated node!\n");
	else
		printf("[testDeleteSelection] failed to deallocate node!\n");

	if (pHead == NULL)
		printf("[testDeleteSelection] successfully reset pHead!\n");
	else
		printf("[testDeleteSelection] failed to reset pHead!\n");
}

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
void testShufflePlaySongs(void)
{
	Record testSong1 = { "Perry, Katy", "Witness", "Chained to the Rhythm", "pop",
			{4, 00}, 3, 5, "Katy Perry - Chained To The Rhythm.wav" },
		testSong2 = { "Perri, Christina", "HEAD OF HEART", "Trust", "Pop",
			{3, 31}, 3, 5, "Christina Perri - Trust.wav"},
		testSong3 = { "Eminem", "SHADYXV", "Vegas", "Rap", 
			{5, 36}, 8, 3, "Vegas.wav"};
	Node* pHead = malloc(sizeof(Node)),
		* pRecord2 = malloc(sizeof(Node)),
		* pRecord3 = malloc(sizeof(Node));
	int testOrder[3] = { 3, 1, 2 }; 

	pHead->pNext = pRecord2;
	pRecord2->pNext = pRecord3;
	pRecord3->pNext = pHead;
	pHead->pPrev = pRecord3;
	pRecord3->pPrev = pRecord2;
	pRecord2->pPrev = pHead;

	pHead->data = testSong1;
	pRecord2->data = testSong2;
	pRecord3->data = testSong3;

	printf("[testShufflePlaySongs] Should play in order of (1) \"Vegas\", "
		"(2) \"Chained to the Rhythm\", (3) \"Trust\"");

	system("pause>>nul");

	shufflePlaySongs(pHead, testOrder);


}