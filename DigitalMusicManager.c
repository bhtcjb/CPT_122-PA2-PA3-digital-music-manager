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
#include "DigitalMusicManager.h"

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
int menu(void)
{
	int selectionInt = -1;
	char selectionStr[4] = "";

	do
	{
		system("cls");
		printf("Menu\t(1)  load\n\t(2)  store\n\t(3)  display\n\t"
			"(4)  insert\n\t(5)  delete\n\t(6)  edit\n\t(7)  sort\n\t(8)  rate"
			"\n\t(9)  play\n\t(10) shuffle\n\t(11) exit\n");
		printf("\nEnter number: ");
		fgets(selectionStr, 4, stdin);
		rewind(stdin);

		if (selectionStr[1] == '\n')
		{
			selectionInt = atoi(selectionStr);
		}
		else if (selectionStr[2] == '\n' && isdigit(selectionStr[1]))
		{
			selectionInt = atoi(selectionStr);
		}

	} while (selectionInt < 1 || selectionInt > 11);

	return selectionInt;
}

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
void initList(Node** pHead)
{
	*pHead = NULL;
}

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
Node* makeNode(Record recordData)
{
	Node* pMem = malloc(sizeof(Node));

	if (pMem != NULL)
	{
		pMem->data = recordData;
		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}

	return pMem;
}

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
Record fixRecord(Record recordData)
{

	if (recordData.songLength.seconds < 0)
		recordData.songLength.seconds = 0;
	if (recordData.songLength.seconds > 59)
		recordData.songLength.seconds = 59;
	if (recordData.timesPlayed < 0)
		recordData.timesPlayed = 0;
	if (recordData.rating < 1)
		recordData.rating = 1;
	if (recordData.rating > 5)
		recordData.rating = 5;

	return recordData;
}

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
int insertFront(Node** pHead, Record recordData)
{
	Node* pNew = NULL;
	Node* pCurr = *pHead;
	int success = 0;

	recordData = fixRecord(recordData);

	pNew = makeNode(recordData);

	if (pNew != NULL)
	{
		success = 1;

		if (*pHead != NULL)
		{
			pNew->pPrev = pCurr->pPrev;
			pCurr->pPrev = pNew;
			pNew->pNext = pCurr;
			*pHead = pNew;
			pNew->pPrev->pNext = pNew;
		}
		else
		{
			*pHead = pNew;
			pNew->pNext = pNew;
			pNew->pPrev = pNew;
		}


	}

	return success;
}

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
int deleteNode(Node** pHead, Node* pTemp)
{
	int success = 0;

	if (*pHead != NULL)
	{
		success = 1;

		if (pTemp->pNext == pTemp)
		{
			*pHead = NULL;
		}
		else
		{
			if (*pHead == pTemp)
			{
				*pHead = pTemp->pNext;
			}
			pTemp->pPrev->pNext = pTemp->pNext;
			pTemp->pNext->pPrev = pTemp->pPrev;
		}
		free(pTemp);
		pTemp = NULL;
	}

	return success;
}

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
int getListLength(Node* pHead)
{
	Node* pCurr = pHead;
	int len = 0;

	if (pHead != NULL)
	{
		do
		{
			++len;
			pCurr = pCurr->pNext;
		} while (pCurr != pHead);
	}

	return len;
}

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
void loadMusic(FILE* inputStream, Node** pHead)
{
	Record currData;
	char buff[400] = "";

	rewind(inputStream);

	while (fgets(buff, 400, inputStream) != NULL)
	{
		if (*buff == '\"')
		{
			strcpy(currData.artist, strtok(buff, "\""));
		}
		else
		{
			strcpy(currData.artist, strtok(buff, ","));
		}
		strcpy(currData.albumTitle, strtok(NULL, ","));
		strcpy(currData.songTitle, strtok(NULL, ","));
		strcpy(currData.genre, strtok(NULL, ","));
		currData.songLength.minutes = atoi(strtok(NULL, ":"));
		currData.songLength.seconds = atoi(strtok(NULL, ","));
		currData.timesPlayed = atoi(strtok(NULL, ","));
		currData.rating = atoi(strtok(NULL, ","));
		strcpy(currData.filePath, strtok(NULL, "\""));

		if (currData.filePath[0] == '\"')
		{
			strcpy(currData.filePath, currData.filePath + 1);
		}
		if (currData.filePath[strlen(currData.filePath) - 1] == '\n')
		{
			currData.filePath[strlen(currData.filePath) - 1] = '\0';
		}
		if (currData.filePath[strlen(currData.filePath) - 1] == '\"')
		{
			currData.filePath[strlen(currData.filePath) - 1] = '\0';
		}

		insertFront(pHead, currData);
	}
}

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
void storeMusic(FILE* outputStream, Node* pHead)
{
	Node* pCurr = pHead;
	int commaFlag = 0;

	if (pHead != NULL)
	{
		do
		{
			for (int i = 0, len = strlen(pCurr->data.artist); i < len; ++i)
			{
				if (pCurr->data.artist[i] == ',')
				{
					commaFlag = 1;
					break;
				}
			}

			if (commaFlag)
				fprintf(outputStream, "\"%s\",", pCurr->data.artist);
			else
				fprintf(outputStream, "%s,", pCurr->data.artist);
			fprintf(outputStream, "%s,", pCurr->data.albumTitle);
			fprintf(outputStream, "%s,", pCurr->data.songTitle);
			fprintf(outputStream, "%s,", pCurr->data.genre);
			fprintf(outputStream, "%d:%d,", pCurr->data.songLength.minutes, pCurr->data.songLength.seconds);
			fprintf(outputStream, "%d,", pCurr->data.timesPlayed);
			fprintf(outputStream, "%d,", pCurr->data.rating);
			fprintf(outputStream, "\"%s\"", pCurr->data.filePath);
			fputc('\n', outputStream);

			pCurr = pCurr->pNext;
		} while (pCurr != pHead);
	}
}

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
void storeMusicWithWarning(FILE* outputStream, Node* pHead)
{
	char confirm[10] = "";

	do
	{
		system("cls");
		printf("Are you sure you want to store changes?\nThis will overwrite your previous data.\n");
		printf("\nType \"continue\" or \"cancel\"\n");
		printf("\nEnter Answer: ");
		fgets(confirm, 10, stdin);
		rewind(stdin);
		if (!strcmp(confirm, "continue\n"))
		{
			storeMusic(outputStream, pHead);
			system("cls");
			printf("Saving...");
			Sleep(500);
			system("cls");
			printf("Complete\n\n");
			system("pause");
			break;
		}
		else if (!strcmp(confirm, "cancel\n"))
		{
			break;
		}
	} while (1);
}

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
void promptInsert(Node** pHead)
{
	Record recordInput;
	int success = 0;

	system("cls");
	printf("Insert New:\n\n");
	changeArtist(&recordInput);
	system("cls");
	printf("Insert New:\n\n");
	changeAlbumTitle(&recordInput);
	system("cls");
	printf("Insert New:\n\n");
	changeSongTitle(&recordInput);
	system("cls");
	printf("Insert New:\n\n");
	changeGenre(&recordInput);
	system("cls");
	printf("Insert New:\n\n");
	changeDuration(&recordInput);
	system("cls");
	printf("Insert New:\n\n");
	changeTimesPlayed(&recordInput);
	system("cls");
	printf("Insert New:\n\n");
	changeRating(&recordInput);
	system("cls");
	printf("Insert New:\n\n");
	changeFilePath(&recordInput);

	success = insertFront(pHead, recordInput);

	system("cls");
	if (success)
	{
		printf("Successfully added new record!");
		system("pause>>nul");
	}
	else
	{
		printf("Failed to add new record.");
		system("pause>>nul");
	}
	system("cls");
}

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
int deleteSelection(Node** pHead, Record* selection)
{
	Node* pTemp = *pHead;
	int success = 0;

	if (pHead != NULL)
	{
		do
		{
			if (&(pTemp->data) == selection)
			{
				success = deleteNode(pHead, pTemp);
				break;
			}
			pTemp = pTemp->pNext;
		} while (pTemp != *pHead);

	}
	return success;
}

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
void promptDelete(Node** pHead)
{
	Record* selection = NULL;
	char yesOrNo[8] = "";
	int cancel = 0,
		success = 0;

	cancel = !searchRecordBySong(*pHead, &selection);

	if (!cancel)
	{
		do
		{
			system("cls");
			printf("Are you sure you would like to delete this record?\n");
			putchar('\t');
			displayRecord(*selection);
			printf("\nType \"yes\" or \"cancel\"\n\n\n");
			fgets(yesOrNo, 8, stdin);
		} while (strcmp(yesOrNo, "yes\n") && strcmp(yesOrNo, "cancel\n"));

		if (!strcmp(yesOrNo, "yes\n"))
		{
			success = deleteSelection(pHead, selection);
		}

		system("cls");
		if (success)
		{
			printf("Successfully deleted record!");
			system("pause>>nul");
			system("cls");
		}
		else
		{
			printf("Failed to delete record.");
			system("pause>>nul");
			system("cls");
		}
	}


}

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
int findRecordByArtist(Node* pHead, const char* inputStr, Record** selection)
{
	Node* pCurr = pHead;
	int numRecords = 0;

	if (pHead != NULL)
	{
		do
		{
			if (strcmp(inputStr, pCurr->data.artist) == 0)
			{
				*selection = &(pCurr->data);
				++numRecords;
			}
			pCurr = pCurr->pNext;
		} while (pCurr != pHead);
	}

	return numRecords;
}

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
int findRecordBySong(Node* pHead, const char* inputStr, Record** selection)
{
	Node* pCurr = pHead;
	int numRecords = 0;

	if (pHead != NULL)
	{
		do
		{
			if (strcmp(inputStr, pCurr->data.songTitle) == 0)
			{
				*selection = &(pCurr->data);
				++numRecords;
			}
			pCurr = pCurr->pNext;
		} while (pCurr != pHead);
	}

	return numRecords;
}

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
int findRecordByArtistAndSong(Node* pHead, const char* inputStrArtist, const char* inputStrSong, Record** selection)
{
	Node* pCurr = pHead;
	int numRecords = 0;

	if (pHead != NULL)
	{
		do
		{
			if (strcmp(inputStrSong, pCurr->data.songTitle) == 0 &&
				strcmp(inputStrArtist, pCurr->data.artist) == 0)
			{
				*selection = &(pCurr->data);
				numRecords = 1;
				break;
			}
			pCurr = pCurr->pNext;
		} while (pCurr != pHead);
	}
	
	return numRecords;
}

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
int searchRecordByArtist(Node* pHead, Record** selection)
{
	char artistName[20],
		songName[30];
	int numRecords = 0,
		cancelFlag = 0;

	do
	{
		system("cls");
		displayRecordsAll(pHead);
		printf("\n\ntype \"cancel\" to cancel");
		printf("\n\nSearch artist: ");

		fgets(artistName, 20, stdin);
		rewind(stdin);


		if (artistName[strlen(artistName) - 1] == '\n')
		{
			artistName[strlen(artistName) - 1] = '\0';
		}

		if (strcmp(artistName, "cancel") == 0)
		{
			cancelFlag = 1;
			break;
		}

		numRecords = findRecordByArtist(pHead, artistName, selection);

		if (numRecords > 1)
		{
			do
			{
				system("cls");
				displayRecordsArtist(pHead, artistName);
				printf("\n\ntype \"cancel\" to cancel");
				printf("\n\nSearch song: ");
				fgets(songName, 30, stdin);
				rewind(stdin);

				if (songName[strlen(songName) - 1] == '\n')
				{
					songName[strlen(songName) - 1] = '\0';
				}

				if (strcmp(songName, "cancel") == 0)
				{
					cancelFlag = 1;
					break;
				}

				numRecords = findRecordByArtistAndSong(pHead, artistName, songName, selection);
				
			} while (!numRecords);

			if (cancelFlag)
			{
				break;
			}
		}

	} while (!numRecords);

	return !cancelFlag;
}

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
int searchRecordBySong(Node* pHead, Record** selection)
{
	char artistName[20],
		songName[30];
	int numRecords = 0,
		cancelFlag = 0;

	do
	{
		system("cls");
		displayRecordsAll(pHead);
		printf("\n\ntype \"cancel\" to cancel");
		printf("\n\nSearch song: ");

		fgets(songName, 30, stdin);
		rewind(stdin);


		if (songName[strlen(songName) - 1] == '\n')
		{
			songName[strlen(songName) - 1] = '\0';
		}

		if (strcmp(songName, "cancel") == 0)
		{
			cancelFlag = 1;
			break;
		}

		numRecords = findRecordBySong(pHead, songName, selection);

		if (numRecords > 1)
		{
			do
			{
				system("cls");
				displayRecordsSong(pHead, songName);
				printf("\n\ntype \"cancel\" to cancel");
				printf("\n\nSearch artist: ");
				fgets(artistName, 20, stdin);
				rewind(stdin);

				if (artistName[strlen(artistName) - 1] == '\n')
				{
					artistName[strlen(artistName) - 1] = '\0';
				}

				if (strcmp(artistName, "cancel") == 0)
				{
					cancelFlag = 1;
					break;
				}

				numRecords = findRecordByArtistAndSong(pHead, artistName, songName, selection);

			} while (!numRecords);

			if (cancelFlag)
			{
				break;
			}
		}

	} while (!numRecords);

	return !cancelFlag;
}

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
void changeArtist(Record* recordData)
{
	printf("Change artist name: ");
	fgets(recordData->artist, 20, stdin);
	rewind(stdin);
	if (recordData->artist[strlen(recordData->artist) - 1] == '\n')
	{
		recordData->artist[strlen(recordData->artist) - 1] = '\0';
	}
}

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
void changeAlbumTitle(Record* recordData)
{
	printf("Change album title: ");
	fgets(recordData->albumTitle, 30, stdin);
	rewind(stdin);
	if (recordData->albumTitle[strlen(recordData->albumTitle) - 1] == '\n')
	{
		recordData->albumTitle[strlen(recordData->albumTitle) - 1] = '\0';
	}
}

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
void changeSongTitle(Record* recordData)
{
	printf("Change song title: ");
	fgets(recordData->songTitle, 30, stdin);
	rewind(stdin);
	if (recordData->songTitle[strlen(recordData->songTitle) - 1] == '\n')
	{
		recordData->songTitle[strlen(recordData->songTitle) - 1] = '\0';
	}
}

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
void changeGenre(Record* recordData)
{
	printf("Change genre: ");
	fgets(recordData->genre, 20, stdin);
	rewind(stdin);
	if (recordData->genre[strlen(recordData->genre) - 1] == '\n')
	{
		recordData->genre[strlen(recordData->genre) - 1] = '\0';
	}
}

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
void changeDuration(Record* recordData)
{
	char minutesBuff[15] = "",
		secondsBuff[15] = "";
	int validFlag = 0,
		minutesTemp = 0,
		secondsTemp = 0;

	do
	{
		validFlag = 1;
		system("cls");
		printf("Change duration minutes: ");
		fgets(minutesBuff, 11, stdin);
		minutesTemp = atoi(minutesBuff);
		rewind(stdin);



		for (int i = 0, len = strlen(minutesBuff); i < len; ++i)
		{
			if (!isdigit(minutesBuff[i]) && minutesBuff[i] != '\n')
			{
				validFlag = 0;
				break;
			}
		}
		if (!validFlag)
		{
			continue;
		}

		printf("\nChange duration seconds: ");
		fgets(secondsBuff, 4, stdin);
		secondsTemp = atoi(secondsBuff);
		rewind(stdin);


		for (int i = 0, len = strlen(secondsBuff); i < len; ++i)
		{
			if (!isdigit(secondsBuff[i]) && secondsBuff[i] != '\n')
			{
				validFlag = 0;
				break;
			}
		}
		if (secondsTemp < 0 || secondsTemp > 59)
		{
			validFlag = 0;
		}
		if (!validFlag)
		{
			continue;
		}

		if (validFlag)
		{
			recordData->songLength.minutes = minutesTemp;
			recordData->songLength.seconds = secondsTemp;
			break;
		}

	} while (1);
}

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
void changeTimesPlayed(Record* recordData)
{
	char timesPlayedBuff[11] = "";
	int validFlag = 0;

	do
	{
		validFlag = 1;
		system("cls");
		printf("Change times played: ");
		fgets(timesPlayedBuff, 11, stdin);
		rewind(stdin);

		if (timesPlayedBuff[strlen(timesPlayedBuff) - 1] == '\n')
		{
			timesPlayedBuff[strlen(timesPlayedBuff) - 1] = '\0';
		}

		for (int i = 0, len = strlen(timesPlayedBuff); i < len; ++i)
		{
			if (!isdigit(timesPlayedBuff[i]) && timesPlayedBuff[i] != '\n')
			{
				validFlag = 0;
				break;
			}
		}


		if (validFlag)
		{
			recordData->timesPlayed = atoi(timesPlayedBuff);
			break;
		}
	} while (1);
}

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
void changeRating(Record* recordData)
{
	char selectionStr[3] = "";
	int ratingTemp = -1;

	do
	{
		system("cls");
		printf("1 - 5\n");
		printf("Change rating: ");
		fgets(selectionStr, 3, stdin);
		rewind(stdin);

		if (selectionStr[1] == '\n')
		{
			ratingTemp = atoi(selectionStr);
		}


	} while (ratingTemp < 1 || ratingTemp > 5);

	recordData->rating = ratingTemp;
}

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
void changeFilePath(Record* recordData)
{
	printf("Change file path: ");
	fgets(recordData->filePath, MAX_PATH, stdin);
	rewind(stdin);
	if (recordData->filePath[strlen(recordData->filePath) - 1] == '\n')
	{
		recordData->filePath[strlen(recordData->filePath) - 1] = '\0';
	}
}

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
void editSelection(Record* recordData)
{
	char selectionStr[3] = "";
	int selectionInt = -1,
		validFlag = 0,
		exitFlag = 0,
		tempSeconds = 0;
	do
	{
		do
		{
			system("cls");
			displayRecord(*recordData);
			printf("\nEdit\t(1) artist\n\t(2) album\n\t(3) song\n\t(4) genre\n\t"
				"(5) duration\n\t(6) plays\n\t(7) rating\n\t(8) file path\n\t(9) exit\n");
			printf("\nEnter number: ");
			fgets(selectionStr, 3, stdin);
			rewind(stdin);

			if (selectionStr[1] == '\n')
			{
				selectionInt = atoi(selectionStr);
			}
			else
			{
				continue;
			}

		} while (selectionInt < 1 || selectionInt > 9);

		system("cls");

		switch (selectionInt)
		{
		case 1: changeArtist(recordData);
			break;
		case 2: changeAlbumTitle(recordData);
			break;
		case 3: changeSongTitle(recordData);
			break;
		case 4: changeGenre(recordData);
			break;
		case 5: changeDuration(recordData);
			break;
		case 6: changeTimesPlayed(recordData);
			break;
		case 7: changeRating(recordData);
			break;
		case 8: changeFilePath(recordData);
			break;
		case 9:
			exitFlag = 1;
		}
	} while (!exitFlag);
}

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
void editRecord(Node* pHead)
{
	Record* selection = NULL;
	int cancelFlag = 0;

	cancelFlag = !searchRecordByArtist(pHead, &selection);

	system("cls");

	if (!cancelFlag)
	{
		editSelection(selection);
	}

}

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
void sortByArtist(Node** pHead)
{
	Node* pCurr = *pHead;
	int len = getListLength(*pHead),
		offset = 0;

	if (*pHead != NULL)
	{
		if (len < 3)
		{
			if (strcmp(pCurr->data.artist, pCurr->pNext->data.artist) > 0)
			{
				*pHead = pCurr->pNext;
			}
		}
		else
		{
			do
			{
				do
				{
					if (strcmp(pCurr->data.artist, pCurr->pNext->data.artist) > 0)
					{
						if (pCurr == *pHead)
						{
							*pHead = pCurr->pNext;
						}

						pCurr->pPrev->pNext = pCurr->pNext;
						pCurr->pNext->pNext->pPrev = pCurr;
						pCurr->pNext = pCurr->pNext->pNext;
						pCurr->pPrev->pNext->pPrev = pCurr->pPrev;
						pCurr->pPrev->pNext->pNext = pCurr;
						pCurr->pPrev = pCurr->pPrev->pNext;
					}
					else
					{
						pCurr = pCurr->pNext;
					}

					++offset;
				} while (offset < len - 1);

				pCurr = *pHead;
				--len;
				offset = 0;
			} while (len > 1);
		}
	}
}

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
void sortByAlbum(Node** pHead)
{
	Node* pCurr = *pHead;
	int len = getListLength(*pHead),
		offset = 0;

	if (*pHead != NULL)
	{
		if (len < 3)
		{
			if (strcmp(pCurr->data.albumTitle, pCurr->pNext->data.albumTitle) > 0)
			{
				*pHead = pCurr->pNext;
			}
		}
		else
		{
			do
			{
				do
				{
					if (strcmp(pCurr->data.albumTitle, pCurr->pNext->data.albumTitle) > 0)
					{
						if (pCurr == *pHead)
						{
							*pHead = pCurr->pNext;
						}

						pCurr->pPrev->pNext = pCurr->pNext;
						pCurr->pNext->pNext->pPrev = pCurr;
						pCurr->pNext = pCurr->pNext->pNext;
						pCurr->pPrev->pNext->pPrev = pCurr->pPrev;
						pCurr->pPrev->pNext->pNext = pCurr;
						pCurr->pPrev = pCurr->pPrev->pNext;
					}
					else
					{
						pCurr = pCurr->pNext;
					}

					++offset;
				} while (offset < len - 1);

				pCurr = *pHead;
				--len;
				offset = 0;
			} while (len > 1);
		}
	}
}

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
void sortByRating(Node** pHead)
{
	Node* pCurr = *pHead;
	int len = getListLength(*pHead),
		offset = 0;

	if (*pHead != NULL)
	{
		if (len < 3)
		{
			if (pCurr->data.rating > pCurr->pNext->data.rating)
			{
				*pHead = pCurr;
			}
		}
		else
		{
			do
			{
				do
				{
					if (pCurr->data.rating > pCurr->pNext->data.rating)
					{
						if (pCurr == *pHead)
						{
							*pHead = pCurr->pNext;
						}

						pCurr->pPrev->pNext = pCurr->pNext;
						pCurr->pNext->pNext->pPrev = pCurr;
						pCurr->pNext = pCurr->pNext->pNext;
						pCurr->pPrev->pNext->pPrev = pCurr->pPrev;
						pCurr->pPrev->pNext->pNext = pCurr;
						pCurr->pPrev = pCurr->pPrev->pNext;
					}
					else
					{
						pCurr = pCurr->pNext;
					}

					++offset;
				} while (offset < len - 1);

				pCurr = *pHead;
				--len;
				offset = 0;
			} while (len > 1);
		}
	}
}

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
void sortByPlays(Node** pHead)
{
	Node* pCurr = *pHead;
	int len = getListLength(*pHead),
		offset = 0;

	if (*pHead != NULL)
	{
		if (len < 3)
		{
			if (pCurr->data.timesPlayed < pCurr->pNext->data.timesPlayed)
			{
				*pHead = pCurr;
			}
		}
		else
		{
			do
			{
				do
				{
					if (pCurr->data.timesPlayed < pCurr->pNext->data.timesPlayed)
					{
						if (pCurr == *pHead)
						{
							*pHead = pCurr->pNext;
						}

						pCurr->pPrev->pNext = pCurr->pNext;
						pCurr->pNext->pNext->pPrev = pCurr;
						pCurr->pNext = pCurr->pNext->pNext;
						pCurr->pPrev->pNext->pPrev = pCurr->pPrev;
						pCurr->pPrev->pNext->pNext = pCurr;
						pCurr->pPrev = pCurr->pPrev->pNext;
					}
					else
					{
						pCurr = pCurr->pNext;
					}

					++offset;
				} while (offset < len - 1);

				pCurr = *pHead;
				--len;
				offset = 0;
			} while (len > 1);
		}
	}
}

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
void sortPrompt(Node** pHead)
{
	char selectionStr[8] = "";
	int selectionInt = -1,
		cancelFlag = 0;

	do
	{
		system("cls");
		printf("Sort by: (1) artist\n\t (2) album\n\t (3) rating\n\t (4) plays\n\n");
		printf("type \"cancel\" to cancel\n\n");
		printf("Enter number: ");
		fgets(selectionStr, 8, stdin);
		rewind(stdin);

		if (strcmp(selectionStr, "cancel\n") == 0)
		{
			cancelFlag = 1;
			break;
		}

		if (selectionStr[1] == '\n')
		{
			selectionInt = atoi(selectionStr);
		}

	} while (selectionInt < 1 || selectionInt > 4);

	if (!cancelFlag)
	{
		switch (selectionInt)
		{
		case 1: system("cls");
			sortByArtist(pHead);
			printf("Successfully sorted by artist!");
			system("pause>>nul");
			break;
		case 2: system("cls");
			sortByAlbum(pHead);
			printf("Successfully sorted by album!");
			system("pause>>nul");
			break;
		case 3: system("cls");
			sortByRating(pHead);
			printf("Successfully sorted by rating!");
			system("pause>>nul");
			break;
		case 4: system("cls");
			sortByPlays(pHead);
			printf("Successfully sorted by times played!");
			system("pause>>nul");
			break;
		}
	}
}

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
void rateRecord(Node* pHead)
{
	Record* selection = NULL;
	int cancelFlag = 0;

	cancelFlag = !searchRecordBySong(pHead, &selection);

	if (!cancelFlag)
	{
		changeRating(selection);
	}

}

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
void playSong(const char* songFilePath, Duration songDuration)
{
	int durationSec = songDuration.minutes * 60 + songDuration.seconds;
	wchar_t wFilePath[MAX_PATH] = L"";

	MultiByteToWideChar(CP_ACP, // uses system default code page
		MB_PRECOMPOSED, // default conversion type
		songFilePath,
		-1, // -1 means NULL terminated
		wFilePath,
		MAX_PATH);

	PlaySound((LPCWSTR) wFilePath, 
		NULL, // handle to executable, not used
		SND_FILENAME // interprets sound as filename
		| SND_ASYNC // plays sound in background, i.e. does not block program
	); 
	
	// wait for duration of song or until input
	for (int startTime = clock() / CLOCKS_PER_SEC, curTime = 0;
		curTime < durationSec; 
		curTime = (clock() / CLOCKS_PER_SEC) - startTime)
	{
		if (_kbhit())
		{
			getchar();
			break;
		}
	}

	PlaySound(NULL, NULL, NULL); // end play
}

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
void playAllSongsFromSelection(Node* pHead, Node* pSelection)
{
	Node* pCurr = pSelection;

	if (pHead != NULL)
	{
		do
		{
			system("cls");
			printf("Now Playing. . .\n\n");
			displayRecord(pCurr->data);
			playSong(pCurr->data.filePath, pCurr->data.songLength);
			pCurr = pCurr->pNext;
		} while (pCurr != pHead);
	}
}

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
void selectSongToPlay(Node* pHead)
{
	Record* selection = NULL;
	Node* pCurr = pHead;
	int cancel = 0;

	cancel = !searchRecordBySong(pHead, &selection);

	system("cls");

	if (!cancel)
	{
		if (pHead != NULL)
		{
			do
			{
				if (selection == &(pCurr->data))
				{
					playAllSongsFromSelection(pHead, pCurr);
					break;
				}
				pCurr = pCurr->pNext;
			} while (pCurr != pHead);
		}
	}

}

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
void shuffleArray(Node* pHead, int* indexArray)
{
	int len = getListLength(pHead),
		temp = 0;

	for (int i = 1; i <= len; ++i)
	{
		do
		{
			temp = rand() % len;
		} while (indexArray[temp] != 0);

		indexArray[temp] = i;
	}
}

/*************************************************************
 * Function: shufflePlaySongs()								 *
 * Date Created: 2/3/25                                      *
 * Date Last Modified: 2/5/25                                *
 * Description:	Plays all songs in list in order according	 *
 *				to input array 								 *
 * Input parameters: Node* pHead, const int orderArray[]	 *
 * Returns: nothing											 *
 * Preconditions: includes "DigitalMusicManager.h"			 *
 *				  includes <stdio.h>						 *
 * Postconditions: none										 *
 *************************************************************/
void shufflePlaySongs(Node* pHead, const int orderArray[])
{
	Node* pCurr = pHead;
	int len = getListLength(pHead),
		currNodeIndex = 0,
		prevNodeIndex = -1;

	
	for (int i = 0; i < len; ++i, prevNodeIndex = currNodeIndex)
	{
		currNodeIndex = orderArray[i];

		if (prevNodeIndex == -1)
		{
			for (int j = 1; j < currNodeIndex; ++j)		
				pCurr = pCurr->pNext;
			
		}
		else
		{
			if ((currNodeIndex - prevNodeIndex) > 0)
			{
				for (int j = 1, dif = currNodeIndex - prevNodeIndex; j <= dif; ++j)
					pCurr = pCurr->pNext;
			}
			else
			{
				for (int j = 1, dif = prevNodeIndex - currNodeIndex; j <= dif; ++j)
					pCurr = pCurr->pPrev;
			}
		}

		system("cls");
		printf("Now Playing. . .\n\n");
		displayRecord(pCurr->data);
		playSong(pCurr->data.filePath, pCurr->data.songLength);
	}

}

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
void displayRecord(Record recordData)
{
	fprintf(stdout, "%s, ", recordData.artist);
	fprintf(stdout, "%s, ", recordData.albumTitle);
	fprintf(stdout, "%s, ", recordData.songTitle);
	fprintf(stdout, "%s, ", recordData.genre);
	fprintf(stdout, "%d:%d, ", recordData.songLength.minutes, recordData.songLength.seconds);
	fprintf(stdout, "%d, ", recordData.timesPlayed);
	fprintf(stdout, "%d, ", recordData.rating);
	fprintf(stdout, "%s\n", recordData.filePath);
}

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
void displayRecordsAll(Node* pHead)
{
	Node* pCurr = pHead;

	if (pHead != NULL)
	{
		do
		{
			displayRecord(pCurr->data);
			pCurr = pCurr->pNext;
		} while (pCurr != pHead);
	}

}

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
int displayRecordsArtist(Node* pHead, const char* artistName)
{
	int success = 0;
	Node* pCurr = pHead;

	if (pHead != NULL)
	{
		do
		{
			if (strcmp(artistName, pCurr->data.artist) == 0)
			{
				displayRecord(pCurr->data);
				success = 1;
			}
			pCurr = pCurr->pNext;

		} while (pCurr != pHead);
	}


	return success;
}

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
int displayRecordsSong(Node* pHead, const char* songName)
{
	int success = 0;
	Node* pCurr = pHead;

	if (pHead != NULL)
	{
		do
		{
			if (strcmp(songName, pCurr->data.songTitle) == 0)
			{
				displayRecord(pCurr->data);
				success = 1;
			}
			pCurr = pCurr->pNext;

		} while (pCurr != pHead);
	}


	return success;
}

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
void displayRecordsPrompt(Node* pHead)
{
	char selectionStr[3] = "",
		artistName[20] = "";
	int selectionInt = -1;

	do
	{
		system("cls");
		printf("Display\t(1) All Records\n\t(2) Records from Artist\n");
		printf("\nEnter number: ");
		fgets(selectionStr, 3, stdin);
		rewind(stdin);

		if (selectionStr[1] == '\n')
		{
			selectionInt = atoi(selectionStr);
		}
		else
		{
			continue;
		}

	} while (selectionInt != 1 && selectionInt != 2);

	switch (selectionInt)
	{
	case 1: system("cls");
		displayRecordsAll(pHead);
		break;
	case 2: system("cls");
		do
		{
			printf("type \"cancel\" to cancel\n");
			printf("\nSearch Artist: ");
			fgets(artistName, 20, stdin);
			rewind(stdin);

			if (artistName[strlen(artistName) - 1] == '\n')
			{
				artistName[strlen(artistName) - 1] = '\0';
			}
			system("cls");
			if (strcmp(artistName, "cancel") == 0)
			{
				break;
			}

		} while (!displayRecordsArtist(pHead, artistName));
		break;
	default:
		fprintf(stderr, "\nHello World\nFatal Error X(\n");
		break;
	}
	putchar('\n');
	system("pause");
}

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
void run(void)
{
	Node* pHead;
	FILE* fileStream = fopen("musicPlayList.csv", "r");
	int selection = -1;

	initList(&pHead);
	srand((unsigned int)time(NULL));

	do
	{
		selection = menu();

		switch (selection)
		{
		case 1:
			if (fileStream != NULL)
			{
				loadMusic(fileStream, &pHead);
				system("cls");
				printf("Loading...");
				Sleep(150);
				system("cls");
				printf("Complete\n\n");
				system("pause");
			}
			else
			{
				fprintf(stderr, "File failed to open\n\n");
			}
			break;
		case 2:
			if (pHead != NULL)
			{
				fclose(fileStream);
				fileStream = fopen("musicPlayList.csv", "w");
				storeMusicWithWarning(fileStream, pHead);
				fclose(fileStream);
				fileStream = fopen("musicPlayList.csv", "r");
			}
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			break;
		case 3:
			if (pHead != NULL)
				displayRecordsPrompt(pHead);
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			break;
		case 4: 
			promptInsert(&pHead);
			break;
		case 5: 
			if (pHead != NULL)
				promptDelete(&pHead);
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			break;
		case 6:
			if (pHead != NULL)
				editRecord(pHead);
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			break;
		case 7:
			if (pHead != NULL)	
				sortPrompt(&pHead);
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			
			break;
		case 8:
			if (pHead != NULL)
				rateRecord(pHead);
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			break;
		case 9: 
			if (pHead != NULL)
				selectSongToPlay(pHead);
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			break;
		case 10: 
			if (pHead != NULL)
			{
				int indexArray[100] = { 0 };
				shuffleArray(pHead, indexArray);
				shufflePlaySongs(pHead, indexArray);
			}
			else
			{
				system("cls");
				printf("No Records Found!\n\n");
				system("pause");
			}
			break;
		case 11: system("cls");
			printf("Exiting...");
			Sleep(500);
			system("cls");
			break;
		default:
			fprintf(stderr, "\nHello World\nFatal Error X(\n");
			break;
		}
	} while (selection != 11);

	fclose(fileStream);
}


