#include "img_concat.h"
#include "includes/argh.h"
#include <vector>
#include <string>


int main(int argc, const char* argv[]) {
	std::vector<std::string> img_path_list;
	char** images;
	size_t images_len = 0;
	bool vFlag = true;

	if ( argc <= 3 ) {
		std::printf("Usage: <program> <output file name> <img1> <img2> ...\n");
		return -1;
	}

	// images = (char **)std::malloc(8 * (argc -2));

	//std::printf("total size: %d\n", 8 * (argc -2));
	//std::printf("argc: %d\nsize of image: %d\n", argc, sizeof(images));

	const char* output_path = argv[2];
	std::string out_path(argv[1]);

	for (size_t idx = 2, j = 0; idx < argc; ++idx, ++j ) {
		img_path_list.push_back( argv[idx] );

		const char* param = argv[idx];
		// size_t argv_length = std::strlen(param);
		// char* img_name = (char*) std::malloc(argv_length + 1);
		// std::strcpy( img_name, param );
		// images[j] = img_name;
		// images_len ++;

	}


	ImageConcat img_concat = ImageConcat( argv[1], vFlag );
	img_concat.save_to_file(img_path_list);

	ImageSpec image_spec {}; // image dimension info

	// uint8_t* result = img_concat.save_to_array( (const char**)images, images_len, &image_spec);

	// print_img_spec(&image_spec);

	/*
	for (size_t i = 0; i < image_spec.height; ++i){
	 	for (size_t j = 0; j < image_spec.width; ++j) {
	 		for (size_t k = 0; k < image_spec.num_channels; ++k) {
	 			size_t indice = i * image_spec.width + j * image_spec.num_channels + k;

				std::printf("%d, ", result[indice]);
			}
			std::putchar('\t');
		}
		std::putchar('\n');

	}
	*/
	/*
	for (size_t idx = 0; idx < images_len; ++idx) {
			std::free(images[idx]);
	}
	*/
	// std::free(images);
	// std::free(result);

}
