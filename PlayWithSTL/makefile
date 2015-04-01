AINAME := ai.cc

TARGETNAME := ai

SOURCES := $(AINAME) sdk.cc Pos.cc const.cc

CXX ?= g++

CFLAGS := -std=c++11 -w -I../logic/src/include

TARGET ?= $(TARGETNAME).so

SDK_PATH?=-iquote./

override CXXFLAGS += \
       -D_AI__ \
       -Wall -Wextra -Wnon-virtual-dtor -Wno-unused-parameter -Winvalid-pch -g\
       $(CPPFLAGS) -fPIC -std=c++0x

$(TARGET):$(SOURCES)
	$(CXX) -shared $(CXXFLAGS) $(LDFLAGS) $^ $(SDK_PATH) -o $@

all: $(TARGET)

clean:
	rm -f $(TARGET)
