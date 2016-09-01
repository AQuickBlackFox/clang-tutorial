CXX := clang++
RTTIFLAG := -fno-rtti
LLVMCONFIG := /home/aditya/llvm/bin/llvm-config

CXXFLAGS := -I$(shell $(LLVMCONFIG) --includedir) $(shell $(LLVMCONFIG) --cxxflags) $(RTTIFLAG)
LLVMLDFLAGS := $(shell $(LLVMCONFIG) --ldflags --libs )

SOURCES = file.cpp

OBJECTS = $(SOURCES:.cpp=.o)
EXES = $(OBJECTS:.o=)
CLANGLIBS = \
-lclangTooling\
-lclangFrontendTool\
-lclangFrontend\
-lclangDriver\
-lclangSerialization\
-lclangCodeGen\
-lclangParse\
-lclangSema\
-lclangStaticAnalyzerFrontend\
-lclangStaticAnalyzerCheckers\
-lclangStaticAnalyzerCore\
-lclangAnalysis\
-lclangARCMigrate\
-lclangRewrite\
-lclangRewriteFrontend\
-lclangEdit\
-lclangAST\
-lclangLex\
-lclangBasic\
$(shell $(LLVMCONFIG) --libs)\
$(shell $(LLVMCONFIG) --system-libs)\
                -lcurses

all: $(OBJECTS) $(EXES)

%: %.o
	$(CXX) -o $@ $< $(CLANGLIBS) $(LLVMLDFLAGS)

clean:
	rm -f $(EXES) $(OBJECTS) *~

