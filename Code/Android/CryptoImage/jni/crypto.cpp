#include <errno.h>
#include <jni.h>
#include <sys/time.h>
#include <android/log.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include <stddef.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;


#define  LOG_TAG    "OCV:libcrypto_activity"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int flag = 0;

Mat img;


typedef struct{
    int x,y, fn;
}locate;


vector<vector<locate> > teste;


vector<int> closerTo(vector<vector<locate> > characterList, unsigned char character){

    vector<int> closeChars;
    int ch = character;
    int closerTemp;
    int i = 1;
    vector<locate> points;
    int signal = 0;
    int dist = 0;

    while( (ch - i) > 0 || (ch + i)<256){
        closerTemp = ch + i;
        if(closerTemp < 256){
            points = characterList[closerTemp];

            if(!points.empty() && points[0].fn!=1 ){
    //        cout << "positivo " << i<< " closerTemp "<< closerTemp << endl;
               signal = '+';
               dist = i;
               break;
            }
        }


        closerTemp = ch - i;
        if(closerTemp > 0){
            points = characterList[closerTemp];
            if(!points.empty() && points[0].fn!=1){
  //             cout << "negativo" << i << " closerTemp "<< closerTemp << endl;
               signal = '-';
               dist = i;
               break;
            }
        }
        i++;

    }

//    cout << "signal "<< signal << " dist "<< dist << endl;

    closeChars.push_back(signal);
    closeChars.push_back(dist);


return closeChars;
}


vector<vector<locate> > listOfCharacters(Mat img){


    if(!img.data){
    	LOGE("ERROR LOAD IMAGE!");
    }


    int cols = img.cols;
	int rows = img.rows;

	if(cols>rows)
	    flag = cols;
	else
	    flag = rows;

    flag++;
	vector<vector<locate> >  points(256);

	LOGD("listOfCharacters 2");

	for(int row = 1; row<rows;row++){
		for(int col = 1; col<cols;col++){
			LOGD("vai");
            int id = img.at<uchar>(Point(col,row));
            locate locatePoint = {col, row};
            points[id].push_back(locatePoint);
        }
	}

	int i = 0;

	while(i<points.size()){

	    if(points[i].empty()){
          // cout << i << endl;
	        unsigned char character = i;
            vector<int> charClose = closerTo(points,character);
            locate close;
	        close.fn = 1;
            close.x = charClose[0];
            close.y = charClose[1];
	        points[i].push_back(close);
	    }
	    i++;
	}

	return points;
}

vector<int> encryptCharacter(vector<vector<locate> > characterList, unsigned char character){

    int charInt = character;
    locate point;
    vector<int>  closeChars;
    vector<int> charEnc;

    vector<locate> points = characterList[charInt];

    if(points[0].fn == 1){

        point = points[0];

        charEnc.push_back(1);
        charEnc.push_back(point.x);
        charEnc.push_back(point.y);
        charEnc.push_back(flag);
        charEnc.push_back(0);

        if(point.x==45){
            charInt = charInt - point.y;
        }else{
            charInt = charInt + point.y;
        }

        points = characterList[charInt];

//        cout << "fn == 1" << " charInt " << charInt << " points.size " << points.size() << endl;
  //      cout << points[0].x << " " << points[0].y << endl;

    }
    point = points[rand()%points.size()];
    charEnc.push_back(point.x);
    charEnc.push_back(point.y);

    return charEnc;

}

vector<int> encryptMessage(vector<vector<locate> > characterList, string message){

    vector<int> cryptMessage;
    vector<int> cryptChar;
    unsigned char ch;
    for(int i = 0; i < message.length(); i++){
        ch = message[i];
        int charInt = ch;
        cryptChar = encryptCharacter(characterList, ch);

    if (cryptChar.size() == 2 && cryptMessage.empty())
            cryptMessage.push_back(0);

    if (cryptChar.size() > 2 && !cryptMessage.empty())
            cryptMessage.push_back(flag);

        for(int j = 0; j<cryptChar.size();j++){
            cryptMessage.push_back(cryptChar[j]);
        }
    }

    return cryptMessage;
}



string dencryptMessage(vector<int> cryptMessage){

    string message = "";
    int i = 0;
    bool hasOp = false;
    int corr = 0;
    while(i<=cryptMessage.size()){

        if(cryptMessage[i]==0){
            i++;

            while(cryptMessage[i]!= flag){
                int col = cryptMessage[i];
                int row = cryptMessage[i+1];


                Scalar color = img.at<uchar>(Point(col,row));
                int id = color.val[0];
                char ch = id;

                if(hasOp){
                    ch = ch + corr;
                    hasOp = false;
                }
                message+=ch;
                i+=2;

                if(i >= cryptMessage.size())
                    break;
            }
        } else if (cryptMessage[i]==1){
            i++;
            hasOp = true;
            if(cryptMessage[i] == 45)
                corr = cryptMessage[i+1]*-1;
            else
                corr = cryptMessage[i+1];

            i+=2;
        }
        i++;

    }

    return message;
}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL Java_com_example_cryptoimage_MainActivity_encryptoText(JNIEnv*, jobject, jlong addrGray);

JNIEXPORT jint JNICALL Java_com_example_cryptoimage_MainActivity_encryptoText(JNIEnv*, jobject, jlong addrGray)
{

    srand ( time(NULL) );
    vector<char const *> images;
/*    images.push_back("./Images/aerial.pgm");
    images.push_back("./Images/boats.pgm");
    images.push_back("./Images/bridge.pgm");
    images.push_back("./Images/D108.pgm");
    images.push_back("./Images/f16.pgm");
    images.push_back("./Images/girl.pgm");
    images.push_back("./Images/lena.jpg");
    images.push_back("./Images/peppers.pgm");*/
//    images.push_back("/storage/emulated/0/Test/Images/pp1209.pgm");
//    images.push_back("/sdcard/aerial.pgm");
    ifstream infile;
//    infile.open("/sdcard/teste.txt");


   if(!infile.good()){

	   LOGE("arquivo nao existe");

   }

 //  infile.open("./Files/teste.txt");
    stringstream buffer;
    buffer << infile.rdbuf();
    string a = buffer.str();
//    LOGD("size message :: " + a.size());
//    cout << "size message :: " << a.size() << endl;

    int i = 0;
    //encrypt
    //    clock_t begin = clock();

    //  a = "â â â â â â â â â é é é é é é é é é é é é é ô ô ô ô ô ô ô ô ô ô  ç ç ç ç çççççççç ";
    clock_t begin = clock();
    clock_t end = clock();
    while(i<images.size()){
//    	LOGD("Image :: " +images[i]);
        cout << "Image :: " << images[i] << endl;
//        char const * teste = 'Image :: ' + images[i];
        LOGD(images[i]);

        begin = clock();
	    vector<vector<locate > >  characterList = listOfCharacters(images[i]);
    //    cout<< "time initial generate listOfChars::  "<< begin << endl;
//	    map<const int, vector<Point>, ltstr> characterList = listOfCharactersAntigo(images[i]);
        end = clock();
      //  cout<< "time end generate listOfChars::  "<< end << endl;
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//        LOGD("time generate listOfChars::  " + elapsed_secs);
        cout<< "time generate listOfChars::  "<< elapsed_secs << endl;
        LOGD("time generate listOfChars::  ");

//        LOGD(teste);
       // cout<< "Criptografando :: " << endl;
        //encrypt
        begin = clock();
        vector<int> cryptMessage = encryptMessage(characterList, a);
        end = clock();

        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//        LOGD("time enc::  " + elapsed_secs );
        cout<< "time enc::  "<< elapsed_secs << endl;
        LOGD("time enc::  ");
//        LOGD("size enc message ::  " + cryptMessage.size());
//        cout<< "size enc message ::  "<< cryptMessage.size() << endl;

//        double raz = double(cryptMessage.size()/a.size()) ;

//        LOGD("raz enc message ::  " + raz);
//        cout<< "raz enc message ::  "<< raz << endl;
    //cout << "Flag " << flag << endl;
//    for(int i = 0; i<cryptMessage.size(); i++)
  //      cout<<cryptMessage[i]<<" ";
    //cout << endl;
 //   cout<< "Decriptografando:: " << endl;

        //decrypt
        begin = clock();
//        string dcryptMessage = dencryptMessage(cryptMessage);
        end = clock();

        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//        LOGD(cout<< "time denc::  " + elapsed_secs);
        cout<< "time denc::  "<< elapsed_secs << endl;
//        LOGD("size denc message ::  " + dcryptMessage.size());
//        cout<< "size denc message ::  "<< dcryptMessage.size() << endl;
//    cout<< dcryptMessage << endl;
//        LOGD("fim "+i);
        cout << "fim " << i << endl;
        i++;

        /*for(int i = 0; i<255;i++){

		vector<Point> pois = characterList[i];
			if(pois.size() <= 0){
			    char ch = i;
			    cout<< "char " << ch << " " << i << endl;

			}

    	}*/

    }

//  clock_t end = clock();

 //       double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
 //       cout<< "time enc::  "<< elapsed_secs << endl;

	//cout << points << endl;


    //imshow("opencvtest",img);

    //showHistogram(img);
    //waitKey(0);

	return jint(0);

}

#ifdef __cplusplus
}
#endif
