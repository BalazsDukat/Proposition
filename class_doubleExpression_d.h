class doubleExpression_d : public doubleExpression
{public:
        doubleExpression_d(doubleExpression*, string, doubleExpression*);
        double ret_value();
private:
	doubleExpression* left;
	doubleExpression* right;
};

doubleExpression_d::doubleExpression_d(doubleExpression* l, string o, doubleExpression* r)
{Operator = o;
left = l;
right = r;
}

double doubleExpression_d::ret_value()
{if(Operator == "+") return (left -> ret_value() + right -> ret_value());
else if(Operator == "-") return (left -> ret_value() - right -> ret_value());
else if(Operator == "*") return (left -> ret_value() * right -> ret_value());
else if(Operator == "/") return (left -> ret_value() / right -> ret_value());
//else if(Operator == "^") return (left -> ret_value() ^ right -> ret_value()); //this doesn't work, needs to be fixed
bad_Operator();
return 0; //just in case
}
