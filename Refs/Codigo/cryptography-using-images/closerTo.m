function [ closerCharacter ] = closerTo( character, list)
%CLOSERTO Summary of this function goes here
%   Detailed explanation goes here

    i = 1;
    
    while ((character -i) > 0 || (character +i) < 256)
        closerTemp = character + i;
        if(closerTemp < 256)       
            posX = list(:,2*closerTemp+1);
            posX(posX==0) = [];

            if(~isempty(posX))
               signal = int16('+'); 
               dist = i;
               break;
            end
        end
        
        closerTemp = character - i;
        if(closerTemp > 0)
            posX = list(:,2*closerTemp+1);
            posX(posX==0) = [];
            
            if(~isempty(posX))
               signal = int16('-'); 
               dist = i;
               break;
            end            
        end
        
        i=i+1;
    end

    closerCharacter = [ signal dist ];
    
    % Returns (sign)(dist)(esca)(zero)
    %           4B    4B    4B    4B  = 16B
end

