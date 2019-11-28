#include <bits/stdc++.h>
#include "ast.h"
#include "Interpreter.h"
#include "Codegen.h"

using namespace std;

LLVMContext Context;
Module *TheModule = new Module("Metamorphose", Context); // Contains all functions and variables
IRBuilder<> Builder(Context); // helps to generate LLVM IR with helper functions
map <string, AllocaInst*>NamedValues; // keeps track of all the values defined in the current scope like a symbol table
std::vector<std::string> FunArgs;


Function *createFunc(IRBuilder<> &Builder, std::string Name)
{
	std::vector<Type *> Integers(FunArgs.size(), Type::getInt32Ty(Context));
	FunctionType *funcType = llvm::FunctionType::get(Builder.getInt32Ty(),false);
	Function *fooFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, Name, TheModule);
	return fooFunc;
}

void setFuncArgs(Function *fooFunc, std::vector<std::string> FunArgs) 
{
	unsigned Idx = 0;
	Function::arg_iterator AI, AE;
	for (AI = fooFunc->arg_begin(), AE = fooFunc->arg_end(); AI != AE;++AI, ++Idx)
	AI->setName(FunArgs[Idx]);
}

BasicBlock *createBB(Function *fooFunc, std::string Name) 
{
	return BasicBlock::Create(Context, Name, fooFunc);
}

GlobalVariable *createGlob(IRBuilder<> &Builder, std::string Name) 
{
	TheModule->getOrInsertGlobal(Name, Builder.getInt32Ty());
	GlobalVariable *gVar = TheModule->getNamedGlobal(Name);
	gVar->setLinkage(GlobalValue::CommonLinkage);
	gVar->setAlignment(4);
	return gVar;
}

Value *createArith(IRBuilder<> &Builder, Value *L, Value *R) 
{
	return Builder.CreateMul(L, R, "multmp");
}

AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, string VarName, string type) 
{
	
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    cout<<"say it isnt so"<<endl;
    AllocaInst *alloca_instruction = nullptr;
    if (type == "int") 
    {

        alloca_instruction = TmpB.CreateAlloca(Type::getInt32Ty(Context), 0, VarName);
    } 
    else if (type == "boolean") 
    {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt1Ty(Context), 0, VarName);
    }
    return alloca_instruction;
}

Value *LogErrorV(const char *Str) 
{
	cout<<Str;
  	return nullptr;
}

Value *Codegen(struct ASTNode *root)
{
	switch (root->nodetype)
	{
		case INTLITERAL:
			int val;
			val = root->litval;
			return ConstantInt::get(Context, APInt(32, val));
			break;
		
		case BinaryOp:
			Value * a;
			Value * b;
			Value * v;
			a = Codegen(root->binarynode.left);
  			b = Codegen(root->binarynode.right);
  			if(a == 0 || b == 0)
  			{
  				return nullptr;
  			}
  			v = nullptr;
  			switch (root->binarynode.op) 
  			{
  				case ADD:
  					// cout<<"Reached Add Codegen"<<endl;
  					v  =  Builder.CreateAdd(a, b, "addition");
  					// cout<<"DONE"<<endl;
  					return v;
  				case SUB: 
  					v = Builder.CreateSub(a, b, "subtraction");
  					return v;
  			}
  			break;
  		
  		case identifier:
  			v = NamedValues[root->identifier_node];
  			if (!v)
    			LogErrorV("Unknown variable name");
  			return v;

  		case declaration:
			// SingleId *pd;
			// pd = dynamic_cast<SingleId*>(root->declaration_node.right);
			string var;
			var = root->declaration_node.right->identifier_node;
			cout<<"REAHCED";

			Value * init_val;
			init_val = nullptr;
			
			AllocaInst * Alloca;
			Function *TheFunction;
			TheFunction = createFunc(Builder, "foo");
			init_val = ConstantInt::get(Context, APInt(32,0));

			// Alloca =  CreateEntryBlockAlloca(TheFunction,var,"int");
			// return init_val;
			// Builder.CreateStore(init_val, Alloca);
			NamedValues[var] = Alloca;
			return init_val;
	}

}









