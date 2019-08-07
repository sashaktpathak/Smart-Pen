#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
#include <chrono>
 
using namespace std;
using namespace std::chrono;
using namespace cv;
 
int main(int argc, char* argv[])
{
    auto start = high_resolution_clock::now();
    string outText;
    string imPath = argv[1];
 
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
      
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
 
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
 
    Mat im = cv::imread(imPath, IMREAD_COLOR);
   
    ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
 
    outText = string(ocr->GetUTF8Text());
 
    cout << outText <<endl;
    auto stop = high_resolution_clock::now();
    auto duration =duration_cast<microseconds>(stop-start);
    cout << "Time taken by function: " << duration.count() << "microseconds" << endl;
    return EXIT_SUCCESS;
}
