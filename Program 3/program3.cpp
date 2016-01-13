#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int maxstack = 20;


struct stype
{
	char A;
    stype *link;
};

bool Emptystack(stype *stfirst, stype *stlast)
{
	return stfirst->link==stlast;
}

void createstack(stype *&stfirst, stype *&stlast)
{
	stfirst=new stype;
	stlast=new stype;
	stfirst->A= '!';
	stlast->A= '?';
	stfirst->link=stlast;
	stlast->link=NULL;
}

int priority(char ch)
{
	int answer=0;

	if(ch=='+') answer = 1;
	else if(ch=='-') answer = 1;
	else if(ch=='*') answer = 2;
	else if(ch=='/') answer = 2;
	else if(ch=='!') answer = -1;
	else if(ch=='?') answer = 8888;
	return answer;
}

void push(stype *&stfirst, stype *stlast, char ch)
{
	stype *knew;
	knew=new stype;
	knew->A=ch;
	knew->link=stfirst->link;
	stfirst->link=knew;
}

char pop(stype*&stfirst, stype*&stlast)
{
	char answer=' ';
	stype *c;
	if (!Emptystack(stfirst,stlast))
	{
		c=stfirst->link;
		stfirst->link=c->link;
		answer=c->A;
		delete c;
	}
	return answer;
}

void readem(stype *&stfirst, stype *&stlast)
{
	string instring, outstring;
	int num;
	int i, len;
	char ch;
	ifstream inf;
	ofstream outf;
	inf.open("Data.dat");
	outf.open("Output.out");

	while(!inf.eof())
	{
		outstring= "";
		inf >> instring;
		len = instring.length();
		for (i=0;i<len;i++)
		{
			ch = instring[i];
			if(ch >= 'A' && ch <= 'Z') 
			{
				outstring += ch;
			}
			else 
			{
				if(Emptystack(stfirst, stlast))
					push (stfirst, stlast, ch);
				
				else if( priority(stfirst->link->A) < priority(ch) )
						push (stfirst, stlast, ch);
						
			
				else //if( priority(stfirst->link->A) > priority(ch) )
				{
					while( !Emptystack(stfirst,stlast) && priority(stfirst->link->A) >= priority(ch) )
					{ 
						outstring += pop (stfirst, stlast);
					}
					push (stfirst, stlast, ch);
				}
			}
		}


					while( !Emptystack (stfirst, stlast)) {
						ch=pop (stfirst, stlast);
						outstring += ch;
					}
					outf << outstring << endl;
	}
}




void main()
{
	stype *stfirst;
	stype *stlast;
	createstack(stfirst, stlast);
	readem (stfirst, stlast);
	system ("pause");
}