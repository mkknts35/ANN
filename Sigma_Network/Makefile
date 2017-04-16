CFLAGS=-std=c++11 -O3
SQLINCLUDES=-I /usr/local/include -I /usr/local/include/cppconn
SQLFLAGS=-l mysqlcppconn
iris: test
	./test -d ann -t iris
arem: test
	./test -d ann -t arem
test: ann.h ann.cpp network.o layer.o sigmoid.o neuron.o util.o sample.o data.o
	g++ $(CFLAGS) -o test $(SQLINCLUDES) $(SQLFLAGS) ann.cpp network.o layer.o sigmoid.o neuron.o util.o data.o sample.o
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
sample.o: sample.h sample.cpp
	g++ $(CFLAGS) -c sample.cpp -o sample.o
ann.o: ann.h ann.cpp network.o layer.o sigmoid.o neuron.o util.o sample.o data.o
	g++ $(CFLAGS) -o ann $(SQLINCLUDES) $(SQLFLAGS) ann.cpp network.o layer.o sigmoid.o neuron.o util.o sample.o data.o
clean:
	rm -f test *.o
