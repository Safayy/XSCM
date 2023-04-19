CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic 
CFLAGS = -I/usr/include/jsoncpp -Iinclude
LDFLAGS = -L/usr/lib -ljsoncpp -lncurses

SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin
TARGET = $(BINDIR)/XSCM

SRCEXT = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INCL = -I $(INCDIR)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CXX) $^ -o $(TARGET) $(LDFLAGS)"; $(CXX) $^ -o $(TARGET) $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(shell mkdir -p $(dir $@))
	@echo " $(CXX) $(CXXFLAGS) $(CFLAGS) $(INCL) -c -o $@ $<"; $(CXX) $(CXXFLAGS) $(CFLAGS) $(INCL) -c -o $@ $<

$(BUILDDIR)/test/%_test.o: test/%_test.cpp
	$(shell mkdir -p $(dir $@))
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<
	chmod +x $@

$(BUILDDIR)/test/%_test: $(BUILDDIR)/test/%_test.o $(filter-out $(BUILDDIR)/main.o,$(OBJECTS))
	$(shell mkdir -p $(dir $@))
	$(CXX) $(LDFLAGS) $^ -o $@

test: $(patsubst %.cpp,$(BUILDDIR)/%.o,$(wildcard test/*_test.cpp))
	$(foreach test, $^, echo Running test $(test); bash $(test);)

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET) $(patsubst %.cpp,$(BUILDDIR)/%.o,$(wildcard test/*_test.cpp)) $(patsubst %.cpp,$(BUILDDIR)/test/%,$(wildcard test/*_test.cpp))

run: $(TARGET)
	@clear
	@./$(TARGET)

.PHONY: test clean run