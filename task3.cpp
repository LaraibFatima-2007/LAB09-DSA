/*
 * Name: Laraib Fatima
 * Class: BSDS 3A
 * Course Instructor: Dr. Fahad Ahmed Satti
 * Lab Engineer: Hassan Mohtashim
 * Date: November 10, 2026
 * Topic: Lab 9 - Task 3: Weighted M-ary Tree - Galaxy Representation
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class TravelRoute {
public:
    float travel_cost;

    TravelRoute(float cost = 0.0) {
        travel_cost = cost;
    }
};
class StarSystem {
public:
    int system_id;
    string name;
    int num_planets;
    float x, y, z;
    bool is_habitable;

    StarSystem** children;
    TravelRoute* routes;
    int child_count;
    int capacity;

    StarSystem(int id, string n, int planets, float px, float py, float pz, bool habitable, int cap = 10) {
        system_id = id;
        name = n;
        num_planets = planets;
        x = px;
        y = py;
        z = pz;
        is_habitable = habitable;

        capacity = cap;
        child_count = 0;
        children = new StarSystem*[capacity];
        routes = new TravelRoute[capacity];
    }
    void addChild(StarSystem* child) {
        if (child_count < capacity) {
            float dx = x - child->x;
            float dy = y - child->y;
            float dz = z - child->z;
            float autoCost = sqrt(dx * dx + dy * dy + dz * dz);

            children[child_count] = child;
            routes[child_count] = TravelRoute(autoCost);
            child_count++;
            
            cout << "Route connected!Calculated travel cost: " << autoCost << endl;
        }
    }
    ~StarSystem() {
        delete[] children;
        delete[] routes;
    }
};

class Galaxy {
private:
    int M;
    StarSystem* root;

    int getSubtreeSize(StarSystem* node) const {
        if (node == NULL) return 0;
        int size = 1;
        for (int i = 0; i < node->child_count; i++) {
            size += getSubtreeSize(node->children[i]);
        }
        return size;
    }
public:
    Galaxy(int max_m, StarSystem* r = NULL) {
        M = max_m;
        root = r;
    }

    void setRoot(StarSystem* r) {
        root = r;
    }
    StarSystem* getRoot() const {
        return root;
    }
    bool is_balanced(StarSystem* x) const {
        if (x == NULL || x->child_count == 0) return true;

        int min_size = -1;
        int max_size = -1;

        for (int i = 0; i < x->child_count; i++) {
            int current_size = getSubtreeSize(x->children[i]);
            if (min_size == -1 || current_size < min_size) min_size = current_size;
            if (max_size == -1 || current_size > max_size) max_size = current_size;

            if (!is_balanced(x->children[i])) return false;
        }

        return (max_size - min_size) <= 1;
    }

    int count_leaves(StarSystem* x) const {
        if (x == NULL) return 0;
        if (x->child_count == 0) return 1;

        int leafCount = 0;
        for (int i = 0; i < x->child_count; i++) {
            leafCount += count_leaves(x->children[i]);
        }
        return leafCount;
    }
};

int main() {
    int m_val;
    cout << "Enter max degree M for Galaxy Tree: ";
    cin >> m_val;

    int totalSystems;
    cout << "Enter total number of star systems to create: ";
    cin >> totalSystems;

    if (totalSystems <= 0) return 0;

    StarSystem** systems = new StarSystem*[totalSystems];

    for (int i = 0; i < totalSystems; i++) {
        int id, planets;
        string name;
        float x, y, z;
        bool habitable;

        cout << "\n-->Star System Index .." << i << ".." << endl;
        cout << "ID: "; cin >> id;
        cout << "Name: "; cin >> name;
        cout << "Num Planets: "; cin >> planets;
        cout << "Coordinates (x y z): "; cin >> x >> y >> z;
        cout << "Is Habitable (1=Yes, 0=No): "; cin >> habitable;

        systems[i] = new StarSystem(id, name, planets, x, y, z, habitable, m_val);
    }

    Galaxy galaxy(m_val, systems[0]);

    int routesCount;
    cout << "\nEnter total travel routes to add: ";
    cin >> routesCount;

    for (int r = 0; r < routesCount; r++) {
        int parentIdx, childIdx;
        cout << "\nRoute " << (r + 1) << ":" << endl;
        cout << "Parent System Index (0 to " << totalSystems - 1 << "): ";
        cin >> parentIdx;
        cout << "Child System Index (0 to " << totalSystems - 1 << "): ";
        cin >> childIdx;

        if (parentIdx >= 0 && parentIdx < totalSystems && childIdx >= 0 && childIdx < totalSystems) {
            systems[parentIdx]->addChild(systems[childIdx]);
        } else {
            cout << "Invalid index! Skipped." << endl;
        }
    }

    cout << "\n--- Galaxy Representation Analysis ---" << endl;
    cout << "Root System: " << galaxy.getRoot()->name << endl;
    cout << "Total Leaf Star Systems: " << galaxy.count_leaves(galaxy.getRoot()) << endl;
    cout << "Is Galaxy Tree Balanced at Root? " << (galaxy.is_balanced(galaxy.getRoot()) ? "Yes" : "No") << endl;

    for (int i = 0; i < totalSystems; i++) {
        delete systems[i];
    }
    delete[] systems;

    return 0;
}