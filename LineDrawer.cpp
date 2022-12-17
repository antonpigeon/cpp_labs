#include <opencv.hpp>
#include <highgui.hpp>

class LineDrawer{
    /*The purpose of this class is to allow the user to draw a line on the image by setting two points.
    The line is drawn between the first point and the mouse cursor until the second point is placed.
    Then, the two points may be returned */

    private:
    cv::Mat base_image;  // the image to draw the line on
    std::string window_name;  // the window to operate in
    cv::Point p1, p2;
    bool p1_set = false, p2_set = false, dead = false;

    static void emptyCallback(int event, int x, int y, int flags, void* userdata) {}

    void myCallback(int event, int x, int y, int flags){ 
        cv::Mat img_to_show = base_image.clone();
        if(event == cv::EVENT_LBUTTONDOWN){
            if(p1_set == false){
                p1 = cv::Point(x, y);
                p1_set = true;
            }
            else if(p2_set == false){
                p2 = cv::Point(x, y);
                p2_set = true;
            }
        }

        else if(event == cv::EVENT_MOUSEMOVE){
            if(p1_set && !p2_set){
                cv::line(img_to_show, p1, cv::Point(x, y), 0, 3);
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
        //cv::setMouseCallback(window_name, emptyCallback, NULL);
        dead = true;
    }

    void changeBaseImage(cv::Mat src){
        base_image = src.clone();
        cv::imshow(window_name, base_image);
    }
    void restart(){
        p1_set = false;
        p2_set = false;
    }
};