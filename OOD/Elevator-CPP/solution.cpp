enum Mode {
	UP,
DOWN, 
IDLE, 
DISPATCH_UP,
DISPATCH_DOWN,
};

const int MAX_LEVEL = 10;
const int MIN_LEVEL = 1;

class Elevator {
	int current_level;
	int target_level;
	Mode mode;
	vector<bool> levels;

	void open_door() {}
void close_door() {}
void go_up() {
	current_level++;
	assert(current_level <= MAX_LEVEL);
}
	void go_down() {
	current_level--;
	assert(current_level >= MIN_LEVEL);
}
	void run_step() {
	if(mode == IDLE)
		return;
	if(current_level < target_level) {
		go_up();
	} else if(current_level > target_level) {
		go_down();
	}
	if(mode == DISPATCH_UP && current_level == target_level) {
		mode = UP;
} else if(mode == DISPATCH_DOWN && current_level == target_level) {
	mode = DOWN;
}
if(levels[current_level] == true) {
	levels[current_level] = false;
open_door();
handle_requests();
close_door();
}
// If no more requests, set idle
bool set_idle = true;
for(auto req: levels) {
	if(req == true) {
set_idle = false;
break;	
}
}
if(set_idle) {
	mode = IDLE;
}
}
// Handle requests inside elevator
void handle_requests() {}
public:
	Elevator() {
		this->current_level = 1;
		this->mode = IDLE;
}
	bool handle_request(int level, Mode mode) {
		assert(mode == UP || mode == DOWN);
		if(mode == DISPATCH_UP || mode == DISPATCH_DOWN) {
			return false;
}
	if(mode == IDLE) {
		target_level = level;
		if(mode == UP) {
			mode = DISPATCH_UP;
		} else {
mode = DISPATCH_DOWN;		
}
levels[level] = true;
return true;
}
if(mode == UP && this->mode == UP && current_level < level) {
	target_level = max(target_level, level);
	levels[level] = true;
	return true;
} else if(mode == DOWN && this->mode == DOWN && current_level > level) {
	target_level = min(target_level, level);
	levels[level] = true;
	return true;
}
return false;
}
};

class Controller {
	vector<Elevator> elevators;
	
	bool go_up(int level) {
	for(auto elevator: elevators) {
		if(elevator.handle_request(level, UP)) {
return true;		
}
}
return false;
}
	bool go_down(int level) {
	for(auto elevator: elevators) {
		if(elevator.handle_request(level, DOWN)) {
return true;		
}
}
return false;
}
}
