#include "SingletonTemplate.h"

MY_NAMESPACE_BEGIN

template<class T>
T* SingletonTemplate<T>::GetInstance() {
	static T *instance = nullptr;
	if (instance == nullptr) {
		instance = new T();
	}
	return instance;
}

MY_NAMESPACE_END