
namespace ds{	};
template <typename _type_>
class List{
public:
	List *prev=NULL;
	List *next=NULL;
	_type_ data=NULL;
	
public:
	List(_type_ d=NULL){
		data=d;
	};
	~List(){
		if(data!=NULL)delete data;
		if(next!=NULL)delete next;
	}
	
	List* selfDestruct(){
		List* temp=next;
		next=NULL;
		delete this;
		return temp;
	}

	List *getNext(){
		return next;
	}
	List *getPrev(){
		return prev;
	}

	List *setNext(_type_ d){
		next=new List();
		next->data=d;
		next->prev=this;
		return next;
	};
	List* del(){
		List *r;
		if(data!=NULL)delete data;
		if(this->prev!=NULL)r=this->prev->next=this->next;
		if(this->next!=NULL)r=this->next->prev=this->prev;
		this->prev=NULL;
		this->next=NULL;
		this->data=NULL;
		delete this;
		
		return r;
	}

	_type_ getData(){
		return data;
	};
	void print(){
		if(data!=NULL){
			std::cout<<*data<<"\n";
		}else{
			std::cout<<"NULL\n";
		}
	}
	//friend __clac__;
	friend int main(int argc, char const *argv[]);
	
};





typedef struct q{
	std::string key;
	void* value;
} dict_node;


template <typename _type_>
class Dict{
	std::string key;
	_type_ value;
	Dict*next=NULL;

public:
	
	~Dict(){
		if(next!=NULL)delete next;
		if(value!=NULL)delete value;
	};

	void setKey(std::string s){
		this->key=s;
	};
	std::string getKey(){
		return key;
	};

	_type_ getValue(){
		return value;
	}
	void clearValue(){
		delete value;
		value=NULL;
	}
	void setValue(_type_ obj){
		if(value!=NULL)delete value;
		value=obj;
	}
	Dict *getNode(std::string name,bool insert=false){
		Dict* temp;
		for(Dict *i=this;i!=NULL;i=i->next){
			if(i->key==name){
				return i;
			}
			temp=i;
		};
		if(insert){
		temp->next=new Dict();
		temp=temp->next;
		temp->key=name;
		temp->value=NULL;
		return temp;}
		return NULL;
	}

	Dict* insert(std::string name,_type_ obj){
		std::cout<<"Inserting "<<name<<"\n";
		//obj->__print__();
		Dict* temp;
		for(Dict *i=this;i!=NULL;i=i->next){
			if(i->key==name){
				delete i->value;
				i->value=obj;
				return i;
			}
			temp=i;
		};

		temp->next=new Dict();
		temp=temp->next;
		temp->key=name;
		temp->value=obj;
		return temp;

	}

	void setNull(std::string name){
		for(Dict *i=this;i!=NULL;i=i->next){
			if(i->key==name){
				std::cout<<"[fuck]\n";
				i->value=NULL;
				i->key="";
			}
		};
	}

	_type_ get(std::string name){
		for(Dict *i=this;i!=NULL;i=i->next){
			if(i->key==name){
				return i->value;
			}
		};

		return NULL;

	}
	/*Dict *getNode(std::string name){
		for(Dict *i=this;i!=NULL;i=i->next){
			if(i->key==name){
				return i;
			}
		};
		return NULL;
	}*/

	Dict* get(int j){
		Dict *temp=this;
		int i=0;
		for( i=0;i<=j;i++){
			if(temp==NULL){
				std::cout<<"[!!]out of size\n";
				break;}
			
			temp=temp->next;
		};
		//std::cout<<"[wowowowoc]get vitr ko i: "<<i<<"\n";
		return temp;
	}

};


/*


class Dict_stack{
	dict_node *data;
	u_int size=0;

	u_int hash(char *str){
		return str[0]+str[str.length()]+str[str.length()/2];
	}
public:
	Dict(int size){
		data=new dict_node[size];
		this->size=size;
	};

	void insert(){}


	
};

*/

