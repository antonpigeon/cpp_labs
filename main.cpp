#include <opencv.hpp>
#include <highgui.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <string>

#include "screenshot.cpp"
#include "LineDrawer.cpp"
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
    cv::Mat screen;
    std::string window_name = "hacks.exe";

    int screen_width = GetSystemMetrics(SM_CXVIRTUALSCREEN);  // These *should* be screen dimensions
    int screen_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    cv::namedWindow(window_name, cv::WINDOW_NORMAL);
    cv::moveWindow(window_name, 0, 0);
    cv::resizeWindow(window_name, screen_width/4, screen_height/4);

    double scale;  // meters per pixel


    /////////////////////////////////initial screenshot//////////////////////////////////
    while(true){
        int pressed_key = cv::pollKey();
        if(pressed_key == 0x08){  // 0x08 is the code of Backspace
            HWND hwnd = GetDesktopWindow();
            screen = captureScreenMat(hwnd);
            break;
        }
        if(pressed_key == 0x1B){  // escape
            cv::destroyAllWindows();
            return 0;
        }
        if(cv::getWindowProperty(window_name, cv::WND_PROP_VISIBLE) == 0){  // if the window was closed (by pressing th red X)
            return 0;
        }
        Sleep(100);
    }

    double hscale = 1.0/4.0, vscale = 1.0/3.0;
    double hwidth = hscale*screen_width, vheight = vscale*screen_height;
    double hstart = (1-hscale)*screen_width, vstart = (1-vscale)*screen_height;
    //cv::Mat src = screen.clone();
    //cv::Mat src = screen(cv::Rect(hstart*screen_width, vstart*screen_height, hscale*screen_width, vscale*screen_height));
    cv::Mat src = screen(cv::Rect(hstart, vstart, hwidth, vheight));
    cv::resizeWindow(window_name, screen_width, screen_height);
    LineDrawer drawer = LineDrawer(window_name, src);

        /////////////////////////////////initial line drawing l==300//////////////////////////////////
    while(true){
        int pressed_key = cv::pollKey();
        if(pressed_key == 0x1B){  // escape
            cv::destroyAllWindows();
            return 0;
        }
        if(drawer.finished()){
            Point p1 = drawer.getPoints()[0];
            Point p2 = drawer.getPoints()[1];
            drawer.restart();
            double distance = std::sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
            double xdiff = p2.x - p1.x, ydiff = p1.y - p2.y;
            double angle = std::acos(ydiff/std::sqrt(xdiff*xdiff + ydiff*ydiff));
            angle = angle*180/3.1415;
            if(xdiff < 0) {angle = 360.0 - angle;}
            distance = std::round(distance);  // rounding before 2014 be like
            scale = 300/distance;
            angle = std::ceil(angle*10.0)/10.0;
            std::cout << angle <<"\n" << distance << "\n";
            std::string angle_info = "H: " + chopOffTailingChars(std::to_string(angle));
            std::string distance_info = "D: " + chopOffTailingChars(std::to_string(distance));
            cv::Mat res_img = src.clone();
            cv::putText(res_img, angle_info, p2, cv::FONT_HERSHEY_PLAIN, 1, (255, 255, 255));
            cv::putText(res_img, distance_info, Point(p2.x, p2.y + 20), cv::FONT_HERSHEY_PLAIN, 1, (255, 255, 255));
            cv::line(res_img, p1, p2, cv::Scalar(0, 0, 255), 3);
            cv::imshow(window_name, res_img);
            break;
        }
        if(cv::getWindowProperty(window_name, cv::WND_PROP_VISIBLE) == 0){
            return 0;
        }
        Sleep(50);
    }

    /////////////////////////////////main lines drawing loops//////////////////////////////////
    while(true){
        int pressed_key = cv::pollKey();
        if(pressed_key == 0x1B){  // escape
            cv::destroyAllWindows();
            return 0;
        }
        if(drawer.finished()){
            Point p1 = drawer.getPoints()[0];
            Point p2 = drawer.getPoints()[1];
            drawer.restart();
            double distance = std::sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
            distance *= scale;
            double xdiff = p2.x - p1.x, ydiff = p1.y - p2.y;
            double angle = std::acos(ydiff/std::sqrt(xdiff*xdiff + ydiff*ydiff));
            angle = angle*180/3.1415;
            if(xdiff < 0) {angle = 360.0 - angle;}
            distance = std::round(distance);  // rounding before 2014 be like
            angle = std::ceil(angle*10.0)/10.0;
            std::cout << angle <<"\n" << distance << "\n";
            std::string angle_info = "H: " + chopOffTailingChars(std::to_string(angle));
            std::string distance_info = "D: " + chopOffTailingChars(std::to_string(distance));
            cv::Mat res_img = src.clone();
            cv::line(res_img, p1, p2, cv::Scalar(0, 0, 255), 3);
            cv::putText(res_img, angle_info, p2, cv::FONT_HERSHEY_PLAIN, 1, (255, 255, 255));
            cv::putText(res_img, distance_info, Point(p2.x, p2.y + 20), cv::FONT_HERSHEY_PLAIN, 1, (255, 255, 255));
            cv::imshow(window_name, res_img);
        }
        if(pressed_key == 0x08){  // backspace
            HWND hwnd = GetDesktopWindow();
            screen = captureScreenMat(hwnd);
            cv::resizeWindow(window_name, screen_width, screen_height);
            src = screen(cv::Rect(hstart, vstart, hwidth, vheight));
            drawer.changeBaseImage(src);
            cv::moveWindow(window_name, 0, 0);
        }
        if(pressed_key == 0x0D){  // ENTER
            cv::moveWindow(window_name, 0, 0);
            cv::resizeWindow(window_name, screen_width/4, screen_height/4);
        }
        if(cv::getWindowProperty(window_name, cv::WND_PROP_VISIBLE) == 0){
            return 0;
        }
        Sleep(50);
    }
    return 0;
}
