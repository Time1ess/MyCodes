class CatDogAsylum {
private:
    queue<pair<int, int>> cats, dogs;
    int idx = 0;
public:
    void adoptCat(vector<int>& ans) {
        if(cats.empty()) {
            return;
        }
        ans.push_back(cats.front().first);
        cats.pop();
    }
    void adoptDog(vector<int>& ans) {
        if(dogs.empty()) {
            return;
        }
        ans.push_back(dogs.front().first);
        dogs.pop();
    }
    void adopt(vector<int>& ans, int adoptType) {
        if(adoptType == 1 || (adoptType == 0 && cats.empty())) {
            adoptDog(ans);
        } else if(adoptType == -1 || (adoptType == 0 && dogs.empty())) {
            adoptCat(ans);
        } else {
            auto p1 = cats.front();
            auto p2 = dogs.front();
            if(p1.second < p2.second) {
                adoptCat(ans);
            } else {
                adoptDog(ans);
            }
        }
    }
    vector<int> asylum(vector<vector<int> > ope) {
        // write code here
        vector<int> ans;
        for(auto op: ope) {
            bool adoptAnimal = op[0] == 2;
            if(!adoptAnimal) {
                int animalId = op[1];
                if(animalId > 0) {
                    dogs.push({animalId, idx++});
                } else {
                    cats.push({animalId, idx++});
                }
            } else {
                adopt(ans, op[1]);
            }
        }
        return ans;
    }
};
