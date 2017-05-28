
/**
 * \file          module_modeleVoiture.c
 * \author    Miroslav
 * \version   1.0
 * \date       12 Novembre 2009
 * \brief       Définit les modèles de voiture et leur particularités.
 *
 * \details    Cette classe surcharge les accesseurs standards du module_voiture pour
 *                  convenir aux spécificités des différents modèles possibles.
 */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex> 
#include <thread>
#include <semaphore.h> 
#include <chrono>
#include <pthread.h> 
#include <time.h> 
#include <iostream>
#include <fstream>


#include <string>

// taille de l'image
#define LON 600
#define LAR 800   


#define iteration_max 150
//nombre de thread
#define NB_THREAD 1
#define N_max 4
// mutex pour protéger VALEUR
pthread_mutex_t mutex; 

using namespace std;
using namespace cv;
Mat image;;
long double reel=0.285,imaginaire=0.01;
double X = 0;
double Y = 0;

// déclarer la fonction pour la conversion de couleur de HSV vers RGB
void HSVtoRGB( unsigned char  *r, unsigned char  *g, unsigned char  *b, unsigned char  h, unsigned char  s, unsigned char  v );
// déclarer la fonction pour la creation de la fractal
void *fractale(void *arg);

int main(int argc, char * argv[]) 
	{

// crée une matrice image qui comporte LON ligne et LAR collogne
image=cv::Mat(LON, LAR, CV_8UC3);
// Initialiser le mutex !! Important !
//pthread_mutex_init(&mutex, NULL); 
// Initialiser les thread NB_THREAD est le nombre  de thread utilisé
pthread_t thread_fractale[NB_THREAD];
// faire une boucle  
refresh:
//http://www.cplusplus.com/reference/ctime/clock/
  clock_t t;
 
  t = clock();
int plage=(int)((LON)/(NB_THREAD));
int v[2];
v[0] = 0;

v[1] = plage;



    for(int i=0;i< NB_THREAD;i++){

    pthread_create (&thread_fractale[i], NULL, fractale, &v);
v[0]=v[0]+plage+1;
v[1]=v[1]+plage;

    }

// Détruire le mutex
//pthread_mutex_destroy(&mutex); 
t = clock() - t;
 // printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

// je stocke dans la chaîne mon_fichier le nom du fichier à ouvrir 
//https://openclassrooms.com/courses/lecture-et-ecriture-dans-les-fichiers-en-c
 ofstream fichier("text.txt", ios::app);  // on ouvre
if(fichier)

        {
 fichier <<  NB_THREAD<<" "<<((float)t) <<";"<<endl;
fichier.close();
}else{ cerr << "Impossible d'ouvrir le fichier !" << endl;}
//Gestion des entrées

  while(char key = cvWaitKey(66)) {
    switch(key){
      case 'a':
      

// Modification de la constante de la fractale 
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
      
      imaginaire = imaginaire - 0.05;
      goto refresh;
      break;

//Utilisation de Zoom/Dezoom 
      case 'd':
      
      X -= 100;
      Y -= 100;
      goto refresh;
      break;
      case 's':
     
      X += 100;
      Y += 100;
      goto refresh;
      break;

      default:
      break;
    }
    if (key == 'q')
    break;
    imshow("fractale",image ); 
  }
// ferme la fenêtre
  cvDestroyWindow("fractale"); 
  return 0;
}


// fonction pour la créeation de la fractal de julia

void *fractale(void* p)
{
int * a = reinterpret_cast<int *>(p);
while(1){
// attend tant qu'il est vérouillé par un autre thread
	//pthread_mutex_lock(&mutex); 
  std::complex<long double> c (reel,imaginaire);

// Programmation de la fonction de la fractale 
int k = a[0];
int l =  a[1];

  for(int x=k;x<l;x++){
      for(int y=0;y<LAR;y++){

long double X1= ((long double)-1 +((long double)(x) *((long double)2/(long double)((LON)-Y))));
long double Y1= ((long double)-1 +((long double)(y) *((long double)2/(long double)((LAR)-X))));
 std::complex<long double> ZC(Y1,X1); 
 
 int iteration=0;
        long double norm = std::norm(ZC);
        while(iteration<iteration_max && norm<N_max){
          ZC=(ZC*ZC)+c;
          norm = std::norm(ZC);
          iteration++;
        }


        if(iteration==iteration_max && norm<N_max){
          image.at<Vec3b>(x,y)[0]=0; 
          image.at<Vec3b>(x,y)[1]=0; 
          image.at<Vec3b>(x,y)[2]=0;
        }
       else{
          int couleur=(int)((float)iteration/(float)iteration_max*360);
          unsigned char brillance=150; 
          unsigned char saturation=150; 
          unsigned char r,g,b;
// definition de la couleur de l'image
	  HSVtoRGB( & r, & g, & b, couleur, brillance, saturation );
          image.at<Vec3b>(x,y)[0]=r;   
          image.at<Vec3b>(x,y)[1]=g;
          image.at<Vec3b>(x,y)[2]=b;
      
      }
    }

} 
//pthread_mutex_unlock(&mutex);
  }

return NULL;
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
