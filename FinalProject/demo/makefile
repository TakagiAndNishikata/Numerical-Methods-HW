CC=g++
TARGET1=main
TARGET2=DFT
TARGET3=Huffman
FLAG= -std=c++11

all: $(TARGET1).cpp $(TARGET2).cpp $(TARGET3).cpp 
	$(CC) $(FLAG) -c $(TARGET1).cpp $(TARGET2).cpp  $(TARGET3).cpp
	$(CC) $(FLAG) -o $(TARGET1) $(TARGET1).o $(TARGET2).o  $(TARGET3).o

clean:
	rm -f $(TARGET1) *.o
