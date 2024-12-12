#pragma once

void algMenu(char& param);
void fileNameMenu(char& filecChoiceParam);
int* readFile(char fileChoiceParam, int& sizeParam);
void innerMerge(int low, int mid, int high, int* src, int* dest);
void merge_func(int low, int high, int* src, int* dest);
int partition(int start, int end, int* arrParam);
void quickSort_func(int low, int high, int* arrParam2 );