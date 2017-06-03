// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-06-03 09:04
// Last modified: 2017-06-03 09:04
// Filename: solution.cpp
// Description:
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};


class PeekingIterator : public Iterator {
private:
    int next_int;
    bool has_next;
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	    has_next = Iterator::hasNext();
	    if(has_next)
	        next_int = Iterator::next();
	}

    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        return next_int;
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
	    int tmp = next_int;
	    has_next = Iterator::hasNext();
	    if(has_next)
	        next_int = Iterator::next();
	    return tmp;
	}

	bool hasNext() const {
	    return has_next;
	}
};
