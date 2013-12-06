OBJ := gpio_output
CLEANOBJ := $(OBJ:%=clean-%)
path = ../GnublinSDK/
include ../GnublinSDK/API-config.mk


.PHONY: $(OBJ)

all: $(OBJ)
$(OBJ): $(path)gnublin.cpp $(path)gnublin.h
	$(CXX) $(CXXFLAGS) -o $@ $@.cpp $(path)gnublin.cpp -I $(path)

clean: $(CLEANOBJ)
$(CLEANOBJ):
	rm -f $(@:clean-%=%)
