class intExpression : public Expression //ABC
{public:
	virtual int ret_value() = 0;
        char ret_type() {return 'i';}
};
