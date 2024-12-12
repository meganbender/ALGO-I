#pragma once
#include<iostream>
#include<cstring>

struct Item
{
	char name[25];
	int qty = 0;
	int weight = 0;
	int value = 0;
	int takenCount = 0; 
};