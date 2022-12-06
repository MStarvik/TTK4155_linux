#include "menu.h"
#include "../user_interface/user_interface.h"
#include "../oled_buffer/oled_buffer.h"

#include <stdio.h>
#include <avr/io.h>

static UserInterface* UI;

void test(void) {
	printf("first_child1 function!\r\n");
}

void timer_init() {
	TCNT0 = 95;
	
	TCCR0 |= (1 << CS20) | (1 << CS02);
	
	TIMSK |= (1 << TOIE0);
}

static unsigned int t = 0;
ISR(TIMER0_OVF_vect) {
	TCNT0 = 95;
	oled_buffer_reset();
	UI_draw(UI);
	oled_buffer_flush();
}

void menu_init() {
	UI = UI_create();
	Node* first = Node_create("first", NULL);
	Node* second = Node_create("second", NULL);
	Node* third = Node_create("third", NULL);
	Node* fourth = Node_create("fourth", NULL);
	Node* fifth = Node_create("fifth", NULL);
	Node* sixth = Node_create("sixth", NULL);
	Node* seventh = Node_create("seventh", NULL);
	Node* eighth = Node_create("eighth", NULL);
	
	Node* first_child1 = Node_create("first_child1", test);
	Node* first_child2 = Node_create("first_child2", test);
	Node* first_child3 = Node_create("first_child3", test);
	
	Node* second_child1 = Node_create("second_child1", test);
	Node* second_child2 = Node_create("second_child2", test);
	
	Node* third_child1 = Node_create("third_child1", test);
	
	Node* first_child1_child1 = Node_create("first_child1_child1", test);
	Node* first_child1_child2 = Node_create("first_child1_child2", test);
	
	Node_addChild(UI->root, first);
	Node_addChild(UI->root, second);
	Node_addChild(UI->root, third);
	Node_addChild(UI->root, fourth);
	Node_addChild(UI->root, fifth);
	Node_addChild(UI->root, sixth);
	Node_addChild(UI->root, seventh);
	Node_addChild(UI->root, eighth);
	
	Node_addChild(first, first_child1);
	Node_addChild(first, first_child2);
	Node_addChild(first, first_child3);
	
	Node_addChild(second, second_child1);
	Node_addChild(second, second_child2);
	
	Node_addChild(third, third_child1);
	
	Node_addChild(first_child1, first_child1_child1);
	Node_addChild(first_child1, first_child1_child2);
	
	UI->selected = first;
	
	timer_init();
}

void menu_update(const uint8_t x, const uint8_t y) {
	UI_update(UI, x, y);
}