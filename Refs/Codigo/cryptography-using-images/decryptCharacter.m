function [ character ] = decryptCharacter( img, posX, posY)
%DECRYPTCHARACTER Summary of this function goes here
%   Detailed explanation goes here

    character = int16(img(posX,posY));
end

