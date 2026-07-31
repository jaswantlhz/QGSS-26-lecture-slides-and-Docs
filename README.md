```text
 ╔════════════════════════════════════════════════════════════════════════════════════════╗
 ║                                                                                        ║
 ║              ██████╗  ██████╗  ███████╗███████╗   ██╗   ███████╗  ██████╗              ║
 ║             ██╔═══██╗██╔════╝  ██╔════╝██╔════╝  ██╔╝   ╚════██║ ██╔════╝              ║
 ║             ██║   ██║██║  ███╗ ███████╗███████╗  ██║    ███████║ ███████╗              ║
 ║             ██║▄▄ ██║██║   ██║ ╚════██║╚════██║  ╚██╗   ██╔════╝ ██╔═══██╗             ║
 ║             ╚██████╔╝╚██████╔╝ ███████║███████║   ╚██╗  ███████╗ ╚██████╔╝             ║
 ║              ╚══▀▀═╝  ╚═════╝  ╚══════╝╚══════╝    ╚═╝  ╚══════╝  ╚══════╝              ║
 ║                                                                                        ║
 ║                    IBM QISKIT GLOBAL SUMMER SCHOOL 2026 (QGSS'26)                      ║
 ║                       OFFICIAL LABS & RESOURCE ARCHIVE                                 ║
 ║                                                                                        ║
 ╚════════════════════════════════════════════════════════════════════════════════════════╝
```

# IBM Qiskit Global Summer School 2026 (QGSS '26) Archive

[![Qiskit](https://img.shields.io/badge/Qiskit-2.x-6929C4?style=for-the-badge&logo=qiskit&logoColor=white)](https://qiskit.org/)
[![IBM Quantum](https://img.shields.io/badge/IBM-Quantum-052147?style=for-the-badge&logo=ibm&logoColor=white)](https://quantum-computing.ibm.com/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg?style=for-the-badge)](LICENSE)
[![Labs](https://img.shields.io/badge/Labs-0_to_4c-ff69b4?style=for-the-badge&logo=jupyter&logoColor=white)](./Labs/)
[![Multilingual](https://img.shields.io/badge/Languages-EN%20%7C%20JA%20%7C%20KO-blueviolet?style=for-the-badge)]()
[![Shared Resources](https://img.shields.io/badge/Shared_Resources-152+_Items-brightgreen?style=for-the-badge)](./share-a-resource/README.md)
[![Memes](https://img.shields.io/badge/Community_Memes-93_Files-orange?style=for-the-badge)](./QGSS26-memes/)

Welcome to the official community archive for the **IBM Qiskit Global Summer School 2026 (QGSS '26)**.

This repository serves as a complete repository of all hands-on laboratory notebooks (Labs 0 through 4c), dual-stack implementations in **Python (Qiskit 2.x)** and **C++**, multilingual translations (English, Japanese, and Korean), 56 PDF research papers & textbooks, 96 curated external web tools, and 93 community-contributed memes and media.

---

## Directory Structure & Master Catalog

```text
.
├── Labs/                               # Hands-on Quantum Computing Labs (Labs 0 to 4c)
│   ├── lab-0/                          # Lab 0: Setup & Qiskit Fundamentals (EN, JA)
│   ├── lab-1/                          # Lab 1: Circuit Building for Real Hardware
│   │   ├── cpp/                        # C++ Implementation with CMake & C++ Headers
│   │   └── python/                     # Pure Python + Qiskit 2.x Implementation
│   ├── lab-2/                          # Lab 2: Quantum Algorithms & State Prep (EN, JA, KO)
│   ├── lab-3/                          # Lab 3: Quantum Noise, Error Mitigation & Characterization (EN, JA, KR)
│   └── lab-4/                          # Lab 4: Advanced Workflows & Applications
│       ├── QGSS2026_Lab4a.ipynb        # Lab 4a: Part A (EN, JA, KO)
│       ├── QGSS2026_Lab4b.ipynb        # Lab 4b: Part B (EN, JA, KO)
│       ├── QGSS2026_Lab4c.ipynb        # Lab 4c: Part C (EN, JA, KO)
│       └── utils/                      # Helper scripts & pre-trained parameter matrices
├── share-a-resource/                   # Community Shared Literature & Web Catalog
│   ├── 56 PDF Papers & Books           # Research papers (Surface codes, QML, QIT, Tensor Networks)
│   ├── share-a-resource-links.txt      # 96 Curated external web links & interactive tools
│   └── README.md                       # Full 152+ item resource index
├── QGSS26-memes/                       # 93 Community Memes, WebP Graphics & Videos
├── LICENSE                             # MIT License
└── README.md                           # Master Catalog & Repository Guide
```

---

## Laboratory Curriculum & Walkthrough Index

All lab notebooks are provided in English (`.ipynb`), along with community translations in Japanese (`_ja.ipynb`) and Korean (`_ko.ipynb` / `_kr.ipynb`).

| Lab # | Topic / Description | Stack / Language | Available Translations | Direct Notebook Link |
|---|---|---|---|---|
| **Lab 0** | **Welcome & Qiskit Setup** | Python / Qiskit 2.x | English, Japanese | [`Labs/lab-0/QGSS2026_Lab0.ipynb`](./Labs/lab-0/QGSS2026_Lab0.ipynb) |
| **Lab 1 (Python)** | **Building Circuits for Real Hardware** | Python / Qiskit 2.x | English, Japanese | [`Labs/lab-1/python/QGSS2026_Lab1.ipynb`](./Labs/lab-1/python/QGSS2026_Lab1.ipynb) |
| **Lab 1 (C++)** | **C++ Quantum Simulation & Walkthrough** | C++17 / CMake | English, Japanese | [`Labs/lab-1/cpp/QGSS2026_Lab1_cpp.ipynb`](./Labs/lab-1/cpp/QGSS2026_Lab1_cpp.ipynb) |
| **Lab 2** | **Quantum Algorithms & State Preparation** | Python / Qiskit 2.x | English, Japanese, Korean | [`Labs/lab-2/QGSS2026_Lab2.ipynb`](./Labs/lab-2/QGSS2026_Lab2.ipynb) |
| **Lab 3** | **Noise, Error Mitigation & Characterization** | Python / Qiskit 2.x | English, Japanese, Korean | [`Labs/lab-3/QGSS2026_Lab3.ipynb`](./Labs/lab-3/QGSS2026_Lab3.ipynb) |
| **Lab 4a** | **Advanced Quantum Applications (Part A)** | Python / Qiskit 2.x | English, Japanese, Korean | [`Labs/lab-4/QGSS2026_Lab4a.ipynb`](./Labs/lab-4/QGSS2026_Lab4a.ipynb) |
| **Lab 4b** | **Advanced Quantum Applications (Part B)** | Python / Qiskit 2.x | English, Japanese, Korean | [`Labs/lab-4/QGSS2026_Lab4b.ipynb`](./Labs/lab-4/QGSS2026_Lab4b.ipynb) |
| **Lab 4c** | **Advanced Quantum Applications (Part C)** | Python / Qiskit 2.x | English, Japanese, Korean | [`Labs/lab-4/QGSS2026_Lab4c.ipynb`](./Labs/lab-4/QGSS2026_Lab4c.ipynb) |

---

## Community Share-a-Resource Collection

The repository features an extensive archive of **152+ community-curated learning materials** located in [`share-a-resource/`](./share-a-resource/README.md).

### 1. Research Papers & Textbooks (56 PDF Documents)
- **Fault-Tolerant QC & Surface Codes**: *A Game of Surface Codes* (Litinski), *Surface Code Quantum Computing by Lattice Surgery*, *Quantum Error Correction for Beginners* (Devitt et al.).
- **Quantum Information Theory & Foundational Notes**: *John Watrous QIC 710 Quantum Information Theory*, *Advanced Quantum Theory Notes*.
- **Quantum Algorithms & Scientific Computation**: *Lecture Notes on Quantum Algorithms* (2507.11565v1), *Quantum Algorithms for Scientific Computation*, *Quantum Viterbi Algorithm*, *Quantum Koopman Algorithms*.
- **Noise Tailoring & Error Mitigation**: *Noise Tailoring for Error Mitigation & Diagnosing Digital Quantum Computers* (2601.04830v2), *Joschka Roffe's QEC Guide*.
- **Quantum Machine Learning**: *Introduction to QML for Non-Practitioners*, *Implicit Differentiation of Tensor Networks*, *QML Tutorial for ML Practitioners*.
- **Quantum Advantage & Hardware**: *Mind the Gaps: The Fraught Road to Quantum Advantage*, *How to Build a Quantum Supercomputer*, *Crossing the 12,000-Atom Barrier*.
- **Foundational Textbooks & Notes**: *Ronald de Wolf's QC Lecture Notes*, *Fred Loceff Vol 1*, *Scott Aaronson Lecture Note Collection*.

### 2. External Web Resources & Tools (96 Links)
- **Waterloo & Cambridge Course Portals**: John Watrous Quantum Information Theory Notes (`cs.uwaterloo.ca/~watrous`), Watrous Book Portal, David Tong Theoretical Physics Lectures (`davidtong.org`).
- **Roadmaps & Conceptual Guides**: QC Roadmaps (`qcroadmap.com`), Quantum Computing for Very Curious (`quantum.country/qcvc`), Informaq (`informaq.spinsphere.xyz`), Tallinn Manual (`ccdcoe.org`).
- **Interactive Circuit Simulators**: Quirk, Quantum-Circuit Studio, Quantum-Kit, Quantum Inspire.
- **Video Courses & Tutorials**: Gilbert Strang's Linear Algebra (MIT), WIRED Quantum Computing 5 Levels, QWorld Lectures.
- **Academic Journals & Series**: JHEP (`Journal of High Energy Physics`), Springer Graduate Texts in Physics, PRX Quantum, Nature NPJ QI, IEEE TQE.
- **Tools & Infrastructure**: Post-Quantum Cryptography Benchmarks, Slurm-Qiskit HPC Clusters, IBM Quantum Learning Modules.

For the full detailed catalog, refer to [`share-a-resource/README.md`](./share-a-resource/README.md).- **Fault-Tolerant QC & Surface Codes**: *A Game of Surface Codes* (Litinski), *Surface Code Quantum Computing by Lattice Surgery*, *Quantum Error Correction for Beginners* (Devitt et al.).
- **Quantum Machine Learning**: *Introduction to QML for Non-Practitioners*, *Implicit Differentiation of Tensor Networks*, *QML Tutorial for ML Practitioners*.
- **Quantum Advantage & Hardware**: *Mind the Gaps: The Fraught Road to Quantum Advantage*, *How to Build a Quantum Supercomputer*, *Crossing the 12,000-Atom Barrier*.
- **Foundational Textbooks & Notes**: *Ronald de Wolf's QC Lecture Notes*, *Fred Loceff Vol 1*, *Scott Aaronson Lecture Note Collection*.

### 2. External Web Resources & Tools (100+ Links)
- **Interactive Circuit Simulators**: Quirk, Quantum-Circuit Studio, Quantum-Kit, Quantum Inspire.
- **Video Courses & Tutorials**: Gilbert Strang's Linear Algebra (MIT), WIRED Quantum Computing 5 Levels, QWorld Lectures.
- **Tools & Infrastructure**: Post-Quantum Cryptography Benchmarks, Slurm-Qiskit HPC Clusters, IBM Quantum Learning Modules.

For the full detailed catalog, refer to [`share-a-resource/README.md`](./share-a-resource/README.md).

---

## QGSS '26 Community Meme Collection

Learning quantum mechanics and debugging quantum hardware queues is an unforgettable experience! The [`QGSS26-memes/`](./QGSS26-memes/) folder preserves **93 community-contributed memes, WebP graphics, and video clips (`.mp4`)** celebrating the fun, hardware struggles, and inside jokes of QGSS '26.

---

## Quickstart & Environment Setup

### 1. Python Virtual Environment Setup

To run the Jupyter Notebooks locally with **Qiskit 2.x**:

```bash
# Create and activate virtual environment
python -m venv qiskit-env
source qiskit-env/bin/activate  # On Windows: qiskit-env\Scripts\activate

# Install Qiskit 2.x ecosystem and Jupyter Lab
pip install "qiskit>=2.0" qiskit-ibm-runtime qiskit-aer matplotlib jupyterlab
```

Launch Jupyter Lab:
```bash
jupyter lab
```

### 2. C++ Environment Setup (Lab 1 C++)

For the high-performance C++ implementation of Lab 1:

```bash
cd Labs/lab-1/cpp

# Create build directory and compile using CMake
mkdir build && cd build
cmake ..
make -j4
```

---

## Qiskit 2.x Code Example: Bell State Entanglement

Here is a working Qiskit 2.x snippet demonstrating circuit creation and execution using `AerSimulator`:

```python
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator

# Initialize 2-qubit circuit with 2 classical bits
qc = QuantumCircuit(2, 2)

# Create superposition on qubit 0 and entangle with qubit 1
qc.h(0)
qc.cx(0, 1)

# Measure both qubits
qc.measure([0, 1], [0, 1])

# Run simulation using AerSimulator
simulator = AerSimulator()
result = simulator.run(qc, shots=1000).result()
counts = result.get_counts()

print("Entanglement Measurement Results:", counts)
print("\nCircuit Diagram:")
print(qc.draw('text'))
```

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

## Acknowledgments & Credits

- **Organizers**: [IBM Quantum](https://quantum-computing.ibm.com/) & [Qiskit Community](https://qiskit.org/)
- **Lecturers & TAs**: IBM Quantum research scientists, Qiskit software developers, and global TAs.
- **Multilingual Translators**: Community volunteers providing Japanese (`ja`) and Korean (`ko`/`kr`) notebook translations.
- **Repository Maintainer**: [@jaswantlhz](https://github.com/jaswantlhz) for compiling the QGSS '26 community archive.

---
*Created for the Quantum Computing Community. Distributed under the [MIT License](LICENSE).*
