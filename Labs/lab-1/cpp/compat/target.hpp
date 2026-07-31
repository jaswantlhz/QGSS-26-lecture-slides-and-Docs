// ============================================================================
// compat/target.hpp -- FakeTorino-like Target for transpilation
//
// Provides a hardcoded Target matching IBM's 133-qubit Heron processor
// (FakeTorino) with its coupling map and native gate set.
//
// TEMPORARY: This can be removed once qiskit-cpp provides built-in
// fake backend support.
//
// Usage:
//   #include "compat/target.hpp"
//   auto target = Qiskit::compat::make_torino_target();
// ============================================================================

#ifndef QISKIT_COMPAT_TARGET_HPP
#define QISKIT_COMPAT_TARGET_HPP

#include <vector>
#include <string>
#include <utility>
#include "transpiler/target.hpp"

namespace Qiskit {
namespace compat {

// FakeTorino coupling map (133-qubit Heron processor, 150 edges)
inline std::vector<std::pair<uint32_t, uint32_t>> torino_coupling_map() {
    return {
        {0,1}, {0,15}, {1,2}, {2,3}, {3,4}, {4,5},
        {4,16}, {5,6}, {6,7}, {7,8}, {8,9}, {8,17},
        {9,10}, {10,11}, {11,12}, {12,13}, {12,18}, {13,14},
        {15,19}, {16,23}, {17,27}, {18,31}, {19,20}, {20,21},
        {21,22}, {21,34}, {22,23}, {23,24}, {24,25}, {25,26},
        {25,35}, {26,27}, {27,28}, {28,29}, {29,30}, {29,36},
        {30,31}, {31,32}, {32,33}, {33,37}, {34,40}, {35,44},
        {36,48}, {37,52}, {38,39}, {38,53}, {39,40}, {40,41},
        {41,42}, {42,43}, {42,54}, {43,44}, {44,45}, {45,46},
        {46,47}, {46,55}, {47,48}, {48,49}, {49,50}, {50,51},
        {50,56}, {51,52}, {53,57}, {54,61}, {55,65}, {56,69},
        {57,58}, {58,59}, {59,60}, {59,72}, {60,61}, {61,62},
        {62,63}, {63,64}, {63,73}, {64,65}, {65,66}, {66,67},
        {67,68}, {67,74}, {68,69}, {69,70}, {70,71}, {71,75},
        {72,78}, {73,82}, {74,86}, {75,90}, {76,77}, {76,91},
        {77,78}, {78,79}, {79,80}, {80,81}, {80,92}, {81,82},
        {82,83}, {83,84}, {84,85}, {84,93}, {85,86}, {86,87},
        {87,88}, {88,89}, {88,94}, {89,90}, {91,95}, {92,99},
        {93,103}, {94,107}, {95,96}, {96,97}, {97,98}, {97,110},
        {98,99}, {99,100}, {100,101}, {101,102}, {101,111}, {102,103},
        {103,104}, {104,105}, {105,106}, {105,112}, {106,107}, {107,108},
        {108,109}, {109,113}, {110,116}, {111,120}, {112,124}, {113,128},
        {114,115}, {114,129}, {115,116}, {116,117}, {117,118}, {118,119},
        {118,130}, {119,120}, {120,121}, {121,122}, {122,123}, {122,131},
        {123,124}, {124,125}, {125,126}, {126,127}, {126,132}, {127,128}
    };
}

// Heron native gate set
inline std::vector<std::string> torino_basis_gates() {
    return {"rz", "sx", "x", "cz"};
}

// Create a Target matching FakeTorino
inline transpiler::Target make_torino_target() {
    return transpiler::Target(torino_basis_gates(), torino_coupling_map());
}

// Adjacency list for the coupling map (useful for topology exercises)
inline std::vector<std::vector<int>> torino_adjacency(int num_qubits = 133) {
    auto edges = torino_coupling_map();
    std::vector<std::vector<int>> adj(num_qubits);
    for (auto& e : edges) {
        if ((int)e.first < num_qubits && (int)e.second < num_qubits) {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
        }
    }
    for (auto& v : adj) std::sort(v.begin(), v.end());
    return adj;
}

} // namespace compat
} // namespace Qiskit

#endif // QISKIT_COMPAT_TARGET_HPP
