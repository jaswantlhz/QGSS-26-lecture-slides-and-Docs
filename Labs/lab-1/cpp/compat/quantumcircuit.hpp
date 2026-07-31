// ============================================================================
// compat/quantumcircuit.hpp -- QuantumCircuit compatibility layer
//
// Thin subclass of Qiskit::circuit::QuantumCircuit that adds:
//   - draw() with wide fold width for Colab and idle_wires filtering
//   - depth() matching Python's qc.depth()
//   - count_ops() matching Python's qc.count_ops()
//   - measure_all() matching Python's qc.measure_all()
//
// TEMPORARY: This wrapper can be removed once qiskit-cpp adds these
// methods natively.
//
// Usage:
//   #include "compat/quantumcircuit.hpp"
//   using namespace Qiskit::compat;
//   QuantumCircuit circ(2, 0);
//   circ.draw();
//   std::cout << "Depth: " << circ.depth() << std::endl;
// ============================================================================

#ifndef QISKIT_COMPAT_QUANTUMCIRCUIT_HPP
#define QISKIT_COMPAT_QUANTUMCIRCUIT_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cmath>
#include "circuit/quantumcircuit.hpp"

namespace Qiskit {
namespace compat {

class QuantumCircuit : public circuit::QuantumCircuit {
public:
    using circuit::QuantumCircuit::QuantumCircuit;

    // Construct from a base circuit::QuantumCircuit (e.g., transpiler output)
    QuantumCircuit(const circuit::QuantumCircuit& other)
        : circuit::QuantumCircuit(other) {}

    // Matches Python's qc.draw(idle_wires=True/False)
    void draw(bool idle_wires = true, size_t fold = 200) const {
        auto* self = const_cast<QuantumCircuit*>(this);
        auto rust_circ = self->get_rust_circuit();
        QkCircuitDrawerConfig conf;
        conf.bundle_cregs = true;
        conf.merge_wires = false;
        conf.fold = fold;
        char* out = qk_circuit_draw(rust_circ.get(), &conf);
        std::string output = format_angles_(std::string(out));
        qk_str_free(out);

        // Strip empty classical register lines when num_clbits == 0
        if (self->num_clbits() == 0) {
            output = strip_empty_cregs_(output);
        }

        if (idle_wires) {
            std::cout << output << std::endl;
            return;
        }

        // Find which qubits have instructions
        std::set<uint_t> active;
        for (uint_t i = 0; i < self->num_instructions(); i++) {
            auto inst = (*self)[i];
            for (auto q : inst.qubits()) active.insert(q);
        }

        // Filter: skip lines belonging to idle qubit wires.
        std::istringstream stream(output);
        std::string line;
        bool skipping = false;

        while (std::getline(stream, line)) {
            int idx = extract_wire_index_(line);
            if (idx >= 0) {
                skipping = (active.find(idx) == active.end());
            } else if (is_classical_line_(line)) {
                skipping = false;
            }
            if (!skipping) {
                std::cout << line << "\n";
            }
        }
    }

private:

    // Try to express a double as a pi fraction string, or round to 2 decimals.
    static std::string angle_to_string_(double val) {
        static const double PI = 3.14159265358979323846;
        static const double TOL = 1e-6;
        static const int denoms[] = {1, 2, 3, 4, 6, 8};
        double abs_val = std::abs(val);
        bool is_neg = val < -TOL;

        for (int n : denoms) {
            for (int k = 1; k <= 8; k++) {
                double target = k * PI / n;
                if (std::abs(abs_val - target) < TOL) {
                    std::string rep;
                    if (is_neg) rep += "-";
                    if (k == 1 && n == 1) rep += "pi";
                    else if (k == 1) rep += "pi/" + std::to_string(n);
                    else if (n == 1) rep += std::to_string(k) + "*pi";
                    else rep += std::to_string(k) + "*pi/" + std::to_string(n);
                    return rep;
                }
            }
        }
        // Not a pi fraction -- round to 2 decimal places
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << val;
        return oss.str();
    }

    // Format angles in the draw output: replace long decimals with pi
    // fractions, padded to original length to preserve box alignment.
    static std::string format_angles_(const std::string& input) {
        std::string result;
        size_t i = 0;
        while (i < input.size()) {
            bool is_neg = false;
            if ((std::isdigit(input[i]) || (input[i] == '-' && i + 1 < input.size() && std::isdigit(input[i+1])))
                && (i == 0 || input[i-1] == '(' || input[i-1] == ' ' || input[i-1] == ',')) {

                size_t start = i;
                if (input[i] == '-') { is_neg = true; i++; }
                while (i < input.size() && std::isdigit(input[i])) i++;

                if (i < input.size() && input[i] == '.') {
                    i++;
                    size_t frac_start = i;
                    while (i < input.size() && std::isdigit(input[i])) i++;

                    if (i - frac_start >= 6) {
                        size_t orig_len = i - start;
                        double val = std::stod(input.substr(start, orig_len));
                        std::string rep = angle_to_string_(val);
                        while (rep.size() < orig_len) rep += ' ';
                        result += rep;
                        continue;
                    }
                }
                result += input.substr(start, i - start);
                continue;
            }
            result += input[i++];
        }
        return result;
    }

    // ---- Classical register / wire helpers ----

    // Remove classical register lines from output when circuit has no classical bits.
    static std::string strip_empty_cregs_(const std::string& input) {
        std::istringstream stream(input);
        std::string line;
        std::string result;
        while (std::getline(stream, line)) {
            if (is_double_line_only_(line)) continue;
            result += line + "\n";
        }
        while (!result.empty() && result.back() == '\n') {
            size_t last_nl = result.find_last_not_of('\n');
            if (last_nl == std::string::npos) { result.clear(); break; }
            result.erase(last_nl + 2);
            break;
        }
        return result;
    }

    static bool is_double_line_only_(const std::string& line) {
        bool found_double = false;
        size_t i = 0;
        while (i < line.size()) {
            if (line[i] == ' ' || line[i] == '\t') { i++; continue; }
            if (i + 2 < line.size() &&
                (unsigned char)line[i]   == 0xE2 &&
                (unsigned char)line[i+1] == 0x95 &&
                (unsigned char)line[i+2] == 0x90) {
                found_double = true;
                i += 3;
                continue;
            }
            return false;
        }
        return found_double;
    }

    // Extract qubit index from a wire label line.
    static int extract_wire_index_(const std::string& line) {
        size_t colon = line.find(':');
        if (colon == std::string::npos || colon < 2) return -1;
        size_t q_pos = std::string::npos;
        for (size_t k = 0; k < colon; k++) {
            if (line[k] == 'q' && (k == 0 || line[k-1] == ' ')) {
                q_pos = k;
                break;
            }
        }
        if (q_pos == std::string::npos) return -1;
        std::string between = line.substr(q_pos + 1, colon - q_pos - 1);
        for (char c : between) {
            if (!std::isdigit(c) && c != '_') return -1;
        }
        size_t last_us = between.rfind('_');
        std::string num_part = (last_us != std::string::npos)
            ? between.substr(last_us + 1) : between;
        if (num_part.empty()) return -1;
        return std::stoi(num_part);
    }

    static bool is_classical_line_(const std::string& line) {
        for (size_t k = 0; k < line.size(); k++) {
            char c = line[k];
            if (c == ' ') continue;
            if (c == 'c' || c == 'm') return true;
            break;
        }
        return false;
    }

public:

    // Matches Python's qc.depth()
    uint_t depth() {
        if (num_instructions() == 0) return 0;
        std::map<uint_t, uint_t> qubit_layer;
        uint_t max_depth = 0;
        for (uint_t i = 0; i < num_instructions(); i++) {
            auto inst = (*this)[i];
            const auto& qubits = inst.qubits();
            const auto& name = inst.instruction().name();
            if (name == "barrier") continue;
            uint_t layer = 0;
            for (auto q : qubits)
                layer = std::max(layer, qubit_layer[q]);
            layer += 1;
            for (auto q : qubits)
                qubit_layer[q] = layer;
            max_depth = std::max(max_depth, layer);
        }
        return max_depth;
    }

    // Matches Python's qc.measure_all()
    QuantumCircuit measure_all() {
        int n = num_qubits();
        QuantumCircuit result(n, n);
        for (uint_t i = 0; i < num_instructions(); i++) {
            auto inst = (*this)[i];
            result.append(inst.instruction(), inst.qubits());
        }
        std::vector<uint_t> all_qubits(n);
        for (int q = 0; q < n; q++) all_qubits[q] = q;
        result.barrier(all_qubits);
        for (int q = 0; q < n; q++)
            result.measure(q, q);
        return result;
    }

    // Matches Python's qc.count_ops()
    std::map<std::string, uint_t> count_ops() {
        std::map<std::string, uint_t> ops;
        for (uint_t i = 0; i < num_instructions(); i++) {
            auto inst = (*this)[i];
            ops[inst.instruction().name()]++;
        }
        return ops;
    }
};

} // namespace compat
} // namespace Qiskit

#endif // QISKIT_COMPAT_QUANTUMCIRCUIT_HPP
