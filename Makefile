CC = g++
CFLAGS = -Wall -c -Wconversion -Wno-deprecated-declarations -Wno-conversion
LIBFLAGS = -framework OpenGL -framework GLUT
LFLAGS = -Wall $(LIBFLAGS)

CPPS = $(wildcard *.cpp)
OBJS = $(CPPS:.cpp=.o)

TARGET = chess

run: $(TARGET)
	./$(TARGET) &

kill:
	killall $(TARGET)
	
$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^

main.o: main.cpp
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET) *.o
