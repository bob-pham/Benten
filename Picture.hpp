#ifndef _PICTURE_HPP_
#define _PICTURE_HPP_

#include "Picture.hpp"
#include "Region.hpp"
#include <Magick++.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#include <iostream>

class Picture {

	public:
		// Picture constructor, takes in a path to an image
		Picture(std::string pic);

		// transforms the picture to be pixelated, default
		void PixelArtTransform(size_t resolution);

		// transforms the picture to triangle vectors
		void TriangleVectorTransform(size_t resolution);

		// transforms the picture to be made of abstract blobs which are filled if fill is true
		void AbstractBlobTransform(bool fill);

		// transforms the pictures to only consist of count pictures
		void ColorReducer(int count);

	private:
		Magick::Image image; // The original image that the picture is going to edit
		Magick::Color DEFAULT_COLOR; // default fill color
		std::string name; // name of the image

		// Identifies regions within the image
		//const std::vector<Region> FindRegions();

		// Colors all the pixels within the area as the average of that area
		void ColorAverage(size_t x, size_t y, size_t w, size_t h, std::mutex mx, unsigned int *count);

		// Generates a square region corresponding to (x,y) coordinate and width and height
		Region* GenerateSquareRegion(size_t x, size_t y, size_t w, size_t h);

		// Helper function for multithreading, so that each region can be done on its own thread 
		void PixelateArea(size_t x, size_t y, size_t w, size_t h, Magick::Image im, std::mutex mx, unsigned int* num);

		Region GenerateTriangleRegion(size_t x, size_t y, size_t w, size_t h);

};

#endif