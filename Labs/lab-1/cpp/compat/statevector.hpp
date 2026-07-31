// ============================================================================
// compat/statevector.hpp -- Temporary Statevector simulation wrapper
//
// Provides basic statevector simulation for qiskit-cpp circuits.
// This is a TEMPORARY compatibility layer pending native Statevector
// support in the qiskit-cpp SDK. It iterates through a QuantumCircuit's
// instructions and applies gate matrices to simulate the quantum state.
//
// Usage:
//   #include "compat/statevector.hpp"
//   auto sv = Qiskit::compat::Statevector::from_instruction(circ);
//   std::cout << sv << std::endl;
// ============================================================================

#ifndef QISKIT_COMPAT_STATEVECTOR_HPP
#define QISKIT_COMPAT_STATEVECTOR_HPP

#include <vector>
#include <complex>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "circuit/quantumcircuit.hpp"

namespace Qiskit {
namespace compat {

class Statevector {
public:
    using complex_t = std::complex<double>;

    // Initialize to |0...0> for num_qubits qubits
    explicit Statevector(uint_t num_qubits)
        : num_qubits_(num_qubits),
          data_(1ULL << num_qubits, {0.0, 0.0}) {
        data_[0] = {1.0, 0.0};
    }

    // Simulate a circuit starting from |0...0>
    // Equivalent to Python's Statevector.from_instruction(circ)
    static Statevector from_instruction(circuit::QuantumCircuit& circ) {
        Statevector sv(circ.num_qubits());
        for (uint_t i = 0; i < circ.num_instructions(); i++) {
            auto inst = circ[i];
            const auto& gate = inst.instruction();
            const auto& qubits = inst.qubits();
            const std::string& name = gate.name();
            const auto& params = gate.params();
            sv.apply_gate_(name, qubits, params);
        }
        return sv;
    }

    const std::vector<complex_t>& data() const { return data_; }
    uint_t num_qubits() const { return num_qubits_; }

    friend std::ostream& operator<<(std::ostream& os, const Statevector& sv) {
        os << "Statevector([";
        for (uint_t i = 0; i < sv.data_.size(); i++) {
            if (i > 0) os << ", ";
            format_complex_(os, sv.data_[i]);
        }
        os << "], dims=(";
        for (uint_t i = 0; i < sv.num_qubits_; i++) {
            if (i > 0) os << ", ";
            os << "2";
        }
        os << "))";
        return os;
    }

private:
    uint_t num_qubits_;
    std::vector<complex_t> data_;

    static constexpr double ATOL = 1e-10;

    // ---- Complex number formatting (matches Python style) ----------------

    static void format_complex_(std::ostream& os, const complex_t& c) {
        double re = std::abs(c.real()) < ATOL ? 0.0 : c.real();
        double im = std::abs(c.imag()) < ATOL ? 0.0 : c.imag();
        format_double_(os, re);
        if (im >= 0.0) os << "+";
        format_double_(os, im);
        os << "j";
    }

    static void format_double_(std::ostream& os, double v) {
        if (v == 0.0) {
            os << "0.";
        } else {
            os << std::setprecision(8) << v;
        }
    }

    // ---- Gate dispatch ---------------------------------------------------

    // Helper: Parameter::as_real() is not const-qualified in qiskit-cpp,
    // so we need to cast away const to call it on params from const references.
    static double param_val_(const circuit::Parameter& p) {
        return const_cast<circuit::Parameter&>(p).as_real();
    }

    void apply_gate_(const std::string& name,
                     const reg_t& qubits,
                     const std::vector<circuit::Parameter>& params) {
        // Single-qubit parameterless gates
        if      (name == "x")    apply_x_(qubits[0]);
        else if (name == "y")    apply_y_(qubits[0]);
        else if (name == "z")    apply_z_(qubits[0]);
        else if (name == "h")    apply_h_(qubits[0]);
        else if (name == "s")    apply_s_(qubits[0]);
        else if (name == "sdg")  apply_sdg_(qubits[0]);
        else if (name == "t")    apply_t_(qubits[0]);
        else if (name == "tdg")  apply_tdg_(qubits[0]);
        else if (name == "sx")   apply_sx_(qubits[0]);
        else if (name == "sxdg") apply_sxdg_(qubits[0]);
        // Single-qubit parameterized gates
        else if (name == "rx")   apply_rx_(param_val_(params[0]), qubits[0]);
        else if (name == "ry")   apply_ry_(param_val_(params[0]), qubits[0]);
        else if (name == "rz")   apply_rz_(param_val_(params[0]), qubits[0]);
        else if (name == "p")    apply_p_(param_val_(params[0]), qubits[0]);
        // Two-qubit gates
        else if (name == "cx")   apply_cx_(qubits[0], qubits[1]);
        else if (name == "cz")   apply_cz_(qubits[0], qubits[1]);
        else if (name == "cy")   apply_cy_(qubits[0], qubits[1]);
        else if (name == "ch")   apply_ch_(qubits[0], qubits[1]);
        else if (name == "swap") apply_swap_(qubits[0], qubits[1]);
        // Three-qubit gates
        else if (name == "ccx")  apply_ccx_(qubits[0], qubits[1], qubits[2]);
        // Non-unitary (skip for statevector simulation)
        else if (name == "measure" || name == "barrier" ||
                 name == "reset"   || name == "delay"   ||
                 name == "id"      || name == "i") {
            // no-op
        }
        else {
            throw std::runtime_error(
                "compat::Statevector: unsupported gate '" + name + "'");
        }
    }

    // ---- Single-qubit gate kernel ----------------------------------------

    void apply_1q_(uint_t qubit, const complex_t m[2][2]) {
        uint64_t n = data_.size();
        uint64_t bit = 1ULL << qubit;
        for (uint64_t i = 0; i < n; i++) {
            if (!(i & bit)) {
                uint64_t j = i | bit;
                complex_t a = data_[i];
                complex_t b = data_[j];
                data_[i] = m[0][0] * a + m[0][1] * b;
                data_[j] = m[1][0] * a + m[1][1] * b;
            }
        }
    }

    // ---- Single-qubit parameterless gates --------------------------------

    void apply_x_(uint_t q) {
        complex_t m[2][2] = {{{0,0},{1,0}}, {{1,0},{0,0}}};
        apply_1q_(q, m);
    }

    void apply_y_(uint_t q) {
        complex_t m[2][2] = {{{0,0},{0,-1}}, {{0,1},{0,0}}};
        apply_1q_(q, m);
    }

    void apply_z_(uint_t q) {
        complex_t m[2][2] = {{{1,0},{0,0}}, {{0,0},{-1,0}}};
        apply_1q_(q, m);
    }

    void apply_h_(uint_t q) {
        double s = 1.0 / std::sqrt(2.0);
        complex_t m[2][2] = {{{s,0},{s,0}}, {{s,0},{-s,0}}};
        apply_1q_(q, m);
    }

    void apply_s_(uint_t q) {
        complex_t m[2][2] = {{{1,0},{0,0}}, {{0,0},{0,1}}};
        apply_1q_(q, m);
    }

    void apply_sdg_(uint_t q) {
        complex_t m[2][2] = {{{1,0},{0,0}}, {{0,0},{0,-1}}};
        apply_1q_(q, m);
    }

    void apply_t_(uint_t q) {
        complex_t t = std::exp(complex_t(0, M_PI / 4.0));
        complex_t m[2][2] = {{{1,0},{0,0}}, {{0,0}, t}};
        apply_1q_(q, m);
    }

    void apply_tdg_(uint_t q) {
        complex_t t = std::exp(complex_t(0, -M_PI / 4.0));
        complex_t m[2][2] = {{{1,0},{0,0}}, {{0,0}, t}};
        apply_1q_(q, m);
    }

    void apply_sx_(uint_t q) {
        complex_t a = {0.5, 0.5};
        complex_t b = {0.5, -0.5};
        complex_t m[2][2] = {{a, b}, {b, a}};
        apply_1q_(q, m);
    }

    void apply_sxdg_(uint_t q) {
        complex_t a = {0.5, -0.5};
        complex_t b = {0.5, 0.5};
        complex_t m[2][2] = {{a, b}, {b, a}};
        apply_1q_(q, m);
    }

    // ---- Single-qubit parameterized gates --------------------------------

    void apply_rx_(double theta, uint_t q) {
        double c = std::cos(theta / 2.0);
        double s = std::sin(theta / 2.0);
        complex_t m[2][2] = {{{c,0},{0,-s}}, {{0,-s},{c,0}}};
        apply_1q_(q, m);
    }

    void apply_ry_(double theta, uint_t q) {
        double c = std::cos(theta / 2.0);
        double s = std::sin(theta / 2.0);
        complex_t m[2][2] = {{{c,0},{-s,0}}, {{s,0},{c,0}}};
        apply_1q_(q, m);
    }

    void apply_rz_(double theta, uint_t q) {
        complex_t e_neg = std::exp(complex_t(0, -theta / 2.0));
        complex_t e_pos = std::exp(complex_t(0,  theta / 2.0));
        complex_t m[2][2] = {{e_neg, {0,0}}, {{0,0}, e_pos}};
        apply_1q_(q, m);
    }

    void apply_p_(double theta, uint_t q) {
        complex_t e = std::exp(complex_t(0, theta));
        complex_t m[2][2] = {{{1,0},{0,0}}, {{0,0}, e}};
        apply_1q_(q, m);
    }

    // ---- Two-qubit gates -------------------------------------------------

    void apply_cx_(uint_t control, uint_t target) {
        uint64_t n = data_.size();
        uint64_t cbit = 1ULL << control;
        uint64_t tbit = 1ULL << target;
        for (uint64_t i = 0; i < n; i++) {
            if ((i & cbit) && !(i & tbit)) {
                std::swap(data_[i], data_[i | tbit]);
            }
        }
    }

    void apply_cz_(uint_t control, uint_t target) {
        uint64_t n = data_.size();
        uint64_t cbit = 1ULL << control;
        uint64_t tbit = 1ULL << target;
        for (uint64_t i = 0; i < n; i++) {
            if ((i & cbit) && (i & tbit)) {
                data_[i] = -data_[i];
            }
        }
    }

    void apply_cy_(uint_t control, uint_t target) {
        uint64_t n = data_.size();
        uint64_t cbit = 1ULL << control;
        uint64_t tbit = 1ULL << target;
        complex_t neg_i = {0, -1};
        complex_t pos_i = {0, 1};
        for (uint64_t i = 0; i < n; i++) {
            if ((i & cbit) && !(i & tbit)) {
                uint64_t j = i | tbit;
                complex_t a = data_[i];
                complex_t b = data_[j];
                data_[i] = neg_i * b;
                data_[j] = pos_i * a;
            }
        }
    }

    void apply_ch_(uint_t control, uint_t target) {
        uint64_t n = data_.size();
        uint64_t cbit = 1ULL << control;
        uint64_t tbit = 1ULL << target;
        double s = 1.0 / std::sqrt(2.0);
        for (uint64_t i = 0; i < n; i++) {
            if ((i & cbit) && !(i & tbit)) {
                uint64_t j = i | tbit;
                complex_t a = data_[i];
                complex_t b = data_[j];
                data_[i] = s * a + s * b;
                data_[j] = s * a - s * b;
            }
        }
    }

    void apply_swap_(uint_t q1, uint_t q2) {
        uint64_t n = data_.size();
        uint64_t bit1 = 1ULL << q1;
        uint64_t bit2 = 1ULL << q2;
        for (uint64_t i = 0; i < n; i++) {
            bool b1 = (i & bit1) != 0;
            bool b2 = (i & bit2) != 0;
            if (b1 && !b2) {
                uint64_t j = (i ^ bit1) | bit2;
                std::swap(data_[i], data_[j]);
            }
        }
    }

    // ---- Three-qubit gates -----------------------------------------------

    void apply_ccx_(uint_t c1, uint_t c2, uint_t target) {
        uint64_t n = data_.size();
        uint64_t cbit1 = 1ULL << c1;
        uint64_t cbit2 = 1ULL << c2;
        uint64_t tbit = 1ULL << target;
        for (uint64_t i = 0; i < n; i++) {
            if ((i & cbit1) && (i & cbit2) && !(i & tbit)) {
                std::swap(data_[i], data_[i | tbit]);
            }
        }
    }
};

} // namespace compat
} // namespace Qiskit

#endif // QISKIT_COMPAT_STATEVECTOR_HPP
