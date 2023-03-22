.PHONY:all
all:client ReadOnlyServer

client:client.cc
	g++ -o $@ $^ -std=c++11
server:ReadOnlyServer.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f client ReadOnlyServer myfifo
