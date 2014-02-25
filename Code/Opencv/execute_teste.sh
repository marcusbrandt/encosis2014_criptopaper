g++ -ggdb `pkg-config --cflags opencv` -o `basename teste.cpp .cpp` teste.cpp `pkg-config --libs opencv`
./teste
