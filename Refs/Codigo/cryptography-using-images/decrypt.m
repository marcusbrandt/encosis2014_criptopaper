% Universidade Federal do Amazonas
% Mikhail Yasha Ramalho Gadelha
% Cryptography using Images - Fixed Coordinates
% decrypt.m - Decrypt the message

% Read Message from file
encryptedFile = fopen('Encrypted File','r');
encryptedMessage = fread(encryptedFile,'ubit10')';
encryptedMessage(length(encryptedMessage)) = [];
fclose(encryptedFile);

% Read the image
img = imread('../Images/lena.jpg','jpg');

% Flag
flag = max(size(img)) +1;

% List of positions of each value of the ASCII table
list = listOfCharacters(img);

% Decrypted Message
decryptedMessage = int16([]);

hasOp = false;
i = 1;
while (i <= length(encryptedMessage))
    
    if(encryptedMessage(i) == 0)
        i = i + 1;
        while(encryptedMessage(i) ~= flag)
            posX = encryptedMessage(i);
            posY = encryptedMessage(i+1);
            
            decryptedChar = decryptCharacter(img,posX,posY);
            
            if(hasOp)
                decryptedChar = decryptedChar + corr;
                hasOp = false;
            end
            
            decryptedMessage = [decryptedMessage decryptedChar];
            i = i + 2;
            
            if(i > length(encryptedMessage))
                break;
            end
        end
    elseif(encryptedMessage(i) == 1)
        i = i + 1;
        hasOp = true;
        
        if (encryptedMessage(i) == int16('+'))
            corr = int16(encryptedMessage(i+1))*-1;
        elseif(encryptedMessage(i) == int16('-'))
            corr = encryptedMessage(i+1);
        end
        i = i + 2;
    end
    i = i + 1;
end