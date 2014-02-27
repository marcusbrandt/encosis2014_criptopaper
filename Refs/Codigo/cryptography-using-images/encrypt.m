% Universidade Federal do Amazonas
% Mikhail Yasha Ramalho Gadelha
% Cryptography using Images - Fixed Coordinates
% encrypt.m - Encrypt the message

% Read the image
img = imread('../Images/lena.jpg','jpg');

% Flag
flag = max(size(img)) +1;

% List of positions of each value of the ASCII table
list = listOfCharacters(img);

encryptedMessage = int16([]);

for i = 1:length(message)
    c = message(i);
    
    encryptedChar = encryptCharacter(list,c,flag);

    if (length(encryptedChar) == 2 && isempty(encryptedMessage))
        encryptedMessage = [0 encryptedMessage];
    end
    
    if (length(encryptedChar) > 2 && ~isempty(encryptedMessage))
        encryptedChar = [ flag encryptedChar];
    end
    
    encryptedMessage = [encryptedMessage encryptedChar];
end

% Write the final message in a file
encryptedFile = fopen('Encrypted File','w');
fwrite(encryptedFile, encryptedMessage,'ubit10');
fclose(encryptedFile);