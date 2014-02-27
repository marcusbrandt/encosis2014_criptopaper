function [ encryptCharacter ] = encryptCharacter(list, character, escape)
%ENCRYPTCHARACTER Summary of this function goes here
%   Detailed explanation goes here

    posX = list(:,2*character+1);
    posY = list(:,2*character+2);
    posX(posX==0) = [];
    posY(posY==0) = [];

    encryptedChar = [];
    
    if (isempty(posX))
        encryptedChar = [encryptedChar 1 closerTo(character,list) escape 0];
        if(encryptedChar(2) == 45)
            newChar = int16(character) - encryptedChar(3);
        else
            newChar = int16(character) + encryptedChar(3);
        end
        
        posX = list(:,2*newChar+1);
        posY = list(:,2*newChar+2);
        posX(posX==0) = [];
        posY(posY==0) = [];
    end        
    
    randPos = randi(length(posX));
    encryptedChar = [encryptedChar posX(randPos) posY(randPos)];
    
    encryptCharacter = encryptedChar;
end