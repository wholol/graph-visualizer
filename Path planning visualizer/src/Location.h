#pragma once
struct Location {
	int posx;
	int posy;
	bool operator==(const Location& other) const{
		return posx == other.posx && posy == other.posy;
	}

	bool operator()(const Location& other) const {		//for set finding
		return posx == other.posx && posy == other.posy;
	}

	bool operator<(const Location& other) {
		return posx < other.posx && posy < other.posy;
		
	}
};