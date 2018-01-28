class Assigner
{public:
        virtual void assign() = 0;
};

class Assigner_i : public Assigner
{public:
	Assigner_i(Operand_i*, intExpression*);
	void assign();
private:
	Operand_i* left = NULL;
        intExpression* right = NULL;
};

Assigner_i::Assigner_i(Operand_i* l, intExpression* r)
{left = l;
right = r;
}

void Assigner_i::assign()
{cout << " Assigner_i working... " << endl;
if(left != NULL && right != NULL)
left -> set_value(right -> ret_value());
else cerr << " ***Assigning didn't work!*** " << endl;
}

class Assigner_d : public Assigner
{public:
	Assigner_d(Operand_d*, doubleExpression*);
	void assign();
private:
	Operand_d* left = NULL;
        doubleExpression* right = NULL;
};

Assigner_d::Assigner_d(Operand_d* l, doubleExpression* r)
{left = l;
right = r;
}

void Assigner_d::assign()
{cout << " Assigner_d working... " << endl;
if(left != NULL && right != NULL)
left -> set_value(right -> ret_value());
else cerr << " ***Assigning didn't work!*** " << endl;
}

class Assigner_s : public Assigner
{public:
	Assigner_s(Operand_s*, stringExpression*);
	void assign();
private:
	Operand_s* left = NULL;
        stringExpression* right = NULL;
};

Assigner_s::Assigner_s(Operand_s* l, stringExpression* r)
{left = l;
right = r;
}

void Assigner_s::assign()
{cout << " Assigner_s working... " << endl;
if(left != NULL && right != NULL)
left -> set_value(right -> ret_value());
else cerr << " ***Assigning didn't work!*** " << endl;
}

class Assigner_b : public Assigner
{public:
	Assigner_b(Operand_b*, boolExpression*);
	void assign();
private:
	Operand_b* left = NULL;
        boolExpression* right = NULL;
};

Assigner_b::Assigner_b(Operand_b* l, boolExpression* r)
{left = l;
right = r;
}

void Assigner_b::assign()
{cout << " Assigner_b working... " << endl;
if(left != NULL && right != NULL)
left -> set_value(right -> ret_value());
else cerr << " ***Assigning didn't work!*** " << endl;
}
