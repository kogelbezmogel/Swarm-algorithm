#pragma once

#include <string>
#include <iostream>

class TestClass {

	protected:
		std::string _text;

	public:
		TestClass() { _text = "STRING"; }
		void sth() { std::cout << _text << "\n"; }
};