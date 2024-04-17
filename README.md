# SOC_Project
Automatic Clock gating on OpenROAD framework
---
abstract: |
  In digital integrated circuit design, achieving a balance between
  power efficiency, performance, and area optimization is paramount.
  This project presents an automated clock gating algorithm integrated
  into the OpenROAD framework to facilitate the development of
  tape-out-ready chips. Leveraging clock gating, which diminishes
  dynamic power consumption by deactivating the clock in dormant
  segments of the circuit, the algorithm aims to bolster power
  efficiency. Implementing automated clock gating after netlist
  generation involves analyzing the netlist to identify signals that can
  be used as enable signals for clock gating, inserting clock gating
  logic into the netlist, and then writing out the modified netlist with
  the added clock gating logic. This approach can be implemented using
  scripting languages, enabling designers to achieve power-efficient
  designs without the need for additional synthesis steps. Evaluation of
  key design metrics, including power consumption, synthesized area,
  place-and-route area, and die area, relative to the percentage of
  gated registers, elucidates the algorithm’s impact and trade-offs.
  
Authors:
- Ansh Bhatnagar (ab10741@nyu.edu)
- Dhana Laxmi Sirigireddy (ds6992@nyu.edu)
- Jayanth Rajaram Sastry  (js12891@nyu.edu)
---

# Introduction

In the field of digital integrated circuits, enhancing power efficiency
is a critical challenge with widespread implications. The global
proliferation of electronic devices, numbering in the billions,
significantly increases the demand for energy. This demand raises
operational costs and environmental concerns due to the associated
carbon emissions from energy production.

Clock gating as described
Figure <a href="#fig:clock" data-reference-type="ref" data-reference="fig:clock">1</a>,
is a technique designed to reduce dynamic power consumption, which
occurs when a circuit switches states, by disabling the clock signal to
inactive parts of the circuit. This approach can significantly reduce
power usage without compromising the functionality of the device.
However, the implementation of clock gating using open source tools
often requires manual intervention, making the process labor-intensive
and susceptible to errors.

Existing automated solutions for clock gating are generally embedded
within proprietary tools, limiting their accessibility to a wide
audience. This situation creates a barrier for many designers,
particularly those in academic settings or part of open-source projects,
who may not have the resources to access such tools.

The project proposes an automated clock gating algorithm integrated into
the OpenROAD framework, an open-source digital circuit design tool. This
integration aims to offer a more accessible, efficient solution for
implementing clock gating, addressing the limitations of current
methods. By making advanced power optimization techniques more widely
available, this initiative seeks to lower the power consumption and
operational costs of digital circuits, benefiting a broad spectrum of
users.

![clock_gating](https://github.com/D-girl-11t/SOC_Project/assets/63849382/f42a3346-cdbf-4847-8022-e31d64eb5854)


# Proposed Approach

In digital integrated circuit design, achieving a balance between power
efficiency, performance, and area optimization is crucial. This project
introduces an automated clock gating algorithm integrated into the
OpenROAD framework to simplify the development of tape-out-ready chips.
Clock gating, a technique that reduces dynamic power consumption by
deactivating the clock in inactive circuit segments, is utilized to
improve power efficiency. The algorithm involves analyzing the
synthesized netlist to identify clock enable signals for gating and
inserting clock gating logic for each identified signal. The modified
netlist integrates the gating logic, effectively reducing power
consumption during idle periods.

The algorithm’s impact and trade-offs can be assessed by evaluating key
design metrics such as power consumption, synthesized area,
place-and-route area, and die area relative to the percentage of gated
registers. The OpenROAD framework is utilized as the foundation for
implementing and evaluating the proposed algorithm.

Here’s a brief overview of the algorithm:

-   Read Netlist and Library: Read the synthesized netlist and the
    corresponding Liberty library.

-   Identify Clock Enable Signals: Analyze the netlist to find signals
    suitable for clock gating, typically based on their activity.

-   Insert Clock Gating Logic: For each identified signal, insert clock
    gating logic by adding AND gates between the clock signal and
    flip-flop clock inputs.

-   Write Modified Netlist: Save the modified netlist with the added
    clock gating logic.

# Related work

In our project, we aim to address the limitations present in existing
clock gating approaches, such as those exemplified by the Lighter
plugin. While solutions like Lighter demonstrate the advantages of
automated clock gating in reducing dynamic power consumption, they may
not be fully optimized for seamless integration within the OpenROAD
environment or lack the requisite level of automation needed for
efficient utilization across various design stages. Notably, Lighter’s
lack of upstreaming to Yosys or OpenROAD severely limits its adoption,
as it is not part of the default design flow for most open-source
designers, resulting in minimal usage.

Our approach seeks to overcome these challenges by automating the
detection and implementation of clock gating opportunities, thereby
enhancing dynamic power and area reduction without compromising
performance. By focusing on seamless integration with the OpenROAD
framework and ensuring comprehensive automation, our method aims to
provide a simpler and more effective means for designers to achieve
power efficiency in ASIC designs, where dynamic power poses a
significant concern.

[Lighter](https://github.com/AUCOHL/Lighter)

[OpenROAD](https://github.com/The-OpenROAD-Project)
# Design Constraints

In our project, we are focused on automating clock gating in digital
integrated circuits to reduce power consumption. This effort is guided
by practical design constraints and optimization targets informed by an
analysis of an existing open-source clock gating plugin. These
benchmarks serve as a foundation for setting achievable goals within our
project timeline.

Our primary objective is to achieve a significant reduction in power
consumption without compromising timing. We aim for a minimum power
reduction of 20%, with the potential for certain designs to see up to
43% less power consumption, as observed in benchmarks of designs such as
AHB_SRAM and blake2s_m\_select used in the lighter project.

In terms of chip area optimization, we seek to decrease the number of
cells while preserving functionality. Benchmarks indicate a potential
reduction percentage ranging from approximately 3.7% to 25.7% across
various designs.

To quantify our progress, we have established specific targets for power
reduction percentage, ranging from 17% to 43%, based on the observed
benchmarks. Additionally, we plan to track the percentage of gated
endpoints as a Figure of Merit (FoM), as this metric provides valuable
insights into the effectiveness of our clock gating implementation.

# System-on-Chip Architecture

Our approach targets the modification of the existing OpenROAD codebase,
written in C++, to seamlessly integrate the Automated Clock Gating
Algorithm. This algorithm will be implemented to optimize power
management after the synthesis phase, which is performed by a separate
tool called Yosys, and before the floorplanning phase, which occurs
within OpenROAD.

Our efforts are focused on extending the capabilities of the OpenROAD
codebase by integrating our automated clock gating technique. Leveraging
the compilation framework provided by OpenROAD (CMake), we are adapting
the existing infrastructure to incorporate our enhancements effectively.
The automated clock gating algorithm, which forms the core of our
solution, will intelligently identify opportunities for clock gating
within the synthesized netlist, targeting inactive segments of the
circuit to reduce power consumption.

Rather than developing entirely new components from scratch, our
approach seeks to build upon the strengths of the existing OpenROAD
codebase. Through targeted modifications, we aim to address specific
power efficiency challenges encountered in SoC design. By strategically
integrating automated clock gating, our project endeavors to achieve a
more power-efficient chip design within the established OpenROAD
workflow, ultimately contributing to advancements in SoC architecture.
Figure <a href="#fig:flow" data-reference-type="ref" data-reference="fig:flow">2</a>
represents the workflow of the project.

<img width="508" alt="Screenshot 2024-02-23 at 3 56 56 PM copy" src="https://github.com/D-girl-11t/SOC_Project/assets/63849382/09624662-22a4-466c-af1a-d6a012aab4ec">


# Proposed Milestones

1\. Familiarize with OpenROAD codebase and Develop clock gating
algorithm: During this initial phase, our focus is on understanding the
OpenROAD codebase and developing the automated clock gating algorithm.
This milestone encompasses tasks aimed at gaining familiarity with the
existing codebase and creating the algorithm to be integrated into the
framework.

2\. Test clock gating algorithm with a finite state machine: The next
milestone involves testing the efficacy of our clock gating algorithm
with a finite state machine. This stage allows us to evaluate the
algorithm’s functionality and effectiveness in a controlled environment,
setting the stage for further implementation.

3\. Implement clock gating in riscv_top_151 processor used in the
Lighter project: Following successful testing with the finite state
machine, we proceed to implement the clock gating algorithm in the
riscv_top_151 processor. This milestone marks the integration of the
algorithm into a more complex design, showcasing its adaptability and
scalability.

4\. Evaluate designs based on specified metrics: With clock gating
implemented in the processor, we move on to evaluating the designs based
on specified metrics. This milestone involves assessing the impact of
clock gating on various design parameters, including power consumption,
performance, and area optimization.

5\. Test and benchmark clock gating algorithm: In this phase, we conduct
extensive testing and benchmarking of the clock gating algorithm. This
milestone allows us to validate the algorithm’s accuracy, efficiency,
and performance under different conditions, ensuring its robustness and
reliability.

6\. Refine and optimize algorithm: Building on insights gained from
testing and benchmarking, we refine and optimize the clock gating
algorithm. This milestone involves fine-tuning the algorithm to improve
its effectiveness and efficiency, addressing any issues or limitations
identified during testing.

7\. Compile project findings and outcomes: As we near the project’s
conclusion, we compile our findings, experiences, and outcomes into
comprehensive project presentations and reports. This milestone
encompasses the documentation of project objectives, methodologies,
results, and conclusions, providing a comprehensive overview of our
work.

8\. Open-source code and create GitHub pull request: The final milestone
involves open-sourcing our code and creating a GitHub pull request
against the OpenROAD repository. This milestone marks the culmination of
our efforts, making our enhancements accessible to the wider community
and contributing to the ongoing development of the OpenROAD framework.

These milestones serve as crucial markers of progress throughout the
project, guiding our efforts and ensuring the successful achievement of
our goals within the specified timeline. The Gantt Chart is presented in
Figure
 <a href="#Gantt" data-reference-type="ref" data-reference="Gantt">3</a>.

![newplot](https://github.com/D-girl-11t/SOC_Project/assets/63849382/10450065-39b2-4ae5-9ac4-8c12c67888e9)


# Verification

Verification of the effectiveness and accuracy of the automated clock
gating algorithm is crucial to ensure its practical utility within the
OpenROAD framework. This phase rigorously tests the algorithm’s ability
to preserve the functional correctness of the design. Tests are designed
to ensure that the algorithm doesn’t inadvertently insert clock gates
where they shouldn’t be, potentially compromising circuit functionality.
This step establishes confidence in the algorithm’s reliability in
preserving design integrity.

# Evaluation

Our methodology involves conducting comparative analyses on select
designs from the OpenROAD Benchmark Suite, evaluating key design metrics
before and after the implementation of clock gating. Specifically, we
focus on metrics such as power consumption, synthesized area,
place-and-route area, core area and die area, with particular attention
to the correlation with the percentage of gated registers.We are
evaluating all these metrics on riscv_top_151 processor which was one of
the designs used in the lighter project. By directly comparing these
metrics before and after clock gating, we aim to quantitatively assess
the algorithm’s effectiveness in reducing power consumption while
balancing performance and area requirements.

Throughout the evaluation process, adjustments to design constraints
will be systematically explored to identify optimal configurations that
yield significant improvements in power, performance, and area (PPA).
Success will be measured against predefined quantitative goals,
including specified reductions in power consumption and enhancements in
synthesized and place-and-route area, all while ensuring chip
performance remains uncompromised.

g++ -o readfile integrated_clockgating.cpp
./readfile 1_synth.v  

