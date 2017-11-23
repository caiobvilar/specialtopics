#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "datasets.hpp"
#include <algorithm>
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "USAGE: ./csvparser <file_path>." << std::endl;
	}
	std::ifstream file(argv[1]);	
	std::string inputdata;
	std::vector<Dataset2> dataset_table1;
	std::vector<Dataset2>::iterator dataset_table1_itr;
	Dataset2 sampleset;
	std::size_t start=0,end=0;
	std::vector<std::string> input_vector;
	std::vector<std::string>::iterator input_vector_itr;
	while(file.good())
	{
		getline(file,inputdata,'\n');
		//If the line read from file is empty, skip this iteration(line)
		if(inputdata.empty())
		{
			continue;
		}
		input_vector.push_back(inputdata);
	}
	//Fill dataset with .csv file data.
	for(input_vector_itr = input_vector.begin();input_vector_itr != input_vector.end();input_vector_itr++)
	{
		//Looks for first occurrence of a coma and sets its position as the end of first field
		end = (*input_vector_itr).find(",",start);
		//sets the pais field as the substring formed from the beginning of the inputdata string to the end variable
		sampleset.pais = (*input_vector_itr).substr(start,end);
		//removes the substring and the comma
		(*input_vector_itr).erase(start,end+1);
		//finds new occurrence of a comma and repeats the steps mentioned above
		end = (*input_vector_itr).find(",",start);
		sampleset.lifexpec=std::stod((*input_vector_itr).substr(start,end));
		(*input_vector_itr).erase(start,end+1);
		end = (*input_vector_itr).find(",",start);
		sampleset.education=std::stod((*input_vector_itr).substr(start,end));
		(*input_vector_itr).erase(start,end+1);
		end = (*input_vector_itr).find(",",start);
		sampleset.pib=std::stod((*input_vector_itr).substr(start,end));
		(*input_vector_itr).erase(start,end+1);
		sampleset.pol_stability=std::stod((*input_vector_itr).substr(start,end));
		dataset_table1.push_back(sampleset);
	}

	//Wards method
	// Create all elements as clusters
	std::vector<cluster> cluster_vec;
	std::vector<cluster>::iterator cluster_vec_itr;
	std::vector<cluster>::iterator cluster_vec_itr2;
	cluster samplecluster;
	for(dataset_table1_itr = dataset_table1.begin();dataset_table1_itr != dataset_table1.end();dataset_table1_itr++)
	{
		samplecluster.name = (*dataset_table1_itr).pais;
		samplecluster.centroid=((*dataset_table1_itr).lifexpec+(*dataset_table1_itr).education+(*dataset_table1_itr).pib+(*dataset_table1_itr).pol_stability)/5;
		samplecluster.number_elements=1;
		cluster_vec.push_back(samplecluster);
	}
	std::cout << "Amount of Clusters: " << cluster_vec.size() << std::endl;
	for(cluster_vec_itr = cluster_vec.begin();cluster_vec_itr != cluster_vec.end();cluster_vec_itr++)
	{
		std::cout << "Cluster Name: " << (*cluster_vec_itr).name << " Centroid: " << (*cluster_vec_itr).centroid <<  " N of Elements: " << (*cluster_vec_itr).number_elements << std::endl;
	}
	//Calculate distances
	dist sample_dist;
	for(cluster_vec_itr = cluster_vec.begin();cluster_vec_itr != cluster_vec.end();cluster_vec_itr++)
	{
		for(cluster_vec_itr2 = cluster_vec.begin();cluster_vec_itr2 != cluster_vec.end();cluster_vec_itr2++)
		{
			sample_dist.name1 = (*cluster_vec_itr).name;
			sample_dist.name2 = (*cluster_vec_itr2).name;
			sample_dist.distance = distance((*cluster_vec_itr),(*cluster_vec_itr2));
			(*cluster_vec_itr).distances.push_back(sample_dist);
		}
	}
	std::vector<dist>::iterator dist_itr;
	for(cluster_vec_itr = cluster_vec.begin();cluster_vec_itr != cluster_vec.end();cluster_vec_itr++)
	{
		std::cout << "CLUSTER: " << (*cluster_vec_itr).name << std::endl;
		for(dist_itr = (*cluster_vec_itr).distances.begin();dist_itr != (*cluster_vec_itr).distances.end();dist_itr++)
		{
			std::cout  << "    "<< (*dist_itr).name2 << " | " << (*dist_itr).distance << std::endl;
		}
	}
	//Merge vectors of distances
	std::vector<dist> dist_mat;
	std::vector<dist>::iterator dist_mat_itr;
	for(cluster_vec_itr = cluster_vec.begin();cluster_vec_itr != cluster_vec.end();cluster_vec_itr++)
	{
		std::cout << "CLUSTER: " << (*cluster_vec_itr).name << std::endl;
		for(dist_itr = (*cluster_vec_itr).distances.begin();dist_itr != (*cluster_vec_itr).distances.end();dist_itr++)
		{
			dist_mat.push_back((*dist_itr));
		}
	}
	//std::cout << "Amount of distances[should be 441]: " << dist_mat.size() << std::endl;
	//Sort Distance Vector
	std::sort(dist_mat.begin(), dist_mat.end(),compare);
	for(dist_mat_itr = dist_mat.begin();dist_mat_itr != dist_mat.end();dist_mat_itr++)
	{
		if((*dist_mat_itr).name1 == (*dist_mat_itr).name2)
		{
			dist_mat.erase(dist_mat_itr);
		}
	}
	for(dist_mat_itr = dist_mat.begin();dist_mat_itr != dist_mat.end();dist_mat_itr++)
	{
		std::cout << (*dist_mat_itr).name1 << " | " << (*dist_mat_itr).name2 << std::endl;
	}
	input_vector.clear();
}
