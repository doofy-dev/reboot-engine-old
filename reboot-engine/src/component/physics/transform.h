#pragma once

#include <vector>
#include "../component.h"
#include "../../math/maths.h"

namespace reboot {
	namespace entity {
		class GameObject;
	}
	namespace component {
		class Transform : public Component{
		private:
			maths::mat4 m_Transofrmation;
			maths::mat4 m_Translation;
			maths::mat4 m_Rotation;
			maths::mat4 m_Scale;

		public:
			entity::GameObject *parent;
			std::vector<entity::GameObject*> childrens;

		public:
			Transform();
			~Transform();

			void createTransformationMatrix();
			void updateChildTransform();
			void Transform::addChild(entity::GameObject* child);
			virtual void update() override;

			inline void setParent(entity::GameObject* parent) { this->parent = parent; }
		};
	}
}