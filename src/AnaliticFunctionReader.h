#ifndef __FUN_READER__
#define __FUN_READER__

#include "BasicFunctions.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>

class AnaliticFunctionReader {

public:
	AnaliticFunctionReader( );
	AnaliticFunctionReader( std::string line );

	void convertSchema( );
	void printSchema( );
	void deleteSpaces( );
	std::string getLine( );
	void setLine( std::string line );
	std::vector<double> getSchema( );
	double function_value_in_point( double x );
	int find_max_index( std::vector<double>& line );

	static int MAX_FUNS;

private:
	std::string _line;
	std::vector<double> _schema;
	std::vector< std::vector<double> > _instruction_schemas;
	std::vector< int > _indexes_for_instruction; // <index_in_schema, priority>
	bool _empty;
	int priorytet{ 0 };

};

#endif //__FUN_READER__