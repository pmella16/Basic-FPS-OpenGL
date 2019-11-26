#include "map.h"

Map::Map() {}

void Map::init() {
	//Positions for houses
	std::vector<vec3> positions = {
		   vec3(-5.0, 0.0, 5.0),
		  vec3(5.0, 0.0, 5.0),
		  vec3(-5.0, 0.0, -5.0),
		  vec3(5.0, 0.0, -5.0)
	};

	//Add houses to the map
	for (int i = 0; i < n_houses; i++) {
		House house;
		house.move(positions.at(i));
		houses.push_back(house);
	}

	m_coords = { m_coord_a, m_coord_b, m_coord_c, //suelo
				m_coord_a, m_coord_c, m_coord_d,
				m_coord_a, m_coord_b, m_coord_e, //pared lateral
				m_coord_e, m_coord_f, m_coord_b,
				m_coord_f, m_coord_g, m_coord_b, //pared trasera
				m_coord_g, m_coord_b, m_coord_c,
				m_coord_c, m_coord_g, m_coord_h, //pared lateral
				m_coord_d, m_coord_h, m_coord_c,
				m_coord_h, m_coord_d, m_coord_a, //pared frontal
				m_coord_h, m_coord_a, m_coord_e
	};
	c_coords = { c_mfloor, c_mfloor, //Suelo
				c_mwall, c_mwall, //pared lateral
		c_mwall, c_mwall, //Pared trasera
		c_mwall, c_mwall, //Pared lateral
		c_mwall, c_mwall, //pared frontal
	};
}

/*
 * Function getCoords() gets all of the coordinates for the map
 */
std::vector<float> Map::getPosCoords() {
	std::vector<float> result;
	for (unsigned int i = 0; i + 3 <= m_coords.size(); i = i + 3) {
		result.push_back(m_coords.at(i));
		result.push_back(m_coords.at(i + 1));
		result.push_back(m_coords.at(i + 2));
		result.push_back(c_coords.at(i));
		result.push_back(c_coords.at(i + 1));
		result.push_back(c_coords.at(i + 2));
	}

	for (int i = 0; i < n_houses; i++) {
		std::vector<float> tmp = houses.at(i).getPosCoords();
		for (unsigned int j = 0; j < tmp.size(); j++) {
			result.push_back(tmp.at(j));
		}
	}
	return result;
}

/*
 * Function moveHouse moves the house_id by the vector mov in {x, y, z} coordinates
 */
void Map::moveHouse(int house_id, vec3 mov) {
	if (house_id <= 0 || house_id >= n_houses) throw "Incorrect house id";
	houses.at(house_id).move(mov);
}
