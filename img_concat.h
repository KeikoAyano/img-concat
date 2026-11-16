#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <opencv2/opencv.hpp>

struct ImageSpec {
    /*
    image dimension info
    width, height, channels
    */
    uint32_t width;
    uint32_t height;
    uint32_t num_channels;
};

// the image concat clas
// handle the image concat function
class ImageConcat {
    private:
    bool vertical_flag; // whether concat vetical or not, true for vertical and false for horizontal
    std::string out_name;  // output file name
    public:
    bool save_to_file(const std::vector<std::string>&);
    uint8_t* save_to_array(const char** images, size_t length, ImageSpec*);
    ImageConcat();
    ImageConcat(const char* out_name, bool v_flag);
    ~ImageConcat();
    void display() {
        std::cout << "Output file name: " << this->out_name << "\t"
                << "If Vertical: " << this->vertical_flag << '\n';
    }
};

cv::Mat concat_image( const std::vector<std::string>&, bool);
cv::Mat concat_image( const char**, size_t, bool );

void print_img_spec(const struct ImageSpec*);