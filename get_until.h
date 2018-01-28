string get_until(istringstream& inSS, const char end)
{char c;
string temp;
while(inSS >> noskipws >> c && c != end && c != '\n' && c != '\r') temp += c;
return temp;
}
