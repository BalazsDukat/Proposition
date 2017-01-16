class boolWrapper : public boolExpression
{public:
    boolWrapper(Operand_b*);
    bool ret_value();
private:
	Operand_b* Op = NULL;
};

boolWrapper::boolWrapper(Operand_b* O)
{Op = O;}

bool boolWrapper::ret_value()
{//cout << "\n returning Operand_value ";
if(Op != NULL) return Op -> ret_value();
return false; //if something goes wrong.
}

class intWrapper : public intExpression
{public:
    intWrapper(Operand_i*);
    int ret_value();
private:
	Operand_i* Op = NULL;
};

intWrapper::intWrapper(Operand_i* O)
{Op = O;}

int intWrapper::ret_value()
{//cout << "\n returning Operand_value ";
if(Op != NULL) return Op -> ret_value();
return 0; //if something goes wrong.
}

class stringWrapper : public stringExpression
{public:
    stringWrapper(Operand_s*);
    string ret_value();
private:
	Operand_s* Op = NULL;
};

stringWrapper::stringWrapper(Operand_s* O)
{Op = O;}

string stringWrapper::ret_value()
{//cout << "\n returning Operand_value ";
if(Op != NULL) return Op -> ret_value();
return "no_value"; //if something goes wrong.
}
