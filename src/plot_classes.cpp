#include "plot_classes.h"
#include <fstream>
#include <iostream>

FunctionPlot2D::FunctionPlot2D() {
	_is_empty = true;
}

FunctionPlot2D::FunctionPlot2D(std::vector< std::pair<double, double> > fun_points, double x_max, double x_min, double y_max, double y_min, sf::Vector2f size, sf::Vector2f pos ) :
_x_max(x_max),
_x_min(x_min),
_y_max(y_max),
_y_min(y_min),
_position(pos),
_size(size) {

	_font.loadFromFile("arial.ttf");
	_is_empty = false;
	_margin_around_plot = 25;
	
	_background.setSize( size );
	_background.setFillColor( sf::Color(255, 255, 255) );
	_background.setPosition( sf::Vector2f(0, 0) );

	int height_whole = size.y;
	int additional_space_for_pointer = 5;

	// setting axes and net
	_x_axis = sf::RectangleShape( sf::Vector2f(size.x - 2 * _margin_around_plot + additional_space_for_pointer, 1) );
	_y_axis = sf::RectangleShape( sf::Vector2f(1, size.y - 2 * _margin_around_plot + additional_space_for_pointer) );
	_x_axis.setFillColor(sf::Color::Black);
	_x_axis.setPosition(sf::Vector2f(_margin_around_plot, height_whole - _margin_around_plot));
	_y_axis.setFillColor(sf::Color::Black);
	_y_axis.setPosition(sf::Vector2f(_margin_around_plot, _margin_around_plot - additional_space_for_pointer));

	sf::RectangleShape net_line( sf::Vector2f(size.x - 2 * _margin_around_plot, 1) );
	net_line.setFillColor( sf::Color(150, 150, 150) );
	int deltaY_px = (height_whole - 2 * _margin_around_plot) / _amount_of_back_lines_x;
	int deltaX_px = (size.x - 2 * _margin_around_plot) / _amount_of_back_lines_y;

	for (int i = 1; i <= _amount_of_back_lines_x; i++) {
		net_line.setPosition( sf::Vector2f(_margin_around_plot, height_whole - _margin_around_plot - i * deltaY_px) );
		_x_axis_back_lines.push_back( sf::RectangleShape(net_line) );
	}

	net_line.setSize( sf::Vector2f(1, size.y - 2 * _margin_around_plot) );
	for (int i = 1; i <= _amount_of_back_lines_y; i++) {
		net_line.setPosition( sf::Vector2f(_margin_around_plot + i * deltaX_px, _margin_around_plot) );
		_y_axis_back_lines.push_back( sf::RectangleShape(net_line) );
	}

	// setting values on axes	
	double real_deltaY = (double) (_y_max - _y_min) / _amount_of_back_lines_x;
	double real_deltaX = (double) (_x_max - _x_min) / _amount_of_back_lines_y;

	_x_axis_values.resize( _amount_of_back_lines_y + 1, sf::Text() );
	for( int i = 0; i < _x_axis_values.size(); ++i ) {
		_x_axis_values[i].setCharacterSize(10);
		_x_axis_values[i].setFillColor( sf::Color(0, 0, 0) );	
		_x_axis_values[i].setString( std::to_string(i * real_deltaX + _x_min).substr(0, 4) );
		_x_axis_values[i].setPosition(_margin_around_plot + i * deltaX_px - 10, height_whole - 15);
		_x_axis_values[i].setFont( _font );
	}
	_y_axis_values.resize( _amount_of_back_lines_x + 1, sf::Text() );
	for( int i = 0; i < _y_axis_values.size(); ++i ) {
		_y_axis_values[i].setCharacterSize(10);
		_y_axis_values[i].setFillColor( sf::Color(0 ,0, 0) );	
		_y_axis_values[i].setString( std::to_string(i * real_deltaY + _y_min).substr(0, 4) );
		_y_axis_values[i].setPosition(2, height_whole - _margin_around_plot - i * deltaY_px - 7);
		_y_axis_values[i].setFont( _font );
	}

	// setting desc of axes and title

	// setting plot
	_fun_shape = sf::VertexArray(sf::LinesStrip, 0);
	std::string path = "fun_conv.txt";
	FILE* file = fopen(path.c_str(), "w");

	for (int i = 0; i < fun_points.size(); i++) {
		if( point_in_field(fun_points[i]) ) {
			std::pair<double, double> point_proj = project_point(fun_points[i]);
			fprintf(file, "(%15f, %15f) => (%15f, %15f) \n", fun_points[i].first, fun_points[i].second, point_proj.first, point_proj.second); 
			_fun_shape.append(sf::Vertex( sf::Vector2f(point_proj.first, point_proj.second), sf::Color(255, 0, 0) ));
		}
	}
	fclose(file);
}


void FunctionPlot2D::draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts) const {

	if( !_is_empty ) {
		r_trg.draw(_background);
		for (auto& line : _x_axis_back_lines)
			r_trg.draw(line);
		for (auto& line : _y_axis_back_lines)
			r_trg.draw(line);
		r_trg.draw(_x_axis);
		r_trg.draw(_y_axis);
		
		for (auto& value : _x_axis_values)
			r_trg.draw(value);
		for (auto& value : _y_axis_values)
			r_trg.draw(value);
		/*
		r_trg.draw(_title);
		r_trg.draw(_x_axis_label);
		r_trg.draw(_y_axis_label);*/

		r_trg.draw(_fun_shape);
	}
	else {
		sf::RectangleShape rec = sf::RectangleShape( sf::Vector2f(100, 100) );
		rec.setFillColor( sf::Color(0, 200, 200) );
		r_trg.draw(rec);
	}
}


void FunctionPlot2D::setUnitX(std::string u) {
	_x_unit = sf::Text(u, _font, 15);
}


void FunctionPlot2D::setUnitY(std::string u) {
	_y_unit = sf::Text(u, _font, 15);
}


void FunctionPlot2D::setTitle(std::string t) {
	_title = sf::Text(t, _font, 15);
}


void FunctionPlot2D::setSize(sf::Vector2f size) {
	_size = size;
}


std::pair<double, double> FunctionPlot2D::project_point( std::pair<double, double> fun_point ) const {
	double x = (_size.x - 2 * _margin_around_plot) * (fun_point.first - _x_min) / (_x_max - _x_min) + _margin_around_plot;
	double y = _size.y - ( (_size.y - 2 * _margin_around_plot) * (fun_point.second - _y_min) / (_y_max - _y_min) + _margin_around_plot );
	return std::pair<double, double>(x, y);
}


bool FunctionPlot2D::point_in_field( std::pair<double, double> point ) const {
	bool res = true;
	if( point.first > _x_max || point.first < _x_min || point.second > _y_max || point.second < _y_min )
		res = false;
	return res;
}