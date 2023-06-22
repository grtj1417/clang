#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Gate {
    int (*GateValue)(struct _Gate*);
    int input1;
    int input2;
} Gate;
Gate gate;
int GateEmptyValue(Gate* obj) {
    return obj->input1;
}

int GateANDValue(Gate* obj) {
    return obj->input1 & obj->input2;
}

int GateORValue(Gate* obj) {
    return obj->input1 | obj->input2;
}

int GateXORValue(Gate* obj) {
    return obj->input1 ^ obj->input2;
}

int GateNOTValue(Gate* obj) {
    return !obj->input1;
}

void CreateEmptyGate(Gate* obj, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    obj->GateValue = GateEmptyValue;
}

void CreateGateAND(Gate* obj, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    obj->GateValue = GateANDValue;
}

void CreateGateOR(Gate* obj, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    obj->GateValue = GateORValue;
}

void CreateGateXOR(Gate* obj, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    obj->GateValue = GateXORValue;
}

void CreateGateNOT(Gate* obj, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    obj->GateValue = GateNOTValue;
}

void CreateGate(Gate* gate, char g, int input1, int input2) {
    if (g == 'A')
        CreateGateAND(gate, input1, input2);
    else if (g == 'O')
        CreateGateOR(gate, input1, input2);
    else if (g == 'X')
        CreateGateXOR(gate, input1, input2);
    else if (g == 'N')
        CreateGateNOT(gate, input1, input2);
    else if (g == 'E')
        CreateEmptyGate(gate, input1, input2);
}

int main() {
    int inputValues[10];
    char gateTypes[10];
    char temp;
    int outputs[10];
    int outputIndex = 0;
    Gate gates[6];

    for (int i = 0; i < 4; i++)
        scanf("%d%c", &inputValues[i], &temp);
    for (int i = 0; i < 6; i++)
        scanf("%c%c", &gateTypes[i], &temp);

    CreateGate(&gates[0], gateTypes[0], inputValues[0], inputValues[1]);   // A
    CreateGate(&gates[1], gateTypes[1], gates[0].GateValue(&gates[0]), gates[0].GateValue(&gates[0]));   // B
    CreateGate(&gates[2], gateTypes[2], gates[0].GateValue(&gates[0]), inputValues[2]);   // C
    CreateGate(&gates[3], gateTypes[3], gates[1].GateValue(&gates[1]), gates[2].GateValue(&gates[2]));   // D
    CreateGate(&gates[4], gateTypes[4], gates[2].GateValue(&gates[2]), inputValues[3]);   // E
    CreateGate(&gates[5], gateTypes[5], gates[3].GateValue(&gates[3]), gates[4].GateValue(&gates[4]));   // F
    // printf("gate 0 = %d\n", gates[0].GateValue(&gates[0]));
    // printf("gate 1 = %d\n", gates[1].GateValue(&gates[1]));
    // printf("gate 2 = %d\n", gates[2].GateValue(&gates[2]));
    // printf("gate 3 = %d\n", gates[3].GateValue(&gates[3]));
    // printf("gate 4 = %d\n", gates[4].GateValue(&gates[4]));
    // printf("gate 5 = %d\n", gates[5].GateValue(&gates[5]));
    /* 1 1 0 1 
    * Gate 0 = (AND)
    * Gate 1 = (EMPTY)
    * Gate 2 = (AND)
    * Gate 3 = (AND)
    * Gate 4 = (XOR)
    * Gate 5 = (OR)
    */
    
    int output1 = gates[1].GateValue(&gates[1]); /* 1 */
    int output2 = gates[3].GateValue(&gates[3]);
    int output3 = gates[5].GateValue(&gates[5]);

    printf("%d,%d,%d\n", output1, output2, output3);
    return 0;
}
