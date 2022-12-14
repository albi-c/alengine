LIB = libalengine.a

DEBUG = true

ifeq ($(DEBUG), true)
	OPTIM_FLAG =
	DEBUG_FLAG = -g
	OBJDIR = build/debug
endif
ifneq ($(DEBUG), true)
	OPTIM_FLAG = -O3
	DEBUG_FLAG =
	OBJDIR = build/release
endif

INCLUDES = -I./lib -I./alengine

CXX       = g++
CXXSTD    = c++20
CXXOPT   := $(OPTIM_FLAG) $(DEBUG_FLAG) $(INCLUDES)
CXXFLAGS := $(CXXOPT) -std=$(CXXSTD)

CC       = gcc
CCSTD    = c2x
CCOPT   := $(OPTIM_FLAG) $(DEBUG_FLAG) $(INCLUDES)
CCFLAGS := $(CCOPT) -std=$(CCSTD)

LFLAGS = $(CXXOPT) -lGL -lglfw -ldl -pthread -lm -lstdc++

SOURCES  := $(shell find alengine/ -type f -name '*.cpp')
OBJECTS  := $(patsubst alengine/%.cpp, $(OBJDIR)/alengine/%.o, $(SOURCES))
CSOURCES := $(shell find alengine/ -type f -name '*.c')
COBJECTS := $(patsubst alengine/%.c, $(OBJDIR)/alengine/%.o, $(CSOURCES))

LIB_SOURCES  := $(shell find lib/ -type f -name '*.cpp')
LIB_OBJECTS  := $(patsubst lib/%.cpp, $(OBJDIR)/lib/%.o, $(LIB_SOURCES))
LIB_CSOURCES := $(shell find lib/ -type f -name '*.c')
LIB_COBJECTS := $(patsubst lib/%.c, $(OBJDIR)/lib/%.o, $(LIB_CSOURCES))

$(LIB): $(OBJECTS) $(COBJECTS) $(LIB_OBJECTS) $(LIB_COBJECTS)
	ar rcs $@ $^

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(LIB) $(OBJECTS) $(COBJECTS)

.PHONY: clean_libs
clean_libs:
	rm -f $(LIB_OBJECTS) $(LIB_COBJECTS)
