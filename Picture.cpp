#include "Picture.hpp"
#include "Region.hpp"
#include <Magick++.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <iostream>

// Picture constructor, takes in a path to an image
Picture::Picture(std::string pic)
{
	name = pic;

	image = Magick::Image();
	image.read(pic);
}


// transforms the picture to be pixelated, default
void Picture::PixelArtTransform(size_t resolution)
{
	//number of threads that are currently running
	volatile unsigned int* threads = new unsigned int(0);
	
	//information about the image so that we don't have to compute it every time 
	size_t length = std::max(image.baseColumns(), image.baseRows()) / resolution;
	size_t image_height = image.baseRows();
	size_t image_width = image.baseColumns();
	size_t height_remainder = image_height % resolution;
	size_t width_remainder = image_width % resolution;
	
	// mutex
	std::mutex px_mx;
	std::string new_name = name.substr(0, name.length() - 4);
	
	new_name.append("_pixel_art.png");
	std::cout << "Starting PixelArtTransform on " + new_name << "\n";

	//Converts the area to be composed of square regions, each region gets its own thread;

	for (size_t h = 0; h < image_height; h += length) {
		for (size_t w = 0; w < image_width; w += length) {

			unsigned int temp_h = h + length >= image_height ? length + height_remainder : length;
			unsigned int temp_w = w + length >= image_width ? length + width_remainder : length;

			px_mx.lock();
			*threads++;

			std::thread(&Picture::PixelateArea, w, h, temp_w, temp_h, image, px_mx, threads).detach();

			px_mx.unlock();

		}
	}

	while (threads != 0);

	//saves the image under new_name
	delete threads;
	image.syncPixels();
	image.write(new_name);

	std::cout << new_name + " Completed!" << std::endl;
}


// transforms the picture to triangle vectors
void Picture::TriangleVectorTransform(size_t resolution)
{
	//TODO
}


// transforms the picture to be made of abstract blobs which are filled if fill is true
void Picture::AbstractBlobTransform(bool fill)
{
	//TODO
}


// transforms the pictures to only consist of count pictures
void Picture::ColorReducer(int count)
{
	//TODO
}

// Generates a square region corresponding to (x,y) coordinate and width and height
Region* Picture::GenerateSquareRegion(size_t x, size_t y, size_t w, size_t h) {
	Region* region = new Region();

	for (size_t ypos = y; ypos < h + y; ypos++) {
		for (size_t xpos = x; xpos < w + x; xpos++) {
			region->AddPixel(xpos, ypos);
		}
	}

	return region;
}

// Helper function for multithreading, so that each region can be done on its own thread 
void Picture::PixelateArea(size_t x, size_t y, size_t w, size_t h, Magick::Image im, std::mutex mx, unsigned int* num) {
	Region* genRegion = GenerateSquareRegion(x, y, w, h);
	genRegion->SetColour(genRegion->AverageColour(im));
	genRegion->ColourRegion(im);

	delete genRegion;

	mx.lock();
	*num--;
	mx.unlock();

}
