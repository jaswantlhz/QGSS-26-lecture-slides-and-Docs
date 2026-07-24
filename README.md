```text

  ██████╗ ██╗███████╗██╗  ██╗██╗████████╗
 ██╔═══██╗██║██╔════╝██║ ██╔╝██║╚══██╔══╝
 ██║   ██║██║███████╗█████═╝ ██║   ██║   
 ██║▄▄ ██║██║╚════██║██╔═██╗ ██║   ██║   
 ╚██████╔╝██║███████║██║  ██╗██║   ██║   
  ╚══▀▀═╝ ╚═╝╚══════╝╚═╝  ╚═╝╚═╝   ╚═╝   

   QISKIT GLOBAL SUMMER SCHOOL 2026 (QGSS '26)  
```

# IBM Qiskit Global Summer School 2026 (QGSS '26)

[![Qiskit](https://img.shields.io/badge/Qiskit-1.x-6929C4?style=for-the-badge&logo=qiskit&logoColor=white)](https://qiskit.org/)
[![IBM Quantum](https://img.shields.io/badge/IBM-Quantum-052147?style=for-the-badge&logo=ibm&logoColor=white)](https://quantum-computing.ibm.com/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Complete_Archive-brightgreen?style=for-the-badge)]()

Welcome to the comprehensive archive of lecture slides, presentation slides, reading guides, and practical workshop materials from the **IBM Qiskit Global Summer School 2026 (QGSS '26)**.

This repository contains the complete curriculum covering fundamental quantum mechanics, quantum algorithm design, hardware reality and noise mitigation, practical Qiskit programming, and research paper reading strategies.

---

## 📅 Lecture Slides & Core Curriculum

The curriculum is structured into core lecture modules led by research scientists and quantum computing experts:

| # | Lecture Title | Speaker / Instructor | Slide Deck |
|---|---|---|---|
| **01** | **Why Quantum? What Problem Are We Solving?** | Roland de Putter | [📄 Slide Deck](./QGSS26_%20Why%20Quantum_%20What%20Problem%20Are%20We%20Solving_%20-%20Roland%20de%20Putter.pdf) |
| **02** | **Quantum Mechanics for Computation** | QGSS 2026 Staff | [📄 Slide Deck](./QGSS%202026%20-%20Quantum%20Mechanics%20for%20Computation.pdf) |
| **03** | **Entanglement & Quantum Effects** | Thaddeus Pellegrini | [📄 Slide Deck](./QGSS2026_%20Entanglement%20%26%20Quantum%20Effects%20-%20Thaddeus%20Pellegrini.pdf) |
| **04** | **Quantum Algorithms I** | Will Kirby | [📄 Slide Deck](./QGSS_Quantum%20Algorithms%20I_Will%20Kirby.pdf) |
| **05** | **Quantum Algorithms II** | Javier Robledo Moreno | [📄 Slide Deck](./QGSS26%20-%20Quantum%20Algorithms%20II%20-%20Javier%20Robledo%20Moreno.pdf) |
| **06** | **Quantum Algorithms III** | Minh Tran | [📄 Slide Deck](./QGSS26%20-%20Quantum%20Algorithms%20III%20-%20Minh%20Tran.pdf) |
| **07** | **Quantum Algorithms IV** | Sabina Dragoi | [📄 Slide Deck](./QGSS26%20-%20Quantum%20Algorithms%20IV%20-%20Sabina%20Dragoi.pdf) |
| **08** | **Programming Quantum Computers** | Ibrahim Shehzad | [📄 Slide Deck](./QGSS26_%20Programming%20Quantum%20Computers%20-%20Ibrahim%20Shehzad.pdf) |
| **09** | **Noise, Hardware, and Reality** | Haimeng Zhang | [📄 Slide Deck](./QGSS26_%20Noise%2C%20Hardware%2C%20and%20Reality%20-%20Haimeng%20Zhang.pdf) |

---

## 🛠️ Workshops, Reading Strategies & Hands-On Exercises

In addition to core lectures, QGSS '26 included dedicated workshops for research methodology, GitHub collaboration, and guided practice:

### 🔬 Quantum Paper Reading Workshop
- 📑 **How to Read a Quantum Paper Guide**: [How to Read a Quantum Paper.pdf](./How%20to%20Read%20a%20Quantum%20Paper.pdf)
- ⚡ **Reading Strategy Cheat Sheet**: [reading-strategy-cheat-sheet (1).pdf](./reading-strategy-cheat-sheet%20(1).pdf)
- 🖥️ **Paper Workshop Presentation**: [qgss-paper-workshop-pres (1).pdf](./qgss-paper-workshop-pres%20(1).pdf)
- 📄 **Featured Research Paper**: [2603.03496v1.pdf](./2603.03496v1.pdf)

### 🐙 Open Source & Hands-on Tools
- 🐙 **GitHub Workshop Presentation**: [qgss-github-workshop-pres.pdf](./qgss-github-workshop-pres.pdf)
- 📝 **Guided Practice Excerpt**: [guided-practice-excerpt.pdf](./guided-practice-excerpt.pdf)

---

## 🚀 Recommended Learning Path

To get the most out of these materials, follow this recommended sequence:

```mermaid
flowchart TD
    A[1. Motivation & Foundations] --> B[2. Entanglement & Quantum Mechanics]
    B --> C[3. Quantum Algorithms I - IV]
    C --> D[4. Programming with Qiskit]
    D --> E[5. Noise, Hardware & Mitigation]
    E --> F[6. Paper Reading & Research Workshop]

    style A fill:#6929C4,color:#fff
    style B fill:#1192E8,color:#fff
    style C fill:#005D5D,color:#fff
    style D fill:#9F1853,color:#fff
    style E fill:#fa4d56,color:#fff
    style F fill:#570408,color:#fff
```

1. **Foundations**: Start with *Why Quantum?* followed by *Quantum Mechanics for Computation* and *Entanglement & Quantum Effects*.
2. **Algorithmic Mastery**: Proceed through *Quantum Algorithms I* to *IV* for a thorough deep dive into phase estimation, VQE, QAOA, and quantum error mitigation strategies.
3. **Implementation**: Study *Programming Quantum Computers* to translate mathematical concepts into executable Qiskit code.
4. **Real Hardware Considerations**: Read *Noise, Hardware, and Reality* to understand decoherence, gate errors, and pulse-level control.
5. **Research Proficiency**: Leverage the *Paper Reading Strategy Cheat Sheet* and workshop slides to analyze cutting-edge quantum literature like `2603.03496v1`.

---

## 💻 Quickstart: Running Qiskit

To execute quantum circuits corresponding to the lecture algorithms:

```bash
# Create and activate virtual environment
python -m venv qiskit-env
source qiskit-env/bin/activate  # On Windows: qiskit-env\Scripts\activate

# Install Qiskit 1.x ecosystem
pip install qiskit qiskit-ibm-runtime matplotlib
```

### 🔬 Basic Bell State Circuit Example

```python
from qiskit import QuantumCircuit
from qiskit.visualization import plot_histogram
from qiskit_aer import AerSimulator

# Create a Quantum Circuit with 2 qubits and 2 classical bits
qc = QuantumCircuit(2, 2)

# Apply Hadamard gate on qubit 0 to create superposition
qc.h(0)

# Apply CNOT gate with control qubit 0 and target qubit 1 to create Entanglement
qc.cx(0, 1)

# Measure qubits
qc.measure([0, 1], [0, 1])

# Simulate execution
simulator = AerSimulator()
result = simulator.run(qc, shots=1000).result()
counts = result.get_counts()

print("Entanglement Measurement Results:", counts)

# Print Qiskit ASCII Circuit
print(qc.draw('text'))
```

#### 📐 Generated Qiskit ASCII Circuit Diagram
```text
     ┌───┐     ┌─┐
q_0: ┤ H ├──■──┤M├───
     └───┘┌─┴─┐└╥┘┌─┐
q_1: ─────┤ X ├─╫─┤M├
          └───┘ ║ └╥┘
c: 2/═══════════╩══╩═
                0  1
```

---

## 🤝 Acknowledgments & Credits

- **Organizers**: [IBM Quantum](https://quantum-computing.ibm.com/) & [Qiskit Community](https://qiskit.org/)
- **Lecturers**: Roland de Putter, Thaddeus Pellegrini, Will Kirby, Javier Robledo Moreno, Minh Tran, Sabina Dragoi, Ibrahim Shehzad, Haimeng Zhang.
- **Repository Maintainer**: QGSS '26 Participant Archive.

---
*Created with for the Quantum Computing Community.*
