#include <iostream>
#include <fstream>
#include "Display.h"

Display::Display() {}

int Display::num_airports(Graph<Airports> *g) {
    return g->getVertexSet().size();
}

int Display::num_flights(Graph<Airports> *g) {
    int i = 0;
    for (Vertex<Airports> *v : g->getVertexSet()) {
        for (Edge<Airports> e : v->getAdj()) {
            i++;
        }
    }
    return i;
}

int Display::flights_per_airport(Graph<Airports> *g, Airports info, vector<Flights> &res) {
    int count = 0;
    Vertex<Airports> *v = g->findVertex(info);
    for (Edge<Airports> e:v->getAdj()) {
        res.emplace_back(v->getInfo().getCode(),e.getDest()->getInfo().getCode(),e.getAlCode());
        count++;
    }
    return count;
}

int Display::airlines_per_airport(Graph<Airports> *g, Airports info, set<string> &res) {
    Vertex<Airports> *v = g->findVertex(info);
    for (Edge<Airports> e:v->getAdj()) {
        res.insert(e.getAlCode());
    }
    return res.size();
}

int Display::countries_per_airport(Graph<Airports> *g, Airports info, set<string> &res) {
    Vertex<Airports> *v = g->findVertex(info);
    for (Edge<Airports> e:v->getAdj()) {
        res.insert(e.getDest()->getInfo().getCountry());
    }
    return res.size();
}

int Display::destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res) {
    vector<Airports> destinations = g->dfs(info);
    for (Airports ap : destinations) {
        res.push_back(ap);
    }
    return res.size();
}

int Display::destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res) {
    vector<Airports> destinations = g->dfs(info);
    if (input == "2") {
        for (Airports ap : destinations) {
            res.insert(ap.getCity());
        }
    }else if (input == "3") {
        for (Airports ap : destinations) {
            res.insert(ap.getCountry());
        }
    }
    return res.size();
}

vector<Airports> bfs_at_distance(Graph<Airports> *g, const Airports &source, int k) {
    vector<Airports> res;
    Vertex<Airports> *v = g->findVertex(source);
    if (v == nullptr)
        return res;

    queue<pair<Vertex<Airports> *, int>> q;
    for (auto v : g->getVertexSet())
        v->setVisited(false);

    q.push({v,0});
    v->setVisited(true);

    while (!q.empty()) {
        auto pair = q.front();
        auto v = pair.first;
        int distance = pair.second;
        q.pop();
        if (distance > k) {
            break;
        }
        res.push_back(v->getInfo());
        for (auto &e : v->getAdj()) {
            auto w = e.getDest();
            if (!w->isVisited()) {
                q.push({w, distance + 1});
                w->setVisited(true);
            }
        }
    }
    return res;
}

int Display::destinations_per_airport_ap(Graph<Airports> *g, Airports info, vector<Airports> &res, int max_distance) {
    vector<Airports> destinations = bfs_at_distance(g,info,max_distance);
    for (Airports ap : destinations)
        res.push_back(ap);
    return res.size();
}

int Display::destinations_per_airport_string(Graph<Airports> *g, Airports info, string input, set<string> &res, int max_distance) {
    vector<Airports> destinations = bfs_at_distance(g,info,max_distance);
    if (input == "2") {
        for (Airports ap : destinations) {
            res.insert(ap.getCity());
        }
    }else if (input == "3") {
        for (Airports ap : destinations) {
            res.insert(ap.getCountry());
        }
    }
    return res.size();
}

int Display::flights_per_city(Graph<Airports> *g, string city, vector<Flights> &res) {
    int i = 0;
    for (Vertex<Airports> *v : g->getVertexSet()) {
        if (v->getInfo().getCity() == city) {
            for (Edge<Airports> e: v->getAdj()) {
                res.emplace_back(v->getInfo().getCode(), e.getDest()->getInfo().getCode(), e.getAlCode());
                i++;
            }
        } else {continue;}
    }
    return i;
}

int Display::countries_per_city(Graph<Airports> *g, string city, set<string> &res) {
    for (Vertex<Airports> *v: g->getVertexSet()) {
        if (v->getInfo().getCity() == city) {
            for (Edge<Airports> e: v->getAdj()) {
                res.insert(e.getDest()->getInfo().getCountry());
            }
        }
        else {continue;}
    }
    return res.size();
}

int Display::flights_per_airline(Graph<Airports> *g, string al_code, vector<Flights> &res) {
    int i = 0;
    for (Vertex<Airports> *v: g->getVertexSet()) {
        for (Edge<Airports> e: v->getAdj()) {
            if (e.getAlCode() == al_code) {
                res.emplace_back(v->getInfo().getCode(), e.getDest()->getInfo().getCode(), e.getAlCode());
                i++;
            }
        }
    }
    return i;
}

int Display::bfs_max_distance(Graph<Airports> *g, const Airports &source, vector<pair<Airports,int>> &res) {
    int max_distance = 0;
    Vertex<Airports> *v = g->findVertex(source);
    if (v == nullptr)
        return 0;

    queue<pair<Vertex<Airports> *, int>> q;
    for (auto v : g->getVertexSet())
        v->setVisited(false);

    q.push({v,0});
    v->setVisited(true);

    while (!q.empty()) {
        auto p = q.front();
        auto v = p.first;
        int distance = p.second;
        q.pop();
        if (distance > max_distance) {
            res.clear();
            max_distance = distance;
            res.emplace_back(v->getInfo(),distance);
        }else if(distance == max_distance) {
            res.emplace_back(v->getInfo(),distance);
        }

        for (auto &e : v->getAdj()) {
            auto w = e.getDest();
            if (!w->isVisited()) {
                q.push({w, distance + 1});
                w->setVisited(true);
            }
        }
    }
    return max_distance;
}

int Display::maximum_trip(Graph<Airports> *g, vector<pair<Airports,Airports>> &res) {
    int max_distance = 0;
    for (Vertex<Airports> *v : g->getVertexSet()) {
        vector<pair<Airports,int>> temp;
        int distance = bfs_max_distance(g,v->getInfo(),temp);
        if(distance > max_distance) {
            res.clear();
            max_distance = distance;
            for (auto p : temp)
                res.emplace_back(v->getInfo(),p.first);
        }else if(distance == max_distance){
            for (auto p : temp)
                res.emplace_back(v->getInfo(),p.first);
        }
    }
    return max_distance;
}

void Display::dfs_art(Graph<Airports> *g, Vertex<Airports> *v, int &i, unordered_set<Vertex<Airports>*> &articulationPoints) {
    v->setVisited(true);
    v->setNum(i);
    v->setLow(i);
    i++;
    int c = 0;

    for (Edge<Airports> edge : v->getAdj()) {
        Vertex<Airports> *w = edge.getDest();
        if (!w->isVisited()) {
            c++;
            dfs_art(g, w, i, articulationPoints);
            v->setLow(min(v->getLow(), w->getLow()));

            if (w->getLow() >= v->getNum() && !articulationPoints.count(v)) {
                articulationPoints.insert(v);
            }
        } else {
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }

    if (v->getNum() == 0 && c > 1 && !articulationPoints.count(v)) {
        articulationPoints.insert(v);
    }
}

int Display::articulation_points(Graph<Airports> *g, vector<Airports> &res) {
    unordered_set<Vertex<Airports>*> art_points;
    Graph<Airports> undirectedGraph = g->createUndirectedGraph();
    for (Vertex<Airports> *v : g->getVertexSet()) {
        if (!v->isVisited()) {
            int i = 0;
            dfs_art(g,v,i,art_points);
        }
    }
    for (Vertex<Airports> *v : art_points) {
        res.push_back(v->getInfo());
    }
    return res.size();
}
