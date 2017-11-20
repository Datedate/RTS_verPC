#ifndef _CONFIG_SYSTEM_H_
#define _CONFIG_SYSTEM_H_

// �l�[���X�y�[�X
#define MY_NAMESPACE_BEGIN  namespace MyClass{
#define MY_NAMESPACE_END	};
#define US_MY_NAME	using MyClass;
#define MY_NAME MyClass

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#endif
