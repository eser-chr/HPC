CXX := g++
CXXFLAGS := -O3 -Wall -shared -std=c++17 -fPIC `python3 -m pybind11 --includes`
LDFLAGS := `python3-config --extension-suffix`

TARGET := game$(LDFLAGS)
SRCDIR := .
BINDIR := .

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*.o $(TARGET)
