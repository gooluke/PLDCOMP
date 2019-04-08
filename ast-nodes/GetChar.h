#pragma once
#include <vector>
#include "Statement.h"
#include "Expression.h"
using namespace std;

/*Node which represents a call of function*/

class GetChar : Expr{
	public:
		GetChar(string oneName) : funcName(oneName) { type=Type("char"); }
		virtual ~GetChar();
		int eval (){
			return 0;
		}
		/*Creates the correspondant IR instruction of this node in CFG*/
		string buildIR(CFG* cfg);
      
	protected:
	    string funcName;
};