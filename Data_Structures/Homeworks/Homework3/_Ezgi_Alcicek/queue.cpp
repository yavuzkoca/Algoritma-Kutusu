#include "queue.h"

bool list::enqueue(patient* newpatient) {
	patient *temp = newpatient;
	if (!isEmpty()) {
		last->next = temp;
		last = temp;
	}
	else {
		head = temp;
		last = temp;
	}
	last->next = NULL;
	++size;
	return true;
}
patient* list::dequeue() {
	if (head == NULL) return NULL;
	patient* temp = head;
	head = head->next;
	return temp;
	delete temp;
}
bool list::isEmpty() { return head == NULL ? true : false; }
void list::create() { head = NULL; last = NULL; size = 0; }