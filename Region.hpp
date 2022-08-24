#ifndef _REGION_HPP_
#define _REGION_HPP_

#include <vector>
#include <utility>
#include <cmath>
#include <Magick++.h>

class Region {
public:
	
	//Default Constructor
	Region();

	//Constructor with pre-defined Color
	Region(Magick::Color c);

	//Returns the pixels associated with the region
	std::vector<std::pair<size_t, size_t>> GetArea();

	//Colours the region
	void ColourRegion(Magick::Image image);

	//Sets the fill color of the region
	void SetColour(Magick::Color c);

	//Finds the average Color of the region;
	Magick::Color AverageColour(Magick::Image i);

	//Adds a pixel to the Image
	void AddPixel(size_t x, size_t y);
private:
	Magick::Color FILL_COLOUR;
	std::vector<std::pair<size_t, size_t>> area; // vector that contains all the coordinates within the area
};

#endif