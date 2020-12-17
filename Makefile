CXX= clang++
DIR=${CURDIR}
CFLAGS=-g -fPIC -I${DIR} -fstack-protector-strong
LDFLAGS=--shared


all: railfence.o libcrypt.so

railfence.o: src/railfence.cpp include/cryptomath.h include/railfence.h
	$(CXX) $(CFLAGS) src/railfence.cpp -o railfence.o -c

libcrypt.so: railfence.o
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o libcrypt.so
	rm *.o

clean:
	rm ./*.o &2>/dev/null
	rm libcrypt.so &2>/dev/null

