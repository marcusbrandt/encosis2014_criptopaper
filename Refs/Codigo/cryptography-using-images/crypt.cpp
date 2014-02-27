#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace cv;
using namespace std;

int flag = 0;

Mat img;


struct ltstr
{
  bool operator()(const int s1, const int s2) const
  {
//    return strcmp(s1, s2) < 0;
    return s1<s2;
  }
};


struct Point {
	int x,
	int y
} point

int [] vector<Point> listOfCharacters(string pathImage){

    img = imread(pathImage,CV_LOAD_IMAGE_COLOR);

    int cols = img.cols;
	int rows = img.rows;
	
	if(cols>rows)
	    flag = cols;
	else
	    flag = rows;

    flag++;
	map<const int, vector<Point>, ltstr> points;
	
	//cout << "Cols :: " << cols << "Rows" << rows << "size = " << (cols*rows) << endl;


	for(int row = 1; row<rows;row++){
		for(int col = 1; col<cols;col++){

			Point colRow = Point(col,row);
		    Scalar color = img.at<uchar>(colRow);		
			int id = color.val[0];
			points[id].push_back(colRow);
			
		}
	}
	return points;
}


vector<int> closerTo(map<const int, vector<Point>, ltstr> characterList, unsigned char character){

    vector<int> closeChars;
    int ch = character;
    int closerTemp;
    int i = 1;
    vector<Point> points;
    int signal = 0;
    int dist = 0;
    
    while( (ch - i) > 0 || (ch + i)<256){
        closerTemp = ch + i;
        if(closerTemp < 256){       
            points = characterList[closerTemp];

            if(!points.empty()){
    //        cout << "positivo " << i<< " closerTemp "<< closerTemp << endl;
               signal = '+'; 
               dist = i;
               break;
            }
        }
        
        
        closerTemp = ch - i;
        if(closerTemp > 0){
            points = characterList[closerTemp];
            if(!points.empty()){
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

vector<int> encryptCharacter(map<const int, vector<Point>, ltstr> characterList, unsigned char character){

    int charInt = character;
    Point point;
    vector<int>  closeChars;
    vector<int> charEnc;
    
    
//    cout << "list "<< characterList.size() << endl;
    
    
    vector<Point> points = characterList[charInt];


    if(points.empty()){
        charEnc.push_back(1);
        closeChars = closerTo(characterList, character);

        charEnc.push_back(closeChars[0]);
        charEnc.push_back(closeChars[1]);
        charEnc.push_back(flag);                
        charEnc.push_back(0);

        /*
        if(encryptedChar(2) == 45)
            newChar = int16(character) - encryptedChar(3);
        else
            newChar = int16(character) + encryptedChar(3);
        end
        
        posX = list(:,2*newChar+1);
        posY = list(:,2*newChar+2);
        */
        
        if(closeChars[0]==45){
            charInt = charInt - closeChars[1];
        }else{
            charInt = charInt + closeChars[1];
        }
        //cout << "charInt new "<< charInt << endl;    
        points = characterList[charInt];
        
    }
    point = points[rand()%points.size()];    
    charEnc.push_back(point.x);
    charEnc.push_back(point.y);   

    return charEnc;

}

vector<int> encryptMessage(map<const int, vector<Point>, ltstr> characterList, string message){

    vector<int> cryptMessage;
    vector<int> aux;
    unsigned char ch;
    for(int i = 0; i < message.length(); i++){
        ch = message[i];
        int charInt = ch;
        aux = encryptCharacter(characterList, ch);
        
    if (aux.size() == 2 && cryptMessage.empty())
            cryptMessage.push_back(0);
    
    if (aux.size() > 2 && !cryptMessage.empty())
            cryptMessage.push_back(flag);
    
//    encryptedMessage = [encryptedMessage encryptedChar];
        
        
        for(int j = 0; j<aux.size();j++){     
            cryptMessage.push_back(aux[j]);
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
                
                Point colRow = Point(col,row);
                Scalar color = img.at<uchar>(colRow);		
                
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

int main()
{

    srand ( time(NULL) );
    vector<string> images;
    images.push_back("./Images/aerial.pgm");
    images.push_back("./Images/boats.pgm");
    images.push_back("./Images/bridge.pgm");
    images.push_back("./Images/D108.pgm");
    images.push_back("./Images/f16.pgm");
    images.push_back("./Images/girl.pgm");
    images.push_back("./Images/lena.jpg");
    images.push_back("./Images/peppers.pgm");
    images.push_back("./Images/pp1209.pgm");
    images.push_back("./Images/zelda.pgm");
        
        ifstream infile;
    infile.open("./Files/Gênesis.txt");
//    infile.open("./Files/teste.txt");    
    stringstream buffer;
    buffer << infile.rdbuf();
    string a = buffer.str();
    
    cout << "size message :: " << a.size() << endl;
    
    int i = 0;
    while(i<images.size()){
        cout << "Image :: " << images[i] << endl;
	    map<const int, vector<Point>, ltstr> characterList = listOfCharacters(images[i]);
    
        //encrypt
        clock_t begin = clock();
        vector<int> cryptMessage = encryptMessage(characterList, a);
        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout<< "time enc::  "<< elapsed_secs << endl;    
        cout<< "size enc message ::  "<< cryptMessage.size() << endl;    
/*    cout << "Flag " << flag << endl;
    cout<< "Criptografando :: ";
    for(int i = 0; i<cryptMessage.size(); i++)
        cout<<cryptMessage[i]<<" ";
    cout << endl;*/
//    cout<< "Decriptografando:: " << endl;

        //decrypt
        begin = clock(); 
        string dcryptMessage = dencryptMessage(cryptMessage);
        end = clock();
    
        elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout<< "time denc::  "<< elapsed_secs << endl;    
        cout<< "size denc message ::  "<< dcryptMessage.size() << endl;    
//    cout<< dcryptMessage << endl;

        cout << "fim " << i << endl;
        i++;
    }
/*	for(int i = 0; i<255;i++){

		vector<Point> pois = characterList[i];
			if(pois.size() <= 0){
			    char ch = i;
			    cout<< "char " << ch << " " << i << endl;
			    
			}

	}


*/
	//cout << points << endl;


    //imshow("opencvtest",img);
    
    //showHistogram(img);
    //waitKey(0);

    return 0;
}