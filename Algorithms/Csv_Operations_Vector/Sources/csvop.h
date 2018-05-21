/* HEADER      : CSV OPERATIONS CLASS - HEADER
 * AUTHOR      : Muhammed YILMAZ
 * START DATE  : 05.05.2018
 * LAST EDIT   : 20.05.2018
 * E-MAIL      : yilmazmu15@gmail.com
 */

#ifndef CSVOP_H
#define CSVOP_H

#include <utility>
#include <vector>
#include <iostream>

class CsvOp
{
    char cruncher;
    std::string fileName;
    std::vector<std::vector<std::string>> csvTable;
public:
    explicit CsvOp(char inCruncher = ';'): cruncher(inCruncher) {}
    explicit CsvOp(std::string inFileName, char inCruncher = ';');
    explicit CsvOp(std::vector<std::vector<std::string>> inCsvTable, const char inCruncher = ';') : csvTable(std::move(inCsvTable)), cruncher(inCruncher) {}
    ~CsvOp() = default;

    void sort_by_column(int columnOrder);
    void read_csv_file();
    std::vector<std::string> column_list(unsigned int returnColumn, unsigned int searchColumn=0, std::string searchString="");
    std::vector<std::vector<std::string>> find_row_by_column(unsigned int searchColumn, std::string searchString);
    bool write_to_file();
    bool write_to_file(const std::string &inFileName, const char &inCruncher);

    // Inline functions... (direct vector functions...)
    inline void clear(){csvTable.clear();}
    inline void insert(int lineOrder, std::vector<std::vector<std::string>> anotherTable)
    { csvTable.insert((csvTable.begin()+lineOrder),anotherTable.begin(), anotherTable.end());}
    inline void insert(int lineOrder, const std::vector<std::string> &line)
    {csvTable.insert((csvTable.begin()+lineOrder),line);}

    // Static functions...
    static std::vector<std::string> line_to_vector(const std::string &line, char seperator);

    /*
    static bool add_line_to_file(std::vector<std::string> line, const string fileName, const char cruncher);
    bool write_to_file();
    */

    //Getters and Setters...
    inline char getCruncher() const {return cruncher;}
    inline void setCruncher(char value) {cruncher = value;}
    inline std::string getFileName() const {return fileName;}
    inline void setFileName(const std::string &value) {fileName = value;}
    inline std::vector<std::vector<std::string>> getCsvTable() const {return csvTable;}

    // Garbage functions...
    void print_table();
    static void print_table(std::vector<std::vector<std::string>> table);
};

#endif // CSVOP_H
