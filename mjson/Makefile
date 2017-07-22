CXX = g++
#CXXFLAGS = -Wall -W -Wno-unused-parameter -pg -g -O0 -D__STDC_FORMAT_MACROS -fPIC -std=c++11
#CXXFLAGS = -O0 -g -pg -pipe -fPIC -W -DTEST -DDEBUG -Wwrite-strings -Wpointer-arith -Wreorder -Wredundant-decls -Wformat -Wall -Wno-unused-parameter -D_GNU_SOURCE -D__STDC_FORMAT_MACROS -std=c++11 -Wno-redundant-decls
CXXFLAGS = -O2 -g -fPIC -W -DTEST -DDEBUG -Wwrite-strings -Wpointer-arith -Wreorder -Wredundant-decls -Wformat -Wall -Wno-unused-parameter -D_GNU_SOURCE -D__STDC_FORMAT_MACROS -std=c++11 -Wno-redundant-decls

OBJECT = mjson
OUTPUT = ./output
INCLUDE_PATH = -I./include
LIBS = -lpthread

LIBRARY = libmjson.a

.PHONY: all clean


BASE_OBJS := $(wildcard src/*.cc)
BASE_OBJS += $(wildcard src/*.c)
BASE_OBJS += $(wildcard src/*.cpp)
OBJS = $(patsubst %.cc,%.o,$(BASE_OBJS))

all: $(LIBRARY)
	@echo "Success, go, go, go..."


$(LIBRARY): $(OBJS)
	rm -rf $(OUTPUT)
	mkdir $(OUTPUT)
	mkdir $(OUTPUT)/include
	mkdir $(OUTPUT)/lib
	rm -rf $@
	ar -rcs $@ $(OBJS)
	cp -rf ./include/*.h $(OUTPUT)/include
	cp ./libmjson.a $(OUTPUT)/lib/
	make -C ./example

$(OBJECT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJS): %.o : %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< -o $@ 

$(TOBJS): %.o : %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c $< $(INCLUDE_PATH) -o $@ 

clean: 
	rm -rf ./*.o
	rm -rf ./src/*.o
	rm -rf $(OUTPUT)
	rm -rf $(LIBRARY)
	rm -rf $(OBJECT)
	rm -rf ./libmjson.a
	make clean -C ./example

