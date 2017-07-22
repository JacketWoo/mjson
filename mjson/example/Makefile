CXX = g++
CXXFLAGS = -pg -g -Wall -Wno-format -g -O0 -std=c++11 -D__XDEBUG__

OBJECT = json_sample

LIB_PATH = -L../output/lib/

LIBS = -lmjson \
	-lpthread

INCLUDE_PATH = -I../output/include/

OBJS = json_sample.o 

.PHONY: all clean

all: $(OBJECT)
	@echo "Success, go, go, go..."

json_sample: json_sample.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDE_PATH) $(LIB_PATH) $(LIBS)

$(OBJS): %.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCLUDE_PATH) 

clean: 
	rm -rf $(OBJECT)
	rm -f $(OBJS)
