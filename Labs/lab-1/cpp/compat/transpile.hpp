// ============================================================================
// compat/transpile.hpp -- Transpilation wrapper matching Qiskit/Python API
//
// Provides generate_preset_pass_manager() that returns a pass manager
// whose run() method produces compat::QuantumCircuit objects (with wide
// draw support on Colab).
//
// TEMPORARY: This wrapper can be removed once qiskit-cpp's draw() accepts
// a fold width parameter.
//
// Usage (matches Python Qiskit API):
//   #include "compat/transpile.hpp"
//   auto target = Qiskit::compat::make_torino_target();
//   auto pm = generate_preset_pass_manager(1, target);
//   auto isa_qc = pm.run(circ);
// ============================================================================

#ifndef QISKIT_COMPAT_TRANSPILE_HPP
#define QISKIT_COMPAT_TRANSPILE_HPP

#include "circuit/quantumcircuit.hpp"
#include "transpiler/target.hpp"
#include "transpiler/preset_passmanagers/generate_preset_pass_manager.hpp"
#include "compat/quantumcircuit.hpp"

namespace Qiskit {
namespace compat {

// Pass manager wrapper whose run() returns compat::QuantumCircuit
class PresetPassManager {
    transpiler::StagedPassManager pm_;
public:
    PresetPassManager(transpiler::StagedPassManager pm) : pm_(pm) {}

    QuantumCircuit run(circuit::QuantumCircuit& circ) {
        circuit::QuantumCircuit result = pm_.run(circ);
        return QuantumCircuit(result);
    }
};

// Matches Python: generate_preset_pass_manager(optimization_level, target=target)
inline PresetPassManager generate_preset_pass_manager(
        int optimization_level,
        transpiler::Target& target) {
    return PresetPassManager(
        transpiler::generate_preset_pass_manager(optimization_level, target));
}

} // namespace compat
} // namespace Qiskit

#endif // QISKIT_COMPAT_TRANSPILE_HPP
