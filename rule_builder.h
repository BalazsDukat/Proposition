vector<Rule> rule_builder(string filename, Operand*& ROOT)
{// 2) /////////////////////////// BUILDING RULES
//the building of rulebase from file happens only once.
//This needs nodes (Operands) to be present on the binary search tree!
vector<Rule> RB; //this will store the rules in memory
ifstream rule_file(filename.c_str()); //user editable
//int counter = 0; //this might be useful later. ID-s for Rules
string line, temp;
while(getline(rule_file,line))
{istringstream rule_istream(line);
//counter++;
if((rule_istream >> temp) && (temp == "IF"))
{Rule* Rp = NULL;
if(Rp = new Rule(boolExp_builder(rule_istream, ROOT)))
{if((rule_istream >> temp) && (temp == "THEN") && (Rp != NULL))
{Rp -> add_THEN(Assigner_builder(rule_istream, ROOT));//multiple THENs? while not ELSE go on ',' as separator
}
else cout << "### badly formed Rule, has no THEN part, or doesn't even exist." << endl
<< " or could not read from file." << endl;

if((rule_istream >> temp) && (temp == "ELSE") && (Rp != NULL))
    {Rp -> add_ELSE(Assigner_builder(rule_istream, ROOT));//multiple ELSEs? as with THENs.
    }
else cout << " no ELSE part, but that's OK" << endl;
RB.push_back(*Rp);
}
else cout << "### COULD NOT CREATE THE IF-SIDE, NO RULE MADE! " << endl;
}
else cout << "### DOESN'T START WITH IF, this is not a rule!" << endl
<< " or could not read from file." << endl;
}
rule_file.close();
return RB;
}
