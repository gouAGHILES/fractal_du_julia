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
long double reel=0.285,imaginaire=0.01;
double X = 0;
double Y = 0;


void HSVtoRGB( unsigned char  *r, unsigned char  *g, unsigned char  *b, unsigned char  h, unsigned char  s, unsigned char  v );

void fractale()
{
  std::complex<long double> c (reel,imaginaire);

  for(int x=0;x<LON;x++){
      for(int y=0;y<LAR;y++){
// conversion de nore image de -1=>1
long double X1= ((long double)-1 +((long double)x *((long double)2/(long double)((LON)-Y))));
long double Y1= ((long double)-1 +((long double)y *((long double)2/(long double)((LAR)-X))));
 std::complex<long double> ZC(Y1,X1); // nouvelle representation de pixel
 
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
          int couleur=(int)((float)iteration/(float)iteration_max*360);
          unsigned char brillance=150; //(unsigned char)((float)iteration/(float)ITERATIONMAX*100);
          unsigned char saturation=150; //(unsigned char)((float)iteration/(float)ITERATIONMAX*100);
          unsigned char r,g,b;
	  HSVtoRGB( & r, & g, & b, couleur, brillance, saturation );
          image.at<Vec3b>(x,y)[0]=r;   // definitions de la couleur de la fractale
          image.at<Vec3b>(x,y)[1]=g;
          image.at<Vec3b>(x,y)[2]=b;
      
      }
    }
  }
}

int main(int argc, char * argv[]) 
	{


  image=cv::Mat(LON, LAR, CV_8UC3);

refresh:
    
    fractale();
     //Gestion des entrées
  while(char key = cvWaitKey(66)) {
    switch(key){
      case 'a':
      

      /* Modification de la fractale à la volée */
      reel = reel + 0.1;
      goto refresh;
      break;
      case 'z':
      
      reel = reel - 0.1;
      goto refresh;
      break;
      case 'o':
      
      imaginaire = imaginaire + 0.1;
      goto refresh;
      break;
      case 'p':
      
      imaginaire = imaginaire - 0.1;
      goto refresh;
      break;

      /* Zoom/Dezomm */
      case 'd':
      
      X -= 15;
      Y -= 15;
      goto refresh;
      break;
      case 's':
     
      X += 15;
      Y += 15;
      goto refresh;
      break;

      default:
      break;
    }
    if (key == 'q')
    break;
    imshow("fractale",image ); 
  }
  cvDestroyWindow("fractale"); // ferme la fenêtre
  return 0;
}
// fonction pour  convertir le modèle de couleur HSV en modèle de couleur RVB.
void HSVtoRGB( unsigned char  *r, unsigned char  *g, unsigned char  *b, unsigned char  h, unsigned char  s, unsigned char  v )
{
	
	unsigned char i,f, p, q, t;

	if (s == 0)
	{
		*r = 0;
		*g = 0;
		*b = 0;
	}

	else
	{
		

		 
    i = h / 43;
    
    f = (h - (i * 43)) * 6;
    
    
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * f) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - f)) >> 8))) >> 8;
        

		switch (i)
		{
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;

		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;

		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;

		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;

		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;

		default:
			*r = v;
			*g = p;
			*b = q;
			break;
		}

	}

	return;
}



unsigned char randomVal(){
return (unsigned char)(rand()%360);
}
