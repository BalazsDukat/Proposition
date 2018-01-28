class Operand_d : public Operand//, public doubleExpression
{public:
	Operand_d(const string);
 	char ret_type() {return 'd';}
	double ret_value();
	void set_value(const double);
private:
	double value;
};

Operand_d::Operand_d(const string n)
{	value = 0.0;
	name = n;
}

double Operand_d::ret_value()
{return value;}

void Operand_d::set_value(const double d)
{value = d;}
