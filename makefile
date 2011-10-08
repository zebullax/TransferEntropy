CC = g++
LIB = 
CFLAGS = -Wall -Werror -g
IFLAGS =

debugSimu : driver.o transferEntropy.o common.o
	$(CC) $(CFLAGS) -D _DEBUG  driver.cpp transferEntropy.cpp common.cpp -o simu

simu : driver.o transferEntropy.o logger.o
	$(CC) $(CFLAGS) driver.cpp transferEntropy.cpp -o simu

driver.o : driver.cpp
	$(CC) $(LIB) $(CFLAGS) -c driver.cpp
transferEntropy.o : transferEntropy.cpp
	$(CC) $(LIB) $(CFLAGS) -c transferEntropy.cpp
common.o : common.cpp
	$(CC) $(LIB) $(CFLAGS) -c common.cpp

clean : 
	rm -f *.o
	rm -f *.out
etags:
	find . -name '*.cpp' -o -name '*.hpp' | xargs etags
