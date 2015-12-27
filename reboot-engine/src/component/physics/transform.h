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
			maths::mat4 m_TransofrmationMatrix;
			maths::mat4 m_TranslationMatrix;
			maths::mat4 m_RotationMatrix;
			maths::mat4 m_ScaleMatrix;

			maths::vec3 m_Position;
			maths::vec3 m_Rotation;
			maths::vec3 m_Scale;

		public:
			entity::GameObject *parent;
			std::vector<entity::GameObject*> childrens;

		public:
			Transform();
			~Transform();

			void createTransformationMatrix();
			void updateChildTransform();

			void addChild(entity::GameObject* child);
			void removeChild(entity::GameObject* child);
			void clearChilds();

			inline maths::vec3& forward() const { return maths::vec3(-m_TransofrmationMatrix.m20, -m_TransofrmationMatrix.m21, -m_TransofrmationMatrix.m22); }
			inline maths::vec3& backward() const { return maths::vec3(m_TransofrmationMatrix.m20, m_TransofrmationMatrix.m21, m_TransofrmationMatrix.m22); }
			inline maths::vec3& down() const { return maths::vec3(-m_TransofrmationMatrix.m10, -m_TransofrmationMatrix.m11, -m_TransofrmationMatrix.m12); }
			inline maths::vec3& up() const { return maths::vec3(m_TransofrmationMatrix.m10, m_TransofrmationMatrix.m11, m_TransofrmationMatrix.m12); }
			inline maths::vec3& left() const { return maths::vec3(-m_TransofrmationMatrix.m00, -m_TransofrmationMatrix.m01, -m_TransofrmationMatrix.m02); }
			inline maths::vec3& right() const { return maths::vec3(m_TransofrmationMatrix.m00, m_TransofrmationMatrix.m01, m_TransofrmationMatrix.m02); }

			void addPosition(maths::vec3& pos);
			void setPosition(maths::vec3 pos);
			void addRotation(maths::vec3& rotation);
			void setRotation(maths::vec3 rotation);
			void addScale(maths::vec3& scale);
			void setScale(maths::vec3 scale);

//			virtual void update() override;

			void setParent(entity::GameObject* parent);
		};
	}
}