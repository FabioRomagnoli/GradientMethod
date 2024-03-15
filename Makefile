CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -Wno-deprecated-enum-enum-conversion
INCLUDES ?= -I/u/sw/toolchains/gcc-glibc/11.2.0/pkgs/eigen/3.3.9/include/eigen3


# MP_PRFX=/home/fabio/Documents/PACS/pacs-examples/Examples
# MP_EXEC_PRFX=${prefix}
# MP_LIB_DIR=${prefix}/lib
# MP_INCLD_DIR=${prefix}/include 

# #REQUIRMENTS
# MP_REQ_LIBS: -L${libdir} -lmuparser
# MP_CPP_FLAGS: -I${includedir} 


# #REQUIRMENTS




.PHONY : all $(EXEC) $(OBJS) clean distclean 

EXEC = main
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(EXEC) 

$(EXEC): $(OBJS)
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) $(inputs) -o $@ $^

$(OBJS): $(SRCS)
	$(CXX)  $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< 


clean:
	$(RM) $(EXEC)
	$(RM) *.o

distclean: clean
	$(RM) $(EXEC)
