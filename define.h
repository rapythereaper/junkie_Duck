/*
-- erroe handeling
-- while if lai dict raw func jasri execute garaunxa ( ignor efunc tira) + multilin input line ne banauna xa;
-- making float and int as num
-- dict lai tracker anuser delete garna xa
-- dict ma variable ko case halna baki xa
-- additional operator (==,!, and,or)
-- function baki xa
-- actual dict data structure ne baki xa

-- all var following tracer garbage collection
-- VM
*/
#define is_oper(ch) (((ch)>'#' && (ch)<'0')||((ch)>='<'&&(ch)<='>')||(ch)=='!'||(ch)==','||(ch)=='{'||(ch)=='}')


#define is_end(ch)  ((ch)=='')
#define is_unary_oper(ch)((ch)=='+' || (ch)=='-'||(ch)=='!')
#define is_binary_oper(ch) ((ch)=='*' || (ch)=='/');
#define int_to_char(n)()

enum BUILT_IN{
	_IF_,
	_FOR_
} ;

#define null -1;
#define TRUE 1;
#define FALSE 0;
void *TEMP;
typedef struct kkk{
	void (*func)(void)=NULL;
	char status=null;
	struct kkk *next=NULL;
	struct kkk *prev=NULL;
	void *obj=NULL;
	int location=0;

}KeyWord_Node;

/*typedef struct kk{
	VM::__syntax__ opcode;
	OBJ *o1=NULL,
	OBJ *o2=NULL,
	OBJ *o2=NULL,
	struct *next=NULL;
} Code_Node;
*/

typedef struct{
	std::string msg;
	bool status=false;

} Err;

typedef struct{
	char str[70];
	u_int len=0;
} c_str;



template <typename _type_>
class Dict;




Err Error;



namespace CONFIG{
	std::string scope="···· ";
	std::string stdin=">> ";
	std::string PROMPT=stdin;
}

