#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <format>
#include <cstdint>
#include "img_concat.h"

bool ImageConcat::save_to_file(const std::vector<std::string>& img_path_list) {
	/* 
	* Concat images either vertical or horzontal
	* then save to file
	* img_path_list: &Vec<String> --> collection of input images
	*/
	
	std::string full_save_path = std::format("{}.png", this->out_name);  //  construct string img path
	cv::Mat result = concat_image(img_path_list, this->vertical_flag);

	return cv::imwrite(full_save_path, result, {cv::IMWRITE_PNG_COMPRESSION, 0});
}

uint8_t* ImageConcat::save_to_array(const char** images, size_t length, ImageSpec* image_spec) {
	/*
	* Concat image & save to 2d array
	* the output array in C order
	* ImageSpec struct save the info for image width, height and channel
	*/
	uint8_t* result ;
	// std::vector<std::string> images_list {};
	// concat image
	cv::Mat output_image = concat_image(images, length, this->vertical_flag);
	// cv::imshow("IMG", output);
	// int k = cv::waitKey(0);
	// get width, height and channels
	cv::Size size = output_image.size();
	int img_width = size.width;
    int img_height = size.height;
	int img_channels = output_image.channels();
	// save image spec
	(*image_spec).width = img_width;
	(*image_spec).height = img_height;
	(*image_spec).num_channels = img_channels;
	// init save array
	size_t total_elem = output_image.total() * output_image.channels();
	result = (uint8_t*)std::malloc(sizeof(uint8_t) * total_elem);

	if (result == nullptr) {
		// mallac failed
		return NULL;
	}

	if (output_image.isContinuous()) {
        std::memcpy(result, output_image.datastart, total_elem * sizeof(uint8_t));
    } else {
        // If non-continuous, clone first or copy row by row
        cv::Mat continuous_image = output_image.clone();
        std::memcpy(result, continuous_image.datastart, total_elem * sizeof(uint8_t));
    }

	return result;

}


ImageConcat::ImageConcat() :
	vertical_flag(true), out_name("output")
{
	// default vertical and out image name "output"
}

ImageConcat::ImageConcat(const char* out_name, bool v_flag) :
	out_name(out_name), vertical_flag(v_flag)
{

}

ImageConcat::~ImageConcat() {
	
}

cv::Mat concat_image( const std::vector<std::string>& img_path_list, bool v_flag) {
	/* Concat sequence of images either vertical or horzontal
	* img_path_list: &Vec<String> --> seq of input images
	* v_flag: bool --> whether concat vertical or horizontal
	*/
	cv::Mat output;  // resule image mat
	std::vector<cv::Mat> img_seq;  // lisy of 2d array
	// convert to seg of cv::Mat
	for (int i = 0; i < img_path_list.size(); i++) {
		img_seq.push_back(cv::imread( img_path_list[i], cv::IMREAD_COLOR));
	}

	if ( v_flag ) {
	// concat vertical
		cv::vconcat(img_seq, output);
	}
	else {
	// horizontally
		cv::hconcat(img_seq, output);
	}

		// std::cout << "Total pixels (after concat): " << output.total() << '\n';
	return output;
}


cv::Mat concat_image( const char** img_path_list,
	 size_t images_length, 
	 bool v_flag) {
	/* Concat sequence of images either vertical or horzontal
	* img_path_list: const char** --> collection of input images
	* images_length: size_t --> length of images
	* v_flag: bool --> whether concat vertical or horizontal
	*/
	cv::Mat output;  // resule image mat
	std::vector<cv::Mat> img_seq;  // lisy of 2d array
	// convert to seg of cv::Mat
	for (int i = 0; i < images_length; i++) {
		img_seq.push_back(cv::imread( img_path_list[i], cv::IMREAD_COLOR));
	}

	if ( v_flag ) {
	// concat vertical
		cv::vconcat(img_seq, output);
	}
	else {
	// horizontally
		cv::hconcat(img_seq, output);
	}

	// std::cout << "Total pixels (after concat): " << output.total() << '\n';
	return output;
}

void print_img_spec(const struct ImageSpec* image_spec) {
	// debug
	std::printf("Image:\nwidth: %d\theight: %d\tnum of channels: %d\n",
		image_spec->width,
		image_spec->height,
		image_spec->num_channels
	);
}