#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user {
	char name[100];
	int num;
} element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;

	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;

	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;

	if (head == NULL) return NULL;

	removed = head;
	head = removed->link;
	free(removed);

	return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
	ListNode* removed;

	removed = pre->link;
	pre->link = removed->link;
	free(removed);

	return head;
}

ListNode* delete_min(ListNode* head) {
	if (head == NULL) return NULL;

	ListNode* p = head->link;
	ListNode* min = head;
	ListNode* minPre = head;

	while (p != NULL) {
		if (min->data.num > p->data.num) {
			minPre = min;
			min = p;
		}
		p = p->link;
	}

	printf("꼴등 탈락 : %s(%d)\n\n", min->data.name, min->data.num);

	if (min == head) {
		head = delete_first(head);
	}
	else {
		head = delete(head, minPre);
	}

	return head;
}

void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link) {
		printf("(%s : %d) ->", p->data.name, p->data.num);
	}
	printf("NULL\n");
}

ListNode* list_random(ListNode* head) {
	ListNode* p = head;

	while (p != NULL) {
		p->data.num = rand() % 1000;
		p = p->link;
	}

	return head;
}

int main() {
	ListNode* head = NULL;
	int i;
	element user[5];

	for (i = 0; i < 5; i++) {
		memset(&user[i], 0, sizeof(element));
	}

	strcpy(user[0].name, "jaemin");
	strcpy(user[1].name, "jiho");
	strcpy(user[2].name, "hyonseo");
	strcpy(user[3].name, "minji");
	strcpy(user[4].name, "minjeong");

	for (int i = 0; i < 5; i++) {
		head = insert_first(head, user[i]);
	}
	print_list(head);

	printf("\n");

	printf("1라운드\n");
	list_random(head);
	print_list(head);
	head = delete_min(head);

	printf("2라운드\n");
	list_random(head);
	print_list(head);
	head = delete_min(head);

	printf("3라운드\n");
	list_random(head);
	print_list(head);
	head = delete_min(head);

	printf("4라운드\n");
	list_random(head);
	print_list(head);
	head = delete_min(head);

	return 0;
}