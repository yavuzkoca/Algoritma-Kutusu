#include <bits/stdc++.h>
int main(int count = 0, char *temp = 0, int i = 0, FILE *stopWordsFile = 0, FILE *wordsFile = 0){
	std::set<std::string> stopWords;
	for(stopWordsFile = fopen("stopwords.txt", "r"), temp = new char[30]; !feof(stopWordsFile); fscanf(stopWordsFile, "%s \n", temp), stopWords.insert(temp), delete[] temp, temp = new char[30]);
	std::map<std::string, int> testMap;
	for(wordsFile = fopen("input.txt", "r"); !feof(wordsFile); delete[] temp, temp = new char[30]){
		for(fscanf(wordsFile, "%29[a-zA-Z]%*[^a-zA-Z] ", temp), i = 0; *(temp+i) != '\0'; *(temp+(i++)) = (*(temp+i) >= 'A' && *(temp+i) <= 'Z') ? (*(temp+i))-('Z'-'z') : *(temp+i));
		(stopWords.find(temp) != stopWords.end()) ? ((++count, testMap.find(temp) != testMap.end()) ? ++testMap[temp] : testMap[temp] = 1) : 0;
	}
	fclose(wordsFile), fclose(stopWordsFile), delete[] temp;
	std::multimap<int, std::string> freq_rev;
	for(std::map<std::string, int>::iterator it_map = testMap.begin(); it_map != testMap.end(); freq_rev.insert(std::make_pair(it_map->second, it_map->first)), it_map++);
	for(std::multimap<int, std::string>::reverse_iterator myit = freq_rev.rbegin(); myit != freq_rev.rend(); printf("%s \t\t\t Frequency: %.2f %%\t\tCount: %i\n", ((*myit).second).c_str(), (((double)((*myit).first)/count)*100), (*myit).first), myit++);
	return 0;
}