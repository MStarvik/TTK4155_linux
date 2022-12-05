#pragma once

#include <stdint.h>

typedef struct Node Node;

struct Node{
	Node* parent;
	Node* prevSibling;
	Node* nextSibling;
	Node* firstChild;
	char* string;
	void(*func)(void);
} ;

Node* Node_create(char* string, void(*func)(void));
Node* Node_addChild(Node* parentNode, Node* childNode);

typedef struct UserInterface UserInterface;

struct UserInterface {
	Node* root;
	Node* selected;
};
	
UserInterface* UI_create();
void UI_exit(UserInterface* UI);
void UI_next(UserInterface* UI);
void UI_prev(UserInterface* UI);
void UI_enter(UserInterface* UI);
void UI_draw(UserInterface* UI);
void UI_update(UserInterface* UI, uint8_t x, uint8_t y);
