#pragma once
#include "../ast-nodes/Type.h"
#include <vector>
#include <string>
#include <iostream>
//! The class for one 3-address instruction

using namespace std;

class BasicBlock;
class IRInstr {
    public:
	    /** The instructions themselves -- feel free to subclass instead */
	    typedef enum {
		    ldconst,
		    add,
		    sub,
		    mul,
		    div,
		    mod,
			and_bin,
			ou_ex_bin,
			ou_bin,
		    rmem,
		    wmem,
		    call,
		    copy, 
		    cmp_eq,
		    cmp_neq,
		    cmp_lt,
		    cmp_le,
		    ret
	    } Operation;

	    /**  constructor */
	    //IRInstr(BasicBlock* bb_, Operation op, Type t, string destination = "") : bb(bb_), op(op), t(t), dest(destination){scopeIndex = bb->get_cfg()->get_index();}
	    IRInstr(BasicBlock* bb_, Operation op, Type t, string destination = "");
	    virtual ~IRInstr() {}
	    Operation getOp() { return op; }
	    string getDestination() { return dest; }
		Type getType(){return t;}
	    int getScopeIndex(){return scopeIndex;}
	    
	    /** Actual code generation */
	    virtual void gen_asm(ostream &o) =0; /**< x86 assembly code generation for this IR instruction */
	
    protected:
        string dest;
	    BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	    Operation op;
	    Type t;
	    int scopeIndex;
	    //vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
	    // if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design. 
};

class RetInstr : public IRInstr {
	public:
		RetInstr(BasicBlock* bb_, Type t) : IRInstr(bb_, ret, t) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
};

class LdconstInstr : public IRInstr {
	public:
		LdconstInstr(BasicBlock* bb_, Type t, string destination, string constant) : IRInstr(bb_, ldconst, t, destination), c(constant) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private: 
		string c;
};

class CopyInstr : public IRInstr {
	public:
		CopyInstr(BasicBlock* bb_, Type t, string destination, string source) : IRInstr(bb_, copy, t, destination), s(source) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private: 
		string s;
};

class AddInstr : public IRInstr {
	public:
		AddInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, add, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class SubInstr : public IRInstr {
	public:
		SubInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, sub, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class MulInstr : public IRInstr {
	public:
		MulInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, mul, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class DivInstr : public IRInstr {
	public:
		DivInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, div, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class ModInstr : public IRInstr {
	public:
		ModInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, mod, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class AndBinInstr : public IRInstr {
	public:
		AndBinInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, and_bin, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class OuExBinInstr : public IRInstr {
	public:
		OuExBinInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, ou_ex_bin, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class OuBinInstr : public IRInstr {
	public:
		OuBinInstr(BasicBlock* bb_, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, ou_bin, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class CmpInstr : public IRInstr {
	public:
		CmpInstr(BasicBlock* bb_, Operation op, Type t, string destination, string operand1, string operand2) : IRInstr(bb_, op, t, destination), x(operand1), y(operand2) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string x;
		string y;
};

class CallInstr : public IRInstr {
	public:
		CallInstr(BasicBlock* bb_, Type t, vector<string>& oneParams) : IRInstr(bb_, call, t, oneParams.at(0)){
			label = oneParams.at(1);
			size_t length = oneParams.size();
			for(size_t i = 2; i < length; i++){
				params.push_back(oneParams.at(i));
			}
		}
		const string ParamRegister[6] = {"rdi","rsi","rdx","rcx","r8","r9"};
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string label;
		vector<string> params;
};

class WmemInstr : public IRInstr {
	public:
		WmemInstr(BasicBlock* bb_, Type t, string destination, string valeur) : IRInstr(bb_, wmem, t, destination), val(valeur) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string val;
};

class RmemInstr : public IRInstr {
	public:
		RmemInstr(BasicBlock* bb_, Type t, string destination, string adress) : IRInstr(bb_, rmem, t, destination), ad(adress) {}
		/** Actual code generation */
		virtual void gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */
	private :
		string ad;
};


