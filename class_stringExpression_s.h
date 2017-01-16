class stringExpression_s : public stringExpression
{public:
    stringExpression_s(stringExpression*, string, stringExpression*);
    string ret_value();
private:
	stringExpression* left;
	stringExpression* right;
};

stringExpression_s::stringExpression_s(stringExpression* l, string o, stringExpression* r)
{left = l;
Operator = o;
right = r;
}

string stringExpression_s::ret_value()
{if(Operator == "+") return (left -> ret_value() + right -> ret_value());
bad_Operator();
return "bad operator"; //just in case
}
