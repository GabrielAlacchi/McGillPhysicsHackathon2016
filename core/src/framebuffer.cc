
#include "framebuffer.hpp"
#include <unistd.h>
#include <fstream>

using namespace vecmath;

void FrameBuffer::appendToFile(std::string json, bool start) {
	std::ofstream file("/tmp/buffer.json", std::ios::out | std::ios::app);

	if (start) {
		file << "{\n\"timestep\": " << _timestep << ",\n\"frames\": "; 
		file << "[\n";
	} else {
		file << ",\n";
	}
	file << json;
}

std::string FrameBuffer::unloadJSON() {
	std::string json = "{ \"frame\": [";
	
	bool firstPass = true;	
	for (BodyData& body : _frame) {
		
		json += firstPass ? "" : ",";
		json += "{";
		json += " \"pos\": {\"x\": " + std::to_string(body.pos.x);
		json += ",\"y\": " + std::to_string(body.pos.y);
		json += ",\"z\": " + std::to_string(body.pos.z);
		json += "},\"mass\": " + std::to_string(body.mass);
		json += ",\"kinetic\": " + std::to_string(body.kinetic);
		json += ",\"potential\": " + std::to_string(body.potential);
		json += ",\"angular\":{\"x\": " + std::to_string(body.angularMomentum.x);
		json += ",\"y\": " + std::to_string(body.angularMomentum.y);
		json += ",\"z\": " + std::to_string(body.angularMomentum.z);
		json += "}}";
		firstPass = false;
	}

	json += "]}";	

	return json;

}

FrameBuffer::FrameBuffer(std::size_t n, long double timestep) {
	_frame.resize(n);
	_timestep = timestep;
}

void FrameBuffer::resize(std::size_t n) {
	_frame.resize(n);
}

void FrameBuffer::setNthBody(std::size_t n, vec3 pos, long double mass, long double kinetic, long double potential, vec3 angular) {
	BodyData& data = _frame.at(n);
	data.pos = pos;
	data.mass = mass;
	data.kinetic = kinetic;
	data.potential = potential;
	data.angularMomentum = angular;
}

void FrameBuffer::sendFrame() {
	
	if (_counter == 0) {
		std::fstream testStream("/tmp/buffer.json");
		if (testStream.good()) {
			testStream.close();
			system("rm /tmp/buffer.json");
		}
	}

	std::string json = unloadJSON();

	bool start = _counter % 60 == 0;	
	if (start) {
	
		if (_counter > 0) {
			std::ofstream file("/tmp/buffer.json", std::ios::out | std::ios::app);
			file << "\n]}";
			file.close();	
		
			std::string curl = "curl 'https://nbodyblackmagic.firebaseio.com/nbodyblackmagic/frame.json' -X PUT -H 'Accept-Encoding: gzip, deflate, sdch, br' -H 'Accept-Language: en-US,en;q=0.8,fr-CA;q=0.6,fr;q=0.4' -H 'User-Agent: cUrl' -H 'Content-Type: application/json' -H 'Accept: ​/​' -H 'Cache-Control: no-cache' -H 'Connection: keep-alive' -H 'DNT: 1' --data-binary @/tmp/buffer.json --compressed";
	
			system(curl.c_str());
			
			std::string dirtyHack = "python ./src/createPlots.py " + std::to_string(_counter);
			dirtyHack += "; rm /tmp/buffer.json";	
			//The dirtiest of dirty hacks	
			//system(dirtyHack.c_str());
			system("rm /tmp/buffer.json");
		}

	}

	++_counter;

	appendToFile(json, start);

}

