#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <unordered_map>

using namespace std;
class Customer {
  private:
    int id;
  public:
    Customer(int id) {
      this->id = id;
    }
    int get_id() {
      return id;
    }
};

enum RoomType {
  SMALL_ROOM,
  MEDIUM_ROOM,
  LARGE_ROOM,
};

class Pricer {
  public:
    float get_price(int days) {
      return days * 10;
    }
};

class Room {
  private:
    int id;
    RoomType type;
    Pricer pricer;
    bool available;
  public:
    Room(int id, RoomType type, Pricer pricer) {
      this->id = id;
      this->type = type;
      this->pricer = pricer;
      this->available = true;
    }
    int get_id() {
      return id;
    }
    void set_pricer(Pricer pricer) {
      this->pricer = pricer;
    }
    bool get_available() {
      return available;
    }
    void set_unavailable() {
      available = false;
    }
    void set_available() {
      available = true;
    }
    float get_price(int days) {
      return pricer.get_price(days);
    }
};

class Hotel {
  unordered_map<RoomType, vector<Room>> rooms;
  unordered_map<int, Room*> reservations;  // customer_id -> room
  unordered_map<int, Room*> checkins;  // customer_id -> room
  unordered_map<int, int> start_times;  // customer_id -> check in timestamp
  public:
  void add_rooms(RoomType t, vector<Room>& rooms) {
    for(auto room: rooms) {
      this->rooms[t].push_back(room);
    }
  }
  bool reserve(RoomType t, int customer_id) {
    if(reservations.find(customer_id) != reservations.end()) {
      return false;
    }
    for(Room& room: rooms[t]) {
      if(room.get_available()) {
        reservations[customer_id] = &room;
        room.set_unavailable();
        return true;
      }
    }
    return false;
  }
  bool cancel_reserve(int customer_id) {
    auto it = reservations.find(customer_id);
    if(it == reservations.end()) {
      return false;	
    }
    Room* room = it->second;
    room->set_available();
    reservations.erase(customer_id);
    return true;
  }
  // With reservation
  bool check_in(int customer_id) {
    auto it = reservations.find(customer_id);
    if(it == reservations.end()) {
      return false;
    }
    Room* room = it->second;
    reservations.erase(customer_id);
    checkins[customer_id] = room;
    start_times[customer_id] = time(nullptr);
    return true;
  }
  // No reservation
  bool check_in(int customer_id, RoomType t) {
    for(auto room: rooms[t]) {
      if(room.get_available()) {
        checkins[customer_id] = &room;
        start_times[customer_id] = time(nullptr);
        return true;
      }
    }
    return false;
  }
  bool check_out(int customer_id) {
    auto it = checkins.find(customer_id);
    if(it == checkins.end()) {
      return false;
    }
    Room* room = it->second;
    int start_time = start_times[customer_id];
    int end_time = time(nullptr);
    int days = ceil(1.0 * (end_time - start_time) / 3600 / 24);
    if(!charge_user(customer_id, room->get_price(days))) {
      return false;
    }
    room->set_available();
    checkins.erase(customer_id);
    start_times.erase(customer_id);
    return true;
  }
  bool charge_user(int customer_id, float price);
};

int main() {
  Pricer pricer;
  vector<Room> small_rooms, medium_rooms, large_rooms;
  for(int i = 0; i < 20; i++) {
    small_rooms.push_back(Room(i, SMALL_ROOM, pricer));
  }
  for(int i = 0; i < 10; i++) {
    medium_rooms.push_back(Room(20 + i, MEDIUM_ROOM, pricer));
  }
  for(int i = 0; i < 5; i++) {
    large_rooms.push_back(Room(30 + i, LARGE_ROOM, pricer));
  }
  Hotel hotel;
  hotel.add_rooms(SMALL_ROOM, small_rooms);
  hotel.add_rooms(MEDIUM_ROOM, medium_rooms);
  hotel.add_rooms(LARGE_ROOM, large_rooms);
  Customer user(1);
  for(int i = 0; i < 30; i++) {
    cout<<hotel.reserve(SMALL_ROOM, i)<<endl;
    if(i > 10 && i % 2 == 0) {
      hotel.cancel_reserve(i - 10);
    }
  }
  return 0;
}
