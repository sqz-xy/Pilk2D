#include "Component.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class ComponentTransform : public Component
{
	explicit ComponentTransform(glm::vec2 pTranslation, float pAngle, glm::vec2 pScale, int pLayer) {

		ComponentTransform::mTranslation = pTranslation;

	}
};
