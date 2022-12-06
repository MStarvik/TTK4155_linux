#include "user_interface.h"
#include "../oled_driver/oled_driver.h"

#include <stdio.h>
#include <stdlib.h>

Node* Node_create(char* string, void(*func)(void)) {
	Node* newNode = malloc(sizeof(Node));
	newNode->parent = NULL;
	newNode->prevSibling = NULL;
	newNode->nextSibling = NULL;
	newNode->firstChild = NULL;
	newNode->string = string;
	newNode->func = func;
	
	printf("node created with string %s\r\n", string);
	return newNode;
}

Node* Node_addChild(Node* parentNode, Node* childNode) {
	childNode->parent = parentNode;
	
	if (parentNode->firstChild == NULL) { //No other children
		parentNode->firstChild = childNode;
	} else { //Other children
		Node* currentChild = parentNode->firstChild;
		while(currentChild->nextSibling != NULL) {
			currentChild = currentChild->nextSibling;
		}
		currentChild->nextSibling = childNode;
		childNode->prevSibling = currentChild;
	}
	
	Node* currentNode = parentNode->firstChild;
	printf("children added to %s, current children are:\r\n", parentNode->string);
	while (currentNode != NULL) {
		printf("%s\r\n", currentNode->string);
		currentNode = currentNode->nextSibling;
	}
	
	return childNode;
}

UserInterface* UI_create() {
	UserInterface* UI = malloc(sizeof(UserInterface));
	Node* root = Node_create(NULL, NULL);
	UI->selected = NULL;
	root->string="";
	UI->root = root;
	
	return UI;
}

void UI_exit(UserInterface* UI) {
	if (UI->selected->parent == NULL) return;
	UI->selected = UI->selected->parent;
}

void UI_next(UserInterface* UI) {
	if (UI->selected->nextSibling == NULL) return;
	UI->selected = UI->selected->nextSibling;
}

void UI_prev(UserInterface* UI) {
	if (UI->selected->prevSibling == NULL) return;
	UI->selected = UI->selected->prevSibling;
}

void UI_enter(UserInterface* UI) {
	if (UI->selected->firstChild == NULL) {
		if (UI->selected->func == NULL) return;
		UI->selected->func();
	} else {
		UI->selected = UI->selected->firstChild;
	}
}

void UI_draw(UserInterface* UI) {
	oled_pos(0,0);
	uint8_t pos = 0;
	Node* currentNode = UI->selected->parent->firstChild;
	while (currentNode != NULL) {
		if (currentNode == UI->selected) {
			//OLED_print(">");
			oled_print_arrow();
		} else {
			oled_print(" ");
		}
		oled_print(currentNode->string);
		currentNode = currentNode->nextSibling;
		pos++;
		oled_pos(pos, 0);
	}
}