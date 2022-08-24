#include "benten.hpp"
#include "Picture.hpp"
#include <Magick++.h>
#include <filesystem>
#include <string>
#include <iostream>

std::string INPUT_PATH = "/in";


int main(int argc, char ** argv)
{
	Magick::InitializeMagick(*argv);

	for (const auto& file : std::filesystem::directory_iterator(INPUT_PATH)) {
		if (!file.is_directory()) {
			std::string command = argv[2];
			Picture pic = Picture(file.path().filename().string());
			pic.PixelArtTransform((unsigned int)argv[3]);
		}
	}


	/*if (argc == 3) {
		Magick::InitializeMagick(*argv);

		if (command == "pixeltransform") {
			for (const auto& file : std::filesystem::directory_iterator(INPUT_PATH)) {
				if (!file.is_directory()) {
					Picture pic = Picture(file.path().filename().string());
					pic.PixelArtTransform((unsigned int) argv[3]);
				}
			}
		}
		else if (command == "vectortransform") {
			for (const auto& file : std::filesystem::directory_iterator(INPUT_PATH)) {
				if (!file.is_directory()) {
					Picture pic = Picture(file.path().filename().string());
					pic.TriangleVectorTransform((unsigned int) argv[3]);
				}
			}
		}
		else if (command == "abstractblob") {
			for (const auto& file : std::filesystem::directory_iterator(INPUT_PATH)) {
				if (!file.is_directory()) {
					Picture pic = Picture(file.path().filename().string());
					pic.AbstractBlobTransform((std::string)argv[3] == "fill");
				}
			}
		}
		else if (command == "colourreduce") {
			for (const auto& file : std::filesystem::directory_iterator(INPUT_PATH)) {
				if (!file.is_directory()) {
					Picture pic = Picture(file.path().filename().string());
					pic.ColorReducer((unsigned int)argv[3]);
				}
			}
		}
		else {
			std::cout << "Invalid command, exiting" << std::endl;
		}
	}
	else if (argc <= 2) {
		std::cout << "Too few commands provided. Please provide a command. Exiting." << std::endl;
	}
	else {
		std::cout << "Too many commands provided, please provide only a single command. Exiting." << std::endl;
	}*/

	return 0;
}
