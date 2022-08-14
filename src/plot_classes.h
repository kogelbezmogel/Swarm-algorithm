#ifndef __PLOT__
#define __PLOT__

#include <vector>
#include <SFML/Graphics.hpp>

class FunctionPlot2D : public sf::Drawable {

	bool _is_empty = { true };

	sf::Vector2f _position;
	sf::Vector2f _size;

	sf::RectangleShape _background;
	sf::RectangleShape _x_axis;
	sf::RectangleShape _y_axis;

	std::vector< sf::RectangleShape > _x_axis_back_lines;
	std::vector< sf::RectangleShape > _y_axis_back_lines;

	std::vector< std::pair<double, double> > _fun_points;
	sf::VertexArray _fun_shape;

	double _x_min;
	double _x_max;
	double _y_min;
	double _y_max;

	int _amount_of_back_lines_x = { 10 };
	int _amount_of_back_lines_y = { 10 };
	int _margin_around_plot = { 25 };

	sf::Text _x_unit;
	sf::Text _y_unit;
	sf::Text _title;
	sf::Text _x_axis_label;
	sf::Text _y_axis_label;
	sf::Font _font;

	sf::Text text;
	std::vector<sf::Text> test_text;
	std::vector<sf::Text> _x_axis_values;
	std::vector<sf::Text> _y_axis_values;

	public:
		FunctionPlot2D( );
		FunctionPlot2D( std::vector< std::pair<double, double> > fun_points, double x_max = 5, double x_min = -5, double y_max = 5, double y_min = -5, sf::Vector2f size = sf::Vector2f(300, 300), sf::Vector2f pos = sf::Vector2f(0, 0));

		virtual void draw(sf::RenderTarget& r_trg, sf::RenderStates r_sts) const override;
		void setUnitX(std::string u);
		void setUnitY(std::string u);
		void setTitle(std::string t);
		void setSize(sf::Vector2f size);
	
	private:
		std::pair<double, double> project_point( std::pair<double, double> fun_point ) const;
		bool point_in_field( std::pair<double, double> point ) const;
};

#endif //__PLOTT__