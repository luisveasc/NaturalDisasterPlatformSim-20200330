CXX=g++
LIBRARY=-I/usr/local/include/libcppsim
INCLUDE=-I/usr/local/include/nlohmann -L/usr/local/include/libcppsim
CXXFLAGS=-std=c++14 -O3 -ggdb -Wall -w -lm -g -lcppsim $(INCLUDE) $(LIBRARY)


OBJS1=obj/main.o obj/platformsim.o obj/cluster.o obj/multicore.o obj/core.o obj/ram.o obj/hhd.o obj/operatorsystem.o
OBJS2=obj/message.o obj/work.o obj/workprocess.o obj/workrequesttoapi.o
OBJS3=obj/activity.o obj/program.o obj/programdeployment.o obj/executeresponse.o obj/executionrequest.o obj/network.o obj/client.o
OBJS4=obj/monitor.o

TARGET=simulator

$(TARGET): $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4)
	        $(CXX) -o $@ $^ $(CXXFLAGS)

obj/main.o:src/main.cc
obj/platformsim.o:src/platformsim.cc include/platformsim.h
obj/cluster.o:src/cluster.cc include/cluster.h
obj/multicore.o:src/multicore.cc include/multicore.h
obj/core.o:src/core.cc include/core.h
obj/ram.o:src/ram.cc include/ram.h
obj/hhd.o:src/hhd.cc include/hhd.h
obj/operatorsystem.o:src/operatorsystem.cc include/operatorsystem.h
obj/message.o:src/message.cc include/message.h
obj/work.o:src/work.cc include/work.h
obj/workprocess.o:src/workprocess.cc include/workprocess.h
obj/workrequesttoapi.o:src/workrequesttoapi.cc include/workrequesttoapi.h
obj/activity.o:src/activity.cc include/activity.h
obj/program.o:src/program.cc include/program.h
obj/programdeployment.o:src/programdeployment.cc include/programdeployment.h
obj/executeresponse.o:src/executeresponse.cc include/executeresponse.h
obj/executionrequest.o:src/executionrequest.cc include/executionrequest.h
obj/network.o:src/network.cc include/network.h
obj/client.o:src/client.cc include/client.h
obj/monitor.o:src/monitor.cc include/monitor.h


obj/%.o:
	$(CXX) -o $@ -c $< $(CXXFLAGS)
clean:
	${RM} $(TARGET)
	${RM} obj/*.o
	${RM} *~

all:
	make clean
	make
