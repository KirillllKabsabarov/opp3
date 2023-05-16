#pragma once
#include<iostream>
template<class T> class Storage {
public:
	Storage() {
		size = 1;
		mas = new T[size];
	}
	Storage(int a) {
		size = a;
		mas = new T[size];
	}
	Storage(const Storage& copy) {
		size = copy.size;
		mas = new T[size];
		for (int i = 0; i < size; ++i)
			mas[i] = copy.mas[i];
	}
	~Storage() {
		delete[] mas;
	}

	void pushObject(int ind, T* value);//добавление элемента в контейнер под определенным индексом
	void setObject(int ind, T* value);//присвоение элементу массива пользовательского значения
	T* deleteObject(int ind);//извлечение с удалением
	T* getObject(int ind);//извлечение без удаления
	int getSize();//получение размера контейнера
private:
	T* mas;//указатель на массив
	int size;
};
template<class T>
void Storage<T>::pushObject(int ind, T* value) {
	int tmpind = ind;
	if (tmpind < 0)//приведение некорректного индекса к нормальному значению				  
		tmpind = 0;
	else if (tmpind > size)//приведение некорректного индекса к нормальному значению			  
		tmpind = size;
	T* newmas = new T[size + 1];
	for (int i = 0; i < tmpind; i++)//запись в новый массив элементов до переданного индекса	  
		newmas[i] = mas[i];
	newmas[tmpind] = *value;//запись в новый массив нового объекта под переданным индексом		  
	for (int i = tmpind; i < size; i++)	//запись в новый массив всех элементов старого после переданного индекса	  
		newmas[i + 1] = mas[i];
	delete[] mas;//освбождение памяти от старого массива				  
	mas = newmas;
	size++;
}
template<class T>
T* Storage<T>::deleteObject(int ind) {
	int tmpind = ind;
	if (size == 1)
		return nullptr;
	else if (tmpind >= size)//приведение некорректного индекса к нормальному значению
		tmpind = size - 1;
	else if (tmpind < 0)//приведение некорректного индекса к нормальному значению
		tmpind = 0;
	T* newmas = new T[size - 1];
	T elem = mas[tmpind];//сохранение удаляемого объекта во временную переменную для его возврата из метода 
	for (int i = 0; i < size; i++) {
		if (i < tmpind)//запись в новый массив всех элементов до переданного индекса
			newmas[i] = mas[i];
		else if (i > tmpind)//запись в новый массив всех элементов после переданного индекса
			newmas[i - 1] = mas[i];
	}
	delete[] mas;//освобождение памяти 
	mas = newmas;
	size--;
	return &elem;
}
template<class T>
T* Storage<T>::getObject(int ind) {
	if (size == 0)
		return nullptr;
	else if (ind >= size)//приведение некорректного индекса к нормальному значению
		return &mas[size - 1];
	else if (ind <= 0)//приведение некорректного индекса к нормальному значению
		return &mas[0];
	return &mas[ind];
}
template<class T>
int Storage<T>::getSize() {
	return size;
}
template<class T>
void Storage<T>::setObject(int ind, T* value) {
	if (size == 0)
		return;
	else if (ind <= 0)//приведение некорректного индекса к нормальному значению
		mas[0] = *value;
	else if (ind >= size)//приведение некорректного индекса к нормальному значению
		mas[size - 1] = *value;
	else
		mas[ind] = *value;
}