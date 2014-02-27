% Universidade Federal do Amazonas
% Mikhail Yasha Ramalho Gadelha
% Cryptography using Images - Fixed Coordinates
% testing.m - Test the encrypt and decrypt

clear
clc

% Message
maxMessageSize = [9000 10000];
% maxMessageSize = 10;
minMessageValue = 0;
maxMessageValue = 255;

% Number of Simulations
numberOfSimulations = 1;

% Performance Measures
avLengOr = zeros(1,numberOfSimulations);
avLengEn = zeros(1,numberOfSimulations);
avLengDe = zeros(1,numberOfSimulations);
avTimeEn = zeros(1,numberOfSimulations);
avTimeDe = zeros(1,numberOfSimulations);
avError = zeros(1,numberOfSimulations);
avRate = zeros(1,numberOfSimulations);
avEnt = zeros(1,numberOfSimulations);

%% Simulations
t = clock;

for k = 1:numberOfSimulations
    clc
    fprintf('============================================================\n')
    fprintf('Simulation number %d\n\n',k);
    
    fprintf('Generating random message... ')
    messageSize = randi(maxMessageSize);
%     message = int16(randi([minMessageValue,maxMessageValue],1,messageSize));
    biblia = fopen('../Gênesis.txt');
%     biblia = fopen('../Bíblia Sagrada.txt');
    message = fread(biblia);
    fclose(biblia);
    
    messageSize = length(message);
    disp('OK');
    avLengOr(k) = messageSize;

    fprintf('Encrypting... ');
    tic; encrypt; encryptTime = toc;
    disp('OK')
    avLengEn(k) = length(encryptedMessage);
    avTimeEn(k) = encryptTime;
    avRate(k) = length(encryptedMessage)/messageSize;
    avEnt(k) = fileEntropy(encryptedMessage);
    
    fprintf('Decrypting... ')
    tic; decrypt; decryptTime = toc;
    disp('OK')
    avLengDe(k) = length(decryptedMessage);
    avTimeDe(k) = decryptTime;
    
    fprintf('Verifying original message and decrypted message... ')
    wrongCharacters = verifyMessages(decryptedMessage,message);
    disp ('OK')
    avError(k) = wrongCharacters;
end

simulationTime = etime(clock,t);

%% Print Informations
clc
disp('Simulations Results:');
disp(['Average Original Message Size = ',num2str(mean(avLengOr)), ' B'])

fprintf('\n');
disp(['Average Encrypted Message Size = ',num2str(mean(avLengEn)), ' B'])
disp(['Average Encrypted/Original message rate = ',num2str(mean(avRate))])
disp(['Encrypted Message Entropy = ', num2str(mean(avEnt))]);
disp(['Average Encrypt Time = ',num2str(mean(avTimeEn)), ' s'])

fprintf('\n');
disp(['Average Decrypted Message Size = ',num2str(mean(avLengDe)), ' B'])
disp(['Average Decrypt Time = ',num2str(mean(avTimeDe)), ' s'])
disp(['Average Decrypted Message error = ',num2str(mean(avError)), ' B'])

fprintf('\n');
disp(['Simulation Time = ',num2str(simulationTime), ' s'])

%% Plot graphics
subplot(4,2,1); plot(1:numberOfSimulations,avLengOr); title('Average Original Message Size');
subplot(4,2,2); plot(1:numberOfSimulations,avLengEn); title('Average Encrypted Message Size');
subplot(4,2,3); plot(1:numberOfSimulations,avLengDe); title('Average Decrypted Message Size');
subplot(4,2,4); plot(1:numberOfSimulations,avRate); title('Average Encrypted/Original message rate');
subplot(4,2,5); plot(1:numberOfSimulations,avEnt); title('Encrypted Message Entropy');
subplot(4,2,6); plot(1:numberOfSimulations,avError); title('Average Decrypted Message error');
subplot(4,2,7); plot(1:numberOfSimulations,avTimeEn); title('Average Encrypt Time');
subplot(4,2,8); plot(1:numberOfSimulations,avTimeDe); title('Average Decrypted Time');