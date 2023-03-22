.PHONY:all
all:shmServer shmClient
shmServer:shmServer.cc
	g++ -o $@ $^ -std=c++11
shmClient:shmClient.cc
	g++ -o $@ $^ -std=c++11
.PHONY:clean
clean:
	rm -rf shmServer shmClient fifotest
