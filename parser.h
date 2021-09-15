#include <stdio.h>




#define buffer_size 1024

Func MAIN;


namespace __stdin__{
	#define __STRING__ LOCATION[0]
	#define __NUMBER__ LOCATION[1]
	#define __ERR__ LOCATION[2]
	#define __END__ LOCATION[3]
	#define __LOOP__ LOCATION[4]
	#define __TOKEN__ LOCATION[5]
	#define __DICK__ LOCATION[7]

	static void *LOCATION[6];

	void* ignore(char*);
	void* make_string(char*);
	void* make_number(char*);
	void *token_create(char*);
	void *make_dick(char*);
	//void* make_var(char*);
	//void*key_check(std::string token,void**);

	void IF();
	void WHILE();
	void FUNC();
	void FUNC_EXC();
	void DICK();

	

	char ch[2]={'\0'};
	unsigned int i=0;

	char input_buffer[buffer_size];
	bool end=false;

	int parse();

	void get_cli_input(FILE *f){
		CALC_STACK::reset();
		printf("Welcome to lang :)\n");
		__start__:
		//if(f==stdin)printf(">>");
		if(f==stdin)std::cout<<CONFIG::PROMPT;

		while(true){
			i=0;
			input_buffer[buffer_size-2]='\0';
			//handel ctrl+d(infinit loop) done;
			if(fgets(input_buffer,buffer_size,f)==NULL){break;};

			parse();
			//printf("%s\n",input_buffer);
			
			if(input_buffer[buffer_size-2]=='\0' ||input_buffer[buffer_size-2]=='\n'){
				goto __start__;
			}
			
		};

	}

	int parse(){
		LOCATION[0]= &&__string__;
		LOCATION[1]= &&__number__;
		LOCATION[2]= &&__err__;
		LOCATION[3]= &&__end__;
		LOCATION[4]= &&__loop__;
		LOCATION[5]=&&__token__;
		LOCATION[7]=&&__dick__;

		Obj obj;
		char o;
		
		Error.status=false;

		//ingonoring whitespases
		__ignore__:
			goto *ignore(input_buffer);
		__string__:
			goto *make_string(input_buffer);
		__number__:
			goto *make_number(input_buffer);
		__dick__:
			goto *make_dick(input_buffer);
		__token__:
			goto *token_create(input_buffer);

		

		
		__loop__:
			
			if(Error.status)goto __err__;
			goto __ignore__;
		__err__:
			std::cout<<"[-]Err: "<<Error.msg<<"\n";
			
			CALC_STACK::clear();
			//std::cout<<"exit\n";
			 exit(0);

		__end__:
			//print ans;
		if(SCOPE_STACK::end->func==&DICK || SCOPE_STACK::end->func==&FUNC|| SCOPE_STACK::end->func==&FUNC_EXC || SCOPE_STACK::end->func==&IF){
			std::cout<<"[--+--]m here!!!\n";
			//CALC_STACK::print_exp();
			if(SCOPE_STACK::end->obj!=NULL)((Obj*)SCOPE_STACK::end->obj)->__print__();
			SCOPE_STACK::end->func();
			std::cout<<"[-]Continue....\n";
			CALC_STACK::print_exp();
			if(SCOPE_STACK::end->func==NULL){CONFIG::PROMPT=CONFIG::stdin;return 0;};
			CONFIG::PROMPT=CONFIG::scope;
			return 0;
			
		}
		CONFIG::PROMPT=CONFIG::stdin;
		std::cout<<"[--ewqewqe+--]m here!!!\n";
		CALC_STACK::push_opcode('\n');
			
			if(CALC_STACK::validate()){
				//err empty field i.E '\n'->olny valid err nee fix fucker;
				if(SCOPE_STACK::end->func==NULL){
					if(CALC_STACK::exp->data!=NULL)
					CALC_STACK::exp->data->__print__();
				}else{
					
					Error.status=false;
					
					SCOPE_STACK::end->func();
					CALC_STACK::clear();
					CALC_STACK::reset();
					goto __loop__;
					
				}
				
				std::cout<<"[+]ALL DONE\n";
			}else{
				std::cout<<"[-]ERR calc err\n";
				SCOPE_STACK::clearAll();
			}
			CALC_STACK::clear();
			CALC_STACK::reset();

		return 0;
	}


	void* ignore(char *str){
		char c[3]={'\0'};
		for (;;i++)
		{	
			if(str[i]=='{'){
				if(i==0 || str[i-1]!=')'){

					return __DICK__;
				}
				if(SCOPE_STACK::end->func==FUNC ){
					SCOPE_STACK::end->func();
					continue;
				}
				//std::cout<<"WHY\n";
				i++;return __END__;};
			if(str[i]=='}' || str[i]==',' || str[i]==':'){
				if(SCOPE_STACK::end->func==DICK || SCOPE_STACK::end->func==FUNC|| SCOPE_STACK::end->func== FUNC_EXC){
					//DICK();
					SCOPE_STACK::end->func();
					continue;
				}
				//std::cout<<"[*]CALLED FOR IGNOE\n";
				return __END__;
			}
			/*if(str[i]=='['){
				return __DICK__;
			}*/

			if((str[i]>'#' && str[i]<'0')||(str[i]>='<'&&str[i]<='>')||str[i]=='!'){
				CALC_STACK::push_opcode(str[i]);
				i++;
				return __LOOP__;
				continue;
			}

			if(str[i]=='\n' || str[i]=='\0'){return __END__;}
			//edit point
			if(str[i]!=' ' && str[i]!='\t' &&str[i]!=','){break;}
		}

		return __STRING__;
	};
	
	void* make_string(char *str){
		std::string token;
		if(str[i]!='"'){return __NUMBER__;};
		for(i++;;i++){

			if(str[i]=='"'){i++;break;};
			if(str[i]=='\n'){return __ERR__;}
			ch[0]=str[i];
			token.append(ch);
		}
		//assign o;
		//std::cout<<token<<"\n";
		CALC_STACK::push_exp(new String(token));
		return __LOOP__;

	}

	void *make_number(char *str){
		int in=0;
		float f=0;
		int j=i;
		//int;
		for (;; ++i){
			if(str[i]=='.'){goto __FLOAT__;};
			if(str[i]==' ' || str[i]=='\n'|| str[i]=='\0'){break;}
			if(is_oper(str[i])){break;};
			if(str[i]>'9' || str[i]<'0'){
				if(in==0)return __TOKEN__;
				std::cout<<"[-] "<<str[i]<<" not a number"<<"\n";
				return  __ERR__;
			}
			
			in=in*10+(str[i]-'0');
			
		}
		
		std::cout<<in<<"\n";
		CALC_STACK::push_exp(new Number(in));
		return __LOOP__;

		__FLOAT__:
			f=in;
			j=i;
			for (i++; ; ++i)
			{
				if(str[i]=='.'){
					std::cout<<"[-]more then one .\n";
					return __ERR__;
				}
				if(str[i]==' ' || str[i]=='\n'|| str[i]=='\0'){break;}
				if(is_oper(str[i])){break;};
				if(str[i]>'9' || str[i]<'0'){

					std::cout<<"[-] "<<str[i]<<" not a number"<<"\n";
					return __ERR__;
				}
				f+=(str[i]-'0')/pow(10,(i-j));
			}
		
		std::cout<<f<<"\n";
		CALC_STACK::push_exp(new Float(f));
		return __LOOP__;
	}

	void *make_dick(char *s){
		SCOPE_STACK::push(&DICK);
		SCOPE_STACK::end->obj=new Dict_t();

		SCOPE_STACK::end->status=0;

		CALC_STACK::push_opcode('(');
		CALC_STACK::print_exp();
		i++;
		return __LOOP__;
	}


	void *token_create(char*s){
		//void*par[]={&&end,&&var};
		char ch[2]={'\0','\0'};
		std::string token="";
		std::string temp_token="";
		Obj*temp_obj;

		for(char *c=s+i;*c!='\n';c=c+1){
			if(*c=='.' && token.length()!=0){i++;goto wtf;};
			if((*c<'a'||*c>'z')&&(*c<'0'||*c>'9')){
					//return __LOOP__;
					break;
			}
			
			*ch=*c;
			token.append(ch);
			i++;
		};
		goto __token_check__;

		wtf:
		 temp_token="";
		temp_obj=VAR_db.get(token);
		//std::cout<<token<<" "<<token.length()<<" m here\n";

		for(char *c=s+i;;c=c+1){
			if((*c<'a'||*c>'z')&&(*c<'0'||*c>'9')){
				if(*c==' ' || *c=='\t' ||*c=='\n' || *c=='.'){
					if(temp_obj!=NULL && temp_obj->get_type()==_DICT_){
						std::cout<<"fumk m hrerenn\n";
						//Obj*temp_oobj=
						((Dict_t*)temp_obj)->getKey(temp_token);
						std::cout<<"omgooomg'\n";
						if(*c=='.'){
							temp_token="";
							temp_obj=((Dict_t*)temp_obj)->getTempObj();
							i++;
							continue;
						}
						//CALC_STACK::push_exp(copy_obj(temp_obj));// needs fix;
						CALC_STACK::push_exp(new Ptr(temp_obj,temp_token));
						std::cout<<"omgooomg 3'\n";
						return __LOOP__;
					}else{
						//error;
					}
					return __LOOP__;
				}else{
					//err;
				}
			}

			*ch=*c;
			temp_token.append(ch);
			i++;

		}

		__token_check__:

		if(token.length()==0)return __LOOP__;
		//reserver check

		if(token=="if"){
			SCOPE_STACK::push(&IF);
			std::cout<<"heheLOL\n";
			CALC_STACK::push_opcode('(');
			i++;
			goto end;
		}else if(token=="while"){
			SCOPE_STACK::push(&WHILE);
			SCOPE_STACK::end->location==i;
			goto end;
		}else if(token=="fn"){
			SCOPE_STACK::push(&FUNC);
			SCOPE_STACK::setObj(new Func());
			CALC_STACK::push_opcode('(');
			std::cout<<"heheLOL123-----\n";
			FUNC();
			goto end;
		}
		std::cout<<"idk----------------- "<<*(s+i)<<"\n";
		if(*(s+i)=='('){
			SCOPE_STACK::push(&FUNC_EXC);
			SCOPE_STACK::setObj(new Var(token));

			CALC_STACK::push_opcode('(');
			i++;

			goto end;
		}
		//var
		CALC_STACK::push_exp(new Var(token));

		end:
			return __LOOP__;
		
	}

	void DICK(){
		std::cout<<"[**]DICK executed\n";
		char *str=input_buffer;
		Dict_t *obj=(Dict_t*)SCOPE_STACK::end->obj;
		//std::cout<<"bsdk\n";
		//CALC_STACK::print_exp();


		if(str[i]==':'){
			if(SCOPE_STACK::end->status==0){
				CALC_STACK::push_opcode(')');
				obj->setKey(CALC_STACK::end_exp->prev->data);
				//CALC_STACK::end_exp->prev->data=NULL;
				CALC_STACK::pop_exp();	
				CALC_STACK::push_opcode('(');
				SCOPE_STACK::end->status=1;
			}
			//error
		};

		if(str[i]==','){
			CALC_STACK::push_opcode(')');
			CALC_STACK::print_exp();
			CALC_STACK::end_exp->prev->data->__print__();
			if(SCOPE_STACK::end->status==1){
				obj->setValue(CALC_STACK::end_exp->prev->data);
			}else{
				obj->insert(CALC_STACK::end_exp->prev->data);
			};
			//CALC_STACK::end_exp->prev->data=NULL;
			CALC_STACK::pop_exp();
			CALC_STACK::push_opcode('(');
			SCOPE_STACK::end->status=0;
			//i++;

		}
		if(str[i]=='}'){
			CALC_STACK::push_opcode(')');
			std::cout<<"[*]this is inside dict value\n";
			if(CALC_STACK::end_exp->data==NULL){
				std::cout<<"[*]wtfffffffff\n";
			}
			CALC_STACK::print_exp();
			CALC_STACK::end_exp->prev->data->__print__();
			if(SCOPE_STACK::end->status==1){
				obj->setValue(CALC_STACK::end_exp->prev->data);
			}else{
				obj->insert(CALC_STACK::end_exp->prev->data);
			};
			
			//obj->insert(CALC_STACK::end_exp->prev->data);
			//CALC_STACK::end_exp->prev->data=NULL;
			CALC_STACK::pop_exp();
			CALC_STACK::push_exp((Obj*)SCOPE_STACK::end->obj);
			std::cout<<"[*]this is stacedk push value\n";
			((Obj*)SCOPE_STACK::end->obj)->__print__();
			SCOPE_STACK::end->obj=NULL;
			SCOPE_STACK::pop();
			//i++;

		}
		/*
		CALC_STACK::end_exp->data->__print__();
		std::cout<<"wy no\n";
		obj->insert(CALC_STACK::end_exp->data);
		CALC_STACK::exp->data=NULL;
		CALC_STACK::pop_exp();
		*/


	}

	void IF(){
		std::cout<<"[**]IF executed\n";
		char *str=input_buffer;
		KeyWord_Node *data=SCOPE_STACK::end;

		if(data->status==-1){
			if(CALC_STACK::end_opcode->data==NULL){return;};
			if(*CALC_STACK::end_opcode->data=='(' && CALC_STACK::end_opcode->prev==NULL){
				if(CALC_STACK::NEW_SCOPE){
					CALC_STACK::pop_opcode();
					CALC_STACK::NEW_SCOPE=false;
					std::cout<<"[-]ERR: PLZ INCLUDE SOMETING\n";	
				}else{
					//CALC_STACK::push_opcode(')');
					data->status=Bool(CALC_STACK::end_exp->prev->data);
					
				/*	Obj * temp=CALC_STACK::end_exp->prev->data;
					if(temp->get_type()!=_RGX_){
						registerCode(VM::PUSH,temp);
					};

					end=new Code_Node();
					end->opcode=VM::CMP;
					end->obj1=end->next;
					registerCode(VM::CMP,VM::NEXT,VM::THIS);
				*/
					CALC_STACK::pop_exp();
					if(*(str+i+1)=='{'){i=i+2;}
					CALC_STACK::clear();
					CALC_STACK::reset();
					//CODE::end->next=new VM::Code_Node();
					//CODE::registerCode(VM::CMP,CODE::NEXT,NULL);
					//std::cout<<int(data->status)<<" dsdsad "<<str[i]<<"\n";
					SCOPE_STACK::pop();
					
			}
			/*data->status=Bool(CALC_STACK::exp->data);
			if(data->status==0)goto b;
			std::cout<<"[**]From tru/flase assign\n";
			*/
			return;
			}
		};

		//if()
		if(data->status==1){
			if(str[i]=='}') goto c;
			std::cout<<"[**]From true assign\n";
			return;
		}

		b:

		if(data->status==0){
			std::cout<<"[**]From False assign\n";
			for(;str[i]!='\n';i++){
				if(str[i]=='}'){
					goto c;
				}
			}
			return;
		}

		c:
		char tok[]="\0\0\0\0";
		int j=0;
		char *ch=str+i;
		while(true){
			if(*ch=='\n' || j==4)break;
			ch=ch+1;
			tok[j]=*ch;
			j++;

		}
		if(strcmp(tok,"else")==0){
			data->status=!data->status;
			i=i+4;
			return;
		}
		std::cout<<"[**]IF popoed\n";
		SCOPE_STACK::pop();

	}

	void WHILE(){
		char *str=input_buffer;
		KeyWord_Node *data=SCOPE_STACK::end;
		if(data->status==-1){
			data->status=Bool(CALC_STACK::exp->data);
			if(data->status==0)goto c;
			std::cout<<"[**]From tru/flase assign\n";
			return;
		};

		if(data->status==1){
			if(str[i]=='}'){
				std::cout<<"[**+++] VALUE OF VSAR:\n";
				VAR_db.get("a")->__print__();
				data->status=-1;
				i=data->location+5;
				std::cout<<"**"<<str[i]<<"\n";
				
			} ;
			std::cout<<"[**]From true assign\n";
			return;
		}
		c:
		if(data->status==0){
			std::cout<<"[**]From False assign\n";
			for(;str[i]!='\n';i++){
				if(str[i]=='}'){
					std::cout<<"[**]While popoed\n";
					SCOPE_STACK::pop();
					i++;
					return;
					//goto c;
				}
			}
			return;
		};

	}

	void FUNC(){
		std::cout<<"[!1]Func\n";
		char *str=input_buffer+i;
		Func* obj=(Func*)SCOPE_STACK::end->obj;
		if(SCOPE_STACK::end->status==-1){
			//push data into 
			if(*str==','){
				//for all in clac stach.... register parms;
				// store str untill };
				CALC_STACK::push_opcode(')');
				CALC_STACK::end_exp->prev->data->__print__();
				obj->registerParms(CALC_STACK::end_exp->prev->data);
				CALC_STACK::pop_exp();
				CALC_STACK::push_opcode('(');
			};
			//yo kam gardena;
			if(*str=='{'){
				std::cout<<"[**]from insede {{{{\n";
				obj->registerParms(CALC_STACK::end_exp->prev->data);
				CALC_STACK::push_opcode(')');
				CALC_STACK::pop_exp();
				CALC_STACK::push_opcode('(');
				//CALC_STACK::push_opcode('\n');
				
				SCOPE_STACK::end->status=1;
				if(*str+1=='{'){i+=2;str=str+2;}
				return;
			}

			std::cout<<"[**]From parms assign\n";
			return;
		};
		
		__body__:
		std::cout<<"[**]from insede body  \n";
		obj->print_parms();
		//SCOPE_STACK::pop();
		if(SCOPE_STACK::end->status==1){
			if(*str=='\n' || *str=='\0'){
				std::cout<<"here\n";
				if(CALC_STACK::NEW_SCOPE)return;
				
				CALC_STACK::push_opcode(')');

				CALC_STACK::push_opcode('(');
				CALC_STACK::pop_exp();
				CALC_STACK::print_exp();
				return;
			}
			if(*str=='}'){
				if(CALC_STACK::NEW_SCOPE){
					CALC_STACK::pop_opcode();
					CALC_STACK::NEW_SCOPE=false;	
				}else{
					CALC_STACK::push_opcode(')');
					CALC_STACK::pop_exp();
				}
				//CALC_STACK::push_opcode(')');
				std::cout<<"poping\n";
				//std::cout<<"__________Type::"<<CALC_STACK::end_exp->prev->data->get_type()<<"\n";
				//CALC_STACK::pop_exp();
				CALC_STACK::push_exp((Obj*)SCOPE_STACK::end->obj);
				((Obj*)SCOPE_STACK::end->obj)->__print__();
				CALC_STACK::print_exp();
				obj->print_code();
				SCOPE_STACK::end->obj=NULL;
				SCOPE_STACK::pop();
			}
		}
		
		

	}

	void FUNC_EXC(){
		std::cout<<"[!1]Func EXC\n";
		char *str=input_buffer+i;
		Var* func=(Var*)SCOPE_STACK::end->obj;
		//Dict_t* obj=(Dict_t*)SCOPE_STACK::end->obj;
		Dict_t* obj=(Dict_t*)TEMP;
		if(SCOPE_STACK::end->status==-1){
			TEMP=new Dict_t();
			SCOPE_STACK::end->status=0;
			obj=(Dict_t*)TEMP;
		}
		if(SCOPE_STACK::end->status==0){
			//push data into 
			if(*str==','){
				std::cout<<"wtf m anisd theere sffdsifhdslkfjdlsf\n";
				//for all in clac stach.... register parms;
				// store str untill };
				CALC_STACK::push_opcode(')');
				CALC_STACK::end_exp->prev->data->__print__();
				obj->insert(CALC_STACK::end_exp->prev->data);
				CALC_STACK::pop_exp();
				CALC_STACK::push_opcode('(');
				return;
			};
			
			if(CALC_STACK::end_opcode->data==NULL){return;};
			if(*CALC_STACK::end_opcode->data=='(' && CALC_STACK::end_opcode->prev==NULL){
				
				if(CALC_STACK::NEW_SCOPE){
					CALC_STACK::pop_opcode();
					CALC_STACK::NEW_SCOPE=false;	
				}else{
					//CALC_STACK::push_opcode(')')
					obj->insert(CALC_STACK::end_exp->prev->data);
					CALC_STACK::pop_exp();
					SCOPE_STACK::end->obj=NULL;
					
				}
				Obj* f=func->getObj();
				if(f==NULL || f->get_type()!=_FUNC_){
					std::cout<<"[-]THe varaible is not Functon\n";
					SCOPE_STACK::pop();
					return;
				}
				((Func*)f)->print_parms();
				((Func*)f)->print_code();
				((Func*)f)->run(obj);
				delete obj;
				SCOPE_STACK::pop();
				std::cout<<"--------end\n";

				
			}
			std::cout<<"wewewewe\n";
		}

		
	}
	

}


