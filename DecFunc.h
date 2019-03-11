#pragma once
#include <string>
#include <vector>
#include "Function.h"
#include "Type.h"
#include "Parameter.h" 
using namespace std;



class DecFunc : public Function{
   public:
      DecFunc(string oneName, string oneType) : name(oneName){returnType = new Type(oneType); }
      ~DecFunc();
      void addParameter(Parameter* param);
      
      virtual void generateCode(ofstream& o){

      }

      
    protected:
       string name;
       Type* returnType;
       vector<Parameter*> params;
};