CXX := g++
RTTIFLAG := -fno-rtti
LLVMCONFIG := ~/llvm60/bin/llvm-config

CXXFLAGS := -I$(shell $(LLVMCONFIG) --src-root)/tools/clang/include -I$(shell $(LLVMCONFIG) --obj-root)/tools/clang/include $(shell $(LLVMCONFIG) --cxxflags) $(RTTIFLAG)
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

t01:
	~/llvm60/bin/clang++ -Xclang -ast-dump -fsyntax-only t01.cpp
t02:
	~/llvm60/bin/clang++ -Xclang -ast-dump -fsyntax-only t02.cpp
