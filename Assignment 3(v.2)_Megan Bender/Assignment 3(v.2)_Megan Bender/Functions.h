#pragma once

void algMenu(char& param);
void fileNameMenu(char& filecChoiceParam);
int* readFile(char fileChoiceParam, int& sizeParam);
void heapsort_func();
void heapWalkUp(int* arrayParam, int sizeParam);
void heapWalkDown(int* arrayParam, int sizeParam);
void radixSort(int* arrayParam, int sizeParam);