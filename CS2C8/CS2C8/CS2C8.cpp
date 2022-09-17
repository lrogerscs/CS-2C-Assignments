// Student name: Lee Rogers
// LAB Assignment 8

#include <iostream>
#include <iomanip>
#include "FHsort.h" // provided from CS2C files
using namespace std;

#define ARRAY_SIZE 320000

template <typename Comparable>
void quickSortX(FHvector<Comparable>& a, int recLimit)
{
    if (recLimit < 2) // if recLimit is below 2, return without running quickSortX
        return;

    quickSortX(a, 0, a.size() - 1, recLimit);
}

template <typename Comparable>
void quickSortX(FHvector<Comparable>& a, int left, int right, int recLimit)
{
    Comparable pivot;
    int i, j;

    if (left + recLimit <= right) // swapped QS_RECURSION_LIMIT with provided recLimit
    {
        pivot = median3(a, left, right);
        for (i = left, j = right - 1; ; )
        {
            while (a[++i] < pivot)
                ;
            while (pivot < a[--j])
                ;
            if (i < j)
                mySwapFH(a[i], a[j]);
            else
                break;
        }

        mySwapFH(a[i], a[right - 1]);  // restore pivot

        // recursive calls on smaller sub-groups
        quickSortX(a, left, i - 1, recLimit);
        quickSortX(a, i + 1, right, recLimit);
    }
    else
        // non-recursive escape valve - insertionSort
        insertionSort(a, left, right);
}

int main() {

    clock_t startTime, stopTime;
    FHvector<int> fhVectorOfInts;

    cout << "ARRAY_SIZE = " << ARRAY_SIZE << endl << endl;

    for (int j = 2; j <= 300; j += 2) {

        fhVectorOfInts.clear(); // clear vector of all values

        for (int i = 0; i < ARRAY_SIZE; i++) {

            fhVectorOfInts.push_back(rand() % 1000000); // add random int value (values will be the same every pass through the loop without the line "srand(time(NULL));")
        }

        startTime = clock();
        quickSortX(fhVectorOfInts, j);
        stopTime = clock();

        cout << "Time: " << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC << " recLimit: " << j << endl;
    }

    cout << "\nCheck first 15 indices to see if array was sorted" << endl;

    // output the first 15 indices to check if quickSortX worked
    for (int k = 0; k < 15; k++) {

        cout << fhVectorOfInts[k] << endl;
    }
    
    return 0;
}

/* Table ----------------------------------------------------------------------------------------------------------------------------------------------

I assumed that we were supposed to time these operations and compare the times.

Note: to keep the table short, I combined some values into a range. The full runs and times will be under the "runs" section.

ARRAY_SIZE = 40000

| recLimit | Sorting time |
|----------|------------- |
| 2        | .032         |
| 4-16     | .03-.031     |
| 18-40    | .032-.039    |
| 40-66    | .04-.049     |
| 68-92    | .051-.059    |
| 94-116   | .061-.07     |
| 118-140  | .071-.08     |
| 142-164  | .082-.09     |
| 166-184  | .091-.099    |
| 186-208  | .1-.109      |
| 210-226  | .11-.119     |
| 228-250  | .12-.128     |
| 252-276  | .129-.14     |
| 278-300  | .141-.151    |

ARRAY_SIZE = 160000

| recLimit | Sorting time |
|----------|--------------|
| 2        | .145         |
| 4-22     | .13-.14      |
| 24-38    | .144-.159    |
| 40-58    | .165-.19     |
| 60-90    | .192-.24     |
| 92-122   | .244-.299    |
| 124-154  | .303-.35     |
| 156-180  | .357-.395    |
| 182-212  | .399-.45     |
| 214-236  | .459-.495    |
| 238-270  | .499-.554    |
| 270-300  | .559-.605    |

ARRAY_SIZE = 320000

| recLimit | Sorting time |
|----------|--------------|
| 2        | .293         |
| 4-24     | .266-.279    |
| 26-42    | .285-.326    |
| 44-62    | .334-.387    |
| 64-82    | .391-.449    |
| 84-118   | .46-.567     |
| 120-150  | .576-.676    |
| 152-180  | .684-.784    |
| 182-214  | .781-.892    |
| 216-246  | .911-1.017   |
| 248-278  | 1.013-1.117  |
| 280-300  | 1.128-1.218  |

This was not actually the biggest array that I could run. I could run larger arrays, but the times started to get very large, so I stuck around 250,000.

Comments ----------------------------------------------------------------------------------------------------------------------------------------------

In each case, the fastest times seemed to occur when recLimit was valued in between 6-18, which makes sense because the optimal range was described
to be in between 5-25 in the modules. Once recLimit reached above 20, the timings began to climb very steadily higher. There were no particularly 
"flat" areas other than when recLimit was between 4 and 16 in the first test with 40,000 ints.

Runs ----------------------------------------------------------------------------------------------------------------------------------------------

Run 1:

ARRAY_SIZE = 40000

Time: 0.032 recLimit: 2
Time: 0.031 recLimit: 4
Time: 0.03 recLimit: 6
Time: 0.03 recLimit: 8
Time: 0.03 recLimit: 10
Time: 0.03 recLimit: 12
Time: 0.03 recLimit: 14
Time: 0.031 recLimit: 16
Time: 0.032 recLimit: 18
Time: 0.033 recLimit: 20
Time: 0.033 recLimit: 22
Time: 0.034 recLimit: 24
Time: 0.034 recLimit: 26
Time: 0.035 recLimit: 28
Time: 0.036 recLimit: 30
Time: 0.036 recLimit: 32
Time: 0.036 recLimit: 34
Time: 0.038 recLimit: 36
Time: 0.038 recLimit: 38
Time: 0.039 recLimit: 40
Time: 0.04 recLimit: 42
Time: 0.04 recLimit: 44
Time: 0.041 recLimit: 46
Time: 0.042 recLimit: 48
Time: 0.043 recLimit: 50
Time: 0.044 recLimit: 52
Time: 0.044 recLimit: 54
Time: 0.045 recLimit: 56
Time: 0.047 recLimit: 58
Time: 0.046 recLimit: 60
Time: 0.047 recLimit: 62
Time: 0.049 recLimit: 64
Time: 0.049 recLimit: 66
Time: 0.051 recLimit: 68
Time: 0.051 recLimit: 70
Time: 0.052 recLimit: 72
Time: 0.053 recLimit: 74
Time: 0.053 recLimit: 76
Time: 0.054 recLimit: 78
Time: 0.055 recLimit: 80
Time: 0.057 recLimit: 82
Time: 0.056 recLimit: 84
Time: 0.056 recLimit: 86
Time: 0.058 recLimit: 88
Time: 0.058 recLimit: 90
Time: 0.059 recLimit: 92
Time: 0.061 recLimit: 94
Time: 0.061 recLimit: 96
Time: 0.063 recLimit: 98
Time: 0.064 recLimit: 100
Time: 0.065 recLimit: 102
Time: 0.066 recLimit: 104
Time: 0.066 recLimit: 106
Time: 0.066 recLimit: 108
Time: 0.068 recLimit: 110
Time: 0.07 recLimit: 112
Time: 0.069 recLimit: 114
Time: 0.07 recLimit: 116
Time: 0.071 recLimit: 118
Time: 0.073 recLimit: 120
Time: 0.074 recLimit: 122
Time: 0.075 recLimit: 124
Time: 0.076 recLimit: 126
Time: 0.075 recLimit: 128
Time: 0.076 recLimit: 130
Time: 0.077 recLimit: 132
Time: 0.077 recLimit: 134
Time: 0.079 recLimit: 136
Time: 0.08 recLimit: 138
Time: 0.08 recLimit: 140
Time: 0.082 recLimit: 142
Time: 0.083 recLimit: 144
Time: 0.083 recLimit: 146
Time: 0.084 recLimit: 148
Time: 0.086 recLimit: 150
Time: 0.086 recLimit: 152
Time: 0.086 recLimit: 154
Time: 0.086 recLimit: 156
Time: 0.088 recLimit: 158
Time: 0.091 recLimit: 160
Time: 0.09 recLimit: 162
Time: 0.09 recLimit: 164
Time: 0.091 recLimit: 166
Time: 0.094 recLimit: 168
Time: 0.092 recLimit: 170
Time: 0.095 recLimit: 172
Time: 0.096 recLimit: 174
Time: 0.096 recLimit: 176
Time: 0.099 recLimit: 178
Time: 0.099 recLimit: 180
Time: 0.096 recLimit: 182
Time: 0.099 recLimit: 184
Time: 0.101 recLimit: 186
Time: 0.1 recLimit: 188
Time: 0.102 recLimit: 190
Time: 0.105 recLimit: 192
Time: 0.102 recLimit: 194
Time: 0.104 recLimit: 196
Time: 0.106 recLimit: 198
Time: 0.107 recLimit: 200
Time: 0.106 recLimit: 202
Time: 0.107 recLimit: 204
Time: 0.109 recLimit: 206
Time: 0.109 recLimit: 208
Time: 0.11 recLimit: 210
Time: 0.111 recLimit: 212
Time: 0.115 recLimit: 214
Time: 0.112 recLimit: 216
Time: 0.115 recLimit: 218
Time: 0.115 recLimit: 220
Time: 0.119 recLimit: 222
Time: 0.118 recLimit: 224
Time: 0.119 recLimit: 226
Time: 0.122 recLimit: 228
Time: 0.12 recLimit: 230
Time: 0.121 recLimit: 232
Time: 0.121 recLimit: 234
Time: 0.122 recLimit: 236
Time: 0.123 recLimit: 238
Time: 0.121 recLimit: 240
Time: 0.128 recLimit: 242
Time: 0.128 recLimit: 244
Time: 0.129 recLimit: 246
Time: 0.128 recLimit: 248
Time: 0.128 recLimit: 250
Time: 0.13 recLimit: 252
Time: 0.129 recLimit: 254
Time: 0.13 recLimit: 256
Time: 0.132 recLimit: 258
Time: 0.133 recLimit: 260
Time: 0.134 recLimit: 262
Time: 0.137 recLimit: 264
Time: 0.136 recLimit: 266
Time: 0.14 recLimit: 268
Time: 0.138 recLimit: 270
Time: 0.14 recLimit: 272
Time: 0.138 recLimit: 274
Time: 0.138 recLimit: 276
Time: 0.146 recLimit: 278
Time: 0.145 recLimit: 280
Time: 0.144 recLimit: 282
Time: 0.141 recLimit: 284
Time: 0.147 recLimit: 286
Time: 0.144 recLimit: 288
Time: 0.148 recLimit: 290
Time: 0.147 recLimit: 292
Time: 0.148 recLimit: 294
Time: 0.152 recLimit: 296
Time: 0.149 recLimit: 298
Time: 0.151 recLimit: 300

Check first 15 indices to see if array was sorted
0
2
3
6
7
7
7
9
9
10
10
10
11
12
12

Run 2:

ARRAY_SIZE = 160000

Time: 0.145 recLimit: 2
Time: 0.137 recLimit: 4
Time: 0.136 recLimit: 6
Time: 0.132 recLimit: 8
Time: 0.13 recLimit: 10
Time: 0.13 recLimit: 12
Time: 0.133 recLimit: 14
Time: 0.133 recLimit: 16
Time: 0.136 recLimit: 18
Time: 0.137 recLimit: 20
Time: 0.14 recLimit: 22
Time: 0.144 recLimit: 24
Time: 0.145 recLimit: 26
Time: 0.148 recLimit: 28
Time: 0.151 recLimit: 30
Time: 0.154 recLimit: 32
Time: 0.153 recLimit: 34
Time: 0.157 recLimit: 36
Time: 0.159 recLimit: 38
Time: 0.165 recLimit: 40
Time: 0.166 recLimit: 42
Time: 0.169 recLimit: 44
Time: 0.173 recLimit: 46
Time: 0.173 recLimit: 48
Time: 0.179 recLimit: 50
Time: 0.179 recLimit: 52
Time: 0.185 recLimit: 54
Time: 0.186 recLimit: 56
Time: 0.19 recLimit: 58
Time: 0.192 recLimit: 60
Time: 0.197 recLimit: 62
Time: 0.198 recLimit: 64
Time: 0.203 recLimit: 66
Time: 0.205 recLimit: 68
Time: 0.209 recLimit: 70
Time: 0.212 recLimit: 72
Time: 0.214 recLimit: 74
Time: 0.218 recLimit: 76
Time: 0.221 recLimit: 78
Time: 0.224 recLimit: 80
Time: 0.229 recLimit: 82
Time: 0.23 recLimit: 84
Time: 0.236 recLimit: 86
Time: 0.239 recLimit: 88
Time: 0.24 recLimit: 90
Time: 0.244 recLimit: 92
Time: 0.249 recLimit: 94
Time: 0.252 recLimit: 96
Time: 0.255 recLimit: 98
Time: 0.258 recLimit: 100
Time: 0.261 recLimit: 102
Time: 0.265 recLimit: 104
Time: 0.271 recLimit: 106
Time: 0.278 recLimit: 108
Time: 0.28 recLimit: 110
Time: 0.289 recLimit: 112
Time: 0.288 recLimit: 114
Time: 0.288 recLimit: 116
Time: 0.288 recLimit: 118
Time: 0.295 recLimit: 120
Time: 0.299 recLimit: 122
Time: 0.303 recLimit: 124
Time: 0.304 recLimit: 126
Time: 0.305 recLimit: 128
Time: 0.315 recLimit: 130
Time: 0.313 recLimit: 132
Time: 0.319 recLimit: 134
Time: 0.32 recLimit: 136
Time: 0.323 recLimit: 138
Time: 0.324 recLimit: 140
Time: 0.331 recLimit: 142
Time: 0.335 recLimit: 144
Time: 0.339 recLimit: 146
Time: 0.341 recLimit: 148
Time: 0.343 recLimit: 150
Time: 0.348 recLimit: 152
Time: 0.35 recLimit: 154
Time: 0.357 recLimit: 156
Time: 0.361 recLimit: 158
Time: 0.364 recLimit: 160
Time: 0.364 recLimit: 162
Time: 0.369 recLimit: 164
Time: 0.373 recLimit: 166
Time: 0.376 recLimit: 168
Time: 0.38 recLimit: 170
Time: 0.385 recLimit: 172
Time: 0.386 recLimit: 174
Time: 0.388 recLimit: 176
Time: 0.389 recLimit: 178
Time: 0.395 recLimit: 180
Time: 0.402 recLimit: 182
Time: 0.399 recLimit: 184
Time: 0.403 recLimit: 186
Time: 0.411 recLimit: 188
Time: 0.409 recLimit: 190
Time: 0.42 recLimit: 192
Time: 0.416 recLimit: 194
Time: 0.427 recLimit: 196
Time: 0.427 recLimit: 198
Time: 0.432 recLimit: 200
Time: 0.443 recLimit: 202
Time: 0.437 recLimit: 204
Time: 0.444 recLimit: 206
Time: 0.443 recLimit: 208
Time: 0.447 recLimit: 210
Time: 0.45 recLimit: 212
Time: 0.459 recLimit: 214
Time: 0.458 recLimit: 216
Time: 0.463 recLimit: 218
Time: 0.459 recLimit: 220
Time: 0.47 recLimit: 222
Time: 0.479 recLimit: 224
Time: 0.476 recLimit: 226
Time: 0.48 recLimit: 228
Time: 0.483 recLimit: 230
Time: 0.487 recLimit: 232
Time: 0.489 recLimit: 234
Time: 0.495 recLimit: 236
Time: 0.501 recLimit: 238
Time: 0.499 recLimit: 240
Time: 0.506 recLimit: 242
Time: 0.506 recLimit: 244
Time: 0.513 recLimit: 246
Time: 0.516 recLimit: 248
Time: 0.528 recLimit: 250
Time: 0.526 recLimit: 252
Time: 0.521 recLimit: 254
Time: 0.531 recLimit: 256
Time: 0.527 recLimit: 258
Time: 0.543 recLimit: 260
Time: 0.536 recLimit: 262
Time: 0.542 recLimit: 264
Time: 0.544 recLimit: 266
Time: 0.542 recLimit: 268
Time: 0.554 recLimit: 270
Time: 0.559 recLimit: 272
Time: 0.562 recLimit: 274
Time: 0.552 recLimit: 276
Time: 0.558 recLimit: 278
Time: 0.569 recLimit: 280
Time: 0.575 recLimit: 282
Time: 0.585 recLimit: 284
Time: 0.582 recLimit: 286
Time: 0.582 recLimit: 288
Time: 0.586 recLimit: 290
Time: 0.589 recLimit: 292
Time: 0.598 recLimit: 294
Time: 0.596 recLimit: 296
Time: 0.604 recLimit: 298
Time: 0.605 recLimit: 300

Check first 15 indices to see if array was sorted
0
0
0
0
0
0
0
1
1
1
1
1
1
2
2

Run 3:

ARRAY_SIZE = 320000

Time: 0.293 recLimit: 2
Time: 0.278 recLimit: 4
Time: 0.274 recLimit: 6
Time: 0.266 recLimit: 8
Time: 0.267 recLimit: 10
Time: 0.268 recLimit: 12
Time: 0.269 recLimit: 14
Time: 0.267 recLimit: 16
Time: 0.275 recLimit: 18
Time: 0.275 recLimit: 20
Time: 0.279 recLimit: 22
Time: 0.279 recLimit: 24
Time: 0.285 recLimit: 26
Time: 0.29 recLimit: 28
Time: 0.299 recLimit: 30
Time: 0.298 recLimit: 32
Time: 0.303 recLimit: 34
Time: 0.309 recLimit: 36
Time: 0.312 recLimit: 38
Time: 0.318 recLimit: 40
Time: 0.326 recLimit: 42
Time: 0.334 recLimit: 44
Time: 0.338 recLimit: 46
Time: 0.348 recLimit: 48
Time: 0.35 recLimit: 50
Time: 0.357 recLimit: 52
Time: 0.363 recLimit: 54
Time: 0.366 recLimit: 56
Time: 0.375 recLimit: 58
Time: 0.381 recLimit: 60
Time: 0.387 recLimit: 62
Time: 0.391 recLimit: 64
Time: 0.405 recLimit: 66
Time: 0.406 recLimit: 68
Time: 0.409 recLimit: 70
Time: 0.417 recLimit: 72
Time: 0.424 recLimit: 74
Time: 0.432 recLimit: 76
Time: 0.438 recLimit: 78
Time: 0.44 recLimit: 80
Time: 0.449 recLimit: 82
Time: 0.46 recLimit: 84
Time: 0.469 recLimit: 86
Time: 0.466 recLimit: 88
Time: 0.476 recLimit: 90
Time: 0.481 recLimit: 92
Time: 0.488 recLimit: 94
Time: 0.491 recLimit: 96
Time: 0.498 recLimit: 98
Time: 0.508 recLimit: 100
Time: 0.514 recLimit: 102
Time: 0.519 recLimit: 104
Time: 0.526 recLimit: 106
Time: 0.533 recLimit: 108
Time: 0.539 recLimit: 110
Time: 0.547 recLimit: 112
Time: 0.557 recLimit: 114
Time: 0.556 recLimit: 116
Time: 0.567 recLimit: 118
Time: 0.576 recLimit: 120
Time: 0.592 recLimit: 122
Time: 0.585 recLimit: 124
Time: 0.598 recLimit: 126
Time: 0.6 recLimit: 128
Time: 0.607 recLimit: 130
Time: 0.614 recLimit: 132
Time: 0.614 recLimit: 134
Time: 0.632 recLimit: 136
Time: 0.63 recLimit: 138
Time: 0.644 recLimit: 140
Time: 0.65 recLimit: 142
Time: 0.652 recLimit: 144
Time: 0.662 recLimit: 146
Time: 0.674 recLimit: 148
Time: 0.676 recLimit: 150
Time: 0.685 recLimit: 152
Time: 0.684 recLimit: 154
Time: 0.695 recLimit: 156
Time: 0.705 recLimit: 158
Time: 0.709 recLimit: 160
Time: 0.717 recLimit: 162
Time: 0.723 recLimit: 164
Time: 0.728 recLimit: 166
Time: 0.738 recLimit: 168
Time: 0.751 recLimit: 170
Time: 0.756 recLimit: 172
Time: 0.762 recLimit: 174
Time: 0.776 recLimit: 176
Time: 0.778 recLimit: 178
Time: 0.784 recLimit: 180
Time: 0.781 recLimit: 182
Time: 0.787 recLimit: 184
Time: 0.794 recLimit: 186
Time: 0.812 recLimit: 188
Time: 0.814 recLimit: 190
Time: 0.813 recLimit: 192
Time: 0.832 recLimit: 194
Time: 0.838 recLimit: 196
Time: 0.836 recLimit: 198
Time: 0.849 recLimit: 200
Time: 0.86 recLimit: 202
Time: 0.864 recLimit: 204
Time: 0.864 recLimit: 206
Time: 0.873 recLimit: 208
Time: 0.878 recLimit: 210
Time: 0.892 recLimit: 212
Time: 0.892 recLimit: 214
Time: 0.913 recLimit: 216
Time: 0.911 recLimit: 218
Time: 0.923 recLimit: 220
Time: 0.931 recLimit: 222
Time: 0.923 recLimit: 224
Time: 0.943 recLimit: 226
Time: 0.936 recLimit: 228
Time: 0.962 recLimit: 230
Time: 0.965 recLimit: 232
Time: 0.96 recLimit: 234
Time: 0.974 recLimit: 236
Time: 0.982 recLimit: 238
Time: 0.993 recLimit: 240
Time: 0.993 recLimit: 242
Time: 0.997 recLimit: 244
Time: 1.017 recLimit: 246
Time: 1.013 recLimit: 248
Time: 1.038 recLimit: 250
Time: 1.038 recLimit: 252
Time: 1.04 recLimit: 254
Time: 1.045 recLimit: 256
Time: 1.048 recLimit: 258
Time: 1.062 recLimit: 260
Time: 1.069 recLimit: 262
Time: 1.072 recLimit: 264
Time: 1.068 recLimit: 266
Time: 1.091 recLimit: 268
Time: 1.098 recLimit: 270
Time: 1.105 recLimit: 272
Time: 1.103 recLimit: 274
Time: 1.116 recLimit: 276
Time: 1.117 recLimit: 278
Time: 1.128 recLimit: 280
Time: 1.148 recLimit: 282
Time: 1.147 recLimit: 284
Time: 1.144 recLimit: 286
Time: 1.162 recLimit: 288
Time: 1.172 recLimit: 290
Time: 1.188 recLimit: 292
Time: 1.206 recLimit: 294
Time: 1.192 recLimit: 296
Time: 1.209 recLimit: 298
Time: 1.218 recLimit: 300

Check first 15 indices to see if array was sorted
0
0
0
0
0
0
0
0
0
0
0
0
1
1
1
*/