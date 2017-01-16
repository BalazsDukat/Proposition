class Operand_i : public Operand//, public intExpression
{public:
	Operand_i(const string);
 	char ret_type() {return 'i';}
	int ret_value();
	void set_value(const int);
private:
	int value;
};

Operand_i::Operand_i(const string n)
{	value = 0;
	name = n;
}

int Operand_i::ret_value()
{return value;}

void Operand_i::set_value(const int i)
{value = i;}
