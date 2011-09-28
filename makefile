CC = g++
LIB = 
CFLAGS = -Wall -Werror
IFLAGS =
LOGFLAG =
simu : driver.o transferEntropy.o logger.o
	$(CC) -Wall -Werror $(LOGFLAG) driver.cpp transferEntropy.cpp logger.cpp -o simu

driver.o : driver.cpp
	$(CC) $(LIB) $(CFLAGS) -c driver.cpp
transferEntropy.o : transferEntropy.cpp
	$(CC) $(LIB) $(CFLAGS) -c transferEntropy.cpp
logger.o : logger.cpp
	$(CC) $(LIB) $(CFLAGS) -c logger.cpp
	
clean : 
	rm -f *.o
	rm -f *.out
