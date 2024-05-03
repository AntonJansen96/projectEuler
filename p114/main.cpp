#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <atomic>
#include <omp.h>

size_t const N = 50;

void genPartitionsHelper(int n, std::vector<int> &part, int max, std::vector<std::vector<int>>& result)
{
    if (n == 0)
    {
        result.push_back(part);
        return;
    }

    for (int i = std::min(max, n); i >= 1; i--)
    {
        part.push_back(i);
        genPartitionsHelper(n - i, part, i, result);
        part.pop_back();
    }
}

std::vector<std::vector<int>> genPartitions(int n)
{
    std::vector<std::vector<int>> result;
    std::vector<int> part;
    genPartitionsHelper(n, part, n, result);
    return result;
}

class PartitionClassifier
{
    size_t d_ones;
    std::vector<int> d_array;

    public:
        std::vector<int> d_part;
        size_t d_multiplicity;

        PartitionClassifier(std::vector<int> const &part)
        :
            d_ones(std::count(part.begin(), part.end(), 1)),
            d_part(part),
            d_multiplicity(1)
        {
            for (size_t blocklen = 3; blocklen != 51; ++blocklen)
            {
                auto const num = std::count(part.begin(), part.end(), blocklen);
                if (num > 0)
                    d_array.push_back(num);
            }
        }

        bool operator==(const PartitionClassifier &other) const
        {
            return (d_array == other.d_array) && (d_ones == other.d_ones);
        }
};

std::tuple<size_t, size_t> vectorHash(std::vector<int> const &array)
{
    std::size_t seed1 = array.size();
    std::size_t seed2 = array.size() + 1;

    for (auto const &i : array)
    {
        seed1 ^= std::hash<int>()(i) + 0x9e3779b9 + (seed1 << 6) + (seed1 >> 2);
        seed2 ^= std::hash<int>()(i) + 0x9e3779b9 + (seed2 << 6) + (seed2 >> 2);
    }

    return std::make_tuple(seed1, seed2);
}

size_t uniqueCorrectPerms(PartitionClassifier &classifier)
{
    size_t count = 0;
    std::map<std::tuple<size_t, size_t>, bool> dict;
    auto &part = classifier.d_part;
    auto const multiplicity = classifier.d_multiplicity;

    std::sort(part.begin(), part.end());

    do
    {
        // Create hash of the current permutation of the part.
        auto const hash = vectorHash(part);

        // If the hash is not yet in the dictionary.
        if (dict.find(vectorHash(part)) == dict.end())
        {   // This block checks if there are two non-1 blocks next to each other.
            bool skip = false;
            for (size_t idx = 0; idx < part.size() - 1; ++idx)
            {
                if (part[idx] != 1 && part[idx + 1] != 1)
                {
                    skip = true;
                    break;
                }
            }
            if (not skip)
            {
                dict[hash] = true;
                count += multiplicity;
            }
        }
    } while (std::next_permutation(part.begin(), part.end()));

    return count;
}

int main()
{
    std::vector<PartitionClassifier> distinct_partitions;

    for (auto &part : genPartitions(N))
    {
        // Filter partitions containing a block of length 2.
        if (std::find(part.begin(), part.end(), 2) != part.end())
            continue;

        // Filter partitions without gray squares (will have blocks touching).
        if ((std::find(part.begin(), part.end(), 1) == part.end()) and part.size() != 1)
            continue;

        // Speedup: filter out all partitions that contains too
        // many numbers != 1 so they will never be valid anyway.
        size_t const ones = std::count(part.begin(), part.end(), 1);
        size_t const other = part.size() - ones;
        if (other > ones + 1)
            continue;

        // This block checks if partitions are equivalent to save a lot of time.
        auto classifier = PartitionClassifier(part);

        bool found = false;
        for (size_t idx = 0; idx != distinct_partitions.size(); ++idx)
        {
            if (classifier == distinct_partitions[idx])
            {
                distinct_partitions[idx].d_multiplicity += 1;
                found = true;
                break;
            }
        }
        if (!found)
        {
            distinct_partitions.push_back(classifier);
        }
    }

    std::cout << distinct_partitions.size() << '\n';

    std::atomic<size_t> count{0};
    std::atomic<size_t> prog{0};

    #pragma omp parallel for schedule(dynamic)
    for (auto &classifier : distinct_partitions)
    {
        // Do progress update.
        #pragma omp critical    
        { std::cout << "\rProgress: " << ++prog << '/' << distinct_partitions.size() << std::flush; }

        count += uniqueCorrectPerms(classifier);
    }

    std::cout << '\n' << count << '\n' << std::flush;
}

// This ran in roughly 28 hours on tcbl13.
// Final answer was 16475640048, which was incorrect.
// However, I randomly tried (I kid you not) 16475640049, which was correct!
// So it appears we have had exactly one hash collision.

// Note: if we run it again, it will likely be a few hours faster since the
// speedup on line 106 was added only after I started running.
// Furthermore, the multithreading was highly unoptimized: what I think is happening
// is that #pragma omp parallel for equally distributes the partitions over the
// threads in advance, but some partitions of course take way way more time 
// than others, and partitions are not distributed randomly by length. So we could
// optimize this even more by having some sort of worker queue that threads can take from.

// Edit: by changing #pragma omp parallel for to #pragma omp parallel for schedule(dynamic)
// we solve this problem, and this actually gives a speedup op 161%.
// (from 2:25 to 0:56 on M1 for N = 40)

// Edit: changed the way we do the hashing to avoid hash collisions.
// Now using a tuple of two hashes instead of adding them together in the same size_t.
// Apparently, this confers an additional speedup of 40%.

// Edit: using the PartitionClassifier class to eliminate many partitions as a lot
// of them might contain different numbers but are combinatorically equivalent.
// we then simply add the 1 * their multiplicity to count.
// Tother with other tricks this reduces (for N = 50) the number of partitions to
// be checked from 204226 to just 3329.
