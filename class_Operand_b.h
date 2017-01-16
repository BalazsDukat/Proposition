class Operand_b : public Operand//, public intExpression
{public:
	Operand_b(const string);
 	char ret_type() {return 'b';}
	bool ret_value();
	void set_value(const bool);
private:
	bool value;
};

Operand_b::Operand_b(const string n)
{	value = false;
	name = n;
}

bool Operand_b::ret_value()
{return value;}

void Operand_b::set_value(const bool b)
{value = b;}
