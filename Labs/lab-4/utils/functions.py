"""
Utility functions for QAOA partition analysis and error mitigation comparison.

This module provides functions to:
- Calculate partitions from experiment results
- Compute cut sizes for graph partitions
- Swap partitions to find better solutions
- Analyze error mitigation results
"""

from typing import Dict, List, Set, Tuple, Any
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import networkx as nx

def plot_partition_graph(
    partition_graph,
    numbers,
    seed=None,
    figsize=(10, 8),
    node_size=800,
    node_color="lightblue",
    font_size=14,
    font_weight="bold",
    show=True,
):
    """
    Plot a partition problem as a complete graph using a spring layout.

    Parameters
    ----------
    partition_graph : networkx.Graph
        Graph whose nodes correspond to indices in `numbers`.
    numbers : list or sequence
        List of numbers being partitioned; node i is labeled with numbers[i].
    seed : int or None, optional
        Random seed for the spring layout (for reproducibility).
    figsize : tuple, optional
        Size of the matplotlib figure.
    node_size : int, optional
        Size of the graph nodes.
    node_color : str or list, optional
        Color of the graph nodes.
    font_size : int, optional
        Font size for node labels.
    font_weight : str, optional
        Font weight for node labels.
    show : bool, optional
        Whether to display the plot immediately.
    """

    # Create spring layout (equivalent to rx.spring_layout)
    pos = nx.spring_layout(partition_graph, seed=seed)

    # Create node labels showing the actual numbers
    node_labels = {i: str(numbers[i]) for i in partition_graph.nodes()}

    # Create edge labels showing the weights
    edge_labels = nx.get_edge_attributes(partition_graph, 'weight')
    
    # Draw the graph
    plt.figure(figsize=figsize)
    nx.draw(
        partition_graph,
        pos=pos,
        with_labels=True,
        labels=node_labels,
        node_size=node_size,
        node_color=node_color,
        font_size=font_size,
        font_weight=font_weight,
    )
    
    # Draw edge labels (weights)
    nx.draw_networkx_edge_labels(
        partition_graph,
        pos=pos,
        edge_labels=edge_labels,
        font_size=10,
        font_color='red'
    )

    plt.title(
        "Partition Problem as a Complete Graph\n"
        "(Node labels show the numbers to partition, edge labels show weights)",
        fontsize=14,
        fontweight="bold",
    )

    if show:
        plt.show()

    print("\nEach node represents a number from our set.")
    print("Edges connect all pairs, weighted by the product of the numbers.")


# Auxiliary function to sample most likely bitstring
def to_bitstring(integer, num_bits):
    result = np.binary_repr(integer, width=num_bits)
    return [int(digit) for digit in result]


def analyze_partition_result(
    final_distribution_bin, numbers, partition_graph, version_name
):
    """
    Analyze and print the partition result from a distribution.

    Args:
        final_distribution_bin: Dictionary of binary counts/probabilities
        numbers: List of numbers to partition
        partition_graph: The graph representing the partition problem
        version_name: String identifier for the version being analyzed
    """
    print(f"\n{'=' * 80}")
    print(f"Analysis for {version_name}")
    print(f"{'=' * 80}")

    n = len(numbers)
    keys = list(final_distribution_bin.keys())
    values = list(final_distribution_bin.values())
    most_likely = keys[np.argmax(np.abs(values))]
    most_likely_bitstring = [int(digit) for digit in most_likely]
    most_likely_bitstring.reverse()

    print(f"Result bitstring: {most_likely_bitstring}")

    # Convert bitstring back to original partition
    qaoa_set1 = [numbers[i] for i in range(n) if most_likely_bitstring[i] == 1]
    qaoa_set2 = [numbers[i] for i in range(n) if most_likely_bitstring[i] == 0]

    difference = abs(sum(qaoa_set1) - sum(qaoa_set2))
    print("\nQAOA Partition Result:")
    print(f"Set 1: {qaoa_set1} (sum = {sum(qaoa_set1)})")
    print(f"Set 2: {qaoa_set2} (sum = {sum(qaoa_set2)})")
    print(f"Difference: {difference}")

    return most_likely_bitstring, qaoa_set1, qaoa_set2, difference, version_name


def get_partitions(experiment_result: List[Dict]) -> Tuple[List[int], List[int], int]:
    """
    Calculate the partitions based on the final expectation values.

    If the expectation value is positive, the node belongs to partition 0 (par0).
    Otherwise, the node belongs to partition 1 (par1).

    Parameters:
    -----------
    experiment_result : List[Dict]
        List of experiment results containing 'loss' and 'exp_map' keys

    Returns:
    --------
    Tuple[List[int], List[int], int]
        par0: List of nodes in partition 0
        par1: List of nodes in partition 1
        best_index: Index of the best result in experiment_result
    """
    par0, par1 = [], []
    best_index = min(
        range(len(experiment_result)), key=lambda i: experiment_result[i]["loss"]
    )

    for i in experiment_result[best_index]["exp_map"]:
        if experiment_result[best_index]["exp_map"][i] >= 0:
            par0.append(i)
        else:
            par1.append(i)

    return par0, par1, best_index




def calc_cut_size(graph: nx.Graph, partition0: Set[int], partition1: Set[int]) -> int:
    """
    Calculate the weighted cut size of a NetworkX graph
    given two disjoint vertex partitions.

    Parameters:
    -----------
    graph : networkx.Graph
        The graph to analyze
    partition0 : Set[int]
        First partition of vertices
    partition1 : Set[int]
        Second partition of vertices

    Returns:
    --------
    float
        The weighted cut size
    """
    cut_size = 0

    for u, v, weight in graph.edges(data="weight"):
        if (u in partition0 and v in partition1) or (
            u in partition1 and v in partition0
        ):
            cut_size += weight

    return int(cut_size)


def get_bits_from_partitions(
    experiment_result: List[Dict], best_index: int
) -> List[int]:
    """
    Convert partition assignments to a list of bits.

    Parameters:
    -----------
    experiment_result : List[Dict]
        List of experiment results
    best_index : int
        Index of the best result

    Returns:
    --------
    List[int]
        List of bits (1 for partition 0, 0 for partition 1)
    """
    cur_bits = []

    for i in experiment_result[best_index]["exp_map"]:
        if experiment_result[best_index]["exp_map"][i] >= 0:
            cur_bits.append(1)
        else:
            cur_bits.append(0)

    return cur_bits



def analyze_error_mitigation_result(
    loss: float,
    experiment_result: List[Dict],
    partition_graph,
    numbers: List[int],
) -> Dict[str, Any]:
    """
    Master function to analyze error mitigation results.

    Given a loss value and experiment result, this function:
    1. Extracts partitions using get_partitions
    2. Calculates initial cut size using calc_cut_size
    3. Optimizes partitions using swap_partitions to find best cut
    4. Maps partition indices to actual numbers
    5. Computes differences vs baseline (if provided)

    Parameters:
    -----------
    loss : float
        Loss value from the error mitigation run
    experiment_result : List[Dict]
        Experiment results containing exp_map with expectation values
    partition_graph : rustworkx.PyGraph
        The partition graph to analyze
    numbers : List[int]
        List of actual numbers/nodes to partition (maps indices to values)
    baseline_loss : float, optional
        Baseline loss for comparison (default: None)
    baseline_best_cut : float, optional
        Baseline best cut size for comparison (default: None)

    Returns:
    --------
    Dict[str, Any]
        Dictionary containing:
        - 'loss': Loss value
        - 'par0': Set of node indices in partition 0
        - 'par1': Set of node indices in partition 1
        - 'par0_size': Number of nodes in partition 0
        - 'par1_size': Number of nodes in partition 1
        - 'best_cut': Best cut size after optimization via swap_partitions
        - 'best_index': Index of best result in experiment_result
        - 'difference': Absolute difference in partition sizes
        - 'set0': List of actual numbers in optimized partition 0
        - 'set1': List of actual numbers in optimized partition 1
        - 'loss_diff': Difference from baseline loss (if baseline provided)
        - 'cut_diff': Difference from baseline best cut (if baseline provided)
        - 'exp_map': The exp_map from the best result
    """
    # Get partitions
    par0, par1, best_index = get_partitions(experiment_result)

    # Calculate cut size
    cut_size = calc_cut_size(partition_graph, par0, par1)
    cur_bits = []

    for i in experiment_result[best_index]["exp_map"]:
        if experiment_result[best_index]["exp_map"][i] >= 0:
            cur_bits.append(1)
        else:
            cur_bits.append(0)
    best_cut, best_bits = cut_size, cur_bits
    #
    # Build result dictionary
    set0 = [int(numbers[i]) for i in range(len(numbers)) if best_bits[i] == 1]
    set1 = [int(numbers[i]) for i in range(len(numbers)) if best_bits[i] == 0]
    result = {
        "loss": loss,
        "par0": par0,
        "par1": par1,
        "par0_size": len(par0),
        "par1_size": len(par1),
        "best_cut": int(best_cut),
        "best_index": best_index,
        "set0": set0,
        "set1": set1,
        "difference": abs(int(sum(set0) - sum(set1))),
        "exp_map":experiment_result[best_index]["exp_map"]
    }

    return result


def compare_error_mitigation_methods(
    results: Dict[str, Dict[str, Any]], baseline_key: str = "No EM"
) -> pd.DataFrame:
    """
    Create a comparison DataFrame for multiple error mitigation methods.

    Parameters:
    -----------
    results : Dict[str, Dict[str, Any]]
        Dictionary mapping method names to their analysis results
    baseline_key : str
        Key for the baseline method (default: 'No EM')

    Returns:
    --------
    pd.DataFrame
        Comparison dataframe with all metrics
    """
    baseline = results[baseline_key]

    comparison_data = []
    for method_name, result in results.items():
        row = {
            "Method": method_name,
            "Loss": result["loss"],
            "Best cut": result["best_cut"],
            "Par0 Size": result["par0_size"],
            "Par1 Size": result["par1_size"],
            "Set0 Sum": sum(result["set0"]),
            "Set1 Sum": sum(result["set1"]),
            "Difference": result["difference"],
        }

        if method_name != baseline_key:
            row["Loss Diff"] = result["loss"] - baseline["loss"]
            row["Cut Diff"] = result["best_cut"] - baseline["best_cut"]
        else:
            row["Loss Diff"] = 0.0
            row["Cut Diff"] = 0.0

        comparison_data.append(row)

    return pd.DataFrame(comparison_data)


def plot_error_mitigation_comparison(
    comparison_df: pd.DataFrame, figsize: Tuple[int, int] = (16, 12)
) -> None:
    """
    Create comprehensive visualization of error mitigation comparison.

    Parameters:
    -----------
    comparison_df : pd.DataFrame
        Comparison dataframe from compare_error_mitigation_methods
    figsize : Tuple[int, int]
        Figure size (width, height)
    """
    fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=figsize)

    colors = ["gray", "blue", "green", "orange", "lightcoral"]

    # Plot 1 (Top Left): Loss values
    ax1.bar(
        comparison_df["Method"],
        comparison_df["Loss"],
        color=colors[: len(comparison_df)],
    )
    ax1.set_ylabel("Loss Value", fontsize=12)
    ax1.set_title(
        "Loss Function Values by Error Mitigation Method",
        fontsize=14,
        fontweight="bold",
    )
    ax1.tick_params(axis="x", rotation=45)
    ax1.grid(axis="y", alpha=0.3)

    # Plot 2 (Top Right): Best cut sizes
    ax2.bar(
        comparison_df["Method"],
        comparison_df["Best cut"],
        color=colors[: len(comparison_df)],
    )
    ax2.set_ylabel("Best Cut Size", fontsize=12)
    ax2.set_title(
        "Best Cut Sizes by Error Mitigation Method", fontsize=14, fontweight="bold"
    )
    ax2.tick_params(axis="x", rotation=45)
    ax2.grid(axis="y", alpha=0.3)

    # Plot 3 (Bottom Left): Partition sums (Set0 and Set1)
    x = np.arange(len(comparison_df))
    width = 0.35

    # Calculate sums - handle both pre-calculated columns and raw data
    if "Set0 Sum" in comparison_df.columns and "Set1 Sum" in comparison_df.columns:
        # Use pre-calculated sums if available
        set0_sums = comparison_df["Set0 Sum"]
        set1_sums = comparison_df["Set1 Sum"]
    elif "set0" in comparison_df.columns and "set1" in comparison_df.columns:
        # Calculate sums from raw set data if columns exist
        set0_sums = comparison_df["set0"].apply(
            lambda x: sum(x) if isinstance(x, (list, tuple)) else x
        )
        set1_sums = comparison_df["set1"].apply(
            lambda x: sum(x) if isinstance(x, (list, tuple)) else x
        )
    else:
        # Fallback: try to infer from other available data
        # This handles the case where we might have the data in a different format
        raise ValueError(
            "DataFrame must contain either 'Set0 Sum'/'Set1 Sum' columns or 'set0'/'set1' columns. "
            "Available columns: " + str(list(comparison_df.columns))
        )

    ax3.bar(x - width / 2, set0_sums, width, label="Set 0", color="steelblue")
    ax3.bar(x + width / 2, set1_sums, width, label="Set 1", color="coral")
    ax3.set_ylabel("Sum of Items", fontsize=12)
    ax3.set_title(
        "Partition Sums by Error Mitigation Method", fontsize=14, fontweight="bold"
    )
    ax3.set_xticks(x)
    ax3.set_xticklabels(comparison_df["Method"], rotation=45)
    ax3.legend()
    ax3.grid(axis="y", alpha=0.3)

    # Plot 4 (Bottom Right): Difference between partition sizes
    ax4.bar(
        comparison_df["Method"],
        comparison_df["Difference"],
        color=colors[: len(comparison_df)],
    )
    ax4.set_ylabel("Absolute Difference", fontsize=12)
    ax4.set_title(
        "Partition Sum Difference by Error Mitigation Method",
        fontsize=14,
        fontweight="bold",
    )
    ax4.tick_params(axis="x", rotation=45)
    ax4.grid(axis="y", alpha=0.3)

    plt.tight_layout()
    plt.show()


def print_comparison_summary(comparison_df: pd.DataFrame) -> None:
    """
    Print a formatted summary of the error mitigation comparison.

    Parameters:
    -----------
    comparison_df : pd.DataFrame
        Comparison dataframe from compare_error_mitigation_methods
    """
    print("=" * 80)
    print("COMPREHENSIVE ERROR MITIGATION COMPARISON")
    print("=" * 80)
    print("\n", comparison_df.to_string(index=False))
    print()

    best_loss_idx = comparison_df["Loss"].idxmin()
    best_cut_idx = comparison_df[
        "Best cut"
    ].idxmax()  # Note: idxmax for best cut (higher is better)
    min_diff_idx = comparison_df["Difference"].idxmin()

    print("\n" + "=" * 80)
    print("KEY FINDINGS:")
    print("=" * 80)
    print(
        f"\n  • Best Loss: {comparison_df.loc[best_loss_idx, 'Method']} "
        f"(Loss: {comparison_df.loc[best_loss_idx, 'Loss']:.2f})"
    )
    print(
        f"  • Best Cut Size: {comparison_df.loc[best_cut_idx, 'Method']} "
        f"(Cut: {comparison_df.loc[best_cut_idx, 'Best cut']:.2f})"
    )
    print(
        f"  • Most Balanced Partition: {comparison_df.loc[min_diff_idx, 'Method']} "
        f"(Difference: {comparison_df.loc[min_diff_idx, 'Difference']:.0f} nodes)"
    )
    # print(f"\n  Technique Descriptions:")
    # print(f"    - No EM: Baseline with no error mitigation")
    # print(f"    - TREX: Twirled Readout Error eXtinction - mitigates readout errors")
    # print(f"    - ZNE + GT: Zero Noise Extrapolation + Gate Twirling - increasing noise to extrapolate to zero")
    # print(f"    - PEC + GT: Probabilistic Error Cancellation + Gate Twirling - inverting and cancelling errors")
    print("\n" + "=" * 80)
