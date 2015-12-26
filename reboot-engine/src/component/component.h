#pragma once



namespace reboot {
	namespace entity {
		class GameObject;
	}
	namespace component {

		class Component {
		public:
			entity::GameObject *gameObject;
			Component();
			virtual ~Component();
			virtual void update();

			inline void assingGameObject(entity::GameObject* GameObject) { this->gameObject = GameObject; }
		};
	}
}