# An empty makefile to copy to a fresh project.
SRCS=main.cpp cleanup.cpp common.cpp map.cpp gfxutil.cpp util.cpp
TARGET=gd-td
OBJS=$(SRCS:.cpp=.o)
CFLAGS=-O2 -fomit-frame-pointer
INCLUDES=-I./include
LFLAGS=-lSDL -lSDL_image
LIBS = 
LIBS_CUSTOM = 
CC=g++

all: $(TARGET)
	@echo "Finished."

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS) $(LIBS_CUSTOM)
	strip --strip-all $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	rm ./*.o ./*~ ./$(TARGET) ./$(TARGET)-*
