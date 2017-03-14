/* http://docs.opencv.org/
 je commance a modifier 
 SOUS MAC :
 port install opencv
 
 g++ -Wall opencv_exempleCPP.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -I/opt/local/include -L/opt/local/lib -std=c++11
 
 SOUS LINUX :
 sudo apt-get install libopencv-core-dev
 sudo apt-get install libopencv-photo-dev
 sudo apt-get install libopencv-contrib-dev
 sudo apt-get install libhighgui-dev
 
 g++ -Wall opencv_exempleCPP.cpp -lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11
 */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex> 
#define LON 600
#define LAR 800   // taille de l'image
#define N_max 4
 #define iteration_max 150
using namespace std;
using namespace cv;
Mat image;;
std::complex<long double> c (0.285,0.01 );  

void fractale()
{
  for(int x=0;x<LON;x++){
      for(int y=0;y<LAR;y++){
// conversion de nore image de -1=>1
long double X= ((long double)-1 +((long double)x *((long double)2/(long double)LON)));
long double Y= ((long double)-1 +((long double)y *((long double)2/(long double)LAR)));
 std::complex<long double> ZC(Y,X); // nouvelle representation de pixel
      
 int iteration=0;
        long double norm = std::norm(ZC);
        while(iteration<iteration_max && norm<N_max){
          ZC=(ZC*ZC)+c;
          norm = std::norm(ZC);
          iteration++;
        }


        if(iteration==iteration_max && norm<N_max){// definition de la couleur de l'image
          image.at<Vec3b>(x,y)[0]=0; 
          image.at<Vec3b>(x,y)[1]=0; 
          image.at<Vec3b>(x,y)[2]=0;
        }
       else{
          int couleur=(int)((float)iteration/(float)iteration_max*255);
          image.at<Vec3b>(x,y)[0]=couleur;   // definitions de la couleur de la fractale
          image.at<Vec3b>(x,y)[1]=couleur;
          image.at<Vec3b>(x,y)[2]=couleur;
      
      }
    }
  }
}

int main(int argc, char * argv[]) 
	{
  image=cv::Mat(LON, LAR, CV_8UC3);

    
    fractale();
     while( true )
     {
     	 
	     imshow("fractale",image ); 
     	 if(cvWaitKey(5) > 0){
        break;
       }
}
  return 0;
}
