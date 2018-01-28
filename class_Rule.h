class Rule
{public:
	Rule(boolExpression*);
	void add_THEN(Assigner*); //later these can be extended to vectors or
	void add_ELSE(Assigner*); //arrays of Assigners.
	void fire();
private:
	boolExpression* IF;
	Assigner* THEN, *ELSE;
    //int RN = 0; //possibly these should have identifiers as currently only
    //their position identifies them when Operands refer to them.
};

Rule::Rule(boolExpression* c)
{IF = c;
THEN = NULL;
ELSE = NULL;
}

void Rule::add_THEN(Assigner* a)
{THEN = a;}

void Rule::add_ELSE(Assigner* a)
{ELSE = a;}

void Rule::fire()
{//cout << " firing Rule" << endl;
if(IF != NULL)
      if(IF -> ret_value() == true)
           {if(THEN != NULL) THEN -> assign();
           //else cerr << " ***NO 'THEN' PART in Rule*** " << endl;
           }
      else {if(ELSE != NULL) ELSE -> assign();
           //else cerr << " ***NO 'ELSE' PART in Rule*** " << endl;
           }
else cerr << " ***NO 'IF' PART!*** how can this Rule even exist???" << endl;
}
