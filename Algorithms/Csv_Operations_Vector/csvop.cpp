/* HEADER      : CSV OPERATIONS CLASS - FUNCTIONS
 * AUTHOR      : Muhammed YILMAZ
 * START DATE  : 05.05.2018
 * LAST EDIT   : 05.05.2018
 * E-MAIL      : yilmazmu15@gmail.com
 */

#include "csvop.h"
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

CsvOp::CsvOp(char inCruncher, std::string inFileName): cruncher(inCruncher), fileName(inFileName)
{
    read_csv_file();
}

CsvOp::~CsvOp()
{
}

std::vector<std::string> CsvOp::line_to_vector(const std::string line, char seperator)
{
    std::vector<std::string> output;
    if(!seperator)
        return output;

    std::string::size_type prev_pos = 0, pos = 0;
    while((pos = line.find(seperator, pos)) != std::string::npos)
    {
        std::string substring( line.substr(prev_pos, pos - prev_pos) );
        output.push_back(substring);
        prev_pos = ++pos;
    }
    output.push_back(line.substr(prev_pos, pos-prev_pos)); // Last word
    return output;
}

void CsvOp::read_csv_file()
{
    std::ifstream myFile (fileName);
    if(!myFile.is_open()){
        std::cout << "File (" << fileName << ") is could not be opened." << std::endl;
        return;
    }
    std::string stringLine;
    while(getline(myFile, stringLine))
    {
        csvTable.push_back(line_to_vector(stringLine, cruncher));
    }
    myFile.close();
}

std::vector<std::string> CsvOp::column_list(unsigned int returnColumn, unsigned int searchColumn, std::string searchString)
{
    std::vector<std::string> list;
    for(unsigned int i = 0; i < csvTable.size(); ++i){
        if(searchString == "" ||
                (!(csvTable[i].size()<searchColumn+1) && csvTable[i][searchColumn]==searchString))
            list.push_back(csvTable[i][returnColumn]);
    }
    return list;
}

std::vector<std::vector<std::string> > CsvOp::find_row_by_column(unsigned int searchColumn, std::string searchString)
{
    std::vector<std::vector<std::string> > table;
    for(unsigned int i = 0; i < csvTable.size(); ++i){
        if(searchString == "" ||
                (!(csvTable[i].size()<searchColumn+1) && csvTable[i][searchColumn]==searchString))
            table.push_back(csvTable[i]);
    }
    return table;
}

void CsvOp::sort_by_column(int columnOrder)
{
    for(unsigned int j = 0; j < csvTable.size()-1; ++j){
        for(unsigned int i = 0; i < csvTable.size()-1; ++i){
            if(csvTable.at(i).at(columnOrder).compare(csvTable.at(i+1).at(columnOrder)) > 0){
                std::swap(csvTable.at(i),csvTable.at(i+1));
            }
        }
    }
}

void CsvOp::print_table()
{
    for(unsigned int i = 0; i < csvTable.size(); i++)
    {
        for(unsigned int j = 0; j < csvTable.at(i).size(); j++)
        {
            std::cout << csvTable.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
}

void CsvOp::print_table(std::vector<std::vector<std::__cxx11::string> > table)
{
    for(unsigned int i = 0; i < table.size(); i++)
    {
        for(unsigned int j = 0; j < table.at(i).size(); j++)
        {
            std::cout << table.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
}
