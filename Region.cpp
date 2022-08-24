#include <vector>
#include <utility>
#include <cmath>
#include <Magick++.h>
#include "Region.hpp"

Region::Region()
{
	FILL_COLOUR = NULL;
	area = std::vector<std::pair<size_t, size_t>>();
}

Region::Region(Magick::Color c)
{
	FILL_COLOUR = c;
	area = std::vector<std::pair<size_t, size_t>>();
}

std::vector<std::pair<size_t, size_t>> Region::GetArea()
{
	return std::vector<std::pair<size_t, size_t>>();
}

//Colours the region
void Region::ColourRegion(Magick::Image image)
{
	for (std::pair<size_t, size_t> pxl : area) {
		image.pixelColor(pxl.first, pxl.second) = FILL_COLOUR;
	}
}

void Region::SetColour(Magick::Color c)
{
	FILL_COLOUR = c;
}

Magick::Color Region::AverageColour(Magick::Image i)
{
	size_t r = 0;
	size_t g = 0;
	size_t b = 0;
	size_t size = area.size();

	for (std::pair<size_t, size_t> pxl : area) {
		Magick::ColorRGB temp = Magick::ColorRGB(i.pixelColor(pxl.first, pxl.second));
		r += pow(temp.red(), 2);
		g += pow(temp.green(), 2);
		b += pow(temp.blue(), 2);
		i.pixelColor(pxl.first, pxl.second) = FILL_COLOUR;
	}
	
	return (Magick::Color) Magick::ColorRGB(sqrt(r / size), sqrt(g / size), sqrt(b / size));

}

void Region::AddPixel(size_t x, size_t y)
{
	area.push_back(std::pair<size_t, size_t>(x, y));
}

