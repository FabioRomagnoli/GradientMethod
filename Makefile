CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -Wno-deprecated-enum-enum-conversion
INCLUDES ?= -I$(mkEigenInc) -I$(MP_INCLD_DIR)

MP_PRFX=/home/fabio/Documents/PACS/pacs-examples/Examples
MP_EXEC_PRFX=$(MP_PRFX)
MP_LIB_DIR=$(MP_PRFX)/lib
MP_INCLD_DIR=$(MP_PRFX)/include 

#REQUIRMENTS
# MP_REQ_LIBS: -L$(MP_LIB_DIR) -lmuparser
# MP_CPP_FLAGS: -I$(MP_INCLD_DIR)



.PHONY : all $(EXEC) $(OBJS) clean distclean 


# get all files *.cpp
SRCS=$(wildcard *.cpp)
# get the corresponding object file
OBJS = $(SRCS:.cpp=.o)
# get all headers in the working directory
HEADERS=$(wildcard *.hpp)

exe_sources=$(filter main%.cpp,$(SRCS))
EXEC=$(exe_sources:.cpp=)

all: $(EXEC) 

$(EXEC): $(OBJS)
	$(CXX)  $(CXXFLAGS) $(MP_REQ_LIBS) $(CPPFLAGS) $(inputs) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(EXEC)
	$(RM) *.o

distclean: clean
	$(RM) $(EXEC)
