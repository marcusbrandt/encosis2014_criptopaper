function [ ent ] = fileEntropy(msg)
%FILEENTROPY Summary of this function goes here
%   Detailed explanation goes here

    pMax = length(msg);
    freq = zeros(1,514);
    for i=0:1:513
       freq(i+1) = length(find(msg==i));
    end

    ent = 0;
    for i=1:1:514
        if (freq(i) == 0)
           continue; 
        end

        ent = ent - (freq(i)/pMax)*(log2(freq(i)/pMax));
    end
end

