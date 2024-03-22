CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -Wno-deprecated-enum-enum-conversion
INCLUDES ?= -I$(mkEigenInc)

# MP_PRFX=/home/fabio/Documents/PACS/pacs-examples/Examples
# MP_EXEC_PRFX=${prefix}
# MP_LIB_DIR=${prefix}/lib
# MP_INCLD_DIR=${prefix}/include 

# #REQUIRMENTS
# MP_REQ_LIBS: -L${libdir} -lmuparser
# MP_CPP_FLAGS: -I${includedir} 


# #REQUIRMENTS


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
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) $(inputs) -o $@ $^

$(OBJS): $(SRCS)
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -c $^


clean:
	$(RM) $(EXEC)
	$(RM) *.o

distclean: clean
	$(RM) $(EXEC)
