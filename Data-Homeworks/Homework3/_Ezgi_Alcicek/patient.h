#ifndef patients
#define patients
struct patient{
	patient* next;
	char name[10];
	int arrive;
	int treatment;
	int codenumber;
	char code[7];
};
#endif // !patients