EXEC     = test_game
EXECOPTS = 

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

INCLUDES = -I../alengine -I../lib

CXX       = g++
CXXSTD    = c++20
CXXOPT   := $(OPTIM_FLAG) $(DEBUG_FLAG) $(INCLUDES)
CXXFLAGS := $(CXXOPT) -std=$(CXXSTD)

CC       = gcc
CCSTD    = c2x
CCOPT   := $(OPTIM_FLAG) $(DEBUG_FLAG) $(INCLUDES)
CCFLAGS := $(CCOPT) -std=$(CCSTD)

LFLAGS = $(CXXOPT) -lGL -lglfw -ldl -pthread -lm -lstdc++

SOURCES  := $(shell find src/ -type f -name '*.cpp')
OBJECTS  := $(patsubst src/%.cpp, $(OBJDIR)/src/%.o, $(SOURCES))
CSOURCES := $(shell find src/ -type f -name '*.c')
COBJECTS := $(patsubst src/%.c, $(OBJDIR)/src/%.o, $(CSOURCES))

STATIC_LIBS := ../libalengine.a

all: $(EXEC)
	@echo $(RDIRS)

$(EXEC): $(OBJECTS) $(COBJECTS) $(STATIC_LIBS)
	$(CXX) $(LFLAGS) -o $@ $(STATIC_LIBS) $^

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c -o $@ $<

run: $(EXEC)
	./$< $(EXECOPTS)

debug: $(EXEC)
	gdb ./$<

crun:
	@$(MAKE) clean
	@$(MAKE) run
cdebug:
	@$(MAKE) clean
	@$(MAKE) debug

clean:
	rm -f $(EXEC) $(OBJECTS) $(COBJECTS)
	rm -rf $(OBJDIR)
