CC = g++
LIB = 
CFLAGS = -Wall -Werror -g
IFLAGS =
LOGFLAG =  -D _DEBUG

debugSimu : driver.o transferEntropy.o logger.o
	$(CC) $(CFLAGS) $(LOGFLAG) driver.cpp transferEntropy.cpp logger.cpp -o simu

simu : driver.o transferEntropy.o logger.o
	$(CC) $(CFLAGS) driver.cpp transferEntropy.cpp logger.cpp -o simu

driver.o : driver.cpp
	$(CC) $(LIB) $(CFLAGS) $(LOGFLAG) -c driver.cpp
transferEntropy.o : transferEntropy.cpp
	$(CC) $(LIB) $(CFLAGS) $(LOGFLAG) -c transferEntropy.cpp
logger.o : logger.cpp
	$(CC) $(LIB) $(CFLAGS) $(LOGFLAG) -c logger.cpp

clean : 
	rm -f *.o
	rm -f *.out

etags:
	find . -name '*.cpp' -o -name '*.hpp' | xargs etags
