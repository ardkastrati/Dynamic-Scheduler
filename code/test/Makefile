CC := mpic++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := ./
BUILDDIR := build
TARGET := bin/test

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++0x# -Wall
LIB := -lboost_unit_test_framework
INC := -I include

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/scheduler
	@mkdir -p $(BUILDDIR)/worker
	@mkdir -p $(BUILDDIR)/datamining
	@mkdir -p $(BUILDDIR)/datamining/grid
	@mkdir -p $(BUILDDIR)/database
	@mkdir -p $(BUILDDIR)/visualiser
	@mkdir -p $(BUILDDIR)/util
	@echo " $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<


clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

test:
	bin/test