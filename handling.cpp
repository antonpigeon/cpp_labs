#include <opencv.hpp>
#include <highgui.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <string>
#include "main.cpp"

using cv::Point;

// WARNING
// TO ALL FUTURE USERS OF OPENCV
// The matrix assignment operator, cv::Mat::operator=, only provides a shallow copy
// Thus, it is possible to modify the right hand argument by modifying the left later in the code, even if rha is const.
// For a deep copy, use A = B.copy();
// Also, colors are very strange
// To generate a BGR color, one should explicitly call the constructor cv::Scalar()
// Otherwise it gives God knows what
// e.g. cv::Scalar(0, 0, 255) is red (as expected), but the tuple (0, 0, 255) is cast to blue,
// and so are (0, 0, 0, 255) and (0, 0, 255, 0)

class LineDrawer{
    /*The purpose of this class is to allow the user to draw a line on the image by setting two points.
    The line is drawn between the first point and the mouse cursor until the second point is placed.
    Then, the two points may be returned */

    private:
    cv::Mat base_image;  // the image to draw the line on
    std::string window_name;  // the window to operate in
    cv::Point p1, p2;
    bool p1_set = false, p2_set = false, dead = false;

    static void emptyCallback(int event, int x, int y, int flags, void* userdata){}

    void myCallback(int event, int x, int y, int flags){ 
        cv::Mat img_to_show = base_image.clone();
        if(event == cv::EVENT_LBUTTONDOWN){
            if(p1_set == false){
                p1 = Point(x, y);
                p1_set = true;
            }
            else if(p2_set == false){
                p2 = Point(x, y);
                p2_set = true;
            }
        }

        else if(event == cv::EVENT_MOUSEMOVE){
            if(p1_set && !p2_set){
                cv::line(img_to_show, p1, Point(x, y), 0, 3);
            }
            if(p2_set){
                cv::line(img_to_show, p1, p2, cv::Scalar(0, 0, 255), 3);
            }
        }
        if(p1_set){
            try{
                cv::imshow(window_name, img_to_show);
            }
            catch(...){
                static int error_counter=0;
                std::cout << "Could not display image!   " << error_counter++ << std::endl;
                // this is not supposed to happen at all
            }
        }
    }
    
    static void staticMyCallback(int event, int x, int y, int flags, void* userdata){
        // wrapper function to make cv::setMouseCallback work
        LineDrawer* drawer = static_cast<LineDrawer*> (userdata);
        drawer->myCallback(event, x, y, flags);
    }

    public:
    LineDrawer(std::string win, cv::Mat const &src): window_name(win), base_image(src.clone()) {  // main constructor
        cv::setMouseCallback(window_name, staticMyCallback, this);  
        cv::imshow(window_name, base_image);  // draw the image initially so there is no empty window
    }

    std::vector<cv::Point> getPoints(){  // returns the ends of the drawn line
        std::vector<cv::Point> res(1, p1);
        res.push_back(p2);
        return res;
    }

    bool finished(){return (p1_set && p2_set);}

    void die(){
        cv::setMouseCallback(window_name, emptyCallback, NULL);
        dead = true;
    }
};

std::string chopOffTailingChars(std::string s, char ch='0'){
    int i = s.length() - 1;
    if(s[i] != ch) return s;
    for(i; i >= 1; i--){
        if(s[i - 1] !=ch){
            return s.substr(0, i);
        }
    }
    return "";
}
int main(){
    //std::string screenshot_path = "C:/opencv_test/screenshot.png";
    cv::Mat src;
    std::string window_name = "word.exe";
    cv::namedWindow(window_name);
    while(true){
        if(cv::pollKey() == 0x08){  // 0x08 is the code of Backspace
            HWND hwnd = GetDesktopWindow();
            src = captureScreenMat(hwnd);
            break;
        }
        Sleep(100);
    }
    LineDrawer drawer = LineDrawer(window_name, src);
    while(true){
        if(cv::pollKey() == 0x08){
            break;
        }
        if(drawer.finished()){
            Point p1 = drawer.getPoints()[0];
            Point p2 = drawer.getPoints()[1];
            drawer.die();
            double distance = std::sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
            double xdiff = p2.x - p1.x, ydiff = p1.y - p2.y;
            double angle = std::acos(ydiff/std::sqrt(xdiff*xdiff + ydiff*ydiff));
            angle = angle*180/3.1415;
            if(xdiff < 0) {angle = 360.0 - angle; std::cout << "changed\n";}
            distance = std::round(distance);  // rounding before 2014 be like
            angle = std::ceil(angle*10.0)/10.0;
            std::cout << angle <<"\n" << distance << "\n";
            std::string angle_info = "Heading: " + chopOffTailingChars(std::to_string(angle));
            std::string distance_info = "Distance: " + chopOffTailingChars(std::to_string(distance));
            cv::putText(src, angle_info, p2, cv::FONT_HERSHEY_PLAIN, 1, (255, 255, 255));
            cv::putText(src, distance_info, Point(p2.x, p2.y + 20), cv::FONT_HERSHEY_PLAIN, 1, (255, 255, 255));
            cv::line(src, p1, p2, cv::Scalar(0, 0, 255), 3);
            cv::imshow(window_name, src);
            break;
        }
        Sleep(50);
    }
    cv::waitKey(0);
    return 0;
}
