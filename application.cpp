// application.cpp <Starter Code>
// Albert Huynh
//
//
// Adam T Koehler, PhD
// University of Illinois Chicago
// CS 251, Fall 2023
//
// Project Original Variartion By:
// Joe Hummel, PhD
// University of Illinois at Chicago
//
// 
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <queue>
#include <stack>
#include <algorithm>

#include "tinyxml2.h"
#include "dist.h"
#include "graph.h"
#include "osm.h"


using namespace std;
using namespace tinyxml2;

class prioritize  // you could also use a struct
{
public:
  bool operator()(const pair<long long, double>& p1, const pair<long long, double>& p2) const
  {
    return p1.second > p2.second; 
  }
};


const double INF = numeric_limits<double>::max();


BuildingInfo searchBuilding(vector<BuildingInfo> Buildings, string query) {
  BuildingInfo building;
  for(int i = 0; i < Buildings.size(); i++) {
      // Find starting building and if abbreviation not found then find substring
      if(query == Buildings.at(i).Abbrev) {
        return Buildings.at(i);
      }
  }

  for(int i = 0; i < Buildings.size(); i++) {
    if(Buildings.at(i).Fullname.find(query) != string::npos) {
      return Buildings.at(i);
    }
  }
  return building;
}

void printInfo(BuildingInfo building, string name) {
  cout << name << " point:" << endl;
  cout << building.Fullname << endl;
  cout << "(" << building.Coords.Lat << ", " << building.Coords.Lon << ")" << endl;
}

// Helper function to help find the center building also accounts for new buildings if there is an unreachable building
BuildingInfo findCenterBuilding(vector<BuildingInfo> Buildings, BuildingInfo building1, BuildingInfo building2, set<long long> buildingUnreachable) {
    Coordinates midpoint = centerBetween2Points(building1.Coords.Lat, building1.Coords.Lon, building2.Coords.Lat, building2.Coords.Lon);
    BuildingInfo centerBuilding;

    double min = INF; 
    for(int i = 0; i < Buildings.size(); i++) {
      if(buildingUnreachable.count(Buildings.at(i).Coords.ID) > 0) {
        continue;
      }
      double dist = distBetween2Points(midpoint.Lat, midpoint.Lon, Buildings.at(i).Coords.Lat, Buildings.at(i).Coords.Lon);
      if(dist < min) {
        min = dist;
        centerBuilding = Buildings.at(i);
      }
    }
    cout << "Destination Building:" << endl;
    cout << centerBuilding.Fullname << endl;
    cout << "(" << centerBuilding.Coords.Lat << ", " << centerBuilding.Coords.Lon << ")" << endl;
    return centerBuilding;
}

Coordinates findNearestNode(BuildingInfo building, map<long long, Coordinates> Nodes, vector<FootwayInfo> Footways) {
  Coordinates nearestNode;
  double min = INF;

  for(auto edge : Footways) {
    for(int i = 0; i < edge.Nodes.size(); i++){
      double dist = distBetween2Points(Nodes.at(edge.Nodes.at(i)).Lat, Nodes.at(edge.Nodes.at(i)).Lon, building.Coords.Lat, building.Coords.Lon);
      if(dist < min) {
        min = dist;
        nearestNode = Nodes.at(edge.Nodes.at(i));
      }
    }
  }
  return nearestNode;
}

// Needed a startNode, the graph full of nodes, a paths parameter, and a predecessor parameter
void dijkstraShortestPath(long long startNode, graph<long long, double> G, map<long long, double>& distances, map<long long, long long>& predecessors) {
  double infinity = INF;
  // discovered set
  set<long long> visitedNodes;

  // frontier queue
  priority_queue<
  pair<long long, double>,          // (key,value) pair
  vector<pair<long long, double>>,  // store pairs in a vector
  prioritize> unvisitedQueue;   // function object

  for(auto vertex : G.getVertices()) {
    distances[vertex] = infinity;
    unvisitedQueue.push(make_pair(vertex, infinity));
  }
  
  distances[startNode] = 0;
  unvisitedQueue.push(make_pair(startNode, 0));

  while(!unvisitedQueue.empty()) {
    pair<long long, double> currV = unvisitedQueue.top();
    unvisitedQueue.pop();

    if(distances[currV.first] == infinity) {
      break;
    }
    else if(visitedNodes.count(currV.first) > 0) {
      continue;
    }
    else {
      visitedNodes.insert(currV.first);
    }

    for(auto adj : G.neighbors(currV.first)) {
      double edgeWeight;
      G.getWeight(currV.first, adj, edgeWeight);
      double altPathDistance = distances[currV.first] + edgeWeight;

      if(altPathDistance < distances[adj]) {
        distances[adj] = altPathDistance;
        predecessors[adj] = currV.first;
        unvisitedQueue.push(make_pair(adj, altPathDistance));
      }
    }
  }
}

// Getting the path to print
void printPath(map<long long, long long> predecessors, long long destination) {
  stack<long long> locations;
  long long currV = destination;

  while(currV != 0) {
    locations.push(currV);
    currV = predecessors[currV];
  }

  while(!locations.empty()) {
    currV = locations.top();
    cout << locations.top();
    locations.pop();
    if(locations.size() > 0) {
      cout << "->";
    }
  }
  cout << endl;
}

void application(
  map<long long, Coordinates>& Nodes, vector<FootwayInfo>& Footways,
  vector<BuildingInfo>& Buildings, graph<long long, double>& G) {

  string person1Building, person2Building;

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);

  while (person1Building != "#") {
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);

    // Searching Building's 1 and 2
    BuildingInfo building1 = searchBuilding(Buildings, person1Building);
    BuildingInfo building2 = searchBuilding(Buildings, person2Building);

    if(building1.Abbrev == "") {
      cout << "Person 1's building not found" << endl;
      cout << endl;
      cout << "Enter person 1's building (partial name or abbreviation), or #> ";
      getline(cin, person1Building);
      continue;
    }
    else if(building2.Abbrev == "") {
      cout << "Person 2's building not found" << endl;
      cout << endl;
      cout << "Enter person 1's building (partial name or abbreviation), or #> ";
      getline(cin, person1Building);
      continue;
    }
    else {
      printInfo(building1, "Person 1's");
      printInfo(building2, "Person 2's");
    }

    bool pathFound = false;
    set<long long> buildingsNotReachable;
    while(!pathFound){
      // Locate Center Building
      BuildingInfo centerBuilding = findCenterBuilding(Buildings, building1, building2, buildingsNotReachable);

      // Find Nearest Nodes from buildings 1, 2 & Center
      Coordinates nearestBuildingNode1 = findNearestNode(building1, Nodes, Footways);
      Coordinates nearestBuildingNode2 = findNearestNode(building2, Nodes, Footways);
      Coordinates nearestBuildingNodeCenter = findNearestNode(centerBuilding, Nodes, Footways);

      cout << endl;
      cout << "Nearest P1 node:" << endl;
      cout << " " << nearestBuildingNode1.ID << endl;
      cout << " (" << Nodes.at(nearestBuildingNode1.ID).Lat << ", " << Nodes.at(nearestBuildingNode1.ID).Lon << ")" << endl;
      cout << "Nearest P2 node:" << endl;
      cout << " " << nearestBuildingNode2.ID << endl;
      cout << " (" << nearestBuildingNode2.Lat << ", " << nearestBuildingNode2.Lon << ")" << endl;
      cout << "Nearest destination node:" << endl;
      cout << " " << nearestBuildingNodeCenter.ID << endl;
      cout << " (" << nearestBuildingNodeCenter.Lat << ", " << nearestBuildingNodeCenter.Lon << ")" << endl;
      cout << endl;

      // Running djikstras algorithm
      map<long long, double> distancesBuilding1;
      map<long long, long long> predecessorsBuilding1;

      map<long long, double> distancesBuilding2;
      map<long long, long long> predecessorsBuilding2;

      dijkstraShortestPath(nearestBuildingNode1.ID, G, distancesBuilding1, predecessorsBuilding1);
      dijkstraShortestPath(nearestBuildingNode2.ID, G, distancesBuilding2, predecessorsBuilding2);
      
      // Printing the path and if it does exist then the path prints
      if(distancesBuilding1[nearestBuildingNode2.ID] >= INF) {
        cout << "Sorry, destination unreachable" << endl;
        pathFound = true;
      }
      else {
        if(distancesBuilding1[nearestBuildingNodeCenter.ID] >= INF || distancesBuilding2[nearestBuildingNodeCenter.ID] >= INF) {
          cout << "At least one person was unable to reach the destination building. Finding next closest building...";
          buildingsNotReachable.emplace(centerBuilding.Coords.ID);
        }
        else {
          cout << "Person 1's distance to dest: " << distancesBuilding1[nearestBuildingNodeCenter.ID] << " miles" << endl;
          cout << "Path: ";
          printPath(predecessorsBuilding1, nearestBuildingNodeCenter.ID);

          cout << "Person 2's distance to dest: " << distancesBuilding2[nearestBuildingNodeCenter.ID] << " miles" << endl;
          cout << "Path: ";
          printPath(predecessorsBuilding2, nearestBuildingNodeCenter.ID);
          pathFound = true;
        }
      }
    }
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);
  }    
}

int main() {
  graph<long long, double> G;

  // maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates>  Nodes;
  // info about each footway, in no particular order
  vector<FootwayInfo>          Footways;
  // info about each building, in no particular order
  vector<BuildingInfo>         Buildings;
  XMLDocument                  xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "") {
    filename = def_filename;
  }

  //
  // Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;


  //
  // TO DO: build the graph, output stats:
  //

  //MILESTONE 5: ADD VERTICES
  for(auto node : Nodes) {
    G.addVertex(node.first);
  }

  //MILESTONE 6: ADD EDGES
  for(auto edge : Footways) {
    for(int i = 0; i < edge.Nodes.size() - 1; i++){
      double dist = distBetween2Points(Nodes.at(edge.Nodes.at(i)).Lat, Nodes.at(edge.Nodes.at(i)).Lon, Nodes.at(edge.Nodes.at(i + 1)).Lat, Nodes.at(edge.Nodes.at(i + 1)).Lon);
      G.addEdge(edge.Nodes.at(i), edge.Nodes.at(i + 1), dist);
      G.addEdge(edge.Nodes.at(i + 1), edge.Nodes.at(i), dist);
    }
  }

  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;

  // Execute Application
  application(Nodes, Footways, Buildings, G);

  //
  // done:
  //
  cout << "** Done **" << endl;
  return 0;
}
