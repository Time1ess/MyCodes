class Car {
  int license_plate;
  static int required_spaces;
  public:
  virtual int get_required_spaces() const = 0;
  int get_license_plate() const {
    return license_plate;
  }
};

int Car::required_spaces = 1;

class SmallCar: public Car {
  static int required_spaces;
  public:
  virtual int get_required_spaces() const {
    return SmallCar::required_spaces;
  }
};

int SmallCar::required_spaces = 1;

class MediumCar: public Car {
  static int required_spaces;
  public:
  virtual int get_required_spaces() const {
    return MediumCar::required_spaces;
  }
};

int MediumCar::required_spaces = 2;

class LargeCar: public Car {
  static int required_spaces;
  public:
  virtual int get_required_spaces() const {
    return LargeCar::required_spaces;
  }
};

int LargeCar::required_spaces = 4;

class Space {
  bool available;

  public:
  bool is_available() {
    return available;
  }
  void set_unavailable() {
    available = false;
  }
  void set_available() {
    available = true;
  }
};

class Floor {
  vector<Space> spaces;
  unordered_map<int, vector<int>> status;  // license_plate -> space indices
  public:
  bool park(const Car* car) {
    int n = spaces.size();
    int required_spaces = car->get_required_spaces();
    for(int i = 0; i < n - required_spaces; i++) {
      bool can_park = true;
      for(int j = i; j < i + required_spaces; j++) {
        if(!spaces[j].is_available()) {
          can_park = false;
          break;
        }
      }
      if(can_park) {
        for(int j = i; j < i + required_spaces; j++) {
          status[car->get_license_plate()].push_back(j);
          spaces[j].set_unavailable();
        }
        return true;
      }
    }
    return false;
  }
  void leave(const Car* car) {
    int license_plate = car->get_license_plate();
    if(status.find(license_plate) == status.end()) {
      return;  // No parking info
    }
    for(auto x: status[license_plate]) {
      spaces[x].set_available();
    }
    status.erase(license_plate);
  }
};

class ParkingLot {
  vector<Floor> floors;
  unordered_map<int, int> status;  // license_plate -> floor index
  unordered_map<int, int> start_time;  // Parking start time
  protected:
  int get_now_time() {
    return 0;
  }
  virtual int get_charge_fee(const Car* car, int st, int et) {
    return (et - st) * 10;
  }
  public:
  ParkingLot(vector<Floor> floors) {
    this->floors = floors;
  }
  bool park(const Car* car) {
    int n = floors.size();
    for(int i = 0; i < n; i++) {
      if(floors[i].park(car)) {
        status[car->get_license_plate()] = i;
        start_time[car->get_license_plate()] = get_now_time();
        return true;
      }
    }
    return false;
  }
  void leave(const Car* car) {
    int license_plate = car->get_license_plate();
    if(status.find(license_plate) == status.end()) {
      return;  // No parking info
    }
    start_time.erase(license_plate);
    status.erase(license_plate);

    Floor& floor = floors[status[license_plate]];
    floor.leave(car);

    // Charge
    int st = start_time[license_plate];
    int et = get_now_time();
    get_charge_fee(car, st, et);
  }
};



