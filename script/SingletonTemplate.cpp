#include "SingletonTemplate.h"

template<class T>
T &SingletonTemplate<T>::GetInstance() {
	static T *instance = nullptr;
	if (instance == nullptr) {
		instance = new T();
	}
	return *instance;
}