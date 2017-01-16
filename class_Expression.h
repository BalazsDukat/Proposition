class Expression //ABC
{public:
	virtual char ret_type() = 0;
        void bad_Operator() {cout << "IF WE GOT HERE THEN THE OPERATOR " << Operator << " PROVED USELESS" << endl;}
protected:
	string Operator;
};
