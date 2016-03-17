/**
* This file is part of ORB-SLAM2.
*
* Copyright (C) 2014-2016 Raúl Mur-Artal <raulmur at unizar dot es> (University of Zaragoza)
* For more information see <https://github.com/raulmur/ORB_SLAM2>
*
* ORB-SLAM2 is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM2 is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ORB-SLAM2. If not, see <http://www.gnu.org/licenses/>.
*/


#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>
#include <iomanip>
#include <time.h>
#include <sys/time.h>

#include<opencv2/opencv.hpp>

#include"System.h"
#include "MapPoint.h"

using namespace std;

int main(int argc, char **argv)
{
    
    
    const string vocabularyPath = "../../../Vocabulary/ORBvoc.bin";
    const string settingPath = "../../../Examples/Monocular/KITTI.yaml";

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(vocabularyPath,settingPath,ORB_SLAM2::System::MONOCULAR,false);

    cv::VideoCapture capture(1);
    
    // Main loop
    cv::Mat im;
    cv::Mat firstPose;
    while(true)
    {
        // Read image from file
        capture >> im;
        

        if(im.empty())
        {
            cerr << endl << "Failed to capture!"<< endl;
            return 1;
        }

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t1 = std::chrono::monotonic_clock::now();
#endif

        // Pass the image to the SLAM system

        cv::Mat pose = SLAM.TrackMonocular(im,0);
        
        if(!pose.empty()){
            cv::Mat rVec;
            cv::Rodrigues(pose.colRange(0, 3).rowRange(0, 3), rVec);
            cv::Mat tVec = pose.col(3).rowRange(0, 3);
            
            const vector<ORB_SLAM2::MapPoint*> vpMPs = SLAM.mpTracker->mpMap->GetAllMapPoints();
            if (vpMPs.size() > 0) {
                std::vector<cv::Point3f> allmappoints;
                for (size_t i = 0; i < vpMPs.size(); i++) {
                    if (vpMPs[i]) {
                        cv::Point3f pos = cv::Point3f(vpMPs[i]->GetWorldPos());
                        allmappoints.push_back(pos);
                    }
                }
                std::vector<cv::Point2f> projectedPoints;
                cv::projectPoints(allmappoints, rVec, tVec, SLAM.mpTracker->mK, SLAM.mpTracker->mDistCoef, projectedPoints);
                for (size_t j = 0; j < projectedPoints.size(); ++j) {
                    cv::Point2f r1 = projectedPoints[j];
                    cv::circle(im, cv::Point(r1.x, r1.y), 2, cv::Scalar(0, 255, 0), 1, 8);
                }
            }
        }
        
        imshow("ORB_SLAM2", im);
        
       
        int k = cv::waitKey(20);
        if (k > 0)
            break;

#ifdef COMPILEDWITHC11
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
#else
        std::chrono::monotonic_clock::time_point t2 = std::chrono::monotonic_clock::now();
#endif

        double ttrack= std::chrono::duration_cast<std::chrono::duration<double> >(t2 - t1).count();

    }

    // Stop all threads
    SLAM.Shutdown();

    return 0;
}

