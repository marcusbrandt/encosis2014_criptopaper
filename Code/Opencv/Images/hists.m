
close all
I = imread('aerial','pgm'); 
figure;
imhist(I);
I = imread('boats','pgm'); 
figure;
imhist(I);
I = imread('bridge','pgm'); 
figure;
imhist(I);
I = imread('D108','pgm'); 
figure;
imhist(I);
I = imread('f16','pgm'); 
figure;
imhist(I);
I = imread('girl','pgm'); 
figure;
imhist(I);
I = imread('peppers','pgm'); 
figure;
imhist(I);
I = imread('pp1209','pgm'); 
figure;
imhist(I);
I = imread('zelda','pgm'); 
figure;
imhist(I);

biblia = fopen('../Bíblia Sagrada.txt');
text = fread(biblia);
figure;
hist(text,255);
fclose(biblia);