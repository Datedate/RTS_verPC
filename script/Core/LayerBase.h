#ifndef _LAYER_BASE_H_
#define _LAYER_BASE_H_

#include "Object.h"
#include "Rectangle.h"

class LayerBase : public Object
{
public:
	LayerBase() {};
	~LayerBase() {};
	CREATE_FUNC(LayerBase);

	bool Init()override;

	void RemoveAllChildren() override;
	void RemoveChild(std::string _name) override;

	void SetSize(Size _size);
private:
	Size	m_size;
};

#endif