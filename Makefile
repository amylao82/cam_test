
# 目标文件名称
TARGET := cam_test

CXX := $(CROSS_COMPILE)g++

STRIP := $(CROSS_COMPILE)strip

INC_DIR := -Iinclude
CFLAGS := -g -fPIC

SRC := $(wildcard ./*.cpp src/*.cpp)
OBJS := $(subst .cpp,.o, $(SRC))
D_FILE := $(subst .cpp,.d, $(SRC))

SRC_C := $(wildcard *.c)
OBJS_C := $(subst .c,.o, $(SRC_C))
D_FILE_C := $(subst .c,.d, $(SRC_C))

LD_LIBS := -pthread

LD_LIBS += -Llib -lmedia_interface -lgeneral -lmi_lib -lcore

all : $(TARGET) 

$(TARGET) : $(OBJS) $(OBJS_C)
	$(CXX) -o $(TARGET) $^ $(LD_LIBS)
	$(STRIP) -s $(TARGET)


%.o : %.cpp
	$(CXX)  $(CFLAGS) -MMD -c -o $@ $(INC_DIR) $<

%.o : %.c
	$(CC) $(CFLAGS) -MMD -c -o $@ $(INC_DIR) $<

clean:
	rm $(TARGET) $(D_FILE) $(D_FILE_C) $(OBJS) $(OBJS_C)
