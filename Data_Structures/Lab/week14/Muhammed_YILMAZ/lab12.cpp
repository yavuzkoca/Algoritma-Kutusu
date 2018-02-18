#include <fstream>
#include <iostream>
#include <set>
#include <map>
#include <locale>
using namespace std;

bool isLetter( char ch );
string tolowerString(string temp);

int main(){

	set<string> stopWords;
	map<string,int> output;
	multimap<int,string> outputRev;

	fstream words,input;
	words.open("stopwords.txt");
	input.open("input.txt");

	string temp;
	while( words >> temp )
	{
		stopWords.insert(temp);
	}

	int numberInput=0;
	while( input >> temp )
	{
		temp = tolowerString(temp);
		if( stopWords.find(temp)!=stopWords.end())
		{
			output[temp]++;
			numberInput++;
		}
	}

	map <string,int>::iterator itr;
	for(itr = output.begin(); itr != output.end(); ++itr)
	{
		outputRev.insert ( pair<int,string>(itr->second,itr->first));
	}

	cout << endl << "Number of word in input file: " << numberInput << endl << endl;

	multimap <int,string>::iterator itrr;
	for(itrr = outputRev.end(); itrr != outputRev.begin(); )
	{
		--itrr;
		cout << itrr->second << "\t" << itrr->first << "\t"
			 <<  (float)itrr->first/(float)numberInput*100 << endl;
	}

	return 0;
}


bool isLetter( char ch ){

	if( ( ch>='a' && ch<='z' ) || ( ch>='A' && ch<='Z' ) )
		return 1;

	return 0;
}

string tolowerString(string temp){

	string temp2;
	for (int i = 0, j=0 ; i < (int)temp.size() ; ++i)
	{
		if(isLetter(temp[i]))
		{
			temp2+= tolower(temp[i]);
		}
	}

	return temp2;
}