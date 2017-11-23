#ifndef DATASETS_HPP
#define DATASETS_HPP
#include <cmath>
class Dataset2
{
	public:

		std::string pais;
		float lifexpec;
		float education;
		float pib;
		float pol_stability;
		float centroid;
		void set_clear()
		{
			this->pais = "";
			this->lifexpec = 0;
			this->education = 0;
			this->pib = 0;
			this->pol_stability = 0;
		}
};

struct dist
{
	std::string name1;
	std::string name2;
	float distance;
};

class cluster
{
	public:
		std::string name;
		float centroid;
		int number_elements;
		std::vector<dist> distances;
		std::vector<Dataset2> sets;
};

float distance(cluster c1,cluster c2)
{
	float euc_dist = pow(c1.centroid-c2.centroid,2);
	float a,b;
	a=(c1.number_elements*c1.number_elements);
	b=(c1.number_elements+c2.number_elements);
	return (a/b)*euc_dist;
}
bool compare(const dist & first,const dist & second)
{
	return first.distance < second.distance;
}
bool needremoval(const dist & first)
{
	return (first.distance == 0);
}
#endif
