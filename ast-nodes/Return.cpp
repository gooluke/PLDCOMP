#include "Return.h"

string Return::buildIR(CFG * cfg){
    /*string var = expr->buildIR(cfg);
    Type typeInt("int");
    vector<string> params;
    params.push_back(var);
    cfg->current_bb->add_IRInstr(IRInstr::ret,typeInt,params);*/
	Type returnType = cfg->get_var_type("retValue");
	if(returnType.getText() == "void"){
		if(expr != nullptr){
			cerr << "Error: return of an void function can not have an expression" << endl;
		}else{
			BasicBlock* beforeReturnBB = cfg->current_bb;
			BasicBlock* afterReturnBB = new BasicBlock(cfg, cfg->new_BB_name());
			cfg->add_bb(afterReturnBB);
			afterReturnBB->set_exit_true(beforeReturnBB->get_exit_true());
			afterReturnBB->set_exit_false(beforeReturnBB->get_exit_false());
			beforeReturnBB->set_exit_true(cfg->get_bb_epilog());
			beforeReturnBB->set_exit_false(nullptr);
		}
	}else{
	    string value= expr->buildIR(cfg);
		if(expr != nullptr && returnType.getText() == expr->getType().getText()){
			BasicBlock* beforeReturnBB = cfg->current_bb;
			BasicBlock* afterReturnBB = new BasicBlock(cfg, cfg->new_BB_name());
			cfg->add_bb(afterReturnBB);
			afterReturnBB->set_exit_true(beforeReturnBB->get_exit_true());
			afterReturnBB->set_exit_false(beforeReturnBB->get_exit_false());
			beforeReturnBB->set_exit_true(cfg->get_bb_epilog());
			beforeReturnBB->set_exit_false(nullptr);
			string left = cfg->create_new_tempvar(Type("int64_t"));
			int offset= cfg->get_var_index("retValue");
			vector<string>params1={left,"-"+to_string(-offset)};
			cfg->current_bb->add_IRInstr(IRInstr::ldconst,Type("int64_t"),params1);
			vector<string>params2={left,"!bp",left};
			cfg->current_bb->add_IRInstr(IRInstr::add,Type("int64_t"),params2);
			vector<string> params3={left,value};
			cfg->current_bb->add_IRInstr(IRInstr::wmem,expr->getType(),params3);
			cfg->current_bb = afterReturnBB;
		}else{
			cerr << "Error: The type of return's expression do not correspond the return type of this function" << endl;
		}
	}
    return "";
}
