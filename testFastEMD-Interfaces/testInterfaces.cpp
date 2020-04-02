//
//  testVersion.cpp
//  FastEMD
//
//  Created by Till Hainbach on 06.03.20.
//  Copyright © 2020 Till Hainbach. All rights reserved.
//

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
//#include "utils/tqdm/tqdm.h"
#include <vector>
#include <unistd.h>
#include <list>
#include "original/emd_hat.hpp"

int main(int argc, char* argv[])
{
    // for each image in folder:
        // load image
        // resize image to dimension N x N
        // calculate cost matrix
    
    const cv::String keys =
        "{help h usage ?    |       | print this message                            }"
        "{@folderPath       |<none> | the folder containing the test images         }"
        "{@outputPath       |<none> | outputPath for results files                  }"
        "{@append           |1      | append results to file or overwrite           }"
    ;
    
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("OpenCV-Interface for the Generalized Compass Operator v1.0.0");
    
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }
    
    cv::String inputPath = parser.get<cv::String>("@folderPath");
    cv::String outputPath = parser.get<cv::String>("@outputPath");
    bool append = parser.get<bool>("@append");
    
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }
    
    int N = 6;

    std::list<cv::String> files;
    for(const auto & entry : std::filesystem::directory_iterator(inputPath))
    {
        cv::String file(entry.path());
        if (hasEnding(file, ".jpg"))
        {
            files.push_back(file);
        }
    }
    files.sort();
    double totalImageFiles = files.size();
    std::cout << "starting to process " << totalImageFiles << " images..." << std::endl;
    
    cv::Mat costMat; //matrix containing cost
    std::ofstream output;
    if (append)
    {
        output.open(outputPath + "/testFastEMDVersions.txt", std::ios_base::app);
    }
    else
    {
        output.open(outputPath + "/testFastEMDVersions.txt");
    }
    // output is a table with header:
    // P, Q, N, EMDdistance, time, method
    
    cv::String firstFile(files.front());
    files.pop_front();
    cv::Mat image; //definde varible images as cv::Mat
    image = cv::imread(firstFile, cv::IMREAD_GRAYSCALE);// Read the file
    for (const auto & file : files)
    {
        cv::Mat nextImage;
        nextImage = cv::imread(file, cv::IMREAD_GRAYSCALE );
        cv::Mat smallImage, smallNextImage;
        if (!nextImage.empty())
        {
            // resize image:
            cv::resize(image, smallImage, cv::Size(N, N));
            cv::resize(nextImage, smallNextImage, cv::Size(N, N));
            
            int THRESHOLD = 3000;
            // calculate cost matrix:
            cv::Mat costMat;
            int maxC = calculateCostMatrix(smallImage, smallNextImage, costMat, THRESHOLD);
            
            // calculate EMD-distance:
            int dist = emd_hat_gd_metric<int>()(smallImage, smallNextImage,
                                                costMat, THRESHOLD);
            
            // output data to txt-file.
            cv::String firstFilename (firstFile);
            firstFilename.erase(0, firstFilename.rfind('/') + 1).erase(firstFilename.rfind('.'));
            cv::String filename (file);
            filename.erase(0, filename.rfind('/') + 1).erase(filename.rfind('.'));
            output << firstFilename << ", " << filename << ", "
                   << N << ", " << dist << std::endl;
            
        }
        else
        {
               std::cout << "error" << std::endl;
        }
        smallImage = smallNextImage;
        firstFile = file;
    }
    output.close();

    return 0;
}


