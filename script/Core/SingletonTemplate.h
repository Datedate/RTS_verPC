#ifndef _SINGLETON_TEMPLATE_H_
#define _SINGLETON_TEMPLATE_H_

#include "ConfigSystem.h"

MY_NAMESPACE_BEGIN

template<class T>

class SingletonTemplate
{
public:
	static T *GetInstance();
protected:
	SingletonTemplate() {};
	~SingletonTemplate() {};
private:
	SingletonTemplate(const SingletonTemplate&);
	const SingletonTemplate &operator=(const SingletomTemplate&);
};

MY_NAMESPACE_END

#endif
