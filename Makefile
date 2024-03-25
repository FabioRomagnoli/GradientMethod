CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -Wno-deprecated-enum-enum-conversion
INCLUDES ?= -I$(mkEigenInc) -I$(MP_INCLD_DIR)

MP_PRFX=/home/fabio/Documents/PACS/pacs-examples/Examples
MP_LIB_DIR=$(MP_PRFX)/lib
MP_INCLD_DIR=$(MP_PRFX)/include/muparserx


#REQUIRMENTS
MP_REQ_LIBS = -L$(MP_LIB_DIR) -lmuparserx
# MP_CPP_FLAGS: -I$(MP_INCLD_DIR)



.PHONY : all $(EXEC) $(OBJS) clean distclean 


# get all files *.cpp
SRCS=$(wildcard *.cpp)
# get the corresponding object file
OBJS = $(SRCS:.cpp=.o)
# get all headers in the working directory
HEADERS=$(wildcard *.hpp)
HEADERS+=GetPot

exe_sources=$(filter main%.cpp,$(SRCS))
EXEC=$(exe_sources:.cpp=)

all: $(EXEC) 

$(EXEC): $(OBJS)
	$(CXX)  $(CXXFLAGS)  $(CPPFLAGS) $(inputs) -o $@ $^ $(MP_REQ_LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(EXEC)
	$(RM) *.o

distclean: clean
	$(RM) $(EXEC)
