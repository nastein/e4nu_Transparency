ROOTCFLAGS  := $(shell root-config --cflags)
ROOTLDFLAGS := $(shell root-config --ldflags)
ROOTLIBS    := $(shell root-config --libs) -lEG
ROOTGLIBS   := $(shell root-config --glibs)

INCLUDES    := -I../include

CXX       := g++
CXXFLAGS  += -std=c++11 -Wall -Wshadow -Warray-bounds -Wmissing-field-initializers -fPIC $(ROOTCFLAGS)
LD        := g++
LDFLAGS   := $(ROOTLDFLAGS)

OBJECTS2   := Subtraction.o run_genie_analysis.o Fiducial.o genie_analysis.o

all: e2a_ep genie_analysis

genie_analysis: $(OBJECTS2)
		$(CXX) -o genie_analysis $(OBJECTS2) $(ROOTCFLAGS) $(ROOTLDFLAGS) $(ROOTLIBS)

clean:
	@echo 'Removing all build files'
	@rm -rf *.o run_e2a_ep run_genie_analysis run_systematics *~

%.o: %.C
	$(CXX) -c $< -O2 $(CXXFLAGS) $(INCLUDES)
