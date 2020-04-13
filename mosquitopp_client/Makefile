SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

CXXFLAGS =    -g  -std=c++11 -Wall

TARGET =    MQTT_Client

$(TARGET):    $(OBJ)
	$(CXX) -o $@ $^ -lmosquitto -lmosquittopp

.PHONY: all
all:    $(TARGET)

.PHONY: clean
clean:
	rm -f *.o $(TARGET)
