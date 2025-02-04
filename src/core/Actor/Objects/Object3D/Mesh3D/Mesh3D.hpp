#ifndef MESH3D_HPP
#define MESH3D_HPP

#include <string>

#include "core/Actor/Objects/Object3D/Object3D.hpp"

namespace NoxEngine {

	class Mesh3D: public Object3D {
		public:
			Mesh3D();
			~Mesh3D();

			bool loadFromFile(const std::string& filepath);
	};

}

#endif // MESH3D_HPP