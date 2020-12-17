CXX= clang++
DIR=${CURDIR}
CFLAGS=-g -fPIC -I${DIR} -fstack-protector-strong
LDFLAGS=--shared


all: railfence.o cryptomath.so

railfence.o: railfence.cpp cryptomath.h
	$(CXX) $(CFLAGS) railfence.cpp -o railfence.o -c

cryptomath.so: railfence.o
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o cryptomath.so
	rm *.o

clean:
	rm ./*.o &2>/dev/null
	rm cryptomath.so &2>/dev/null

