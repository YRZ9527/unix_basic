#ifndef COMMON_H
#define COMMON_H

typedef struct NUMRULE {
    int IntegerChance;   // 整数和分数概率0全为分数 100:全为整数
    int PositiveChance;  // 0:全为负数，100：全为正数
    int MoleculeRange;   // 分子范围 1 - X
    int DenominatorRange;  // 分母范围 1 - X
} Numrule;

#endif  // COMMON_H
