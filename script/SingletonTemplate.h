#ifndef _SINGLETON_TEMPLATE_H_
#define _SINGLETON_TEMPLATE_H_

template<class T>

class SingletonTemplate
{
public:
	static T &GetInstance();
protected:
	SingletonTemplate() {};
	~SingletonTemplate() {};
private:
	SingletonTemplate(const SingletonTemplate&);
	const SingletonTemplate &operator=(const SingletomTemplate&);
};

#endif
