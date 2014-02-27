function [ wrongCharacters ] = verifyMessages( decryptedMessage, message )
%VERIFYMESSAGES Summary of this function goes here
%   Detailed explanation goes here

    wrongCharacters = 0;
    
    for i=1:length(message)
        if(message(i) ~= decryptedMessage(i))
            wrongCharacters = wrongCharacters + 1;
        end
    end

end

