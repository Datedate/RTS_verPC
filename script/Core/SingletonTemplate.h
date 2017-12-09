#ifndef _SINGLETON_TEMPLATE_H_
#define _SINGLETON_TEMPLATE_H_

template<class T>

class SingletonTemplate
{
public:
	static T* GetInstance() {
		static T *instance = nullptr;
		if (instance == nullptr) {
			instance = new T();
		}
		return instance;
	}
protected:
	SingletonTemplate() {};
	~SingletonTemplate() {};
private:
	SingletonTemplate(const SingletonTemplate&);
	const SingletonTemplate &operator=(const SingletonTemplate&) ;
};

#endif
