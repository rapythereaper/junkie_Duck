namespace OBJ_STACK{
	List<Obj*> head;
	List<Obj*> *end=&head;

	void push(Obj *o){
		end=end->setNext(o);
	}

	Obj* pop(){
		if(&head==end)return NULL;
		Obj *o=end->getData();
		end=end->getPrev();
		return o;
	};

	void clear(){
		if(end->getNext()!=NULL)delete end->getNext();
		end->next=NULL;
	};

	void clearAll(){
		if(head.getNext()!=NULL)
		delete head.getNext();
		head.next=NULL;
	}

}

namespace EXC_STACK{
	typedef struct Node
	{
		Dict_t *data;
		struct Node *prev=NULL;	
	} Node;

	Node head;
	Node *end=&head;

	void push(Dict_t *d){
		Node *temp=end;
		end=new Node();
		end->data=d;
		end->prev=temp;
	};
	Dict_t *pop(){
		Dict_t *temp=end->data;
		if(end->prev!=NULL){
			Node *t=end;
			end=end->prev;
			delete t;
		}
		return temp;
	}
}




namespace VM{
	void __add__(Obj *o,Obj *o1);
	void __sub__(Obj *o,Obj *o1);
	void __mul__(Obj *o,Obj *o1);
	void __div__(Obj *o,Obj *o1);
	void __assign__(Obj *o,Obj *o1);
	//void __comp__(Obj*o,Obj *O1);
	void __call__(Obj *o,Obj *o1);

	void (*func[])(Obj*,Obj*)={__add__,__sub__,__mul__,__div__,__assign__};
	//SYNTAX COUNT 5;
	char FLAG=0;
	Obj *rax;
	Obj *rbx;
	Obj *rcx;
	enum __syntax__{
		ADD,
		SUB,
		MUL,
		DIV,
		ASSIGN,
		COMP,



	};

	typedef struct Code_Node
	{
		void *obj1=NULL;
		void *obj2=NULL;
		__syntax__ opcode;
		struct Code_Node *next=NULL;
	} Code_Node;


	
	void clear_Code_Node(Code_Node *c){
		Code_Node *i;
		for(i=c;i!=NULL;){
			c=c->next;
			delete (Obj*)i->obj1;
			delete (Obj*)i->obj1;
			delete i;
			i=c;
		}
	}
	void run(Code_Node *code){
		d_type type;
		for(;code!=NULL;code=code->next){
			type=((Obj*)code->obj1)->get_type();
			if(type==_RGX_)
				rax=OBJ_STACK::pop();
			else if((type==_VAR_ || type==_PTR_) && code->opcode!=ASSIGN)
				rax=copy_obj(((Obj*)code->obj1)->getObj());
			else
				rax=((Obj*)code->obj1);
				

			

			type=((Obj*)code->obj2)->get_type();
			if(type==_RGX_)
				rbx=OBJ_STACK::pop();
			else if(type==_VAR_ || type==_PTR_)
				rbx=((Obj*)code->obj2)->getObj();
			else
				rbx=((Obj*)code->obj2);
			
			
			func[code->opcode](rax,rbx);
			//checl for err before each loop
			std::cout<<"--------well\n";
			OBJ_STACK::push(rax);
			std::cout<<"------well 100\n";
			rax->__print__();
			std::cout<<"------well 100\n";
			
		}
	

		//OBJ_STACK::clearAll();

	}

	void __add__(Obj *o,Obj *o1){o->__add__(o1);};
	void __sub__(Obj *o,Obj *o1){o->__sub__(o1);}
	void __mul__(Obj *o,Obj *o1){o->__mul__(o1);}
	void __div__(Obj *o,Obj *o1){o->__div__(o1);}
	void __assign__(Obj *o,Obj *o1){std::cout<<"--------well2\n";o->__equal__(o1);}
	


	/*void __call__(Obj*o,Obj*o1){
		if(o->get_type()!=_Func_){
			//err
			return;
		};
		(Func*)o->call(o1);
		rax=o->out;

	}*/
	



}



