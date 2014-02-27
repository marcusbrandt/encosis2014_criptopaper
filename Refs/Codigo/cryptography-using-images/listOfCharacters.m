function [ list ] = listOfCharacters( img )
%LISTOFCHARACTERS Summary of this function goes here
%   Detailed explanation goes here

    [num occ] = mode(double(img(:)));
    list = zeros(occ,512);
    
    for i = 0:255
        [row col] = find(img==i);
        
        if(isempty(row))
           row = 0; 
           col = 0; 
        end
        
        list(1:length(row),2*i+1) = row;
        list(1:length(col),2*i+2) = col;
    end
    
end

