class Operand_s : public Operand//, public stringExpression
{public:
	Operand_s(const string);
 	char ret_type() {return 's';}
	string ret_value();
	void set_value(const string);
private:
	string value;
};

Operand_s::Operand_s(const string n)
{	value = "";
	name = n;
}

string Operand_s::ret_value()
{return value;}

void Operand_s::set_value(const string s)
{value = s;}
