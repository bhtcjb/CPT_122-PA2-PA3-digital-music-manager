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
#include "TestDigitalMusicManager.h"

int main(void)
{
	run();

	return 0;
}