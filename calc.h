//#include "dataStruc.h"
namespace __stdin__{int parse();};



namespace CALC_STACK{
	List <Obj*> *exp;
	List <char*> *opcode;
	List <char*>*end_opcode;
	List <Obj *> *end_exp;
	bool new_scope=true;
	bool NEW_SCOPE=true;

	//int scope_tracker=0;

	Obj* pop_exp();
	void push_exp(Obj*);
	char pop_opcode();

	int opcode_prec(char c) {

	    if(c == '^')
	        return 5;
	    else if(c == '*' || c == '/')
	        return 4;
	    else if(c == '+' || c == '-')
	        return 3;
	     else if(c=='<' || c=='>')
	    	return 2;
	    else if(c=='(')
	    	return 1;
	    else if(c=='=')
	    	return 0;
	    else
	        return -1;
	};

	void reset(){
		//delete exp;
		//delete opcode;
		exp=new List<Obj*>();
		opcode=new  List<char*>();
		end_exp=exp;
		end_opcode=opcode;

		//scope_tracker=0;
	}
	void clear(){
		/*if(exp!=NULL && opcode!=NULL){
			delete exp;
			delete opcode;
		};*/
		if(exp!=NULL && opcode!=NULL){
			delete opcode;
			for(List <Obj*>*i=exp;i!=NULL;){
				//std::cout<<"Normal delete\n";
				if(i->data!=NULL &&( i->data->type==_DICT_ || i->data->type==_FUNC_|| i->data->type==_VAR_)){
					//std::cout<<"Dick delete\n";
					std::cout<<"-----------------Tracker:"<<i->data->getTracker()<<"\n";
					if(i->data->getTracker()!=0){
						i->data=NULL;
					}
				}
				i=i->selfDestruct();
				std::cout<<"---------------Tracker end\n";
			}
		}
		

		exp=NULL;
		opcode=NULL;
	}

	bool validate(){
		//halka err xa with = oper
		//if(exp==end_exp && *end_opcode->data=='\n') return true;
		if(end_opcode!=opcode){
			//std::cout<<"operssss: "<<*end_opcode->data<<"\n";
			if(end_opcode->prev==opcode){
				std::cout<<"[!]waht\n";
				if(end_exp==exp){
					std::cout<<"[!]waht122\n";
				}
			}
		};
		if(exp==end_exp->prev){
		std::cout<<"afafsafsaf\n";

		}
		if(exp==end_exp && end_opcode==opcode)return true;
		if(exp==end_exp->prev && end_opcode->prev==opcode ) return true;
		//if(end_exp->prev==NULL)return false;
		
		return false;
	}



	char pop_opcode(){
		if(end_opcode->prev==NULL){return 0;};
		end_opcode=end_opcode->prev;
		return *(end_opcode->data);


	}


	void push_opcode(char c){
		//new_scope=true;
		if(end_exp==exp && c=='\n'){;return;}

		char op;
		Obj* n;
		if(c=='(')NEW_SCOPE=true;
		if(c=='('||c=='='){new_scope=true;goto push;};
	//if(!is_unary_oper(c)){new_scope=true;};
		if(c==')'){
			//NEW_SCOPE=false;
			while(end_opcode->prev!=NULL){
				op=pop_opcode();
				if(op=='(')break;
				//clacl wala code;
				/*calc(pop_exp(),op,pop_exp())
				std::cout<<pop_exp();
				std::cout<<op;
				std::cout<<pop_exp();
				*/

				n=calc(pop_exp(),op,pop_exp());
				//if(n==NULL){return;};
				//std::cout<<"[//*]"<<*(int*)n->data<<"\n";
				push_exp(n);
				
				
			};
			//std::cout<<"\n[*]arthemetic err!";
			//end_opcode=end_opcode->next;
			return;
		}

		if(end_opcode->prev!=NULL){
				//if( opcode_prec(c)<=opcode_prec(*end_opcode->prev->data)){
					//std::cout<<*end_opcode->prev->data<<"\n";
				while(end_opcode->prev!=NULL&&opcode_prec(c)<=opcode_prec(*end_opcode->prev->data)){
					
					
					if(*end_opcode->prev->data=='(')break;
					op=pop_opcode();
					//if(op=='(')break;
					//calc wala code();
					/*std::cout<<pop_exp();
					std::cout<<op;
					std::cout<<pop_exp();
					push_exp(9);
					*/
					
					n=calc(pop_exp(),op,pop_exp());
					if(n==NULL){return;};
					//std::cout<<"[//*]"<<*(int*)n->data<<"\n";
					push_exp(n);
					
				}
			

		};

		push:
		if(end_opcode->data!=NULL)delete end_opcode->data;
		end_opcode->data=new char(c);
		if(end_opcode->next==NULL){
			end_opcode=end_opcode->setNext(NULL);
		}else{
			end_opcode=end_opcode->next;
		}

		//std::cout<<"[+]pushed: "<<*end_opcode->prev->data;
	}
	

	void push_exp(Obj* a){
		NEW_SCOPE=false;
		
		//if(end_exp->data!=NULL)delete end_exp->data; ...... LHS Mai append vako xa so garnu parden;
		if((end_exp->prev==NULL|| new_scope) ){
			char c=pop_opcode();
			if(c==0 || c=='('||c=='='){
				push_opcode(c);
			}else if(is_unary_oper(c)){
				a->__comp__(c);
				std::cout<<"here\n";
			
			}else{
				//std::cout<<"[*]Err expexted uniry operator: "<<c<<"\n";
				Error.msg= "is not a unirary operator!";
				Error.status=true;
				return;
			}


		}
		new_scope=false;
		NEW_SCOPE=false;

		end_exp->data=a;
		if(end_exp->next==NULL){
			end_exp=end_exp->setNext(NULL);
		}else{
			end_exp=end_exp->next;
		}
	}

	Obj* pop_exp(){
		if(end_exp->prev==NULL){return 0;};
		end_exp=end_exp->prev;
		return (end_exp->data);


	}

	void print_exp(){
		for(List <Obj *> *o=exp;o!=NULL;o=o->next){
			if(o->data==NULL){
				std::cout<<"[?*]NULL\n";
			}else{
				std::cout<<"[?*]";
				o->data->__print__();
			}
		}
	}
}



namespace SCOPE_STACK{

	KeyWord_Node head;                            
	KeyWord_Node *end=&head;
	//HELPER::SCOPE_STACK_END=end;
	KeyWord_Node *end_static=end;
	//HELPER::SCOPE_STACK_END=end;
	void push(void (*func)(void)){
		if(end->next==NULL){
			end->next=new KeyWord_Node;
			end->next->prev=end;	
		};
		end=end->next;
		end->func=func;
		end->status=-1;

		end_static=end;
		HELPER::SCOPE_STACK_END=end;

	};

	void pop(){
		if(end!=&head){
			end=end->prev;
			HELPER::SCOPE_STACK_END=end;
		}
	}

	void setObj(Obj *o){
		end->obj=o;
	}
	void* getObj(){
		void* temp=end->obj;
		end->obj=NULL;
		return temp;

	}
	void exectue(){

	};

	void clear(){
		for(;end_static!=end;){
			end_static=end_static->prev;
			delete end_static->next;
		};
		

	};

	void clearAll(){
		for(;end_static!=&head;){
			end_static=end_static->prev;
			if(end_static->next->obj!=NULL)delete (Obj*)end_static->next->obj;
			delete end_static->next;
		};


	}
}



//Dict<Obj *> VAR_db;
/*
namespace BYTE_CODE{
	Code_Node main;
	Code_Node *main_end=main;

	void clear(){
		Code_Node*temp=NULL;
		for(Code_Node*i=main->next;i!=NULL;){
			temp=i;
			if(i->obj1!=NULL)delete i->obj1;
			if(i->obj2!=NULL)delete i->obj2;
			if(i->obj3!=NULL)delete i->obj3;
			i=i->next;
			delete temp;
		}
		
	};
	void insert_main(Code_Node *n){
		main_end->next=n;
		main_end=main_end->next;
	}
}
*/