
#CXX = g++
#CXX = clang++

EXE = kite

SOURCES = main.cpp stb_image.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS = -std=c++17
CXXFLAGS += -Wall -Wformat

LIBS += -L/usr/local/lib -L/opt/homebrew/lib
LIBS += -lglfw -lglew -framework OpenGL

CXXFLAGS += -I/opt/homebrew/include
CXXFLAGS += -Iinclude


# rules

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: clean $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
