#include "Libr.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ������� ��� �������� ������ ����
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = (char*)malloc(strlen(data) + 1); // +1 ��� '\0'
    strcpy(newNode->data, data); // �������� ������
    newNode->next = NULL; // ���������� ��������� ���� NULL
    return newNode;
}

// ������� ��� ���������� ���� � ����� ������
void append(Node** head, const char* str) {
    Node* new_node = createNode(str);
    if (*head == NULL) {
        *head = new_node;
    }
    else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// ������� ��� ���������� ���� � ������ ������
void append_forward(Node** head, const char* data) {
    Node* new = createNode(data);
    new->next = *head;
    *head = new;
}

// ������� ��� ���������� ������ �� ��� ��������
void split(Node* source, Node** fir, Node** sec) {
    if (source == NULL) {
        *fir = NULL;
        *sec = NULL;
        return; // ���� ������ ����, ������ �� ������
    }

    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;

    // �������� ���������, ����� ������� ������
    while (fast != NULL) {
        fast = fast->next; // ���������� fast �� 1 ����
        if (fast != NULL) {
            slow = slow->next; // ���������� slow �� 1 ����
            fast = fast->next; // ���������� fast �� 1 ����
        }
    }

    *fir = source; // ������ ��������
    *sec = slow->next; // ������ ��������
    slow->next = NULL; // ��������� �����
}

// ������� ��� ������� ���� ��������������� �������
Node* merge(Node* a, Node* b) {
    Node* result = NULL;

    // ������� ������
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // �������� ������� �������
    if (strcmp(a->data, b->data) <= 0) {
        result = a;
        result->next = merge(a->next, b); // ����������� �����
    }
    else {
        result = b;
        result->next = merge(a, b->next); // ����������� �����
    }
    return result;
}

// ������� ���������� ������
void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;

    // ������� ������
    if (head == NULL || head->next == NULL) {
        return;
    }
    // ��������� ������
    split(head, &a, &b);

    // ��������� ��� ��������
    mergeSort(&a);
    mergeSort(&b);

    // ������� ��������������� ��������
    *headRef = merge(a, b);
}

// ������� ��� ������ ������
void printList(Node* node) {
    while (node != NULL) {
        printf("%s\n", node->data);
        node = node->next;
    }
}