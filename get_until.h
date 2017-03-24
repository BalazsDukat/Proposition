string get_until(istringstream& inSS, const char end)
{char c;
string temp;
while(inSS >> noskipws >> c && c != end) temp += c;
return temp;
}
