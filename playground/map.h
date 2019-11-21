#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

//Coordinates for the ground and walls of map
#define m_coord_a 10.0f, -1.0f, 10.0f
#define m_coord_b 10.0f, -1.0f, -10.0f
#define m_coord_c -10.0f, -1.0f, -10.0f
#define m_coord_d -10.0f, -1.0f, 10.0f
#define m_coord_e 10.0f, 1.0f, 10.0f
#define m_coord_f 10.0f, 1.0f, -10.0f
#define m_coord_g -10.0f, 1.0f, -10.0f
#define m_coord_h -10.0f, 1.0f, 10.0f
//color
#define c_mwalls 0.8f, 0.7f, 0.7f
#define c_mfloors 0.4f, 0.4f, 0.4f
#define c_mwall c_mwalls, c_mwalls, c_mwalls
#define c_mfloor c_mfloors, c_mfloors, c_mfloors

//Coordinates for the houses
#define h_coord_a -0.5f, -1.0f, 0.5f
#define h_coord_b 0.5f, -1.0f, 0.5f
#define h_coord_c -0.5f, 0.0f, 0.5f
#define h_coord_d 0.5f, 0.0f, 0.5f
#define h_coord_e 0.0f, 0.4f, 0.5f
#define h_coord_f -0.5f, -1.0f, -0.5f
#define h_coord_g 0.5f, -1.0f, -0.5f
#define h_coord_h -0.5f, 0.0f, -0.5f
#define h_coord_i 0.5f, 0.0f, -0.5f
#define h_coord_j 0.0f, 0.4f, -0.5f
//Color
#define c_hwalls 1.0f, 1.0f, 0.8f
#define c_hroofs 1.0f, 0.6f, 0.4f
#define c_hroof c_hroofs, c_hroofs, c_hroofs
#define c_hwall c_hwalls, c_hwalls, c_hwalls

//Number of vertices in whole map
#define n_vertexes_h 42 * 3
#define n_houses 4
#define n_vertexes_m 30 * 3
#define n_vertexes ((n_vertexes_h * n_houses) + n_vertexes_m) * 2


class Map {
private:
	//Class and object house
	class House {
		std::vector<float> h_coords;
		std::vector<float> c_coords;
	public:
		House() {
			h_coords = { h_coord_a, h_coord_b, h_coord_c, //Pared frontal
						h_coord_c, h_coord_b, h_coord_d,
						h_coord_d, h_coord_g, h_coord_b, //pared lateral
						h_coord_d, h_coord_i, h_coord_g, 
						h_coord_h, h_coord_f, h_coord_g, //pared trasera
						h_coord_g, h_coord_i, h_coord_h,
						h_coord_c, h_coord_a, h_coord_f, //pared lateral
						h_coord_c, h_coord_f, h_coord_h,
						h_coord_c, h_coord_e, h_coord_d, //techo frontal
						h_coord_h, h_coord_j, h_coord_i, //techo trasero
						h_coord_d, h_coord_e, h_coord_i, //techo lateral
						h_coord_e, h_coord_i, h_coord_j,
						h_coord_c, h_coord_e, h_coord_j, //techo lateral
						h_coord_c, h_coord_h, h_coord_j
			};
			c_coords = { c_hwall, c_hwall, //pared frontal
				c_hwall, c_hwall, //pared lateral
				c_hwall, c_hwall, //pared trasera
				c_hwall, c_hwall, //pared lateral
				c_hroof, //techo frontal
				c_hroof, //techo trasero
				c_hroof, c_hroof, //techo lateral
				c_hroof, c_hroof //techo lateral
			};
		}

		void move(vec3 disp) {
			for (unsigned int i = 0; i < h_coords.size(); i = i + 3) {
				h_coords.at(i) += disp.x;
				h_coords.at(i+1) += disp.y;
				h_coords.at(i+2) += disp.z;
			}
		}
		std::vector<float> getPosCoords() {
			std::vector<float> result;
			for (unsigned int i = 0; i+3 <= h_coords.size(); i = i + 3) {
				result.push_back(h_coords.at(i));
				result.push_back(h_coords.at(i+1));
				result.push_back(h_coords.at(i+2));
				result.push_back(c_coords.at(i));
				result.push_back(c_coords.at(i + 1));
				result.push_back(c_coords.at(i + 2));
			}
			return result;
		}
	};


	//Map variables
	std::vector<float> m_coords;
	std::vector<float> c_coords;
	std::vector<House> houses;

public: 
	Map();
	void init();
	int getNumHouses() { return n_houses;}
	std::vector<float> getPosCoords();
	void moveHouse(int house_id, vec3 mov);
};

#endif