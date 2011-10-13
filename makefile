CC = g++
LIB = 
CFLAGS = -Wall -Werror -g
IFLAGS =

rebuild : cleanAll etags debugSimu

#BUILD TARGET
debugSimu : driver.o transferEntropy.o common.o dataFile.o
	$(CC) $(CFLAGS) -D _DEBUG  driver.cpp transferEntropy.cpp common.cpp dataFile.cpp -o simu

simu : driver.o transferEntropy.o logger.o
	$(CC) $(CFLAGS) driver.cpp transferEntropy.cpp -o simu

driver.o : driver.cpp
	$(CC) $(LIB) $(CFLAGS) -c driver.cpp
transferEntropy.o : transferEntropy.cpp
	$(CC) $(LIB) $(CFLAGS) -c transferEntropy.cpp
common.o : common.cpp
	$(CC) $(LIB) $(CFLAGS) -c common.cpp
dataFile.o : dataFile.cpp
	$(CC) $(LIB) $(CFLAGS) -c dataFile.cpp

#CLEAN TARGET
clean : 
	find . -type f \( -name '*.o' -o -name '*.out' -o -name '*.*\~' \) -exec rm -f {} \;
cleanAll : 
	find . -type f \( -name '*.o' -o -name '*.out' -o -name '*.log' -o -name '*.*\~' \) -exec rm -f {} \;

#REBUILD TAGS
etags:
	find . -name '*.cpp' -o -name '*.hpp' | xargs etags
