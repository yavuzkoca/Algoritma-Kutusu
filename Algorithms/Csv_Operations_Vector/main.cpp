/* HEADER	   : Csv Operations
 * AUTHOR	   : Muhammed YILMAZ
 * E-MAIL	   : yilmazmu15@gmail.com
 */

#include <iostream>
#include "csvop.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Operations -> \t CsvOp myFile(',',\"sample.csv\");" << endl << endl;
         
    CsvOp myFile(',',"sample.csv");
    cout << "File: " << myFile.getFileName() << endl
         << "Cruncher: " << myFile.getCruncher() << endl
         << "Line: " << myFile.getCsvTable().size() << endl;
    myFile.print_table();


    cout << endl << endl << endl;
    cout << "Operations -> \t CsvOp subTable(myFile.find_row_by_column(2,\"ST  JOHNS COUNTY\"));" << endl
         << "\t\t subTable.setFileName(\"output.csv\");" << endl
         << "\t\t subTable.setCruncher(';');" << endl << endl;

    CsvOp subTable(myFile.find_row_by_column(2,"ST  JOHNS COUNTY"));
    subTable.setFileName("output.csv");
    subTable.setCruncher(';');

    cout << "File: " << subTable.getFileName() << endl
         << "Cruncher: " << subTable.getCruncher() << endl
         << "Line: " << subTable.getCsvTable().size() << endl;
	subTable.print_table();

	return EXIT_SUCCESS;
}