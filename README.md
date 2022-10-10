# Benten

Benten is a multithreaded CLI image editor written in C++ and utilizes the ImageMagick library. 
Benten is able to transform images into predefined permutations.

## Edit Options:

- PixelArtTransform
	- Converts the image to be composed of pixels of a predefined resolution
- TriangleVectorTransform
	- Converts the image to be composed of interlocking triangles
- CircleAreaTransform
	- Converts the image to be composed of a collection of adjacently placed randomly sized coloured circles
- AbstractBlobTransform
	- Converts the image into a collection of unconnected blobs defined by color that permiate in random directions
- ColorReducer
	- Converts the image to be composed only of a certain number of colours
- Silhoutter
	- Uses edge detection to reduce the image down to only its consituent edges
