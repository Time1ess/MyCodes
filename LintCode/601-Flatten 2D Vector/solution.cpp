class Vector2D {
private:
    vector<vector<int>>& vec;
    vector<vector<int>>::iterator vec_it;
    vector<int>::iterator elem_it;
public:
    Vector2D(vector<vector<int>>& vec2d): vec(vec2d) {
        vec_it = vec.begin();
        if(vec_it != vec.end()) {
            elem_it = vec_it->begin();
        }
    }
    
    bool moveToNext() {
        if(vec_it == vec.end()) {
            return false;
        }
        if(elem_it == vec_it->end()) {
            ++vec_it;
            if(vec_it != vec.end()) {
                elem_it = vec_it->begin();
            } else {
                return false;
            }
        } else {
            ++elem_it;
        }
        return true;
    }

    int next() {
        // Write your code here
        int ans = *elem_it;
        moveToNext();
        return ans;
    }

    bool hasNext() {
        if(vec_it == vec.end()) {
            return false;
        }
        while(elem_it == vec_it->end()) {
            if(!moveToNext()) {
                return false;
            }
        }
        return true;
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
