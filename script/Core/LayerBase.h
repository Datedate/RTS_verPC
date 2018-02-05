#ifndef _LAYER_BASE_H_
#define _LAYER_BASE_H_

#include "Object.h"
#include "Rectangle.h"

class SpriteBase;
class ParticleSystem;

class LayerBase : public Object
{
public:
	LayerBase() {};
	~LayerBase() {};
	CREATE_FUNC(LayerBase);

	bool Init()override;
	void RemoveAllChildren() override;
	void RemoveChild(std::string _name) override;
	void AddChild(SpriteBase* _sprite);
	void AddChild(SpriteBase* _sprite, int order);
	void AddChild(ParticleSystem* _particle);
	void AddChild(ParticleSystem* _particle , int order);
	void SortChildren();
	void PushSpriteToRenderer();
	void SetSize(Size _size);
	std::vector<Object*> GetSpriteContainer()const;
private:
	Size	m_size;
	bool	m_isChildChange;
};

#endif