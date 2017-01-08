#pragma once

#ifndef EARTH_API_H
#define EARTH_API_H


#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "MLBasic/util/Util.h"
#include "MLBasic/lib/image/feature/bow/Vocabulary.h"
#include "MLBasic/lib/image/feature/bow/ConstructHist.h"
#include "MLBasic/lib/image/feature/bow/DenseSIFT.h"
#include "MLBasic/lib/recognition/svm/SVM.h"
#include "libsvm.h"
#include "IUnityGraphics.h"


using namespace std;


Mat constructImageMat(unsigned char image[], const int &origin_height, const int &origin_width, const int &height, const int &width) {
    Mat img = Mat(1, origin_height * origin_width, CV_8U, image);
    Mat new_img = img.reshape(0, origin_height);
    Mat smooth_img = ImageUtil::ImageSmooth(new_img, 3, 3);
    Mat resized_mat = ImageUtil::ImageReSize(smooth_img, height, width, false);
    return resized_mat;
}

Mat getHist(const Mat &img, const string &dict_path, const int &minHessian, const int &width, const int &height) {
    Mat dictionary = Util::readMat(dict_path);
    DenseSIFT sift = DenseSIFT::build(minHessian, width, height, false);
    ConstructHist hist = ConstructHist::build(sift, dictionary);
    hist.computeImageDescriptor(img);
    return hist.getHistDescriptor();
}

int classify(const string &model_name, const Mat &x, double &prob) {
    int res = SVMModel::testSVM(x, model_name);
    return res;
}

bool isTellurion(const string &model_name, const Mat &x) {
    int res = SVMModel::testSVM(x, model_name);
    if (res == 0) return false;
    else return true;
}

extern "C" int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API predict(unsigned char image[], const int origin_height, const int origin_width,
            const int minHessian, const int height, const int width,
            const string multi_class_model_name, const string one_class_model_name, const string dict_path, const double threashold, double prob) {
    Mat img = constructImageMat(image, origin_height, origin_width, height, width);
    Mat feature = getHist(img, dict_path, minHessian, width, height);
    if(feature.rows == 0)
        return -1;
    int res = -1;
    prob = 0;
    if (isTellurion(one_class_model_name, feature)) {
        res = classify(multi_class_model_name, feature, prob);
        //if (prob < threashold) res = -1;
    }
    return res;
}


#endif // !EARTH_API_H




