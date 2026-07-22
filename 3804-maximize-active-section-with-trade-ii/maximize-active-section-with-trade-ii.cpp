class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();
        int totalOnes = count(s.begin(), s.end(), '1');

        // Store all zero blocks.
        vector<int> zeroStart;
        vector<int> zeroEnd;
        vector<int> zeroLength;

        // For every position, store the zero block containing it.
        vector<int> zeroBlockId(n, -1);

        int i = 0;

        while (i < n) {
            if (s[i] == '1') {
                i++;
                continue;
            }

            int start = i;

            while (i < n && s[i] == '0') {
                i++;
            }

            int end = i - 1;
            int id = zeroStart.size();

            zeroStart.push_back(start);
            zeroEnd.push_back(end);
            zeroLength.push_back(end - start + 1);

            for (int j = start; j <= end; j++) {
                zeroBlockId[j] = id;
            }
        }

        int zeroBlocks = zeroLength.size();

        // pairGain[i] = lengths of zero block i and i + 1.
        vector<int> pairGain;

        for (int j = 0; j + 1 < zeroBlocks; j++) {
            pairGain.push_back(
                zeroLength[j] + zeroLength[j + 1]
            );
        }

        // Sparse table for maximum pair gain.
        int m = pairGain.size();

        vector<int> logValue(max(2, m + 1), 0);

        for (int j = 2; j <= m; j++) {
            logValue[j] = logValue[j / 2] + 1;
        }

        vector<vector<int>> sparseTable;

        if (m > 0) {
            int levels = logValue[m] + 1;

            sparseTable.assign(levels, vector<int>(m));
            sparseTable[0] = pairGain;

            for (int level = 1; level < levels; level++) {
                int length = 1 << level;

                for (int j = 0; j + length <= m; j++) {
                    sparseTable[level][j] = max(
                        sparseTable[level - 1][j],
                        sparseTable[level - 1]
                                   [j + (length >> 1)]
                    );
                }
            }
        }

        auto rangeMaximum = [&](int left, int right) {
            if (left > right) {
                return 0;
            }

            int length = right - left + 1;
            int level = logValue[length];

            return max(
                sparseTable[level][left],
                sparseTable[level]
                           [right - (1 << level) + 1]
            );
        };

        vector<int> answer;

        for (auto& query : queries) {
            int left = query[0];
            int right = query[1];

            /*
             * Locate the first zero block intersecting [left, right].
             */
            int firstBlock;

            if (s[left] == '0') {
                firstBlock = zeroBlockId[left];
            } else {
                firstBlock = lower_bound(
                    zeroStart.begin(),
                    zeroStart.end(),
                    left
                ) - zeroStart.begin();
            }

            /*
             * Locate the last zero block intersecting [left, right].
             */
            int lastBlock;

            if (s[right] == '0') {
                lastBlock = zeroBlockId[right];
            } else {
                lastBlock = (
                    upper_bound(
                        zeroEnd.begin(),
                        zeroEnd.end(),
                        right
                    ) - zeroEnd.begin()
                ) - 1;
            }

            // No zero block or only one zero block means no valid trade.
            if (
                firstBlock >= zeroBlocks ||
                lastBlock < 0 ||
                firstBlock >= lastBlock ||
                zeroStart[firstBlock] > right ||
                zeroEnd[lastBlock] < left
            ) {
                answer.push_back(totalOnes);
                continue;
            }

            auto clippedLength = [&](int block) {
                int start = max(zeroStart[block], left);
                int end = min(zeroEnd[block], right);

                return max(0, end - start + 1);
            };

            int bestGain = 0;

            // Pair containing the first zero block.
            bestGain = max(
                bestGain,
                clippedLength(firstBlock) +
                clippedLength(firstBlock + 1)
            );

            // Pair containing the last zero block.
            bestGain = max(
                bestGain,
                clippedLength(lastBlock - 1) +
                clippedLength(lastBlock)
            );

            // Completely contained pairs between the boundary blocks.
            int interiorLeft = firstBlock + 1;
            int interiorRight = lastBlock - 2;

            bestGain = max(
                bestGain,
                rangeMaximum(interiorLeft, interiorRight)
            );

            answer.push_back(totalOnes + bestGain);
        }

        return answer;
    }
};