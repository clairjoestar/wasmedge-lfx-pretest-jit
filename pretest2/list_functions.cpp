#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/CommandLine.h"

#include <memory>
#include <string>

using namespace llvm;

// Command line option for input file
static cl::opt<std::string> InputFilename(
    cl::Positional,
    cl::desc("<input LLVM IR file>"),
    cl::Required
);

int main(int argc, char **argv) {
    // Parse command line arguments
    cl::ParseCommandLineOptions(argc, argv, "LLVM Function Lister\n");

    // Create LLVM context
    LLVMContext Context;
    SMDiagnostic Err;

    // Parse the LLVM IR file
    std::unique_ptr<Module> M = parseIRFile(InputFilename, Err, Context);

    if (!M) {
        Err.print(argv[0], errs());
        return 1;
    }

    outs() << "Module: " << M->getName() << "\n";
    outs() << "========================================\n";
    outs() << "Functions in this module:\n";
    outs() << "========================================\n\n";

    int funcCount = 0;
    int definedCount = 0;
    int declaredCount = 0;

    // Iterate over all functions in the module
    for (Function &F : *M) {
        funcCount++;
        
        outs() << "Function #" << funcCount << ":\n";
        outs() << "  Name: " << F.getName() << "\n";
        
        // Check if function is a declaration or definition
        if (F.isDeclaration()) {
            outs() << "  Type: Declaration (external)\n";
            declaredCount++;
        } else {
            outs() << "  Type: Definition\n";
            outs() << "  Basic Blocks: " << F.size() << "\n";
            outs() << "  Arguments: " << F.arg_size() << "\n";
            definedCount++;
        }
        
        // Print return type
        outs() << "  Return Type: ";
        F.getReturnType()->print(outs());
        outs() << "\n";
        
        // Print parameter types
        if (F.arg_size() > 0) {
            outs() << "  Parameter Types: ";
            for (auto &Arg : F.args()) {
                Arg.getType()->print(outs());
                outs() << " ";
            }
            outs() << "\n";
        }
        
        outs() << "\n";
    }

    outs() << "========================================\n";
    outs() << "Summary:\n";
    outs() << "  Total Functions: " << funcCount << "\n";
    outs() << "  Defined: " << definedCount << "\n";
    outs() << "  Declared (external): " << declaredCount << "\n";
    outs() << "========================================\n";

    return 0;
}