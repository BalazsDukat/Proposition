string get_from_until(istringstream& inSS, const char beginning, const char end)
{char c;
string temp;
while(inSS >> noskipws >> c && c != beginning);
while(inSS >> noskipws >> c && c != end) temp += c;
return temp;
}