class Print:public Func{
public:
	void run(Dict_t *parms){
		Obj *o=parms->get(0);
		if(o!=NULL){
			o->__print__();
			return;
		}
		std::cout<<"null\n";
	}
};
REGISTER("print",new Print())