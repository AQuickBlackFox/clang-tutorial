/*
Check for global constants
*/
#include <iostream>
#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;

class MyASTVisitor: public RecursiveASTVisitor<MyASTVisitor> {
public:
    MyASTVisitor(Rewriter &R) : TheRewriter(R) {}

    bool VisitFunctionDecl(FunctionDecl *f){
        if(f->hasBody()){
            llvm::errs()<<"Found a body: "<<f->getNameInfo().getName()<<"\n";
                                                f->dump();
        }
        return true;
    }

    bool VisitStmt(Stmt *s){
        if(isa<Expr>(s)){
            llvm::errs()<<"Expr"<<"\n";
        }
        return true;
    }

    bool VisitVarDecl(VarDecl *D)
    {
        if(D->hasGlobalStorage()){
            ValueDecl *vd = D;
            llvm::errs()<<vd->getType().getAsString()<<"\n";
            VarDecl *vad = D;
            llvm::errs()<<vad->evaluateValue()->getInt()<<"\n";
            NamedDecl *nd = D;
            llvm::errs()<<nd->getNameAsString()<<"\n";
            llvm::errs()<<"Found global"<<"\n";
        }
        return true;
    }

private:
    Rewriter &TheRewriter;
};

class MyASTConsumer : public ASTConsumer {
public:
    MyASTConsumer(Rewriter &R) : Visitor(R){}

    bool HandleTopLevelDecl(DeclGroupRef DR) override {
        for(DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b!=e; ++b){
            Visitor.TraverseDecl(*b);
//            (*b)->dump();
        }
        return true;
    }
private:
    MyASTVisitor Visitor;
};

class MyFrontendAction : public ASTFrontendAction {
public:
    MyFrontendAction() {}
    void EndSourceFileAction() override {
      SourceManager &SM = TheRewriter.getSourceMgr();
    }

    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                    StringRef file) override {
        llvm::errs() << "** Creating AST consumer for: "<<file<<"\n";
        TheRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
        return llvm::make_unique<MyASTConsumer>(TheRewriter);
    }
private:
    Rewriter TheRewriter;
};

int main(int argc, const char **argv) {
    cl::OptionCategory MyToolCategory("Example1");
    // parse the command-line args passed to your code
    CommonOptionsParser op(argc, argv, MyToolCategory);
    // create a new Clang Tool instance (a LibTooling environment)
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    // run the Clang Tool, creating a new FrontendAction (explained below)
    return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}
