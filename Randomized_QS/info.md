# 🌀 Randomized Quicksort

## 🔍 Introduction
**Randomized Quicksort** is a variation of the standard **Quicksort** algorithm.  
In regular Quicksort, a pivot element is usually chosen as the first, last, or middle element of the array.  
However, if the input data is already sorted (or nearly sorted), this choice can lead to **worst-case performance**.

To avoid this, **Randomized Quicksort** chooses the pivot element **randomly**.  
This randomization reduces the chance of encountering the worst case and gives much better expected performance.

---

## ⚙️ Algorithm Steps

1. **Choose a Random Pivot**  
   Select a random element from the array as the pivot.

2. **Partition the Array**  
   Arrange elements so that:
   - All elements smaller than the pivot come **before** it.  
   - All elements greater than the pivot come **after** it.

3. **Recursively Apply Quicksort**  
   Apply the same process to the left and right subarrays.

---

## 🧠 Example

Suppose the array is:

[8, 3, 5, 2, 7]


- Randomly pick a pivot (say, `5`)
- Partition around `5` → `[3, 2] [5] [8, 7]`
- Recursively sort `[3, 2]` → `[2, 3]`
- Recursively sort `[8, 7]` → `[7, 8]`

Final sorted array → `[2, 3, 5, 7, 8]`

---

## ⏱️ Time Complexity

| Case | Description | Time Complexity |
|------|--------------|-----------------|
| **Best Case** | Array splits evenly at each step | `O(n log n)` |
| **Average Case** | Random pivot gives fairly balanced splits | `O(n log n)` |
| **Worst Case** | Random pivot repeatedly picks poor splits | `O(n²)` |

However, because the pivot is **chosen randomly**, the chance of consistently poor splits is **extremely low**.  
Therefore, the **expected time complexity** is:

Expected Time Complexity = O(n log n)


---

## 💡 Advantages of Randomized Quicksort

- Reduces the possibility of worst-case scenarios.
- Simple to implement and efficient in practice.
- Performs well for large datasets.

---

## 🧩 Space Complexity

- **Space Complexity:** `O(log n)` (for recursion stack)

---

## ✅ Summary

| Property | Randomized Quicksort |
|-----------|----------------------|
| Pivot Selection | Random |
| Average Time Complexity | `O(n log n)` |
| Worst Time Complexity | `O(n²)` |
| Space Complexity | `O(log n)` |
| Algorithm Type | Divide and Conquer |
| Stability | Not Stable |

---

> 📝 **In short:**  
> Randomized Quicksort is just like normal quicksort, but by picking the pivot randomly, it avoids bad splits and achieves `O(n log n)` expected time complexity on average.
