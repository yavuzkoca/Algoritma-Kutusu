/* HEADER	   : Csv Operations
 * AUTHOR	   : Muhammed YILMAZ
 * E-MAIL	   : yilmazmu15@gmail.com
 */

#include <iostream>
#include "csvop.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Operations -> \t CsvOp myFile(',',\"sample3.csv\");" << endl << endl;
         
    CsvOp myFile("sample3.csv",',');
    cout << "File: " << myFile.getFileName() << endl
         << "Cruncher: " << myFile.getCruncher() << endl
         << "Line: " << myFile.getCsvTable().size() << endl;
    myFile.print_table();


    cout << endl << endl << endl;
    cout << "Operations -> \t CsvOp subTable(myFile.find_row_by_column(1,\"BAL\"));" << endl
         << "\t\t subTable.setFileName(\"output.csv\");" << endl
         << "\t\t subTable.setCruncher(';');" << endl << endl;

    CsvOp subTable(myFile.find_row_by_column(1," \"BAL\""));
    subTable.setFileName("output.csv");

    cout << "File: " << subTable.getFileName() << endl
         << "Cruncher: " << subTable.getCruncher() << endl
         << "Line: " << subTable.getCsvTable().size() << endl;
	subTable.print_table();

	subTable.write_to_file("output.csv", ',');


	return EXIT_SUCCESS;
}