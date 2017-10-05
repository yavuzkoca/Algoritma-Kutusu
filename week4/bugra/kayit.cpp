#import "kayit.h"
#import <string.h>
#import <stdio.h>
#import <stdlib.h>

void Record::Create(const char *name, const char *no){
	int sizeName;
	int sizeTelNo;
	for(sizeName = 0; *(name + sizeName) != '\0'; ++sizeName);
	for(sizeTelNo = 0; *(no + sizeTelNo) != '\0'; ++sizeTelNo);
	this->name = (char *)malloc(sizeof(char) * (sizeName + 1));
	this->no = (char *)malloc(sizeof(char) * (sizeTelNo + 1));
	strcpy(this->name, name);
	strcpy(this->no, no);
}

void Record::Delete(){
	free(name);
	free(no);
}