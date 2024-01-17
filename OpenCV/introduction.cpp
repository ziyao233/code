#include<cassert>
#include<iostream>
#include<string>

#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>

int
main(int argc, const char *argv[])
{
	assert(argc == 2);

	cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);

	if (img.empty()) {
		std::cerr << "Cannot read the image: " << argv[1] << std::endl;
		return -1;
	}

	cv::imshow("Display window", img);
	cv::waitKey(0);

	return 0;
}
