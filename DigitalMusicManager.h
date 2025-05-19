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
#ifndef DIGITAL_MUSIC_MANAGER_H
#define DIGITAL_MUSIC_MANAGER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct duration
{
	int minutes;
	int seconds;
}Duration;

typedef struct record
{
	char artist[20];
	char albumTitle[30];
	char songTitle[30];
	char genre[20];
	Duration songLength;
	int timesPlayed;
	int rating;
	char filePath[MAX_PATH];
}Record;

typedef struct node
{
	Record data;
	struct node* pNext;
	struct node* pPrev;
}Node;


/*************************************************************
 * Function: menu()	                                         *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description: Prompts user for menu selection, repeating   *
 *				until valid. Returns user selection 		 *
 * Input parameters: nothing                                 *
 * Returns: int user selection                               *
 * Preconditions: includes <stdio.h> and <stdlib.h>          *
 * Postconditions: none                                      *
 *************************************************************/
int menu(void);

/*************************************************************
 * Function: initList()                                      *
 * Date Created: 1/22/25                                     *
 * Date Last Modified: 1/22/25                               *
 * Description: Initializes list as NULL					 *
 * Input parameters: Node** pHead                            *
 * Returns: nothing			                                 *
 * Preconditions: none							             *
 * Postconditions: *pHead will be changed to NULL            *
 *************************************************************/
void initList(Node** pHead);

/*************************************************************
 * Function: makeNode()                                      *
 * Date Created: 1/22/25                                     *
 * Date Last Modified: 2/2/25                                *
 * Description: Allocates memory for node and sets data 	 *
 *				to recordData. Returns pointer to new Node.	 *
 * Input parameters: Record recordData                       *
 * Returns: pointer to the new node                          *
 * Preconditions: includes <stdlib.h>			             *
 * Postconditions: none							             *
 *************************************************************/
Node* makeNode(Record recordData);

/*************************************************************
 * Function: fixRecord()                                     *
 * Date Created: 2/7/25                                      *
 * Date Last Modified: 2/9/25                                *
 * Description: Corrects invalid data in record				 *
 * Input parameters: Record recordData                       *
 * Returns: copy of updated Record		                     *
 * Preconditions: none							             *
 * Postconditions: none							             *
 *************************************************************/
Record fixRecord(Record recordData);

/*************************************************************
 * Function: insertFront()                                   *
 * Date Created: 1/22/25                                     *
 * Date Last Modified: 2/5/25                                *
 * Description: Inserts a node to the front of the list, and *
 *				adjusts *pHead accordingly					 *
 * Input parameters: Node** pHead, Record recordData         *
 * Returns: int, 1 if successfully added node, 0 if failed   *
 * Preconditions: includes "DigitalMusicManager.h"           *
 * Postconditions: *pHead will be changed to new node	     *
 *************************************************************/
int insertFront(Node** pHead, Record recordData);

/*************************************************************
 * Function: deleteNode()                                    *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description: Deletes the Node from list given by input.	 *
 * Input parameters: Node** pHead, Node* pTemp		         *
 * Returns: int, 1 if successfully deleted node, 0 if failed *
 * Preconditions: *pTemp must be in list					 *
 *					includes <stdlib.h>			             *
 * Postconditions: *pHead will be changed if *pTemp is *pHead*
 *************************************************************/
int deleteNode(Node** pHead, Node* pTemp);

/*************************************************************
 * Function: getListLength()                                 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description: Returns length of list						 *
 * Input parameters: Node* pHead					         *
 * Returns: int length of list								 *
 * Preconditions: none							             *
 * Postconditions: none										 *
 *************************************************************/
int getListLength(Node* pHead);

/*************************************************************
 * Function: loadMusic()									 *
 * Date Created: 1/24/25                                     *
 * Date Last Modified: 2/3/25                                *
 * Description: Reads from input file and inserts records	 *
 *				to front of list							 *
 * Input parameters: FILE* inputStream, Node** pHead         *
 * Returns: nothing											 *
 * Preconditions: input file must follow denoted format      *
 *				  input file must be open for reading		 *
 *				  includes "DigitalMusicManager.h"			 *
 *				  includes <string.h> <stdio.h> <stdlib.h>	 *
 * Postconditions: *pHead will be changed to new node		 *
 *************************************************************/
void loadMusic(FILE* inputStream, Node** pHead);

/*************************************************************
 * Function: storeMusic()									 *
 * Date Created: 1/27/25                                     *
 * Date Last Modified: 2/3/25                                *
 * Description: Reads from list and prints contents to		 *
 *				output in proper format						 *
 * Input parameters: FILE* outputStream, Node** pHead        *
 * Returns: nothing											 *
 * Preconditions: list data must be initialized			     *
 *				  output file must be open for writing		 *
 *				  includes <string.h> <stdio.h>				 *
 * Postconditions: Output file will be overwritten			 *
 *************************************************************/
void storeMusic(FILE* outputStream, Node* pHead);

/*************************************************************
 * Function: storeMusicWithWarning()						 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description: Prompts user if they are sure they want to	 *
 *				overwrite data before storing record         *
 * Input parameters: FILE* outputStream, Node* pHead         *
 * Returns: nothing											 *
 * Preconditions: list data must not be null			     *
 *				  output file must be open for writing		 *
 *				  includes "DigitalMusicManager.h"			 *
 *				  includes <string.h> <stdio.h>	<stdlib>	 *
 *						   <windows.h>						 *
 * Postconditions: Output file will be overwritten			 *
 *************************************************************/
void storeMusicWithWarning(FILE* outputStream, Node* pHead);

/*************************************************************
 * Function: promptInsert()									 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description: Prompts user for data to input for inserting *
 *				new record.									 *
 * Input parameters: Node** pHead					         *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h>						 *
 * Postconditions: New record will be inserted to list		 *
 *				   and *pHead will be adjusted accordingly	 *
 *************************************************************/
void promptInsert(Node** pHead);

/*************************************************************
 * Function: deleteSelection()								 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description:	Deletes a node based on *selection			 *
 * Input parameters: Node** pHead,  Record* selection        *
 * Returns: int 1 if success or 0 if not					 *
 * Preconditions: record selection must exist in the list	 *
 *				  includes "DigitalMusicManager.h"			 *
 * Postconditions: Record matching *selection will be		 *
 *				   deleted from list, *pHead will change if  *
 *				   *pHead data = *selection					 *
 *************************************************************/
int deleteSelection(Node** pHead, Record* selection);

/*************************************************************
 * Function: promptDelete()									 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description:	Prompts user to search for record to delete	 *
 *				by song and deletes song from list			 *
 * Input parameters: Node** pHead					         *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h>						 *
 * Postconditions: Record that user selects will be deleted	 *
 *				   *pHead will be changed accordingly		 *
 *************************************************************/
void promptDelete(Node** pHead);

/*************************************************************
 * Function: findRecordByArtist()							 *
 * Date Created: 2/7/25                                      *
 * Date Last Modified: 2/7/25                                *
 * Description:	Finds any records in list with the given	 *
 *				artist name. Returns number found, and 		 *
 *				indirectly stores address of last record	 *
 *				found in *selection							 *
 * Input parameters: Node* pHead, const char* inputStr		 *
 *					 Record** selection					     *
 * Returns: int number of records found	with artist name	 *
 * Preconditions: includes <string.h>						 *
 * Postconditions: *selection will be set to record address  *
 *				   if record is found						 *
 *************************************************************/
int findRecordByArtist(Node* pHead, const char* inputStr, Record** selection);

/*************************************************************
 * Function: findRecordBySong()								 *
 * Date Created: 2/7/25                                      *
 * Date Last Modified: 2/7/25                                *
 * Description:	Finds any records in list with the given	 *
 *				song name. Returns number found, and 		 *
 *				indirectly stores address of last record	 *
 *				found in *selection							 *
 * Input parameters: Node* pHead, const char* inputStr,		 *
 *					 Record** selection					     *
 * Returns: int number of records found	with song name		 *
 * Preconditions: includes <string.h>						 *
 * Postconditions: *selection will be set to record address  *
 *				   if record is found						 *
 *************************************************************/
int findRecordBySong(Node* pHead, const char* inputStr, Record** selection);

/*************************************************************
 * Function: findRecordByArtistAndSong()					 *
 * Date Created: 2/7/25                                      *
 * Date Last Modified: 2/7/25                                *
 * Description:	Finds any records in list with both the		 *
 *				given artist andsong name. Returns number	 *
 *				found, and indirectly stores address of last *
 *				record found in *selection					 *
 * Input parameters: Node* pHead, const char* inputStrArtist *
 *					 const char* inputStrSong,				 *
 *					 Record** selection					     *
 * Returns: int number of records found	with artist and song *
 *			name											 *
 * Preconditions: includes <string.h>						 *
 * Postconditions: *selection will be set to record address  *
 *				   if record is found						 *
 *************************************************************/
int findRecordByArtistAndSong(Node* pHead, const char* inputStrArtist, const char* inputStrSong, Record** selection);

/*************************************************************
 * Function: searchRecordByArtist()							 *
 * Date Created: 1/27/25                                     *
 * Date Last Modified: 2/7/25                                *
 * Description:	Allows user to search for a song by artist	 *
 *				name. If multiple records are found, the	 *
 *				user can then search by song. Indirectly	 *
 *				returns address of record selection.		 *
 * Input parameters: Node* pHead, Record** selection	     *
 * Returns: int 1 if success, 0 if user canceled			 *
 * Preconditions: artist and song cannot be named "cancel"   *
 *				  includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h> <string.h>				 *
 * Postconditions: *selection will be set to record address  *
 *				   of user selected record					 *
 *************************************************************/
int searchRecordByArtist(Node* pHead, Record** selection);

/*************************************************************
 * Function: searchRecordBySong()							 *
 * Date Created: 2/4/25                                      *
 * Date Last Modified: 2/7/25                                *
 * Description:	Allows user to search for a song by song	 *
 *				name. If multiple records are found, the	 *
 *				user can then search by artist. Indirectly	 *
 *				returns address of record selection.		 *
 * Input parameters: Node* pHead, Record** selection	     *
 * Returns: int 1 if success, 0 if user canceled			 *
 * Preconditions: song and artist cannot be named "cancel"   *
 *				  includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h> <string.h>				 *
 * Postconditions: *selection will be set to record address  *
 *				   of user selected record					 *
 *************************************************************/
int searchRecordBySong(Node* pHead, Record** selection);

/*************************************************************
 * Function: changeArtist()									 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user to change artist name. Stores	 *
 *				change indirectly to recordData				 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <string.h>				 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeArtist(Record* recordData);

/*************************************************************
 * Function: changeAlbumTitle()								 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user to change album name. Stores	 *
 *				change indirectly to recordData				 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <string.h>				 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeAlbumTitle(Record* recordData);

/*************************************************************
 * Function: changeSongTitle()								 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user to change song name. Stores	 *
 *				change indirectly to recordData				 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <string.h>				 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeSongTitle(Record* recordData);

/*************************************************************
 * Function: changeGenre()									 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user to change genre. Stores		 *
 *				change indirectly to recordData				 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <string.h>				 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeGenre(Record* recordData);

/*************************************************************
 * Function: changeDuration()								 *
 * Date Created: 1/27/25                                     *
 * Date Last Modified: 1/27/25                               *
 * Description:	Prompts user to change duration, repeating	 *
 *				until valid input. Stores change indirectly  *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <string.h>	<stdlib.h>	 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeDuration(Record* recordData);

/*************************************************************
 * Function: changeTimesPlayed()							 *
 * Date Created: 1/27/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user to change times played,		 *
 *				repeating until valid input. Stores change   *
 *				indirectly to recordData					 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <string.h>	<stdlib.h>	 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeTimesPlayed(Record* recordData);

/*************************************************************
 * Function: changeRating()									 *
 * Date Created: 1/27/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user to change rating, repeating	 *
 *				until valid input. Stores change indirectly  *
 *				to recordData								 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <stdlib.h>				 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeRating(Record* recordData);

/*************************************************************
 * Function: changeFilePath()								 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description:	Prompts user to change file path. Stores	 *
 *				change indirectly to recordData				 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes <stdio.h> <string.h>				 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void changeFilePath(Record* recordData);

/*************************************************************
 * Function: editSelection()								 *
 * Date Created: 1/24/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user to edit any field of the 		 *
 *				given record. Loops until user selects exit. *
 *				Changes will be stored indirectly to		 *
 *				recordData									 *
 * Input parameters: Record* recordData					     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h> <stdlib.h>				 *
 * Postconditions: recordData will store user input			 *
 *************************************************************/
void editSelection(Record* recordData);

/*************************************************************
 * Function: editRecord()									 *
 * Date Created: 1/24/25                                     *
 * Date Last Modified: 1/27/25                               *
 * Description:	Allows user to search by artist	and edit the *
 *				selected record.							 *
 * Input parameters: Node* pHead						     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 * Postconditions: data in list will be edited by user		 *
 *************************************************************/
void editRecord(Node* pHead);

/*************************************************************
 * Function: sortByArtist()									 *
 * Date Created: 2/5/25                                      * 
 * Date Last Modified: 2/5/25                                *
 * Description:	Sorts list from a-b based on artist name	 *
 * Input parameters: Node** pHead						     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <string.h>						 *
 * Postconditions: *pHead will be changed according to new	 *
 *				   list order								 *
 *************************************************************/
void sortByArtist(Node** pHead);

/*************************************************************
 * Function: sortByAlbum()									 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Sorts list from a-b based on album name		 *
 * Input parameters: Node** pHead						     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <string.h>						 *
 * Postconditions: *pHead will be changed according to new	 *
 *				   list order								 *
 *************************************************************/
void sortByAlbum(Node** pHead);

/*************************************************************
 * Function: sortByRating()									 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Sorts list from 1-5 based on rating			 *
 * Input parameters: Node** pHead						     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 * Postconditions: *pHead will be changed according to new	 *
 *				   list order								 *
 *************************************************************/
void sortByRating(Node** pHead);

/*************************************************************
 * Function: sortByPlays()									 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Sorts list from high-low based on times		 *
 *				played										 *
 * Input parameters: Node** pHead						     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 * Postconditions: *pHead will be changed according to new	 *
 *				   list order								 *
 *************************************************************/
void sortByPlays(Node** pHead);

/*************************************************************
 * Function: sortPrompt()									 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Prompts user to sort by sorting type and	 *
 *				sorts list by selected type					 *
 * Input parameters: Node** pHead						     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h> <string.h>				 *
 * Postconditions: *pHead will be changed according to new	 *
 *				   list order								 *
 *************************************************************/
void sortPrompt(Node** pHead);

/*************************************************************
 * Function: rateRecord()									 *
 * Date Created: 1/27/25                                     *
 * Date Last Modified: 1/27/25                               *
 * Description:	Allows user to search record by song and	 *
 *				change its rating							 *
 * Input parameters: Node* pHead						     *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 * Postconditions: list data will be edited by user			 *
 *************************************************************/
void rateRecord(Node* pHead);

/*************************************************************
 * Function: playSong()										 *
 * Date Created: 2/2/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description:	Plays wav song from given file path for the	 *
 *				given duration, or until user presses a key. *
 *				Song does not repeat if duration is longer	 *
 *				than song. Windows sound will play if it	 *
 *				cannot find song from file path				 *
 * Input parameters: const char* songFilePath,				 *
 *					 Duration songDuration					 *
 * Returns: nothing											 *
 * Preconditions: song must be wav file,					 *
 *				  winmm.lib must be included in linker		 *
 *				  additional dependencies,					 *
 *				  includes <window.h> <ctype.h> <time.h>	 *
 *						   <conio.h> and <stdio.h>			 *
 * Postconditions: none										 *
 *************************************************************/
void playSong(const char* songFilePath, Duration songDuration);

/*************************************************************
 * Function: playAllSongsFromSelection()					 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/4/25                                *
 * Description:	Plays all songs after selected node. Stops	 *
 *				at end of list.								 *
 * Input parameters: Node* pHead, Node* pSelection			 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h>						 *
 * Postconditions: none										 *
 *************************************************************/
void playAllSongsFromSelection(Node* pHead, Node* pSelection);


/*************************************************************
 * Function: selectSongToPlay()								 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/3/25                                *
 * Description:	Allows user to search by song, and plays all *
 *				songs in list from selection				 *
 * Input parameters: Node* pHead							 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h>						 *
 * Postconditions: none										 *
 *************************************************************/
void selectSongToPlay(Node* pHead);

/*************************************************************
 * Function: shuffleArray()									 *
 * Date Created: 2/5/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Fills array with random integers from 1 to	 *
 *				list length									 *
 * Input parameters: Node* pHead, int* indexArray			 *
 * Returns:	nothing											 *
 * Preconditions: Array must be initialized with 0's		 *
 *				  random seed must be set					 *
 *				  includes "DigitalMusicManager.h"			 *
 *				  includes <stdlib.h>						 *
 * Postconditions: outputs int* array of shuffle order		 *
 *************************************************************/
void shuffleArray(Node* pHead, int* indexArray);

/*************************************************************
 * Function: shufflePlaySongs()								 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Plays all songs in list in order according	 *
 *				to input array								 *
 * Input parameters: Node* pHead, const int orderArray[]	 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h>						 *
 * Postconditions: none										 *
 *************************************************************/
void shufflePlaySongs(Node* pHead, const int orderArray[]);

/*************************************************************
 * Function: displayRecord()								 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Displays all data of record to screen		 *
 * Input parameters: Record recordData						 *
 * Returns: nothing											 *
 * Preconditions: record data must be initialized			 *
 *				  includes <stdio.h>						 *
 * Postconditions: none										 *
 *************************************************************/
void displayRecord(Record recordData);

/*************************************************************
 * Function: displayRecordsAll()							 *
 * Date Created: 1/22/25                                     *
 * Date Last Modified: 2/3/25                                *
 * Description:	Displays all records in list order to screen *
 * Input parameters: Node* pHead							 *
 * Returns: nothing											 *
 * Preconditions: record data must be initialized			 *
 *				  includes "DigitalMusicManager.h"			 *
 * Postconditions: none										 *
 *************************************************************/
void displayRecordsAll(Node* pHead);

/*************************************************************
 * Function: displayRecordsArtist()							 *
 * Date Created: 1/24/25                                     *
 * Date Last Modified: 2/3/25                                *
 * Description:	Displays all records with given artist name  *
 * Input parameters: Node* pHead, const char* artistName	 *
 * Returns: int 1 if any records were found, and 0 if not	 *
 * Preconditions: record data must be initialized			 *
 *				  includes "DigitalMusicManager.h"			 *
 * Postconditions: none										 *
 *************************************************************/
int displayRecordsArtist(Node* pHead, const char* artistName);

/*************************************************************
 * Function: displayRecordsSong()							 *
 * Date Created: 2/4/25                                      *
 * Date Last Modified: 2/4/25                                *
 * Description:	Displays all records with given song name    *
 * Input parameters: Node* pHead, const char* artistName	 *
 * Returns: int 1 if any records were found, and 0 if not	 *
 * Preconditions: record data must be initialized			 *
 *				  includes "DigitalMusicManager.h"			 *
 * Postconditions: none										 *
 *************************************************************/
int displayRecordsSong(Node* pHead, const char* songName);

/*************************************************************
 * Function: displayRecordsPrompt()							 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 1/29/25                               *
 * Description:	Prompts user whether they want to display    *
 *				all records or records by artist. If user	 *
 *				selects display by artist, allows user to	 *
 *				search for artist to display. Displays		 *
 *				record according to user selection			 *
 * Input parameters: Node* pHead							 *
 * Returns: nothing											 *
 * Preconditions: record data must be initialized			 *
 *				  includes "DigitalMusicManager.h"			 *
 * Postconditions: none										 *
 *************************************************************/
void displayRecordsPrompt(Node* pHead);

/*************************************************************
 * Function: run()											 *
 * Date Created: 1/29/25                                     *
 * Date Last Modified: 2/9/25                                *
 * Description:	Allows user to select options from menu and	 *
 *				runs any command the user selects.			 *
 * Input parameters: none									 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 * Postconditions: none										 *
 *************************************************************/
void run(void);


#endif // !DIGITAL_MUSIC_MANAGER_H