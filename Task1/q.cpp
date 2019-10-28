#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string>
#include<string.h>
#define INPUTFILE "Task.txt"

using namespace std;

char OUTPUTFILE[] = "file.txt";

int kol;

bool ignore = false;

bool same(const char* a, const char* b) // Аналог strcopy
{
	if (a == nullptr || b == nullptr)
	{
		return false;
	}
	if (a[0] == '\0')
	{
		if (b[0] == '\0')
			return true;
		return false;
	}
	bool f = true;
	int i = 0;
	while(f && a[i]!='\0' && b[i]!='\0')
	{
		f = a[i] == b[i];
		++i;
	}
	return f;
}

bool isdigit(char n[10]) //  Является ли первый символ строки числом
{
	if (n[0] == '0' || n[0] == '1' || n[0] == '2' || n[0] == '3' ||
		n[0] == '4' || n[0] == '5' || n[0] == '6' || n[0] == '7' ||
		n[0] == '8' || n[0] == '9')
		return true;
	return false;
}

struct Value // Множество значений переменной
{
	int vals;
	bool nin;
	
	void set(int val)
	{
		this->vals = val;
		if (this->nin == true)
		{
			this->nin = false;
		}
	}
	
	Value(){this->nin = true;}
	
	Value(int i){this->vals = i;this->nin = false;}
	
	~Value(){}
	
	Value& operator=(Value other)
	{
		this->nin = other.nin;
		this->vals = other.vals;
		return *this;
	}
	Value operator+(Value other)
	{
		Value v;
		v.vals = this->vals + other.vals;
		return v;
	}
	void cl() // Очистка переменной
	{
		this->nin = true;
	}
};

struct Variable // Переменная
{
	Value val;
	char name[4] = "";
	char type[4];
	char area;
	long long int rangeleft;
	long long int rangeright;
	Variable(){this->cl();}
	Variable(const char name[4])
	{
		int i = 0;
		while(name[i]!='\0')
		{
			this->name[i] = name[i];
			++i;
		}
		this->name[i] = '\0';
		this->cl();
	}
	Variable(int i, const char name[4], const char tname[4], const char area, int l = 0, int r = 0)
	{
		for(int i = 0; i < 4; ++i)
		{
			this->name[i] = name[i];
			this->type[i] = tname[i];
		}
		this->area = area;
		this->rangeleft = l;
		this->rangeright = r;
		this->val = Value(i);
	}
	Variable(Value& v, const char name[4], const char tname[4], const char area, int l = 0, int r = 0)
	{
		for(int i = 0; i < 4; ++i)
		{
			this->name[i] = name[i];
			this->type[i] = tname[i];
		}
		this->area = area;
		this->rangeleft = l;
		this->rangeright = r;
		this->val = v;
		
	}
	Variable(Value& f_v,Value& g_v,const char name[4], const char tname[4], const char area, int l = 0, int r = 0)
	{
		for(int i = 0; i < 4; ++i)
		{
			this->name[i] = name[i];
			this->type[i] = tname[i];
		}
		this->area = area;
		this->rangeleft = l;
		this->rangeright = r;
		this->val = f_v + g_v;
		
	}
	~Variable(){}
	Variable& operator=(Variable other)
	{
		for(int i = 0; i < 4; ++i)
		{
			this->name[i] = other.name[i];
			this->type[i] = other.type[i];
		}
		this->area = other.area;
		this->val = other.val;
		this->rangeleft = other.rangeleft;
		this->rangeright = other.rangeright;
		return *this;
	}
	void cl() // Очистка переменной (#)
	{
		this->val.cl();
	}
	void set(int i) // Сменить значение
	{
		val.set(i);
	}
};

class Perhaps // Набор переменных
{
public:
	Variable vars[20];
	int state;
	int isused;
public:
	explicit Perhaps(const char f1[4],const char f2[4],const char f3[4],const char f4[4], const char h[4])
	{
		this->isused = 4;
		vars[0] = Variable(f1);
		vars[1] = Variable(f2);
		vars[2] = Variable(f3);
		vars[3] = Variable(f4);
		vars[4] = Variable(h);
	}
	explicit Perhaps(){this->isused = 0;}
	explicit Perhaps(int i, int j, const char iname[4], const char jname[4], Perhaps& f, Perhaps& g)
	{
		this->vars[0] = Variable(i,"f_c","int",'l',0,0);
		this->vars[1] = Variable(j,"g_c","int",'l',0,0);
		this->isused = f.isused + g.isused + 2;
		for(int i = 0; i < f.isused; ++i)
		{
			if (f.vars[i].area == 'g')
			{
				continue;
			}
			else if(f.vars[i].name[1] == '\0')
			{
				char tmp = f.vars[i].name[0];
				f.vars[i].name[0] = 'f';
				f.vars[i].name[1] = '_';
				f.vars[i].name[2] = tmp;
				f.vars[i].name[3] = '\0';
				this->vars[i+2] = Variable(f.vars[i].val,f.vars[i].name,"int",'l',0,0);
			}
			else
			{
				this->vars[i+2] = Variable(f.vars[i].val,f.vars[i].name,"int",'l',0,0);
			}
		}
		for(int i = 0; i < g.isused; ++i)
		{
			if (g.vars[i].area == 'g')
			{
				continue;
			}
			if (f.vars[i].area != 'g' && g.vars[i].name[1] == '\0')
			{
				char tmp = g.vars[i].name[0];
				g.vars[i].name[0] = 'g';
				g.vars[i].name[1] = '_';
				g.vars[i].name[2] = tmp;
				g.vars[i].name[3] = '\0';
				vars[i+1+f.isused] = Variable(g.vars[i].val,g.vars[i].name,"int",'l',0,0);
			}
			else
			{
				this->vars[i+1+f.isused] = Variable(f.vars[i].val,f.vars[i].name,"int",'l',0,0);
			}
		}
	}
	~Perhaps(){}
	void setstate(int st)
	{
		this->state = st;
	}
	Perhaps& operator+=(Perhaps other)
	{
		for(int i = 0; i < other.isused; ++i)
		{
			this->vars[isused] = other.vars[i];
			++this->isused;
		}
		return *this;
	}
	Perhaps& operator=(Perhaps other)
	{
		this->isused = other.isused;
		for(int i = 0; i < other.isused; ++i)
		{
			this->vars[i] = other.vars[i];
		}
		return *this;
	}
	Variable& operator[](const char c[10])
	{
		int d = -1;
		for(int i = 0; !same(vars[i].name,c); ++i)
		{
			d = i;
			if (d>20)
			break;
		}
		++d;
		return vars[d];
	}
};

class State // Состояние
{
public:

	Perhaps list;
	int commandnumber;

public:

	State()
	{this->commandnumber = 0;}
	State(const char f1[4],const char f2[4],const char f3[4],const char f4[4], const char h[4])
	{
		this->list = Perhaps(f1,f2,f3,f4,h);
		this->commandnumber = 0;
	}
	State(int i, int j, const char iname[4], const char jname[4], State& f, State& g)
	{
		this->commandnumber = 0;
		this->list = Perhaps(i,j,iname,jname,f.list,g.list);
	}
	State(Perhaps P)
	{
		this->list = P;
		this->commandnumber = 0;
	}
	~State(){}
	void setstate(int st)
	{
		this->list.setstate(st);
	}
	State& operator=(State other)
	{
		this->list = other.list;
		this->commandnumber = other.commandnumber;
		return *this;
	}
	void standart(Perhaps p, int i)
	{
		this->list = p;
		this->commandnumber = i;
	}
	void add(const char op[], int c)
	{
		this->list[op].set(c);
	}
	void add(const char op[], const char first[], const char second[])
	{
		this->list[op].val = this->list[first].val + this->list[second].val;
	}
	void add(const char op[], const char first[], int c)
	{
		this->list[op].val = this->list[first].val + c;
	}
	void add(const char op[], int c, const char first[])
	{
		this->list[op].val = this->list[first].val + c;
	}
	void add(const char op[], int d, int c)
	{
		this->list[op].val = d + c;
	}
	void add(const char op[], const char other[])
	{
		this->list[op].val = this->list[other].val;
	}
};

class States // Набор состояний
{
public:

	State state[200];
	int length;
	int last;
	int strings;
	
public:

	explicit States(const char f1[4],const char f2[4],const char f3[4],const char f4[4], const char h[4])
	{
		this->length = 1;
		this->last = 0;
		this->strings = 0;
		this->state[0] = State(f1,f2,f3,f4,h);
	}
	explicit States()
	{
		this->length = 0;
		this->last = 0;
		this->strings = 0;
	}
	States(State s)
	{
		this->state[0] = s;
		this->length = 1;
		this->last = 1;
		this->strings = 1;
	}
	~States(){}
	void add(const char name1[4],const char name2[4], int i, int j)
	{
		this->state[this->length-1].add(name1,i);
		this->state[this->length-1].add(name2,j);
	}
	void add(int i, int j, const char iname[4], const char jname[4], States& f, States& g)
	{
		for(int f_c = 0; f_c < f.length; ++f_c)
		{
			if (f.state[f_c].commandnumber == i)
			{
				for(int g_c = 0; g_c < g.length; ++g_c)
				{
					if (g.state[g_c].commandnumber == j)
					{
						this->state[this->length] = State(i,j,iname,jname,f.state[f_c],g.state[g_c]);
						this->last = 1;
						++this->strings;
						++this->length;
						
					}
				}
			}
		}
	}
	States& operator=(States other)
	{
		for(int i = 0; i < other.length; ++i)
		{
			this->state[i] = other.state[i];
		}
		this->last = 0;
		this->length = other.length;
		this->strings = other.strings;
		return *this;
	}
	States& operator+=(States other)
	{
		other.state[0].commandnumber = this->state[this->length-1].commandnumber+1;
		this->state[this->length] = other.state[0];
		this->last = 1;
		this->length += this->last;
		if (other.state[0].commandnumber > -1)
		{
				++this->strings;
		}
		return *this;
	}
	States& operator<<=(States other)
	{
		for(int i = 0; i < other.last; ++i)
		{
			this->state[this->length+i] = other.state[other.length-1-other.last+i];
		}
		this->last = other.last;
		this->length += this->last;
		return *this;
	}
	Perhaps& prev()
	{
		return this->state[length-1].list;
	}
	int cn()
	{
		return this->state[length-1].commandnumber+1;
	}
	int nn()
	{
		return this->strings;
	}
	int ln()
	{
		return this->length;
	}
};

class Operation
{
public:
	char oper[7];
	int conda;
	char op1[10];
	char ope2[10];
	char ope3[10];
	int iftrue;
	int iffalse;
	char cvol[10];
	bool cd;
	bool op2d;
	bool op3d;
public:
Operation()
{}
Operation(const char oper[7],int conda, const char op1[10], const char ope2[10],
			const char ope3[10],int iftrue,int iffalse, const char cvol[10],bool cd,bool op2d,bool op3d)
{
	this->conda = conda;
	this->iftrue = iftrue;
	this->iffalse = iffalse;
	this->cd = cd;
	this->op2d = op2d;
	this->op3d = op3d;
	for(int i = 0; i < 10; ++i)
	{
		if (i < 7) this->oper[i] = oper[i];
		this->op1[i] = op1[i];
		this->ope2[i] = ope2[i];
		this->ope3[i] = ope3[i];
		this->cvol[i] = cvol[i];
	}
}
void set(const char oper[7],int conda, const char op1[10], const char ope2[10],
			const char ope3[10],int iftrue,int iffalse, const char cvol[10],bool cd,bool op2d,bool op3d)
{
	this->conda = conda;
	this->iftrue = iftrue;
	this->iffalse = iffalse;
	this->cd = cd;
	this->op2d = op2d;
	this->op3d = op3d;
	for(int i = 0; i < 10; ++i)
	{
		if (i < 7) this->oper[i] = oper[i];
		this->op1[i] = op1[i];
		this->ope2[i] = ope2[i];
		this->ope3[i] = ope3[i];
		this->cvol[i] = cvol[i];
	}
}
~Operation() {}
int digitality(const char str[])
{
	int sum = 0;
	int k = 1;
	for(int i = 0; str[i] != '\0'; ++i)
	{
		sum += k*sum + (str[i] - '0');
		k *= 10;
	}
	return sum;
}
	Operation& operator=(Operation other)
	{
		this->conda = other.conda;
		this->iftrue = other.iftrue;
		this->iffalse = other.iffalse;
		this->cd = other.cd;
		this->op2d = other.op2d;
		this->op3d = other.op3d;
		for(int i = 0; i < 10; ++i)
		{
			if (i < 7) this->oper[i] = oper[i];
			this->op1[i] = other.op1[i];
			this->ope2[i] = other.ope2[i];
			this->ope3[i] = other.ope3[i];
			this->cvol[i] = other.cvol[i];
		}
		return *this;
}
char* name()
{
	return this->oper;
}

char* op()
{
	return this->op1;
}

char* op2()
{
	return this->ope2;
}

char* op3()
{
	return this->ope3;
}

int op2dig()
{
	return digitality(this->ope2);
}

int op3dig()
{
	return digitality(this->ope3);
}

int cond()
{
	return this->conda;
}

char* condvol()
{
	return this->cvol;
}

int condvold()
{
	return digitality(this->cvol);
}

bool dop2()
{
	return this->op2d;
}

bool dop3()
{
	return this->op3d;
}
int truego()
{
	return iftrue;
}
int falsego()
{
	return iffalse;
}
bool dcvol()
{
	return this->cd;
}

};

class Graph
{
	Operation flow[30];
	int length;
public:
Graph(){this->length = 0;}
	int len()
	{
		return this->length;
	}
	Operation& operator[](int j)
	{
		return flow[j];
	}
	void add(const char oper[7],int conda, const char op1[10], const char ope2[10],
			const char ope3[10],int iftrue,int iffalse, const char cvol[10],bool cd,bool op2d,bool op3d)
	{
		this->flow[length].set(oper,conda,op1,ope2,ope3,iftrue,iffalse,cvol,cd,op2d,op3d);
		++this->length;
	}
	Graph& operator=(Graph other)
	{
		this->length = other.length;
		for(int i = 0; i < other.length; ++i)
		{
			this->flow[i] = other.flow[i];
		}
		return *this;
	}
	
};
Graph grmode(int i, FILE* fin)
{
	Graph gr;
	if (i == 0)
	{//this->flow[length].set(oper,conda,op1,ope2,ope3,iftrue,iffalse,cvol,cd,op2d,op3d);
		gr.add("new",-1,"h","","",-1,-1,"",true,true,true);
	}
	else if (i==1)
	{
		gr.add("new",-1,"h","","",1,1,"",true,true,true);
		gr.add("=",-1,"x","4","",2,2,"",true,true,true);
		gr.add("=",-1,"y","1","",3,3,"",true,true,true);
		gr.add("=",-1,"h","a","",4,4,"",true,false,true);
		gr.add("=",-1,"x","3","",5,5,"",true,true,true);
		gr.add("if",1,"x","7","",6,13,"",true,true,true);
		gr.add("=",-1,"y","10","",8,8,"",true,true,true);;
		gr.add("if",3,"h","b","",7,13,"",true,false,true)
		gr.add("if",3,"h","y","",9,10,"",true,false,true)
		gr.add("=+",-1,"h","a","",13,13,0,true,false,true);
		gr.add("new",-1,"h",0,0,-1,-1,0,true,true,true);
		gr.add("new",-1,"h",0,0,-1,-1,0,true,true,true);
		gr.add("new",-1,"h",0,0,-1,-1,0,true,true,true);
	}
	else if (i==2)
	{
	}
	return gr;
}

void word(char reader[26], int& count,char* w)
{
	int i = 0;
	while(reader[count] == ' ' || reader[count] == '\t' || reader[count] == ',' || reader[count] == ';' || reader[count] == '\n')
	{
		++count;
	}
	while(reader[count] != ' ' && reader[count] != '\0'
			&& reader[count] != '\t' && reader[count] != '\n' && reader[count] != ',' && reader[count] != ';')
	{
		w[i] = reader[count];
		++count;
		++i;
	}
	while(reader[count] == ' ' || reader[count] == '\t' || reader[count] == ',' || reader[count] == ';' || reader[count] == '\n')
	{
		++count;
	}
	w[i] = '\0';
}

bool printtt(States& states_f, States& states_g) // печатаем в OUTPUTFILE
{
		FILE *fin;
		if ((fin = fopen(OUTPUTFILE, "w")) == nullptr)
		{
			printf("Не удалось открыть файл\n");
			return false;
		}
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","f_c");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","g_c");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","f_a");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","f_b");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","f_x");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","f_y");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","g_a");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","g_b");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","g_x");
				fprintf(fin,"%c",'}');
								fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%s","g_y");
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",'\n');
	for(int i = 1; i <= states_f.strings; ++i)
		{
			for(int j = 1; j <= states_g.strings; ++j)
			{
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%d",i);
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%d",j);
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');

		for(int f_c = 0; f_c < states_f.length; ++f_c)
		{
			if (states_f.state[f_c].commandnumber == i)
			{
				fprintf(fin,"%c",' ');
				if (states_f.state[f_c].list["a"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_f.state[f_c].list["a"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				if (states_f.state[f_c].list["b"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_f.state[f_c].list["b"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				if (states_f.state[f_c].list["x"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_f.state[f_c].list["x"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				if (states_f.state[f_c].list["y"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_f.state[f_c].list["y"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
			}
		}
		for(int g_c = 0; g_c < states_g.length; ++g_c)
		{
			if (states_g.state[g_c].commandnumber == j)
			{
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				if (states_g.state[g_c].list["a"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_g.state[g_c].list["a"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				if (states_g.state[g_c].list["b"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_g.state[g_c].list["b"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				if (states_g.state[g_c].list["x"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_g.state[g_c].list["x"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
				fprintf(fin,"%c",' ');
				fprintf(fin,"%c",'{');
				fprintf(fin,"%c",' ');
				if (states_g.state[g_c].list["y"].val.nin)
					{fprintf(fin,"%c",'#'); fprintf(fin,"%c",' ');}
				else
				{
					fprintf(fin,"%d",states_g.state[g_c].list["y"].val.vals);
					fprintf(fin,"%c",' ');
				}
				fprintf(fin,"%c",'}');
			}
		}

				fprintf(fin,"%c",'\n');
			}
		}
	fclose(fin);
	return true;
}

bool iff(int a, int op, int b)
{
	return true;
}

States preparse(Operation gr, Perhaps presil, int& st) // Парсинг программы
{
	State state(presil);
		if(same(gr.name(),"ifgoto"))
		{
			if (gr.dcvol())
			{
				if (iff(presil[gr.op()].val.vals,gr.cond(),gr.condvold()))
					st = gr.truego();
				else
					st = gr.falsego();
			}
			else
			{
				if (iff(presil[gr.op()].val.vals,gr.cond(),presil[gr.condvol()].val.vals))
					st = gr.truego();
				else
					st = gr.falsego();
			}
		}
		else if(same(gr.name(),"goto"))
		{
			st = gr.truego();
		}
		else if(same(gr.name(),"="))
		{
			if (gr.dop2())
				state.add(gr.op(),gr.op2dig());
			else
				state.add(gr.op(),gr.op2());
		}
		else if(same(gr.name(),"+="))
		{
			if (gr.dop2())
			{
				if (gr.dop3())
					state.add(gr.op(),gr.op2dig(),gr.op3dig());
				else
					state.add(gr.op(),gr.op2dig(),gr.op3());
			}
			else
			{
				if (gr.dop3())
					state.add(gr.op(),gr.op2(),gr.op3dig());
				else
					state.add(gr.op(),gr.op2(),gr.op3());
			}
		}
	state.setstate(st);
	return state;
}

bool parser(Graph grf,Graph grg,Graph grm, int a1, int a2, int b1, int b2)
{
	States states_f("a","b","x","y","h");
	states_f.add("a","b",a1,b1);
	States states_g("a","b","x","y","h");
	states_g.add("a","b",a2,b2);
	int state = -1;
	for(int i = 0; i < grm.len(); ++i)
	{
		states_f += preparse(grm[i],states_f.prev(),state);
		states_g <<= states_f;
	}
	state = 0;
	for(;state != -1;)
	{
		states_f += preparse(grf[state],states_f.prev(),state);
	}
	state = 0;
	for(;state != -1;)
	{
		states_g += preparse(grg[state],states_g.prev(),state);
	}
	return true;
}

int main(int argc, char* argv[])
{
	try{
	bool con = false;
	int digit[4];
	for(int i = 1; i < 5; ++i)
	{
		digit[i-1] = std::stoi(argv[i]);
	}
	if(argc > 5)
	{
		if(!strcmp(argv[5],"-count"))
		{
			con = true;
			if (argc > 6)
			{
				if (!strcmp(argv[6],"-file") && argc > 7)
				{
					int j = 0;
					while(argv[7][j]!='\0')
					{
						OUTPUTFILE[j] = argv[7][j];
						++j;
					}
					OUTPUTFILE[j] = '\0';
				}
				else throw 1;
			}
		}
		else if (!strcmp(argv[5],"-file") && argc > 6)
		{
			int j = 0;
			while(argv[6][j]!='\0')
			{
				OUTPUTFILE[j] = argv[6][j];
				++j;
			}
			OUTPUTFILE[j] = '\0';
			if (argc > 7)
			{
				if(!strcmp(argv[7],"-count")) con = true;
				else throw 1;
			}
		}
		else throw 1;
	}
	FILE *fin;
	Graph grf,grg,grm;
	char filename[] = INPUTFILE;
	if ((fin = fopen(filename, "r")) == nullptr)
	{
		printf("Не удалось открыть файл\n");
		return 1;
	}
	grm = grmode(0,fin);
	grf = grmode(1,fin);
	grg = grmode(2,fin);
	parser(grf,grg,grm,digit[0],digit[2],digit[1],digit[3]);
	fclose(fin);
	if(con)
	cout<<kol<<'\n';
	return 0;
	}
	catch(...) {
		cout<<"БЕДА! 2019, Gonopolskiy Mark. \ng++ <name> -Wall -Werror -O2\n./2019_421_Gonopolskiy <f_a> <f_b> <g_a> <g_b> [-file <filename>] [-count]\n";
		return 1;
	}
}
