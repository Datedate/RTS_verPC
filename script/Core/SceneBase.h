#ifndef _SCENE_BASE_H_
#define _SCENE_BASE_H_

#include "Object.h"
#include "Rectangle.h"

class CameraBase;
class LightBase;

class SceneBase :public Object
{
public:
	SceneBase() {};
	~SceneBase() {};
	CREATE_FUNC(SceneBase);

	CameraBase* GetCamera() const { return m_camera; }
	LightBase* GetLight() const { return m_light; }

	//virtual void Render(Renderer* renderer, const Mat4& eyeTransform, const Mat4* eyeProjection = nullptr);
	//virtual void Render(Renderer* renderer, const Mat4* eyeTransforms, const Mat4* eyeProjections, unsigned int multiViewCount);

	/** override function */
	bool Init()override;
	//virtual void AddChild(Object* _child);
	virtual void RemoveAllChildren() override;
	virtual void RemoveChild(std::string _childname)override;
protected:
	CameraBase*	m_camera;
	LightBase*	m_light;
	Size		m_size;
};

#endif

