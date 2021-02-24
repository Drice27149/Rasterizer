#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include "Loader.hpp"
#include "Vector.hpp"

int isNumber(char c){
	return (c >= '0' && c <= '9') || (c == '.') || (c =='-') || (c=='e');
}

float stringToFloat(std::string& s, int l, int r){
	// judge 1.5e-002
	int findE = -1;
	for(int i = l; i <= r; i++) if(s[i] == 'e') findE = i;
	if(findE != -1){
		// adjust scale for small obj such as bunny.obj
		return stringToFloat(s, l, findE-1) * std::pow(10.0, stringToFloat(s, findE+1, r)+2.0);
	}
	
	// judge 1.5
	int neg = 0;
	if(s[l] == '-') neg = 1, l++;
	int dotPos = r+1;
	for(int i = l; i <= r; i++) if(s[i] == '.') dotPos = i;
	float left = 0.0f, right = 0.0f;
	for(int i = l; i <= dotPos-1; i++){
		left = left * 10.0 + (s[i] - '0');
	}
	for(int i = r; i >= dotPos+1; i--){
		right = right * 0.1 + (s[i] - '0');
	}
	if(!neg) return left + right * 0.1;
	else return -(left + right * 0.1);
}

int stringToInt(std::string& s, int l, int r){
	int neg = 0;
	if(s[l] == '-') neg = 1, l++;
	int left = 0;
	for(int i = l; i <= r; i++) left = left * 10 + s[i] - '0';
	if(!neg) return left;
	else return -left;
}

std::vector<float> parseFloat(std::string line){
	std::vector<float> nums;
	int ptr = 0;
	while(ptr < line.size()){
		if(!isNumber(line[ptr])) ptr++;
		else{
			int np = ptr;
			while(np+1 < line.size() && isNumber(line[np+1])) np++;
			nums.push_back(stringToFloat(line, ptr, np));
			ptr = np + 1;
		}
	}
	return nums;
}

std::vector<int> parseInt(std::string line){
	std::vector<int> nums;
	int ptr = 0;
	while(ptr < line.size()){
		if(!isNumber(line[ptr])) ptr++;
		else{
			int np = ptr;
			while(np+1 < line.size() && isNumber(line[np+1])) np++;
			nums.push_back(stringToInt(line, ptr, np));
			ptr = np + 1;
		}
	}
	return nums;
}

void Loader::loadFile(std::string fileName){
	std::ifstream infile(fileName);
	std::string line;
	std::vector<Vector> vertexs;
	std::vector<Vector> normals;
	std::vector<Vector> uvs;
	triangles.clear();
	
	while(std::getline(infile, line)){
		if(line[0] == 'v' && line[1] == ' '){
			// vertex
			std::vector<float> nums = parseFloat(line);
			assert(nums.size() == 3);
			Vector vertex(3);
			vertex.init(nums);
			vertexs.push_back(vertex);
			normals.push_back(Vector(0.0f, 0.0f, 0.0f));
		}
		else if(line[0] == 'f'){
			// face v/vt/vn
			// vertex index start from 1
			std::vector<int> nums = parseInt(line); 
			if(nums.size() == 3){
				Triangle triangle(vertexs[nums[0]-1], vertexs[nums[1]-1], vertexs[nums[2]-1]);
				triangle.vid[0] = nums[0] - 1;
				triangle.vid[1] = nums[1] - 1;
				triangle.vid[2] = nums[2] - 1;
				for(int num: nums) normals[num - 1] = normals[num - 1] + triangle.normal;
				triangles.push_back(triangle);
			}
			else if(nums.size() == 6){
				Triangle triangle(vertexs[nums[0]-1], vertexs[nums[2]-1], vertexs[nums[4]-1]);
				for(int i = 0; i < 6; i++){
					if(!(i%2)){
						triangle.vid[i/2] = nums[i] - 1;
						normals[nums[i] - 1] = normals[nums[i] - 1] + triangle.normal;
					}
					else{
						triangle.st[i/2] = uvs[nums[i] - 1];
					}
				}
				triangles.push_back(triangle);
			}
			else{
				int invalidNumberCount = 1;
				assert(invalidNumberCount == 0);
			}
		}
		else if(line[0] == '#'){
			// comment line
		}
		else if(line[0] == 'v' && line[1] == 't'){
			std::vector<float> nums = parseFloat(line);
			assert(nums.size() == 2);
			Vector uv(2);
			uv.init(nums);
			uvs.push_back(uv);
		}
		else{
			int haveOtherToken = 1;
			assert(haveOtherToken == 0);
		}
	}
	
	for(Vector& normal: normals) normal.normalize();
	for(Triangle& triangle: triangles){
		triangle.Kd = Vector(0.2, 0.2, 0.2);
		triangle.Ks = Vector(0.5, 0.5, 0.5);
		triangle.Ka = Vector(0.005, 0.005, 0.005);
		for(int i = 0; i < 3; i++) triangle.normals[i] = normals[triangle.vid[i]];
	}
}









