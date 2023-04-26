# **1.** Translate the following hexadecimal numbers to binary. <br>0x0, 0x10, 0xF, 0x1F, 0xA4, 0xFF
### **Resposta:**
### **0x0  ->** 0000 0000
### **0x10 ->** 0001 0000
### **0xF  ->** 0000 1111
### **0x1F ->** 0001 1111
### **0xA4 ->** 1010 0100
### **0xFF ->** 1111 1111 

<hr>

# **2.** Find the bitwise and, or and xor of the following:
## **a)** 0xC6 with 0x35
### **Resposta:**
### 1100 0110 & 0011 0101 **-> 1**
### 1100 0110 | 0011 0101 **-> 1**
### 1100 0110 ^ 0011 0101 **-> 1**
## **b)** 0x19 with 0x24
### **Resposta:**
### 0001 1001 & 0010 0100 **-> 0**
### 0001 1001 | 0010 0100 **-> 1**
### 0001 1001 ^ 0010 0100 **-> 1**
## **c)** 0xD3 with 0xC7
### **Resposta:**
### 1101 0011 & 1100 0111 **-> 1**
### 1101 0011 | 1100 0111 **-> 1**
### 1101 0011 ^ 1100 0111 **-> 1**
## **d)** 0x17 with 0xFF
### **Resposta:**
### 0001 0111 & 1111 1111 **-> 1**
### 0001 0111 | 1111 1111 **-> 1**
### 0001 0111 ^ 1111 1111 **-> 1**

<hr>

# **3.** Find the 1’s complement of the following:<br>0xC6, 0x35, 0xD3 and 0xC7.
### **Resposta:**
### **0xC6 ->** 1100 0110 (inverte) = 0011 1001 + 1 = **0011 1010**
### **0x35 ->** 0011 0101 (inverte) = 1100 1010 + 1 = **0011 0110**
### **0xD3 ->** 1101 0011 (inverte) = 0010 1100 + 1 = **0010 1101**
### **0xC7 ->** 1100 0111 (inverte) = 0011 1000 + 1 = **0011 1001**

<hr>

# **4.** In this question & is bitwise and, | is bitwise or, ^ is bitwise xor, and ! is 1’s complement. a is any given two digit hexadecimal number. Explain why each of the following identities holds.
## **a) 0xFF & a = a. (0xFF is the identity for AND)**
### **Resposta:**
### Como 0xFF equivale à '1111 1111', a operação & (and) de 0xFF com a resultará em a pois onde o bit é '1' no primeiro operando (0xFF), manterá igual no segundo (a), pois fará 8 operações de and referentes a cada índice, ou seja, se 'a' for '1001 1101', essa operação realizará as seguintes operações: 1 and 1 (1), 1 and 0 (10), 1 and 0 (100), 1 and 1 (1001), 1 and 1 (1001 1), ..., 1 and 1 (1001 1101).
## b) **0xFF | a = 0xFF. (0xFF is the absorbent for OR)**
### **Resposta:**
### Assim como na alternativa anterior, 0xFF que equivale à '1111 1111' realizará 8 operações de | (or) com todos os índices do segundo operador (a). Nesse sentido, independente do valor de 'a', serão realizadas 8 operações de | (or) em que há pelo menos um operador '1', assim, o resultado será '1111 1111' independente do valor de 'a'.
## c) **0xFF ^ a = !a**
### **Resposta:**
### O operador ^ (exclusive or) realiza a operação entre dois operandos, e quando forem diferentes resulta em '1', quando forem iguais resulta em '0'. Nesse sentido, como 0xFF = '1111 1111', todas as operações onde o operador de a for '0' resultarão em '1' pois '1 ^ 0 = 1', e onde o operador de 'a' for '1' resultarão em '0' pois '1 ^ 1 = 0', logo, todos os valores de 'a' são invertidos, resultado em '!a'. Exemplo: '1111 1111 (0xFF) ^ 0110 1011 (a) = 1001 0100'.
## **d) 0 & a = 0. (0 is the absorbent for AND)**
## **e) 0 | a = a. (0 is the identity for OR)**
## **f) 0 ^ a = a. (0 is the identity for XOR)**
## **g) a ^ a = 0 (a is its own inverse under XOR)**
## **h) For any three two digit hexadecimal numbers a, b and c: If a ^ b = c then a ^ c = b.**

<hr>

# **5.** Write a program that counts the number of bits set in an integer. For example, the number 5 (decimal), which is 0000000000000101 (binary), has two bits set.

<hr>

# **6.** Write a program that takes a 32-bit integer (long int) and splits it into eight 4-bit values. (Be careful of the sign bit.)

<hr>

# **7.** Write a program that will take the bits in a number and shift them to the left end. For example, 01010110 (binary) would become 11110000 (binary).