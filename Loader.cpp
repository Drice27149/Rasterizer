#include <fstream>
#include <iostream>
#include <cassert>
#include "Loader.hpp"
#include "Vector.hpp"

int isNumber(char c){
	return (c >= '0' && c <= '9') || (c == '.') || (c =='-');
}

float stringToFloat(std::string& s, int l, int r){
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
	triangles.clear();
	
	int cnt = 0;
	
	while(std::getline(infile, line)){
		if(line[0] == 'v'){
			std::vector<float> nums = parseFloat(line);
			assert(nums.size() == 3);
			Vector vertex(3);
			vertex.init(nums);
			vertexs.push_back(vertex);
		}
		else if(line[0] == 'f'){
			// vertex index start from 1
			// option one, compute normal based on given vertex order
			// option two, render both side of the triangle
			cnt++;
			if(cnt == 11) cnt--;
			std::vector<int> nums = parseInt(line); 
			Triangle triangle(vertexs[nums[0]-1], vertexs[nums[1]-1], vertexs[nums[2]-1]);
			triangle.color = Vector((float)cnt*0.05, (float)cnt*0.05, (float)cnt*0.05); // temp
			triangles.push_back(triangle);
		}
		else{
			int haveOtherToken = 1;
			assert(haveOtherToken == 0);
		}
	}
	printf("cnt = %d\n",cnt);
}









