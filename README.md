# Mahjong Winning Hand Algorithm

## Author
B11901095 電機二 朱振瑀

## Problem 

Design an efficient algorithm to determine whether a Mahjong Hand is a "Winning Hand". The input contains 'n' in the first line (indicating input size), and 'n' positive unsorted integers following, each representing the value of a tile (different tiles can have the same values). Assume that all integers are no larger than 'm'. A "Winning Mahjong Hand" is a hand such that all tiles can be formed into one pair (two tiles of the same value) and several menzis. A menzi can be a straight (three tiles with consecutive values, e.g., 3,4,5) or triplet (three tiles with the same value, e.g., 13,13,13). Every tile has to be used.
Note: this problem is not exactly the same as the typical Mahjong game. We assume there are no suits(萬筒條字) and the value of a tile is not limited to 1~9, and the number of tiles in a hand can be any non-negative integer, not limited to 14 or 17.

## Sample Solution

### Pseudo-code

```pseudo
function isWinningHand(tileCount, tileArray):
    if tileCount % 3 != 2:
        return false
    make tileMap a new Map
    for each tile in tileArray:
        tileMap[tile]++
    for i in keys of tileMap:
        if tileMap[i] >= 2:
            copiedMap = copy(tileMap)
            copiedMap[i] -= 2
            remainingIterations = (tileCount - 2) / 3

            for i in keys of copiedMap:
                while tileMap[i] >=3:
                    tileMap[i] -= 3
                    remainingIterations--
                while tileMap[i] > 0:
                    if tileMap[i+1] > 0 and tileMap[i+2] > 0 :
                        copiedMap[i]--
                        copiedMap[i+1]--
                        copiedMap[i+2]--
                        remainingIterations--
                    else break
            if remainingIterations == 0:
                    return true

    return false
```
### Explanation

1. Convert hand from array to map

    Basically this is counting sort. It is more convenient to deal with this problem if you know how many tiles there are with a certain value. 

2. Early return
    
    The hand is a winning hand only if the nubmer of tiles % 3 = 2, that is because a winning hand consists of x menzis and 1 pair, so total tile count = 3x+2

3. Extract pair

    The value of the pair can only be a value that appears multiple times, so try it for every possible value. A subproblem is the process to determine whether the remaining tiles can be all formed into menzis after extracting a certain pair.

4. Extract menzi

    After extracting a pair, we have to check whether or not the remaining tiles can be all formed into menzis. We find a menzi that must be in the winning hand if it exists, remove it, and check whether the remaining tiles can be all formed into menzis. 

5. Greedy choice

     When extracting menzi, a triplet formed by three tiles with the smallest remaining value is always in the winning hand if exists. If less than two of the remaining tiles have the smallest value, than try form a straight (i i+1 i+2), assuming the smallest remaining value is i. If this straight does not exist, then the winning hand for this subproblem does not exist. 

     Explanation: A tile with smallest remaining value i can only be formed into two cases of menzi: the (i i i) triplet and (i i+1 i+2) straight. If the tile cannot be formed into either of those, then the tile does not belong to any menzi. Since there can be no tiles unused in a winning hand, a winning hand for this subproblem does not exist. Besides, when there are at least three tiles with smallest value i, (i i i) must be a menzi in some possible winning hand. We prove this by cut and paste. Assume a winning hand exists and there are at least three tiles with smallest value i but the triplet (i i i) is not in any winning hand. Thus, the only menzi the smallest tile can form is the (i i+1 i+2) straight. Because there are at least three tiles with value i and a winning hand exists, you can certainly extract three (i i+1 i+2) straights. However, these three straights can also be reformed into three triplets: (i i i), (i+1 i+1 i+1), (i+2 i+2 i+2). Substituting the three straights from the winning hand without (i i i) creates a new winning hand with the triplet(i i i), which is a contradiction to the assumption.    


### complexity analysis

1.Time complexity:O(m*n) 

In the double nested for loop, the outer loop has O(m) iterations because it checks every existing key(min:1, max:m), and the inner loop has O(n) iterations because it checks every menzi, and the number of menzis = (n-2)/3.

2.Space complexity:O(m)

In the map, we at most need m keys. There are copied maps, but deleted after each outer for loop iteration, so it does not result in extra space complexity.


### compile and run

#### compile
```sh
make
```

#### run
```sh
./bin/mj inputs/xxx.in
```

#### output
"Yes", if a winning hand exists.

"No", otherwise.