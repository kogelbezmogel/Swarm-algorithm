#include "AnaliticFunctionReader.h"
#include <algorithm>
#include <functional>

int AnaliticFunctionReader::MAX_FUNS = 20;

AnaliticFunctionReader::AnaliticFunctionReader() {
	_empty = true;
	BasicFunctions::Initialize();
}

AnaliticFunctionReader::AnaliticFunctionReader( std::string name ) {
	
	BasicFunctions::Initialize();
	std::fstream file(name, std::ios::in);
		std::getline(file, _line);
	file.close();
	convertSchema();
}

void AnaliticFunctionReader::convertSchema() {
	deleteSpaces();
	_schema.clear();
	_indexes_for_instruction.clear();
	_instruction_schemas.clear();

	for( int i = 0; i < _line.size(); ++i ) {
		if( _line[i] == '(' ) {
			priorytet += MAX_FUNS;
		}
		else if( _line[i] == ')' ) {
			priorytet -= MAX_FUNS;
		}
		else if( _line[i] == '+' ) {
			_schema.push_back( BF::SUM + priorytet );
		}
		else if( _line[i] == '-' ) {
			_schema.push_back( BF::SUBSTRACT + priorytet );
		}
		else if( _line[i] == '*' ) {
			_schema.push_back( BF::MULTIPLY + priorytet );
		}
		else if( _line[i] == '/' ) {
			_schema.push_back( BF::DIVIDE + priorytet );
		}
		else if( _line[i] == '^' ) {
			_schema.push_back( BF::POWER + priorytet );
		}
		else if( _line[i] == 'l' ) {
			if( _line[i+1] == 'n' ) {
				++i;
				_schema.push_back(-2);
				_schema.push_back( BF::LN + priorytet );
			}
			else if( _line[i+1] == 'g' ) {
				++i;
				_schema.push_back(-2);
				_schema.push_back( BF::LG + priorytet );
			}
			else if( _line[i+1] == 'o' ) {
				i += 2;
				_schema.push_back(-2);
				_schema.push_back( BF::LOG + priorytet );
			}
		}
		else if( _line[i] == 'x' ) {
			_schema.push_back(-1);
		}
		else {
			_schema.push_back( std::stof( _line.substr(i, _line.size() - i) ) );
		}
	}
	// sorting the indexes
	int schema_len = _schema.size();
	int max_index;
	std::vector<double> copy_schema = _schema ; 
	while ( schema_len > 1 ) {

		max_index = find_max_index(copy_schema);
		
		_indexes_for_instruction.push_back(max_index);
		_instruction_schemas.push_back(copy_schema);

		copy_schema[max_index + 1] = 0;
		copy_schema.erase( copy_schema.begin() + max_index - 1, copy_schema.begin() + max_index + 1 );

		schema_len -= 2;
	}
	// place for result of all schemas
	_instruction_schemas.push_back( std::vector<double>({0}) );
}

void AnaliticFunctionReader::setLine(std::string line) {
	_line = line;
}

std::vector<double> AnaliticFunctionReader::getSchema() {
	return _schema;
}

void AnaliticFunctionReader::deleteSpaces() {

	std::string new_line = "";
	for( auto i : _line ){
		if( i != ' ')
			new_line += i;
	} 
	_line = new_line;
}

void AnaliticFunctionReader::printSchema() {
		
		std::cout << "\n\nSchemat glowny\n|";
		for( auto i : _schema )
			std::cout << i << "|";
		std::cout << std::endl;

		std::cout << "\n\nStworzone schematy\n";
		for( const auto& schema : _instruction_schemas) {
			for( const auto& el : schema)
				std::cout << "[" << el << "]";
			std::cout << "\n";
		}

		std::cout << "\n\nIndeksy\n";
		for( auto ind : _indexes_for_instruction )
			std::cout << "[" << ind << "]";
		std::cout << "\n";
	}

std::string AnaliticFunctionReader::getLine() {
	return _line;
}

int AnaliticFunctionReader::find_max_index( std::vector<double>& line ) {
	int max = line.size() - 2;
	for(int i = line.size() - 2; i > 0; i-=2 ) {
		if( line[i] > line[max] ) {
			max = i;
		}
	}
	return max;
}


double AnaliticFunctionReader::function_value_in_point(double x) {
	int index;
	double val;
	double x1;
	double x2;

	for( int i = 0; i < _indexes_for_instruction.size(); i++ ) {
		index = _indexes_for_instruction[i];

		x1 = (_instruction_schemas[i][index-1] == -1 ? x : _instruction_schemas[i][index-1]);
		x2 = (_instruction_schemas[i][index+1] == -1 ? x : _instruction_schemas[i][index+1]);
		val = BasicFunctions::fun_vec[ (int)_instruction_schemas[i][index] % MAX_FUNS ](x1, x2);

		// wstawienie wczesniej wyliczonych wartosci do nastepnego schematu przed indeksem 	
		for(int k = 0; k < index - 1; k++)
			_instruction_schemas[i+1][k] = _instruction_schemas[i][k];
	
		// wstawienie wyliczonej wartosci do kolejnego schematu
		_instruction_schemas[i+1][index - 1] = val;

		// wstawianie wczesniej wyliczonych wartosci do nastepnego schematu po indeksie
		for(int k = index+2; k < _instruction_schemas[i].size(); k++)
			_instruction_schemas[i + 1][k - 2] = _instruction_schemas[i][k];	
	}
	return _instruction_schemas[ _instruction_schemas.size() - 1 ][0];
}
