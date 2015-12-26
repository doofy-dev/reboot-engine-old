#include "transform.h"
#include "../../entity/gameObject.h"


namespace reboot {
	namespace component {
		using namespace maths;
		Transform::Transform() :Component() {
			m_Translation = mat4::translation(vec3(0, 0, 0));
			m_Scale = mat4::scale(vec3(1, 1, 1));
			m_Rotation = mat4::identity();
		}
		
		Transform::~Transform() {
			for (unsigned int i = 0; i < childrens.size(); i++) {
				delete &childrens[i];
			}
		}

		void Transform::update() {

		}

		void Transform::addChild(entity::GameObject* child) {
			child->transform->setParent(gameObject);
			childrens.push_back(child);
		}
	}
}