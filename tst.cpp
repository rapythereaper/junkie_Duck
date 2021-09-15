#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "define.h"
#include "dataStruc.h"
#include "dataType.h"

#include "calc.h"
#include "parser.h"


int main(int argc, char const *argv[]){


	/*CALC_STACK::reset();
	CALC_STACK::push_exp(new Number(1));

	CALC_STACK::push_opcode('+');
	
	CALC_STACK::push_exp(new Number(1));

	CALC_STACK::push_opcode('+');
	CALC_STACK::print();
	CALC_STACK::push_exp(new Number(1));
	CALC_STACK::push_opcode('\n');
	CALC_STACK::clear();
	*/
	

	//std::cout<<*(int*)a->get();
	if(argc==2){
		FILE *f=fopen(argv[1], "r");
		if(f==NULL){
			std::cout<<"[!]ERR: '"<<argv[1]<<"' does not exist\n";
			return 0;
		}
		__stdin__::get_cli_input(f);
	}else{
	__stdin__::get_cli_input(stdin);
	}

/*
	Var a("a");
	Var b("b");
	Number n(123);
	Float s(12.5);
	a.__equal__(&n);
	b.__equal__(&s);
	VAR_db.get("a")->__print__();
	VAR_db.get("b")->__print__();


	char a[]="helloworld\n";
	__stdin__::make_var(a);
	*/



	//delete  e;
	return 0;
	

}



