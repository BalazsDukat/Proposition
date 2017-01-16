class Operand
{public:
	string ret_name();
        virtual char ret_type() = 0;
        Operand* ret_left();
        Operand* ret_right();
        void set_left(Operand*);
        void set_right(Operand*);
protected:
	string name;
	Operand* left = NULL, *right = NULL;
};

string Operand::ret_name()
{return name;}

Operand* Operand::ret_left()
{return left;}

Operand* Operand::ret_right()
{return right;}

void Operand::set_left(Operand* l)
{left = l;}

void Operand::set_right(Operand* r)
{right = r;}
