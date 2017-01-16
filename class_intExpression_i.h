class intExpression_i : public intExpression
{public:
        intExpression_i(intExpression*, string, intExpression*);
        int ret_value();
private:	
	intExpression* left;
	intExpression* right;
};

intExpression_i::intExpression_i(intExpression* l, string o, intExpression* r)
{Operator = o;
left = l;
right = r;
}

int intExpression_i::ret_value()
{if(Operator == "+") return (left -> ret_value() + right -> ret_value());
else if(Operator == "-") return (left -> ret_value() - right -> ret_value());
else if(Operator == "*") return (left -> ret_value() * right -> ret_value());
else if(Operator == "/") return (left -> ret_value() / right -> ret_value());
else if(Operator == "^") return (left -> ret_value() ^ right -> ret_value());
bad_Operator();
return 0; //just in case
}
