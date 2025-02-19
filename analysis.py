import matplotlib.pyplot as plt
import numpy as np

globe_optimizations = {
    "Baseline": [149.432800, 149.078156, 149.200241, 149.456406, 149.838181],
    "Clang & -O3": [87.544670, 87.578232, 87.118912, 88.099012, 86.423901],
    "Pass-by-reference + const": [79.941566, 78.463921, 79.290189, 80.002810, 79.849910],
    "calcColor sort into find min": [62.837563, 62.669020, 63.991781, 62.147289, 62.312189],
    "Cache solveScaler": [61.650349, 61.493982, 61.629380, 61.638933, 61.500499],
    "Inline vector fns": [59.336449, 59.329853, 59.3289201, 59.339180, 59.330198],
    "std::vector to store Shapes": [59.582714, 59.572893, 59.580218, 59.582009, 59.609810],
    "OpenMP": [20.528299, 20.603994, 20.585447, 20.730810, 20.635468],
    "cache animation file data": [18.241960, 17.976510, 18.129013, 17.891272, 17.982912],
    "Swap Vector for glm::dvec3": [16.061337, 15.889606, 15.992389, 15.951021, 16.001291],
    "Use -O2 & -march=native": [15.997168, 16.070015, 16.010291, 15.893781, 15.982391]
}

pianoroom_optimizations = {
    "Baseline": [2.338898, 2.276867, 2.242707, 2.245594, 2.262816],
    "Clang & -O3": [1.097889, 1.109045, 1.103675, 1.100612, 1.106452],
    "Pass-by-reference + const": [0.902211, 0.906634, 0.915279, 0.910149, 0.907137],
    "calcColor sort into find min": [0.677787, 0.674361, 0.680516, 0.679136, 0.675707],
    "Cache solveScaler": [0.556714, 0.552245, 0.557643, 0.553557, 0.556254],
    "Inline vector fns": [0.600457, 0.599541, 0.607841, 0.606935, 0.601469],
    "std::vector to store Shapes": [0.597746, 0.600229, 0.602494, 0.601621, 0.600050],
    "OpenMP": [0.213480, 0.215623, 0.217733, 0.224879, 0.217462],
    "getLightIntersection early exit": [0.211994, 0.212027, 0.210880, 0.210315, 0.210534],
    "cache animation file data": [0.163746, 0.172653, 0.171921, 0.177115, 0.176974],
    "Swap Vector for glm::dvec3": [0.132569, 0.132404, 0.133807, 0.132101, 0.133420],
    "Use -O2 & -march=native": [0.130013, 0.129786, 0.130102, 0.129605, 0.131308]
}

fig, axs = plt.subplots(2, 1, figsize=(14, 10))

# Plot globe
labels1 = list(globe_optimizations.keys())
means1 = [np.mean(values) for values in globe_optimizations.values()]
x_positions1 = np.arange(len(labels1))

axs[0].bar(x_positions1, means1, capsize=5, color='skyblue', edgecolor='black')
axs[0].set_xticks(x_positions1)
axs[0].set_xticklabels(labels1, rotation=45, ha='right')
axs[0].set_ylabel("Execution Time (seconds)")
axs[0].set_title("Globe")

# Plot pianoroom
labels2 = list(pianoroom_optimizations.keys())
means2 = [np.mean(values) for values in pianoroom_optimizations.values()]
x_positions2 = np.arange(len(labels2))

axs[1].bar(x_positions2, means2, capsize=5, color='lightgreen', edgecolor='black')
axs[1].set_xticks(x_positions2)
axs[1].set_xticklabels(labels2, rotation=45, ha='right')
axs[1].set_xlabel("Optimization Technique")
axs[1].set_ylabel("Execution Time (seconds)")
axs[1].set_title("Pianoroom")

plt.tight_layout()
# plt.show()
plt.savefig('optimization_results.png', dpi=300, bbox_inches='tight')