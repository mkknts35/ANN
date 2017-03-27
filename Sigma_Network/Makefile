CFLAGS=-std=c++11 -O3
SQLINCLUDES=-I /usr/local/include -I /usr/local/include/cppconn
SQLFLAGS=-l mysqlcppconn
run: test
	./test
test: test.h test.cpp network.o layer.o sigmoid.o neuron.o util.o data.o
	g++ $(CFLAGS) -o test $(SQLINCLUDES) $(SQLFLAGS) test.cpp network.o layer.o sigmoid.o neuron.o util.o data.o
network.o: network.h network.cpp
	g++ $(CFLAGS) -c network.cpp -o network.o
layer.o: layer.h layer.cpp
	g++ $(CFLAGS) -c layer.cpp -o layer.o
sigmoid.o: sigmoid.h sigmoid.cpp
	g++ $(CFLAGS) -c sigmoid.cpp -o sigmoid.o
neuron.o: neuron.h neuron.cpp
	g++ $(CFLAGS) -c neuron.cpp -o neuron.o
util.o: util.h util.cpp
	g++ $(CFLAGS) -c util.cpp -o util.o
data.o: data.h data.cpp
	g++ $(CFLAGS) -c data.cpp -o data.o
clean:
	rm -f test *.o
