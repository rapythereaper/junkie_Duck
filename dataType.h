#include <stdlib.h>
#include <iostream>
#include <cstring>

namespace HELPER{
KeyWord_Node *SCOPE_STACK_END;	
}


enum d_type{

	_NUMBER_,
	_INT_,
	_FLOAT_,
	_STRING_,
	_BOOL_,
	_ARRAY_,
	_DICT_,
	_PTR_,
	_ERR_,
	_VAR_,
	_FUNC_,
	_RGX_

};

class Obj{
public:
	void *data=NULL;
	size_t size=0;
	d_type type;
	u_int tracker=0;
public:
	u_int getTracker(){return tracker;};
	Obj(){};
	virtual ~Obj(){if(data!=NULL)free(data);}
	void* get(){return data;};
	d_type get_type(){return type;};
	int get_size(){return size;};


	friend Obj* calc(Obj *lhs,char ch,Obj *rhs);
	friend char Bool(Obj*o);
	virtual Obj* getObj(){return this;};
	virtual void __lessThen__(Obj *o){return;};
	virtual void __greaterThen__(Obj *o){return;};
	virtual void __isEqual__(Obj *o){return;};
	virtual void __add__(Obj *o){return;};
	virtual void __sub__(Obj *o){return;};
	virtual void __mul__(Obj *o){return;};
	virtual void __div__(Obj *o){return;};
	virtual void __equal__(Obj *o){return;};
	virtual void __comp__(char c){return;};
	virtual void __print__(){return;};


};


inline void Delete(Obj *o){
	if (o->getTracker()==0) delete o;
}

//#define typeCheck(n)(switch((n)){case _INT_:return 0;case _FLOAT_:return 0;default: return (n) })
inline d_type typeCheck(d_type n){
	switch(n){
		case _INT_:
			return _INT_;

		case _FLOAT_:
			return _INT_;

		default:
		 return n;
	}

}
Obj*  copy_obj(Obj *_old_);

Dict<Obj*> VAR_db;

#define check_for_scope(i,j) ((i)->type==_VAR_ || (i)->type==_PTR_ || (i)->type==_RGX_||(j)->type==_VAR_ || (j)->type==_PTR_ || (j)->type==_RGX_)

Obj* byte_maker(Obj*,Obj *,char,Obj*);
/*
Obj* calc(Obj *lhs,char ch,Obj *rhs){

	//Obj* temp=lhs;
	if(lhs==NULL){
		Error.msg="Too much operator";
		Error.status=true;
		return NULL;

	};
	//std::cout<<"[*]calc:"<<lhs->type<<" "<<ch<<" "<<rhs->type<<"\n";
	//check for var

	if(rhs->type==_PTR_){
		rhs=(Obj*)rhs->data;
	}
 	if(rhs->type==_VAR_ ){
		rhs=VAR_db.get(*(std::string*)rhs->data);

		if(rhs==NULL )return NULL;
		
	};
	if(lhs->type==_VAR_ && ch!='='){
		if(VAR_db.get(*(std::string*)lhs->data)==NULL)return NULL;
		lhs=copy_obj(VAR_db.get(*(std::string*)lhs->data));
		
	}

	std::cout<<"[*]calc:"<<lhs->type<<" "<<ch<<" "<<rhs->type<<"\n";
	

	if(typeCheck(lhs->type)==typeCheck(rhs->type)|| lhs->type==_VAR_ || lhs->type==_PTR_){
		goto __clc__;
	}else{
		std::cout<<"[*]ERR in compatable types\n";
		return NULL;
	}

	__clc__:
	switch(ch){
		case '<':
			lhs->__lessThen__(rhs);break;
		case '>':
			lhs->__greaterThen__(rhs);break;
		case '+':
			lhs->__add__(rhs);break;
		case '-':
			lhs->__sub__(rhs);break;
		case '*':
			lhs->__mul__(rhs);break;
		case '/':		
			lhs->__div__(rhs);break;
		case '=':
			lhs->__equal__(rhs);break;
		default:
			std::cout<<"lol  "<<ch<<"\n";
			Error.msg="unknown operator";
			Error.status=true;
			return NULL;
	}
	std::cout<<"ttt\n";
	/*if(ch=='='){
		std::cout<<"myan wdsadsadsadsadsadsad\n";
		std::cout<<temp->type<<" omg\n";
		return temp;}*/
/*	return lhs;

};*/
Obj* calc(Obj *lhs,char ch,Obj *rhs){

	//Obj* temp=lhs;
	if(lhs==NULL){
		Error.msg="Too much operator";
		Error.status=true;
		return NULL;

	};
	//std::cout<<"[*]calc:"<<lhs->type<<" "<<ch<<" "<<rhs->type<<"\n";
	//check for var
	//LOOP FOR SCOPE;
	if(check_for_scope(lhs,rhs)){
		for(KeyWord_Node *i=HELPER::SCOPE_STACK_END; i!=NULL && i->prev!=NULL ;i=i->prev){
			if(((Obj*)i->obj)->type==_FUNC_){
				byte_maker(((Obj*)i->obj),lhs,ch,rhs);
				Delete(lhs);
				lhs=new Obj();
				lhs->type=_RGX_;
				return lhs;
			}
		}
	}

	if(rhs->type==_PTR_){
		rhs=(Obj*)rhs->data;
	}
 	if(rhs->type==_VAR_ ){
		rhs=VAR_db.get(*(std::string*)rhs->data);

		if(rhs==NULL )return NULL;
		
	};
	if(lhs->type==_VAR_ && ch!='='){
		if(VAR_db.get(*(std::string*)lhs->data)==NULL)return NULL;
		lhs=copy_obj(VAR_db.get(*(std::string*)lhs->data));
		
	}

	std::cout<<"[*]calc:"<<lhs->type<<" "<<ch<<" "<<rhs->type<<"\n";
	

	if(typeCheck(lhs->type)==typeCheck(rhs->type)|| lhs->type==_VAR_ || lhs->type==_PTR_){
		goto __clc__;
	}else{
		std::cout<<"[*]ERR in compatable types\n";
		return NULL;
	}

	__clc__:
	switch(ch){
		case '<':
			lhs->__lessThen__(rhs);break;
		case '>':
			lhs->__greaterThen__(rhs);break;
		case '+':
			lhs->__add__(rhs);break;
		case '-':
			lhs->__sub__(rhs);break;
		case '*':
			lhs->__mul__(rhs);break;
		case '/':		
			lhs->__div__(rhs);break;
		case '=':
			lhs->__equal__(rhs);break;
		default:
			std::cout<<"lol  "<<ch<<"\n";
			Error.msg="unknown operator";
			Error.status=true;
			return NULL;
	}
	std::cout<<"ttt\n";
	/*if(ch=='='){
		std::cout<<"myan wdsadsadsadsadsadsad\n";
		std::cout<<temp->type<<" omg\n";
		return temp;}*/
	return lhs;

};




class Reg:public Obj{
	public: Reg(){this->type=_RGX_;}
};

class Float:public Obj{
public:
	Float(float n){
		data=new float(n);
		std::cout<<"[*]"<<n<<"  "<<*(float*)data<<"\n";
		type=_FLOAT_;
		size=sizeof(float);
	};
	Float(){type=_FLOAT_;};

	void __print__(){
		std::cout<<*(float*)data<<"\n";
	}

	void __add__(Obj *o){
		*(float*)data=*(float*)data + *(float*)(o->data);
		std::cout<<"[**]FROM FLOAT:"<< *(float*)(o->data)<<"\n";
	}
	
	void __sub__(Obj *o){
		*(float*)data=*(float*)data - *(float*)(o->data);
	}

	void __mul__(Obj *o){
		*(float*)data=*(float*)data * (*(float*)(o->data));
	};

	void __div__(Obj *o){
		*(float*)data=*(float*)data / (*(float*)(o->data));
	}


};

class Number:public Obj{
public:
	//int
	Number(){type=_INT_;}
	Number(int n){
		data=new int(n);
		type=_INT_;
		size=sizeof(int);
	}
	Number(std::string s){
		//determin the size dynamicly ..............
		size=4;
		data=malloc(size);
		type=_NUMBER_;
		int n=0;
		for(int i=0;i<s.length();i++){
			n=n*10+(s[i]-'0');
			
		}
		memcpy(data,&n,size);
	};

	void __print__(){
		std::cout<<*(int*)data<<"\n";
	}


	void __add__(Obj *o){
		*(int*)data=*(int*)data + *(int*)(o->data);
	}
	
	void __sub__(Obj *o){
		*(int*)data=*(int*)data - *(int*)(o->data);
	}

	void __mul__(Obj *o){
		*(int*)data=*(int*)data * (*(int*)(o->data));
	};

	void __div__(Obj *o){
		Obj *temp;
		int r=*(int*)data % *(int*)o->data;
		if(r==0){
			*(int*)data=*(int*)data / *(int*)o->data;
		}else{
			std::cout<<"[/]"<<(float)*(int*)data/ (float)*(int*)o->data<<"\n";
			temp=new Float((float)*(int*)data/ (float)*(int*)o->data);
			free(data);
			data=temp->data;
			type=_FLOAT_;
			temp->data=NULL;
			delete temp;

		}
	};

	void __lessThen__(Obj *o){
		if(*(int*)data < *(int*)o->data){
		
			*(int*)data=1;
		}else{
			*(int*)data=0;
		};
	};
	void __greaterThen__(Obj *o){
		if(*(int*)data > *(int*)o->data){
			*(int*)data=1;
		}else{
			*(int*)data=0;
		};
	};

	void __comp__(char c){
		if(c=='-'){*(int*)data*= (-1);};
	}
};

class String:public Obj{
public:
	String(){type=_STRING_;}
	String(std::string s){
		type=_STRING_;
		data=new std::string(s);
		size=s.length();
		
	};
	std::string C_String(){
		return *((std::string*)data);
	}
	String(char *str){
		for(size_t i=0;;i++){
			
		}
	}

	void __print__(){
		std::cout<<*(std::string*)data<<"\n";
	}

	void __add__(Obj *o){
		
		*(std::string*)data+=*(std::string*)o->data;
		
	}
	
	void __sub__(Obj *o){
		return;
	}

	void __mul__(Obj *o){
		return;
	};

	void __div__(Obj *o){
		return;
	}
	
	
	
};

class Dict_t:public Obj{
	//u_int tracker=0;
	Dict<Obj*> *temp=NULL;
public:
	Dict_t(){
		type=_DICT_;
		data=new Dict<Obj *>();
		size=0;
	};
	~Dict_t(){
		std::cout<<"[++++*****++++*****]tracker "<< tracker<<"\n";
		if(tracker!=0){ std::cout<<"wwewewewe\n";data=NULL;};
	};
	Obj* getTempObj(){
		if(temp==NULL)return NULL;

		return temp->getValue();
	}
	void setKey_TempObj(std::string s){
		temp->setKey(s);
	}

	int getTracker(){
		return tracker;
	};

	void incTracker(){
		tracker++;
	};

	void decTracker(){
		tracker--;
		if(tracker==0){
			delete (Dict<Obj*>*)data;
		};
	}

	bool getKey(std::string s){
		temp=((Dict<Obj*>*)(data))->getNode(s);
		if(temp==NULL) return false;
		return true;
	};
	bool getKey(int i){
		temp=((Dict<Obj*>*)(data))->get(i);
		if(temp==NULL) return false;
		return true;
	}



	void setKey(std::string s){
		std::cout<<"hello\n";
			temp=((Dict<Obj*>*)(data))->insert(s,NULL);
			std::cout<<temp->getKey()<<"\n";
			size++;
			return;
		
		//error:

	}
	void setKey(Obj*o){
		if(o->type==_VAR_){
			temp=((Dict<Obj*>*)(data))->insert(*(std::string*)o->data,NULL);
			size++;
			return;
		}
		//error:
		
	};

	void setValue(Obj *o){
		if(temp->getValue()!=NULL)temp->clearValue();
		temp->setValue(copy_obj(o));
		//temp=NULL;
		//size++;
		return;
	}

	Obj* get(std::string s){
		return ((Dict<Obj*>*)data)->get(s);
	}
	void insert(Obj *o){
		std::cout<<"[*]wywywy\n";
		std::cout<<o->type<<" olala \n";
		o->__print__();
		if(o->type==_VAR_){
			Obj *ob=VAR_db.get(*(std::string*)(o->data));
			std::cout<<"[*]FROM DICTTT\n";
			//ob->__print__();
			((Dict<Obj*>*)data)->insert(*(std::string*)(o->data),ob);
			VAR_db.setNull(*(std::string*)(o->data));

			size++;
			return;
		}

		((Dict<Obj*>*)data)->insert(std::to_string(size),o);
		size++;

	}

	void push(Obj *o){
		((Dict<Obj*>*)data)->insert(std::to_string(size),o);
		size++;
	}


	void __print__(){
		Dict<Obj*>*o;
		Obj* obj;
		std::cout<<"{\n";
		for(int i=0;i<size;i++){
			o=((Dict<Obj*>*)data)->get(i);
			if(o!=NULL ){
				std::cout<<" "<<o->getKey()<<":";
				if((obj=o->getValue())!=NULL){
					obj->__print__();
				}else{
					std::cout<<"nullo\n";
				}
			}else{
				std::cout<<"nullo\n";
			}

		}
		std::cout<<"}\n";
	}
	
};

#include "VM.h"

class Var:public Obj{

public:
	Var(){type=_VAR_;};
	Var(std::string name){
		type=_VAR_;
		std::string *temp=new std::string(name);
		data=temp;
	};
	Obj* getObj(){
		Dict_t *node;
		EXC_STACK::Node *i;
		for(i=EXC_STACK::end;;i=i->prev){
			if(i->prev==NULL)return VAR_db.get(*(std::string*)this->data);
			if(i->data->getKey(*(std::string*)this->data)){
				std::cout<<"BREAKING BAD\n\n";
				break;
			};
		}
		std::cout<<*(std::string*)this->data<<"\n";
		i->data->getTempObj()->__print__();
		return i->data->getTempObj();
		//check for scope;

	}

	Obj* getData(){
		Obj *obj=copy_obj(VAR_db.get(*(std::string*)this->data));
		return obj;
	}


	void __add__(Obj *o){
		Obj *obj=copy_obj(VAR_db.get(*(std::string*)this->data));
		obj->__add__(o);
		free(this->data);
		this->data=obj->data;
		this->size=obj->size;
		this->type=obj->type;
	};

	void __equal__(Obj *o){
		//std::cout<<"Entered\n";
		Obj *obj=copy_obj(o);
		obj->__print__();
		VAR_db.insert(*(std::string*)this->data,obj);
			
	};

	/*void __greaterThen__(Obj *O){
		Obj *o=VAR_db.get(*(std::string*)this->data);
		this->size=4;
		this->type= _INT_;
		free(this->data);
		if(o==NULL){this->data=0;return;}
		o->data=
		o->__greaterThen__()
	}*/
	void __print__(){
		Obj *o=VAR_db.get(*(std::string*)this->data);
		if(o==NULL){
			std::cout<<"null\n";
		}else{
			o->__print__();
		}

	}



} ;



class Ptr:public Obj{
	Dict_t *ptr;
	std::string str;
public:
	Ptr(Obj *o,std::string s){
		this->str=s;
		type=_PTR_;
		ptr=(Dict_t*)o;
		if(ptr==NULL){
			data=ptr;
		}else{
			data=ptr->getTempObj();
		}
		//this->name=name;
	}
	~Ptr(){
		std::cout<<"m dead\n";
		data=NULL;
	}
	void __print__(){
		std::cout<<"why u callijn me babu\n";
		if(data==NULL){
			std::cout<<"null\n";
			return;
		}
		((Obj*)data)->__print__();
	}
	void __equal__(Obj *o){
		
		if(ptr==NULL)return;//errr;
		if(data==NULL){
			std::cout<<"cout\n";
			ptr->setKey(str);
			//((Dict_t*)data)->setValue(o);
			//return;

		}
		std::cout<<"cout2\n";
		ptr->setValue(o);
		std::cout<<"m here2\n";
	}
};



class Func:public Obj{
	Dict_t *parms; 
	VM::Code_Node code;
	VM::Code_Node *end;
public:
	Func(){
		type=_FUNC_;
		end=&code;
		parms=new Dict_t();
	};
	~Func(){
		tracker--;
		if(tracker==0){
			delete parms;
			VM::clear_Code_Node(code.next);
		}
	};
	void registerParms(Obj *o){
		if(o->get_type()!=_VAR_){std::cout<<"[*]Must be var\n";return;}//err
		parms->insert(new String(*(std::string*)o->data));
	}
	void registerCode(Obj*lhs,VM::__syntax__ syntax,Obj*rhs){
		end->next=new VM::Code_Node();
		end=end->next;
		end->obj1=lhs;
		end->opcode=syntax;
		end->obj2=rhs;

	};

	virtual void run(Dict_t *parms){
		std::string key;
		printf("wtfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff\n");
		std::cout<<parms->get_size()<<"\n";
		for(int i=0;i<this->parms->get_size();i++){
			if(i>=parms->get_size()){break;}
			this->parms->getKey(i);
			parms->getKey(i);
			key=((String*)(this->parms->getTempObj()))->C_String();
			parms->setKey_TempObj(key);

		}
		std::cout<<"[*]PARAMETERSS :::\n";
		parms->__print__();
		EXC_STACK::push(parms);
		VM::run(code.next);
		EXC_STACK::pop();
		std::cout<<"sdsadsaad\n";
	}

	void print_parms(){
		parms->__print__();
	}
	void print_code(){
		for(VM::Code_Node *i=code.next;i!=NULL;i=i->next){
			std::cout<<"[*]BYTE CODE: "<<((Obj*)i->obj1)->get_type()<<" "<<i->opcode<<" "<<((Obj*)i->obj2)->get_type()<<"\n";
		}

		//run(NULL);
	}
	void __print__(){
		std::cout<<"[Function]\n";
	}

};

char Bool(Obj *o){
	if(*(int*)o->data==0){
		return 0;
	}
	return 1;
}


/*class List{
	void *data=ptr
public:
	List(std::string s,int len){
		data=malloc(len*sizeof(void*))
	};
	~List();
	
};

/*
class Dict
{
public:
	Dict();
	~Dict();
	
};

*/

/*class Err:public Obj{
public:
	Err(std::string s){
		type=_ERR_;
		data=new std::string(s); 
	};
	

	
};*/





void IF(bool status){


}




Obj*  copy_obj(Obj* _old_){
	std::cout<<"ay yooo\n";
	Obj* _new_;
	switch(_old_->type){
		case _INT_:
			_new_=new Number();
			break;
		case _FLOAT_:
			_new_=new Float();
			break;
		case _STRING_:
			_new_=new String();
			_new_->data=new std::string(*(std::string*)_old_->data);
			_new_->size=_old_->size;
			return _new_;
			break;
		case _VAR_:
			((Obj*)_old_)->tracker++;
			return _old_;
		case _FUNC_:
			((Obj*)_old_)->tracker++;
			return _old_;
		case _RGX_:
			std::cout<<"REFFFF\n";
			return new Reg();
		case _DICT_:
			((Dict_t*)_old_)->incTracker();
			return _old_;

	};
	_new_->data=malloc(_old_->size);

	memcpy(_new_->data,(void*)_old_->data,_old_->size);
	_new_->size=_old_->size;
	
	return _new_;

}

VM::Code_Node CODE_STACK;
VM::Code_Node *end=&CODE_STACK;

Obj* byte_maker(Obj *func,Obj *lhs,char ch,Obj *rhs){
	std::cout<<"------+++--------------here\n";
	VM::__syntax__ opcode;
	switch(ch){
		/*case '<':
			end->opcode=VM::ST;break;
		case '>':
			end->opcode=VM::GT;break;*/
		case '+':
			opcode=VM::ADD;break;
		case '-':
			opcode=VM::SUB;break;
		case '*':
			opcode=VM::MUL;break;
		case '/':		
			//opcode=VM::DIV;break;
		case '=':
			opcode=VM::ASSIGN;break;
		default:
			std::cout<<"lol  "<<ch<<"\n";
			Error.msg="unknown operator";
			Error.status=true;
			return NULL;
	}

	((Func*)func)->registerCode(copy_obj(lhs),opcode,copy_obj(rhs));
	return NULL;

}