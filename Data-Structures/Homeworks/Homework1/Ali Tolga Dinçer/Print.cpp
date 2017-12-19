#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void writeFoundWord(char* word, string direction, int rowbeg, int rowend, int colbeg, int colend)
{ // Function to write the found words by their id's and places.
	ofstream myfile;
	myfile.open("foundWordsInfo.txt", ios::app);
	for (size_t i = 0; i < strlen(word); i++)
	{
		myfile << *(word + i);
	}
	myfile << " " << direction << " " << "[";
	myfile << rowbeg << "]" << "[" << colbeg << "]" << " - " << "[";
	myfile << rowend << "]" << "[" << colend << "]" << endl;
	myfile.close();
}

void erasePuzzle(char **puzzleArray)
{ // Function to erase the words from the puzzle.
	FILE *fp;
	fp = fopen("foundWordsInfo.txt", "r"); // Reading the places of the words from the file
	char *temp = NULL, *way = NULL;
	while (!feof(fp))
	{
		if (temp != NULL) // Deleting the previous dynamically created char arrays.
		{
			delete[] temp;
		}
		if (way != NULL)
		{
			delete[] way;
		}
		temp = new char[16]; // Creating 2 new char arrays to take the wordno and direction.
		way = new char[15];
		int rowbeg, colbeg, rowend, colend;
		char c;
		fscanf(fp, "%s %s %c %d %c %c %d %c %c %c %d %c %c %d %c", 
			temp, way, &c, &rowbeg, &c, &c, &colbeg, &c, &c, &c,  &rowend, &c, &c, &colend, &c);
		temp[15] = '\0';
		way[14] = '\0';
		if(feof(fp))
		{
			break;
		}

		if (way[0] == 'H')
		{
			if (colbeg < colend)
			{
				for (int i = colbeg; i <= colend; i++)
				{
					*((*(puzzleArray + rowbeg)) + i) = ' ';
				}
				continue;
			}
			else
			{
				for (int i = colbeg; i >= colend; i--)
				{
					*((*(puzzleArray + rowbeg)) + i) = ' ';
				}
				continue;
			}
		} // End of if Horizontal.

		if (way[0] == 'V')
		{
			if (rowbeg < rowend)
			{
				for (int i = rowbeg; i <= rowend; i++)
				{
					*((*(puzzleArray + i)) + colbeg) = ' ';
				}
				continue;
			}
			else
			{
				for (int i = rowbeg; i >= rowend; i--)
				{
					*((*(puzzleArray + i)) + colbeg) = ' ';
				}
				continue;
			}
		} // End of if Vertical.

		if (way[0] == 'D')
		{
			if (rowbeg < rowend && colbeg < colend)
			{ // From top left to down right.
				while (rowbeg != rowend + 1 && colbeg != colend + 1)
				{
					*((*(puzzleArray + rowbeg)) + colbeg) = ' ';
					if (rowbeg == 14 || colbeg == 14)
					{
						break;
					}
					rowbeg++;
					colbeg++;
				}
				continue;
			}

			if (rowbeg < rowend && colbeg > colend)
			{ // From top right to down left.
				while (rowbeg != rowend + 1 && colbeg != colend - 1)
				{
					*((*(puzzleArray + rowbeg)) + colbeg) = ' ';
					if (rowbeg == 14 || colbeg == 0)
					{
						break;
					}
					rowbeg++;
					colbeg--;
				}
				continue;
			}

			if (rowbeg > rowend && colbeg < colend)
			{ // From down left to up right.
				while (rowbeg != rowend - 1 && colbeg != colend + 1)
				{
					*((*(puzzleArray + rowbeg)) + colbeg) = ' ';
					if (rowbeg == 0 || colbeg == 14)
					{
						break;
					}
					rowbeg--;
					colbeg++;
				}
				continue;
			}

			if (rowbeg > rowend && colbeg > colend)
			{ // From down right to up left.
				while (rowbeg != rowend - 1 && colbeg != colend - 1)
				{
					*((*(puzzleArray + rowbeg)) + colbeg) = ' ';
					if (rowbeg == 0 || colbeg == 0)
					{
						break;
					}
					rowbeg--;
					colbeg--;
				}
				continue;
			}
		} // End of if Diagonal.

	} // End of file.
	fclose(fp);

	fp = fopen("lastVersionPuzzle.txt", "w"); // Writing the new puzzle.
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			fprintf(fp, "%c ", puzzleArray[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

