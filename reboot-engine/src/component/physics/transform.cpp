#include "transform.h"
#include "../../entity/gameObject.h"


namespace reboot {
	namespace component {
		using namespace maths;
		Transform::Transform() :Component("Transform") {
			m_Position = vec3(0, 0, 0);
			m_Scale = vec3(1, 1, 1);
			m_Rotation = vec3(0, 0, 0);
			parent = nullptr;
			createTransformationMatrix();
		}
		
		Transform::~Transform(){
			clearChilds();
		}

		void Transform::addChild(entity::GameObject* child) {
			child->transform->setParent(gameObject);
			childrens.push_back(child);
			createTransformationMatrix();
		}

		void Transform::setParent(entity::GameObject* parent) {
			this->parent = parent;
			createTransformationMatrix();
		}

		void Transform::createTransformationMatrix() {
			mat4 m_RotationMatrix =
			m_RotationMatrix.rotation(m_Rotation.x, vec3(1, 0, 0))*
			m_RotationMatrix.rotation(m_Rotation.y, vec3(0, 1, 0))*
			m_RotationMatrix.rotation(m_Rotation.z, vec3(0, 0, 1));

			m_TranslationMatrix = mat4::translation(m_Position);
			m_ScaleMatrix = mat4::scale(m_Scale);

			entity::GameObject* par = parent;
			std::vector<entity::GameObject*> branch;
			while (par != nullptr) {
				branch.push_back(par);
				par = par->transform->parent;
			}
			int count = branch.size();
	//		std::cout << count << std::endl;


			mat4 transform(1.0f);

			//std::cout << transform << std::endl;
		/*	for (unsigned  i = count; i-- >0;)
			{
				transform *= branch[i]->transform->m_TranslationMatrix*branch[i]->transform->m_RotationMatrix*branch[i]->transform->m_ScaleMatrix;
			}
		//	std::cout << transform << std::endl;
		/*	if (parent != nullptr) {

				m_TransofrmationMatrix = parent->transform->getTransformationMatrix();
			/*	m_RotationMatrix = parent->transform->m_RotationMatrix * m_RotationMatrix;
				m_ScaleMatrix = parent->transform->m_ScaleMatrix * m_ScaleMatrix;
				m_TranslationMatrix = parent->transform->m_TranslationMatrix * m_TranslationMatrix;
			}
			//*/

			m_TransofrmationMatrix = transform * m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
			updateChildTransform();
//			std::cout << "Transform created: "<<std::endl << m_TransofrmationMatrix << std::endl;
		}

		void Transform::updateChildTransform() {
			for (unsigned int i = 0; i < childrens.size(); i++)
				childrens[i]->transform->createTransformationMatrix();
		}

		void Transform::removeChild(entity::GameObject* child) {
			for (unsigned int i = 0; i < childrens.size(); i++)
				if (childrens[i] == child)
				{
					delete childrens[i];
					break;
				}
		}

		void Transform::clearChilds() {
			for (unsigned int i = 0; i < childrens.size(); i++)
				delete childrens[i];
		}

		void Transform::addPosition(vec3& pos) {
			m_Position += pos;
			createTransformationMatrix();
		}

		void Transform::setPosition(vec3 pos) {
			m_Position = pos;
			createTransformationMatrix();
		}

		void Transform::addRotation(vec3& rotation) {
			m_Rotation += rotation;
			createTransformationMatrix();
		}

		void Transform::setRotation(vec3 rotation) {
			m_Rotation = rotation;
			createTransformationMatrix();
		}

		void Transform::addScale(vec3& scale) {
			m_Scale += scale;
			createTransformationMatrix();
		}

		void Transform::setScale(vec3 scale) {
			m_Scale = scale;
			createTransformationMatrix();
		}

	}
}